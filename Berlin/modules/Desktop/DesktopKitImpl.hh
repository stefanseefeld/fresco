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
#ifndef _DesktopKitImpl_hh
#define _DesktopKitImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/DesktopKit.hh>
#include <Warsaw/LayoutKit.hh>
#include <Warsaw/ToolKit.hh>
#include <Warsaw/WidgetKit.hh>
#include <Warsaw/Desktop.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

class WindowImpl;
class DesktopImpl;

class DesktopKitImpl : public virtual POA_DesktopKit, public KitImpl
{
 public:
  DesktopKitImpl(KitFactory *, const PropertySeq &);
  virtual ~DesktopKitImpl();
  virtual void bind(ServerContext_ptr);
  virtual Desktop_ptr desk();
  virtual Window_ptr shell(Controller_ptr);
  virtual Window_ptr transient(Controller_ptr);
  virtual Window_ptr pulldown(Controller_ptr);
 private:
  Desktop_var   desktop;
  LayoutKit_var layout;
  ToolKit_var   tool;
  WidgetKit_var widget;
  vector<WindowImpl *> windows;
};

#endif /* _DesktopKitImpl_hh */
