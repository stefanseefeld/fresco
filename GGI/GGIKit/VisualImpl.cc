/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org>
 * http://www.fresco.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 */

#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/SHM.hh>
#include <Fresco/config.hh>
#include <Fresco/Transform.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Event.hh>
#include "VisualImpl.hh"
#include <sys/ipc.h>

using namespace Prague;
using namespace Fresco;

GGIDrawableFactory * GGI::GGIKit::VisualImpl::_factory = 0;

GGI::GGIKit::VisualImpl::VisualImpl(PixelCoord w, PixelCoord h) :
  ControllerImpl(false),
  _width(w),
  _height(h)
{
    Trace trace("VisualImpl::VisualImpl");
    Console *console = Console::instance();
    if (!_factory) _factory = console->get_extension<GGIDrawableFactory>("GGIDrawableFactory");
    Fresco::Drawable::PixelFormat format = Console::instance()->drawable()->pixel_format();
    /*
     * the drawable plus some memory for the event queue
     */
    size_t size = w * h * format.size + 64*1024;
    _shm = SHM::allocate(size);

    _ggi = _factory->create_drawable(_shm, w, h, 3);
    _drawable = console->activate_drawable(_ggi);
    ggi_mode mode = _ggi->mode();
    char buffer[256];
    ggiSPrintMode(buffer, &mode);
    _mode = buffer;
}

GGI::GGIKit::VisualImpl::~VisualImpl()
{
    Trace trace("VisualImpl::~VisualImpl");
    SHM::deallocate(_shm);
}

char * GGI::GGIKit::VisualImpl::name()
{
    return CORBA::string_dup(_ggi->name().c_str());
}

char * GGI::GGIKit::VisualImpl::mode()
{
    return CORBA::string_dup(_mode.c_str());
}

void GGI::GGIKit::VisualImpl::request(Fresco::Graphic::Requisition &requisition)
{
    Trace trace("VisualImpl::request");
    requisition.x.defined = true;
    requisition.x.natural = requisition.x.maximum = requisition.x.minimum =
      _width / Console::instance()->drawable()->resolution(xaxis);
    requisition.x.align = 0.;
    requisition.y.defined = true;
    requisition.y.natural = requisition.y.maximum = requisition.y.minimum =
      _height / Console::instance()->drawable()->resolution(yaxis);
    requisition.y.align = 0.;
    requisition.z.defined = false;
}

void GGI::GGIKit::VisualImpl::draw(DrawTraversal_ptr traversal)
{
    Trace trace("VisualImpl::draw");
    DrawingKit_var drawing = traversal->drawing();
    drawing->copy_drawable(_drawable, 0, 0, _width, _height);
}

void GGI::GGIKit::VisualImpl::extension(const Allocation::Info &info, Region_ptr region)
{
    Trace trace("VisualImpl::extension");
    GraphicImpl::extension(info, region);
}

CORBA::Boolean GGI::GGIKit::VisualImpl::handle_positional(PickTraversal_ptr traversal,
                                                          const Fresco::Input::Event &event)
{
    Trace trace("VisualImpl::handle_positional");

    // Grab keyboard focus
    // FIXME: hardcoded device values == Evil
    if (!have_focus(0)) request_focus(Controller_var(_this()), 0);

    if (event[0].attr._d() == Input::button) handle_pointer_button(event);
    else if (event[0].attr._d() == Input::positional) move(traversal, event);
    else
    {
        std::cerr << "VisualImpl::handle_positional: "
                    << "Ignoring positional event" << std::endl;
    }
    return true;
}

