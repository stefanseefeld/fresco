/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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

#include "Desktop/DesktopKitImpl.hh"
#include "Desktop/WindowImpl.hh"
#include "Desktop/Titlebar.hh"
#include "Desktop/Border.hh"
#include "Berlin/Logger.hh"
#include "Berlin/Plugin.hh"

DesktopKitImpl::DesktopKitImpl() {}
DesktopKitImpl::~DesktopKitImpl() {}

void DesktopKitImpl::bind(ServerContext_ptr sc)
{
  CloneableImpl::bind(sc);
  CORBA::Object_var object = context->getSingleton(interface(Desktop));
  desktop = Desktop::_narrow(object);
  
  lk = obtain(context, LayoutKit);
  wk = obtain(context, WidgetKit);
}

Desktop_ptr DesktopKitImpl::desk()
{
  return Desktop::_duplicate(desktop);
}


Window_ptr DesktopKitImpl::shell(Graphic_ptr g)
{
  SectionLog section(Logger::desktop, "DesktopKitImpl::shell");
  WindowImpl *window = new WindowImpl;
  window->_obj_is_ready(_boa());
  Color gray = {0.5, 0.5, 0.5, 1.0};

  Titlebar *tb = new Titlebar(gray);
  tb->_obj_is_ready(_boa());
  Command_var move = window->move();
  Graphic_var tbframe = wk->outset(Graphic_var(tb->_this()), gray, false);
  Graphic_var tbdragger = wk->dragger(tbframe, move);

  Corner *left = new Corner(gray);
  left->_obj_is_ready(_boa());
  Command_var lresize = window->moveResize(1.0, 0.0, Window::left|Window::bottom);
  Graphic_var lframe = wk->outset(Graphic_var(left->_this()), gray, false);
  Graphic_var ldragger = wk->dragger(lframe, lresize);

  Border *border = new Border(gray);
  border->_obj_is_ready(_boa());
  Command_var bresize = window->moveResize(0.0, 0.0, Window::bottom);
  Graphic_var bframe = wk->outset(Graphic_var(border->_this()), gray, false);
  Graphic_var bdragger = wk->dragger(bframe, bresize);

  Corner *right = new Corner(gray);
  right->_obj_is_ready(_boa());
  Command_var rresize = window->moveResize(0.0, 0.0, Window::right|Window::bottom);
  Graphic_var rframe = wk->outset(Graphic_var(right->_this()), gray, false);
  Graphic_var rdragger = wk->dragger(rframe, rresize);

  Graphic_var vbox = lk->vbox();
  Graphic_var hbox = lk->hbox();
  hbox->append(ldragger);
  hbox->append(bdragger);
  hbox->append(rdragger);
  vbox->append(tbdragger);
  vbox->append(g);
  vbox->append(hbox);
  window->body(vbox);
  window->insert(desktop, true);
  windows.push_back(window);
  desktop->appendController(Controller_var(window->_this()));
  return window->_this();
}

Window_ptr DesktopKitImpl::transient(Graphic_ptr g)
{
  SectionLog section(Logger::desktop, "DesktopKitImpl::shell");
  WindowImpl *window = new WindowImpl;
  window->_obj_is_ready(_boa());
  Color gray = {0.5, 0.5, 0.5, 1.0};

  Titlebar *tb = new Titlebar(gray);
  tb->_obj_is_ready(_boa());
  Command_var move = window->move();
  Graphic_var tbframe = wk->outset(Graphic_var(tb->_this()), gray, false);
  Graphic_var tbdragger = wk->dragger(tbframe, move);

  Corner *left = new Corner(gray);
  left->_obj_is_ready(_boa());
  Command_var lresize = window->moveResize(1.0, 0.0, Window::left|Window::bottom);
  Graphic_var lframe = wk->outset(Graphic_var(left->_this()), gray, false);
  Graphic_var ldragger = wk->dragger(lframe, lresize);

  Border *border = new Border(gray);
  border->_obj_is_ready(_boa());
  Command_var bresize = window->moveResize(0.0, 0.0, Window::bottom);
  Graphic_var bframe = wk->outset(Graphic_var(border->_this()), gray, false);
  Graphic_var bdragger = wk->dragger(bframe, bresize);

  Corner *right = new Corner(gray);
  right->_obj_is_ready(_boa());
  Command_var rresize = window->moveResize(0.0, 0.0, Window::right|Window::bottom);
  Graphic_var rframe = wk->outset(Graphic_var(right->_this()), gray, false);
  Graphic_var rdragger = wk->dragger(rframe, rresize);

  Graphic_var vbox = lk->vbox();
  Graphic_var hbox = lk->hbox();
  hbox->append(ldragger);
  hbox->append(bdragger);
  hbox->append(rdragger);
  vbox->append(tbdragger);
  vbox->append(g);
  vbox->append(hbox);
  window->body(vbox);
  window->insert(desktop, false);
  windows.push_back(window);
  desktop->appendController(Controller_var(window->_this()));
  return window->_this();
}

EXPORT_PLUGIN(DesktopKitImpl,interface(DesktopKit))
