/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#include <Fresco/config.hh>
#include <Fresco/Server.hh>
#include <Fresco/ClientContext.hh>
#include <Fresco/Trigger.hh>
#include <Fresco/resolve.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/Transform.hh>
#include <Fresco/Unicode.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/CommandImpl.hh>
#include <Berlin/RefCountVar.hh>
#include "DesktopKitImpl.hh"
#include "WindowImpl.hh"
#include "Pulldown.hh"
#include "Manipulator.hh"

using namespace Prague;
using namespace Fresco;

DesktopKitImpl::DesktopKitImpl(const std::string &id, const Fresco::Kit::PropertySeq &p)
  : KitImpl(id, p) {}
DesktopKitImpl::~DesktopKitImpl() {}
void DesktopKitImpl::bind(ServerContext_ptr context)
{
  Trace trace("DesktopKitImpl::bind");
  KitImpl::bind(context);
  CORBA::Object_var object = context->get_singleton("IDL:fresco.org/Fresco/Desktop:1.0");
  _desktop = Desktop::_narrow(object);
  _desktop->increment();
  Fresco::Kit::PropertySeq props;
  props.length(0);
  _layout  = resolve_kit<LayoutKit>(context, "IDL:fresco.org/Fresco/LayoutKit:1.0", props);
  _tool    = resolve_kit<ToolKit>(context, "IDL:fresco.org/Fresco/ToolKit:1.0", props);
  _widget  = resolve_kit<WidgetKit>(context, "IDL:fresco.org/Fresco/WidgetKit:1.0", props);
  _text    = resolve_kit<TextKit>(context, "IDL:fresco.org/Fresco/TextKit:1.0", props);
  _command = resolve_kit<CommandKit>(context, "IDL:fresco.org/Fresco/CommandKit:1.0", props);
  _image   = resolve_kit<ImageKit>(context, "IDL:fresco.org/Fresco/ImageKit:1.0", props);
  _figure  = resolve_kit<FigureKit>(context, "IDL:fresco.org/Fresco/FigureKit:1.0", props);

  ClientContext_var client = context->client();
  _exit = client->exit();
}

Desktop_ptr DesktopKitImpl::desk()
{
  return RefCount_var<Fresco::Desktop>::increment(_desktop);
}


