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
#include <Warsaw/Desktop.hh>
#include <Berlin/ControllerImpl.hh>
#include <vector>

class WindowImpl : implements(Window), public ControllerImpl
{
  class Manipulator : implements(Command)
  {
  public:
    virtual ~Manipulator() {}
    void bind(StageHandle_ptr h) { handle = StageHandle::_duplicate(h);}
    virtual void execute(const Message &) = 0;
  protected:
    StageHandle_var handle;
  };
  typedef vector<Manipulator *> mtable_t;
 public:
  WindowImpl();
  virtual ~WindowImpl();
  void insert(Desktop_ptr);
  Command_ptr move();
  Command_ptr resize();
  Command_ptr moveResize(Alignment, Alignment, CORBA::Short);
  Command_ptr relayer();

  virtual void pick(PickTraversal_ptr);
 private:
  StageHandle_var handle;
  mtable_t manipulators;
};

#endif /* _WindowImpl_hh */
