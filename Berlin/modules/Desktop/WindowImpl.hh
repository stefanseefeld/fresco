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
#ifndef _WindowImpl_hh
#define _WindowImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Window.hh>
#include <Warsaw/Command.hh>
#include <Berlin/ControllerImpl.hh>
#include <Desktop/DesktopImpl.hh>
#include <vector>

class WindowImpl : implements(Window), public ControllerImpl
{
  class Manipulator : implements(Command)
    {
    public:
      Manipulator(DesktopImpl *d, DesktopImpl::Info &i) : desktop(d), info(i) {}
      virtual ~Manipulator() {}
      virtual void execute(const Message &) = 0;
    protected:
      DesktopImpl *desktop;
      DesktopImpl::Info &info;
    };
 public:
  WindowImpl(DesktopImpl *);
  virtual ~WindowImpl();
  void insert();
  Command_ptr reposition();
  Command_ptr resize();
  Command_ptr relayer();

  virtual void pick(PickTraversal_ptr);
 private:
  DesktopImpl *desktop;
  DesktopImpl::Info  info;
  vector<Manipulator *> manipulators;
};

#endif /* _WindowImpl_hh */