CORBA::Boolean GGI::GGIKit::VisualImpl::handle_non_positional(const Fresco::Input::Event &event)
{
    Trace trace("VisualImpl::handle_non_positional");
    /*
     * FIXME !: we assume a lot about the (berlin) event layout here. Make that more flexible...
     */
    Input::Toggle toggle = event[0].attr.selection();
    ggi_event ggi;
    // giiEventSend will discard events without this field filled in.
    // I'm not sure if the actual value should depend on the source of the
    // event, or what (there's ggi.any.source for that, but that's filled in
    // as being a fake event by EventSend; this seems to be about which of the
    // input queues are handed the event.
    ggi.any.target = GII_EV_TARGET_ALL;
    // XGGI will crash (and understandably so!) if we don't fill this in
    ggi.any.size = sizeof(gii_key_event);
    if (toggle.actuation == Input::Toggle::press) ggi.any.type = evKeyPress;
    else if (toggle.actuation == Input::Toggle::hold) ggi.any.type = evKeyRepeat;
    else if (toggle.actuation == Input::Toggle::release) ggi.any.type = evKeyRelease; // not generated actually
    ggi.key.modifiers = 0;     // FIXME: wrong, should track state of modifier keys
    ggi.key.sym = toggle.number;
    // FIXME: the following is wildly incorrect:
    ggi.key.label = toggle.number;   // XGGI looks at this one
    // ggi.key.label = 'L; // useful for testing, so it's obvious if an app
                           // is reading this field
    ggi.key.button = 50;   // == scancode for 'M', ditto
    /*
     * FIXME !: the ggi_event structure is quite incomplete here. The real structure looks so:

    typedef struct {

    COMMON_DATA;

    uint32    modifiers;    current modifiers in effect
    uint32    sym;        meaning of key    (includes modifiers)
    uint32  label;        label on key
    uint32  button;        button number (== raw scancode)

    } gii_key_event;

     * and we need to figure out a way to fill the remaining members, i.e. reconstruct them from the sym
     * given that this is the only information we conserve in the berlin key event...
     */
    forward_event(ggi);
    return true;
}

void GGI::GGIKit::VisualImpl::move(Fresco::PickTraversal_ptr traversal,
                                   const Input::Event &event)
{
    Trace trace("VisualImpl::move");

    ggi_event ggi;
    ggi.any.target = GII_EV_TARGET_ALL;
    ggi.any.size = sizeof(gii_pmove_event);

    Input::Position position;
    if (-1 == get_position(event, position))
    {
        std::cerr << "VisualImpl::move error: non-positional event!"
                  << std::endl;
        return;
    }
    Transform_var trafo = traversal->current_transformation();
    trafo->inverse_transform_vertex(position);
    ggi.any.type = evPtrAbsolute;
    // This, really, is incorrect -- in (eg) the multihead case, we can't
    // assume that there's One True Resolution.
    // Perhaps people trying to run pixel-based apps across two displays at
    // different resolutions deserve what they get...
    const Fresco::Coord res_x = Console::instance()->drawable()->resolution(xaxis);
    ggi.pmove.x = static_cast<int>(position.x * res_x);
    const Fresco::Coord res_y = Console::instance()->drawable()->resolution(yaxis);
    ggi.pmove.y = static_cast<int>(position.y * res_y);
    const Fresco::Coord res_z = Console::instance()->drawable()->resolution(zaxis);
    ggi.pmove.z = static_cast<int>(position.z * res_z);
    ggi.pmove.wheel = 0; // I don't even know what this means.
    forward_event(ggi);
}

void GGI::GGIKit::VisualImpl::handle_pointer_button(const Input::Event &event)
{
    Trace trace("VisualImpl::handle_pointer_button");

    Input::Toggle toggle;
    // I stole this bit from Event.hh, get_position()
    Input::Device device = event[0].dev;
    for (size_t i = 0; i != event.length(); i++)
    {
        // Why do we check the devices like this?
        if (event[i].dev != device) continue;
        if (event[i].attr._d() == Input::button)
        {
            toggle = event[i].attr.selection();
            break;
        }
    }
    ggi_event ggi;
    ggi.any.target = GII_EV_TARGET_ALL;
    ggi.any.size = sizeof(ggi_pbutton_event);
    if (toggle.actuation == Input::Toggle::press)
        ggi.any.type = evPtrButtonPress;
    else if (toggle.actuation == Input::Toggle::release)
        ggi.any.type = evPtrButtonRelease;
    else
    {
        std::cerr << "VisualImpl::handle_pointer_button: "
                  << "unknown toggle -- neither press nor release!"
                  << std::endl;
        return;
    }
    ggi.pbutton.button = toggle.number;
    forward_event(ggi);
}

void GGI::GGIKit::VisualImpl::forward_event(const ggi_event &event)
{
    Trace trace("VisualImpl::forward_event");
    // giiEventSend(ggiJoinInputs(_ggi->visual(), 0), const_cast<ggi_event *>(&event));
    ggiEventSend(_ggi->visual(), const_cast<ggi_event *>(&event));
}
