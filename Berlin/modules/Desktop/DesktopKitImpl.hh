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
#ifndef _DesktopKitImpl_hh
#define _DesktopKitImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/DesktopKit.hh>
#include <Warsaw/LayoutKit.hh>
#include <Warsaw/WidgetKit.hh>
#include <Warsaw/Screen.hh>
#include <Berlin/CloneableImpl.hh>
#include <vector>

class WindowImpl;
class DesktopImpl;

class DesktopKitImpl : implements(DesktopKit), virtual public CloneableImpl
{
 public:
  DesktopKitImpl(Screen_ptr, LayoutKit_ptr, WidgetKit_ptr);
  virtual ~DesktopKitImpl();
  Window_ptr shell(Graphic_ptr);
  Window_ptr transient(Graphic_ptr);
 private:
  Screen_var screen;
  DesktopImpl *desktop;
  Stage_var  stage;
  LayoutKit_var lk;
  WidgetKit_var wk;
  vector<WindowImpl *> windows;
};

#endif /* _DesktopKitImpl_hh */