Window_ptr DesktopKitImpl::shell(Controller_ptr g, Fresco::ClientContext_ptr n)
{
  Trace trace("DesktopKitImpl::shell");
  WindowImpl *window = new WindowImpl;
  activate(window);
  Window_var wptr = window->_this();

  RefCount_var<Graphic> vbox = _layout->vbox();
  RefCount_var<Graphic> hbox = _layout->hbox();
  Graphic_var down = _layout->vbox();

  Graphic::Requisition req;
  // GraphicImpl::init_requisiton(req) not needed as we init
  // everything manualy!
  req.preserve_aspect = false;

  req.x.defined = true;
  req.x.minimum = 200.;
  req.x.natural = 200.;
  req.x.maximum = 200.;
  req.x.align = 0.;

  req.y.defined = true;
  req.y.minimum = 0.;
  req.y.natural = 0.;
  req.y.maximum = _layout->fill();
  req.y.align = 0.;

  req.z.defined = false;

  Raster_var raster = _image->create("exit.png");
  Image_var exitgraphic = _figure->pixmap(raster);
  Trigger_var exitbutton = _widget->button(exitgraphic, _exit);
  raster = _image->create("shade.png");
  // Take out the shader for now, as it doesn't work yet.
  //Image_var shadergraphic = _figure->pixmap(raster);
  //Command_var shade = shader(wptr, down);
  //Trigger_var shaderbutton = _widget->button(shadergraphic, shade);

  RefCount_var<Graphic> tbbuttons = _layout->hbox();
  //  tbbuttons->append_graphic(shaderbutton);
  tbbuttons->append_graphic(RefCount_var<Graphic>(_layout->hspace(20.)));
  tbbuttons->append_graphic(exitbutton);

  Command_var mover = move(wptr);
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::outset);

  Unistring const * const title = n->application_title();
  RefCount_var<Graphic> titletext = _text->chunk(*title);
  delete title;

  RefCount_var<Graphic> titlebox = _layout->hbox_align_elements(0.);
  titlebox->append_graphic(RefCount_var<Graphic>(_layout->hfill()));
  titlebox->append_graphic(RefCount_var<Graphic>(_tool->rgb(titletext, 0., 0., 0.)));
  titlebox->append_graphic(RefCount_var<Graphic>(_layout->hfill()));
  titlebox->append_graphic(RefCount_var<Graphic>(_layout->margin(tbbuttons, 20.)));
  RefCount_var<Graphic> tbframe = _tool->frame(titlebox, 20., spec, true);

  RefCount_var<Graphic> tbdragger = _tool->dragger(tbframe, mover);

  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var lresize = move_resize(wptr, 1.0, 0.0, Window::left|Window::bottom);
  RefCount_var<Graphic> lframe = _tool->frame(RefCount_var<Graphic>(_layout->glue_requisition(req)), 20., spec, true);
  RefCount_var<Graphic> ldragger = _tool->dragger(lframe, lresize);

  req.x.minimum = 0.;
  req.x.natural = 0.;
  req.x.maximum = _layout->fill();
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var bresize = move_resize(wptr, 0.0, 0.0, Window::bottom);
  RefCount_var<Graphic> bframe = _tool->frame(RefCount_var<Graphic>(_layout->glue_requisition(req)), 20., spec, true);
  RefCount_var<Graphic> bdragger = _tool->dragger(bframe, bresize);

  req.x.minimum = 200.;
  req.x.natural = 200.;
  req.x.maximum = 200.;
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var rresize = move_resize(wptr, 0.0, 0.0, Window::right|Window::bottom);
  RefCount_var<Graphic> rframe = _tool->frame(RefCount_var<Graphic>(_layout->glue_requisition(req)), 20., spec, true);
  RefCount_var<Graphic> rdragger = _tool->dragger(rframe, rresize);

  hbox->append_graphic(ldragger);
  hbox->append_graphic(bdragger);
  hbox->append_graphic(rdragger);
  vbox->append_graphic(tbdragger);

  down->append_graphic(RefCount_var<Graphic>(_layout->align(g, 0., 0.)));
  down->append_graphic(hbox);
  vbox->append_graphic(down);
  //RefCount_var<Graphic> background = _tool->rgb(vbox, 0.827, 0.827, 0.866);
  RefCount_var<Graphic> background = _tool->rgb(vbox, 0.8, 0.8, 0.8);
  wptr->body(background);
  /*
   * FIXME: we need to take care to include the window control elements 
   *        into the control graph too...
   *        - stefan
   */
  wptr->append_controller(g);
  window->insert(_desktop);
  _desktop->append_controller(wptr);
  wptr->mapped(true);
  return wptr._retn();
}

