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
#include "VisualImpl.hh"
#include <sys/ipc.h>

using namespace Prague;
using namespace Fresco;

GGIDrawableFactory *VisualImpl::_factory = 0;

VisualImpl::VisualImpl(PixelCoord w, PixelCoord h)
  : ControllerImpl(false), _width(w), _height(h)
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

VisualImpl::~VisualImpl()
{
  Trace trace("VisualImpl::~VisualImpl");
  SHM::deallocate(_shm);
}

char *VisualImpl::name()
{
  std::cout << _ggi->name() << std::endl;
  return CORBA::string_dup(_ggi->name().c_str());
}

char *VisualImpl::mode()
{
  return CORBA::string_dup(_mode.c_str());
}

void VisualImpl::request(Fresco::Graphic::Requisition &requisition)
{
  Trace trace("VisualImpl::request");
  requisition.x.defined = true;
  requisition.x.natural = requisition.x.maximum = requisition.x.minimum = _width * 10;// / _drawable->resolution(xaxis);
  requisition.x.align = 0.;
  requisition.y.defined = true;
  requisition.y.natural = requisition.y.maximum = requisition.y.minimum = _height * 10;// / _drawable->resolution(yaxis);
  requisition.y.align = 0.;
  requisition.z.defined = false;
}

void VisualImpl::draw(DrawTraversal_ptr traversal)
{
  Trace trace("VisualImpl::draw");
  DrawingKit_var drawing = traversal->drawing();
  drawing->copy_drawable(_drawable, 0, 0, _width, _height);
}

void VisualImpl::extension(const Allocation::Info &info, Region_ptr region)
{
  Trace trace("VisualImpl::extension");
  GraphicImpl::extension(info, region);
}

CORBA::Boolean VisualImpl::handle_positional(PickTraversal_ptr traversal, const Fresco::Input::Event &event)
{
  Trace trace("VisualImpl::handle_positional");
  ControllerImpl::handle_positional(traversal, event);
}

CORBA::Boolean VisualImpl::handle_non_positional(const Fresco::Input::Event &event)
{
  Trace trace("VisualImpl::handle_non_positional");
  std::cout << "VisualImpl::handle_non_positional" << std::endl;
  /*
   * FIXME !: we assume a lot about the (berlin) event layout here. Make that more flexible...
   */
  Input::Toggle toggle = event[0].attr.selection();
  ggi_event ggi;
  // giiEventSend will discard events without this field filled in
  // I'm not sure if the actual value should depend on the source of the
  // event, or what (there's ggi.any.source for that, but that's filled in
  // as being a fake event by EventSend; this seems to be about which of the
  // input queues are handed the event.
  ggi.any.target = GII_EV_TARGET_ALL;
  if (toggle.actuation == Input::Toggle::press) ggi.any.type = evKeyPress;
  else if (toggle.actuation == Input::Toggle::hold) ggi.any.type = evKeyRepeat;
  else if (toggle.actuation == Input::Toggle::release) ggi.any.type = evKeyRelease; // not generated actually
  ggi.key.sym = toggle.number;
  /*
   * FIXME !: the ggi_event structure is quite incomplete here. The real structure looks so:

   typedef struct {
   
   COMMON_DATA;
   
   uint32	modifiers;	current modifiers in effect 
   uint32	sym;		meaning of key	
   uint32  label;		label on key		
   uint32  button;		button number	
   
   } gii_key_event;

   * and we need to figure out a way to fill the remaining members, i.e. reconstruct them from the sym
   * given that this is the only information we conserve in the berlin key event...
   */
  forward_event(ggi);
}

void VisualImpl::forward_event(const ggi_event &event)
{
  Trace trace("VisualImpl::forward_event");
//  giiEventSend(ggiJoinInputs(_ggi->visual(), 0), const_cast<ggi_event *>(&event));
  ggiEventSend(_ggi->visual(), const_cast<ggi_event *>(&event));
}
