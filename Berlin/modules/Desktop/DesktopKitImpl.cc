/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
 * http://www.berlin-consortium.org
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

#include <Warsaw/config.hh>
#include <Warsaw/Server.hh>
#include <Warsaw/resolve.hh>
#include "Desktop/DesktopKitImpl.hh"
#include "Desktop/WindowImpl.hh"
#include "Desktop/Pulldown.hh"
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

DesktopKitImpl::DesktopKitImpl(KitFactory *f, const PropertySeq &p) : KitImpl(f, p) {}
DesktopKitImpl::~DesktopKitImpl()
{
  for (vector<WindowImpl *>::iterator i = windows.begin(); i != windows.end(); i++)
    {
      (*i)->unmap();
      (*i)->_dispose();
    }
}

void DesktopKitImpl::bind(ServerContext_ptr context)
{
  KitImpl::bind(context);
  CORBA::Object_var object = context->getSingleton(interface(Desktop));
  desktop = Desktop::_narrow(object);
  
  PropertySeq props;
  props.length(0);
  layout = resolve_kit<LayoutKit>(context, interface(LayoutKit), props);
  tool   = resolve_kit<ToolKit>(context, interface(ToolKit), props);
  widget = resolve_kit<WidgetKit>(context, interface(WidgetKit), props);
}

Desktop_ptr DesktopKitImpl::desk()
{
  return Desktop::_duplicate(desktop);
}


Window_ptr DesktopKitImpl::shell(Controller_ptr g)
{
  Trace trace("DesktopKitImpl::shell");
  WindowImpl *window = new WindowImpl;
  window->_obj_is_ready(_boa());

  Graphic::Requisition req;
  req.x.defined = true;
  req.x.minimum = 0.;
  req.x.natural = 0.;
  req.x.maximum = layout->fil();
  req.x.align = 0.;
  req.y.defined = true;
  req.y.minimum = 200.;
  req.y.natural = 200.;
  req.y.maximum = 200.;
  req.y.align = 0;
  Command_var move = window->move();
  ToolKit::FrameSpec spec;
  spec.bbrightness(0.5);
  Graphic_var tbframe = tool->frame(Graphic_var(layout->glueRequisition(req)), 10., spec, true);
  Graphic_var tbdragger = tool->dragger(tbframe, move);

  req.x.minimum = 200.;
  req.x.natural = 200.;
  req.x.maximum = 200.;
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var lresize = window->moveResize(1.0, 0.0, Window::left|Window::bottom);
  Graphic_var lframe = tool->frame(Graphic_var(layout->glueRequisition(req)), 10., spec, true);
  Graphic_var ldragger = tool->dragger(lframe, lresize);

  req.x.minimum = 0.;
  req.x.natural = 0.;
  req.x.maximum = layout->fil();
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var bresize = window->moveResize(0.0, 0.0, Window::bottom);
  Graphic_var bframe = tool->frame(Graphic_var(layout->glueRequisition(req)), 10., spec, true);
  Graphic_var bdragger = tool->dragger(bframe, bresize);

  req.x.minimum = 200.;
  req.x.natural = 200.;
  req.x.maximum = 200.;
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var rresize = window->moveResize(0.0, 0.0, Window::right|Window::bottom);
  Graphic_var rframe = tool->frame(Graphic_var(layout->glueRequisition(req)), 10., spec, true);
  Graphic_var rdragger = tool->dragger(rframe, rresize);

  Graphic_var vbox = layout->vbox();
  Graphic_var hbox = layout->hbox();
  hbox->append(ldragger);
  hbox->append(bdragger);
  hbox->append(rdragger);
  vbox->append(tbdragger);
  vbox->append(g);
  vbox->append(hbox);
  Graphic_var background = tool->rgb(vbox, 0.7, 0.7, 0.7);
  window->body(background);
  /*
   * FIXME: we need to take care to include the window control elements 
   *        into the control graph too...
   *        - stefan
   */
  window->appendController(g);
  window->insert(desktop, true);
  windows.push_back(window);
  desktop->appendController(Controller_var(window->_this()));
  return window->_this();
}

Window_ptr DesktopKitImpl::transient(Controller_ptr g)
{
  Trace trace("DesktopKitImpl::transient");
  WindowImpl *window = new WindowImpl;
  window->_obj_is_ready(_boa());
  ToolKit::FrameSpec spec;
  spec.bbrightness(0.5);

  Graphic::Requisition req;
  req.x.defined = true;
  req.x.minimum = 0.;
  req.x.natural = 0.;
  req.x.maximum = layout->fil();
  req.x.align = 0.;
  req.y.defined = true;
  req.y.minimum = 200.;
  req.y.natural = 200.;
  req.y.maximum = 200.;
  req.y.align = 0;
  Command_var move = window->move();
  Graphic_var tbframe = tool->frame(Graphic_var(layout->glueRequisition(req)), 10., spec, true);
  Graphic_var tbdragger = tool->dragger(tbframe, move);

  req.x.minimum = 200.;
  req.x.natural = 200.;
  req.x.maximum = 200.;
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var lresize = window->moveResize(1.0, 0.0, Window::left|Window::bottom);
  Graphic_var lframe = tool->frame(Graphic_var(layout->glueRequisition(req)), 10., spec, true);
  Graphic_var ldragger = tool->dragger(lframe, lresize);

  req.x.minimum = 0.;
  req.x.natural = 0.;
  req.x.maximum = layout->fil();
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var bresize = window->moveResize(0.0, 0.0, Window::bottom);
  Graphic_var bframe = tool->frame(Graphic_var(layout->glueRequisition(req)), 10., spec, true);
  Graphic_var bdragger = tool->dragger(bframe, bresize);

  req.x.minimum = 200.;
  req.x.natural = 200.;
  req.x.maximum = 200.;
  req.y.minimum = 40.;
  req.y.natural = 40.;
  req.y.maximum = 40.;
  Command_var rresize = window->moveResize(0.0, 0.0, Window::right|Window::bottom);
  Graphic_var rframe = tool->frame(Graphic_var(layout->glueRequisition(req)), 10., spec, true);
  Graphic_var rdragger = tool->dragger(rframe, rresize);

  Graphic_var vbox = layout->vbox();
  Graphic_var hbox = layout->hbox();
  hbox->append(ldragger);
  hbox->append(bdragger);
  hbox->append(rdragger);
  vbox->append(tbdragger);
  vbox->append(g);
  vbox->append(hbox);
  Graphic_var background = tool->rgb(vbox, 0.7, 0.7, 0.7);
  window->body(background);
  /*
   * FIXME: we need to take care to include the window control elements 
   *        into the control graph too...
   *        - stefan
   */
  window->appendController(g);
  window->insert(desktop, false);
  windows.push_back(window);
  desktop->appendController(Controller_var(window->_this()));
  return window->_this();
}

Window_ptr DesktopKitImpl::pulldown(Controller_ptr g)
{
  Trace trace("DesktopKitImpl::pulldown");
  Pulldown *menu = new Pulldown;
  menu->_obj_is_ready(_boa());
  ToolKit::FrameSpec out;
  out.bbrightness(0.5);

  Graphic_var outset = tool->frame(g, 20., out, true);
  menu->body(outset);
  menu->appendController(g);
  menu->insert(desktop, false);
  windows.push_back(menu);
  desktop->appendController(Controller_var(menu->_this()));
  return menu->_this();
}

extern "C" KitFactory *load()
{
  static string properties[] = {"implementation", "DesktopKitImpl"};
  return new KitFactoryImpl<DesktopKitImpl> (interface(DesktopKit), properties, 1);
}
