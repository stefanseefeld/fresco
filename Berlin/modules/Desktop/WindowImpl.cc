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

#include "Desktop/WindowImpl.hh"
#include "Berlin/Vertex.hh"
#include "Berlin/Logger.hh"

class Repositioner : public WindowImpl::Manipulator
{
public:
  Repositioner(DesktopImpl *desktop, DesktopImpl::Info &info) : WindowImpl::Manipulator(desktop, info) {}
  virtual void execute(const Message &message)
    {
      Vertex *position;
      if (message.payload >>= position)
	{
	  info.position += *position;
	  desktop->reposition(info, info.position);
	}
      else  cerr << "Repositioner::execute : wrong message type !" << endl;
    }
};

class Resizer : public WindowImpl::Manipulator
{
public:
  Resizer(DesktopImpl *desktop, DesktopImpl::Info &info) : WindowImpl::Manipulator(desktop, info) {}
  virtual void execute(const Message &message)
    {
      Vertex *size;
      if (message.payload >>= size);// window->desktop->resize(window->info, size);
      else cerr << "Resizer::execute : wrong message type !" << endl;
    }
};

class Relayerer : public WindowImpl::Manipulator
{
public:
  Relayerer(DesktopImpl *desktop, DesktopImpl::Info &info) : WindowImpl::Manipulator(desktop, info) {}
  virtual void execute(const Message &message)
    {
    }
};

WindowImpl::WindowImpl(DesktopImpl *d)
  : desktop(d), manipulators(2)
{
  manipulators[0] = new Repositioner(desktop, info);
  manipulators[0]->_obj_is_ready(_boa());
  manipulators[1] = new Resizer(desktop, info);
  manipulators[1]->_obj_is_ready(_boa());
}

WindowImpl::~WindowImpl()
{
  manipulators[0]->_dispose();
  manipulators[1]->_dispose();  
}

void WindowImpl::insert()
{
  Vertex position, size;
  position.x = position.y = position.z = 100;
  size.x = size.y = size.z = 0;
  info = desktop->insert(this, position, size, 0);
}

Command_ptr WindowImpl::reposition() { return manipulators[0]->_this();}
Command_ptr WindowImpl::resize() { return manipulators[1]->_this();}
Command_ptr WindowImpl::relayer() { return Command::_nil();}

CORBA::Boolean WindowImpl::handle(PickTraversal_ptr traversal, const CORBA::Any &any)
{
  SectionLog section(Logger::picking, "WindowImpl::handle");
  Graphic_var child = body();
  if (!CORBA::is_nil(child))
    {
      child->traverse(traversal);
      PickTraversal_var picked = traversal->picked();
      if (!CORBA::is_nil(picked))
	return Controller_var(picked->receiver())->handle(picked, any);
    }
  return false;
}