Window_ptr DesktopKitImpl::transient(Controller_ptr g)
{
  Trace trace("DesktopKitImpl::transient");
  WindowImpl *window = new WindowImpl();
  activate(window);
  Window_var wptr = window->_this();
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::outset);

  Graphic::Requisition req;
  // GraphicImpl::init_requisiton(req) not needed as we init
  // everything manualy!
  req.preserve_aspect = false;

  req.x.defined = true;
  req.x.minimum = 0.;
  req.x.natural = 0.;
  req.x.maximum = _layout->fill();
  req.x.align = 0.;

  req.y.defined = true;
  req.y.minimum = 200.;
  req.y.natural = 200.;
  req.y.maximum = 200.;
  req.y.align = 0;

  req.z.defined = false;

  Command_var mover = move(wptr);
  RefCount_var<Graphic> tbframe = _tool->frame(RefCount_var<Graphic>(_layout->glue_requisition(req)), 20., spec, true);
  RefCount_var<Graphic> tbdragger = _tool->dragger(tbframe, mover);

  req.x.defined = true;
  req.x.minimum = 200.;
  req.x.natural = 200.;
  req.x.maximum = 200.;
  req.x.align = 0.;

  RefCount_var<Graphic> printgraphic = _layout->glue_requisition(req);
  Command_var print = _command->print(_tool->rgb(_layout->align(g, 0., 0.), 0.8, 0.8, 0.8));
  Trigger_var tbprint = _widget->button(printgraphic, print);

  req.x.minimum = 200.;
  req.x.natural = 200.;
  req.x.maximum = 200.;
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var lresize = move_resize(wptr, 1.0, 0.0, Window::left|Window::bottom);
  RefCount_var<Graphic> lframe = _tool->frame(RefCount_var<Graphic>(_layout->glue_requisition(req)), 20., spec, true);
  RefCount_var<Graphic> ldragger = _tool->dragger(lframe, lresize);

  req.x.minimum = 0.;
  req.x.natural = 0.;
  req.x.maximum = _layout->fill();
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var bresize = move_resize(wptr, 0.0, 0.0, Window::bottom);
  RefCount_var<Graphic> bframe = _tool->frame(RefCount_var<Graphic>(_layout->glue_requisition(req)), 20., spec, true);
  RefCount_var<Graphic> bdragger = _tool->dragger(bframe, bresize);

  req.x.minimum = 200.;
  req.x.natural = 200.;
  req.x.maximum = 200.;
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var rresize = move_resize(wptr, 0.0, 0.0, Window::right|Window::bottom);
  RefCount_var<Graphic> rframe = _tool->frame(RefCount_var<Graphic>(_layout->glue_requisition(req)), 20., spec, true);
  RefCount_var<Graphic> rdragger = _tool->dragger(rframe, rresize);

  RefCount_var<Graphic> vbox = _layout->vbox();
  RefCount_var<Graphic> background = _tool->rgb(vbox, 0.8, 0.8, 0.8);
  RefCount_var<Graphic> hbox1 = _layout->hbox();
  hbox1->append_graphic(tbprint);
  hbox1->append_graphic(tbdragger);
  RefCount_var<Graphic> hbox = _layout->hbox();
  hbox->append_graphic(ldragger);
  hbox->append_graphic(bdragger);
  hbox->append_graphic(rdragger);
  vbox->append_graphic(hbox1);
  vbox->append_graphic(RefCount_var<Graphic>(_layout->align(g, 0., 0.)));
  vbox->append_graphic(hbox);
  wptr->body(background);
  /*
   * FIXME: we need to take care to include the window control elements 
   *        into the control graph too...
   *        - stefan
   */
  wptr->append_controller(g);
  window->insert(_desktop);
  _desktop->append_controller(wptr);
  return wptr._retn();
}

Window_ptr DesktopKitImpl::pulldown(Controller_ptr g)
{
  Trace trace("DesktopKitImpl::pulldown");
  Pulldown *menu = new Pulldown();
  activate(menu);
  Window_var wptr = menu->_this();
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::outset);

  RefCount_var<Graphic> outset = _tool->frame(g, 20., spec, true);
  RefCount_var<Graphic> background = _tool->rgb(outset, 0.8, 0.8, 0.8);
  wptr->body(background);
  wptr->append_controller(g);
  menu->insert(_desktop);
  _desktop->append_controller(wptr);
  return wptr._retn();
}

Command_ptr DesktopKitImpl::move(Fresco::Window_ptr window)
{
  Manipulator *manipulator = new Mover(window);
  activate(manipulator);
  return manipulator->_this();
}

Command_ptr DesktopKitImpl::resize(Fresco::Window_ptr window)
{
  Manipulator *manipulator = new Resizer(window);
  activate(manipulator);
  return manipulator->_this();
}

Command_ptr DesktopKitImpl::move_resize(Fresco::Window_ptr window, Fresco::Alignment x, Fresco::Alignment y, CORBA::Short border)
{
  Manipulator *manipulator = new MoveResizer(window, _desktop, x, y, border);
  activate(manipulator);
  return manipulator->_this();
}

Command_ptr DesktopKitImpl::relayer(Fresco::Window_ptr window)
{
  Manipulator *manipulator = new Relayerer(window);
  activate(manipulator);
  return manipulator->_this();
}

Command_ptr DesktopKitImpl::map(Fresco::Window_ptr window, CORBA::Boolean flag)
{
  Manipulator *manipulator;
  if (flag) manipulator = new Mapper(window);
  else manipulator = new Unmapper(window);
  activate(manipulator);
  return manipulator->_this();
}

Command_ptr DesktopKitImpl::shader(Fresco::Window_ptr window, Fresco::Graphic_var to_shade)
{
  Manipulator *manipulator;
  if (CORBA::is_nil(to_shade)) {
    std::cout << "1" << std::endl;
  } else {
    if (CORBA::is_nil(to_shade->body())) {
      std::cout << "2" << std::endl;
    }
  }
  manipulator = new Shader(window, to_shade);
  activate(manipulator);
  return manipulator->_this();
}

extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "DesktopKitImpl"};
  return create_kit<DesktopKitImpl> ("IDL:fresco.org/Fresco/DesktopKit:1.0", properties, 2);
}
