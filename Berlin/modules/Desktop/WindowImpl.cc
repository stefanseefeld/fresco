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

#include "Berlin/Vertex.hh"
#include "Berlin/Logger.hh"
#include "Desktop/WindowImpl.hh"

class Repositioner : public WindowImpl::Manipulator
{
public:
  virtual void execute(const Message &message)
    {
      if (CORBA::is_nil(handle)) return;
      Vertex *delta;
      if (message.payload >>= delta)
	{
 	  Vertex p = handle->position();
	  handle->position(p + *delta);
	}
      else  cerr << "Repositioner::execute : wrong message type !" << endl;
    }
};

class Resizer : public WindowImpl::Manipulator
{
public:
  virtual void execute(const Message &message)
    {
      if (CORBA::is_nil(handle)) return;
      Vertex *delta;
      if (message.payload >>= delta)
	{
 	  Vertex s = handle->size();
	  handle->size(s + *delta);
	}
      else cerr << "Resizer::execute : wrong message type !" << endl;
    }
};

class Relayerer : public WindowImpl::Manipulator
{
public:
  virtual void execute(const Message &message)
    {
      if (CORBA::is_nil(handle)) return;
      Stage::Index i;
      if (message.payload >>= i)
	{
	  handle->layer(i);
	}
      else cerr << "Relayerer::execute : wrong message type !" << endl;
    }
};

WindowImpl::WindowImpl()
  : ControllerImpl(true), manipulators(3)
{
  manipulators[0] = new Repositioner;
  manipulators[0]->_obj_is_ready(_boa());
  manipulators[1] = new Resizer;
  manipulators[1]->_obj_is_ready(_boa());
  manipulators[2] = new Relayerer;
  manipulators[2]->_obj_is_ready(_boa());
}

WindowImpl::~WindowImpl()
{
  manipulators[0]->_dispose();
  manipulators[1]->_dispose();  
  manipulators[2]->_dispose();  
}

void WindowImpl::insert(Desktop_ptr desktop)
{
  Vertex position, size;
  position.x = position.y = position.z = 100;
  size.x = size.y = size.z = 0;
  desktop->begin();
  handle = desktop->insert(Graphic_var(_this()), position, size, 0);
  desktop->end();
  for (mtable_t::iterator i = manipulators.begin(); i != manipulators.end(); i++)
    (*i)->bind(handle);
}

Command_ptr WindowImpl::reposition() { return manipulators[0]->_this();}
Command_ptr WindowImpl::resize() { return manipulators[1]->_this();}
Command_ptr WindowImpl::relayer() { return manipulators[2]->_this();}

void WindowImpl::pick(PickTraversal_ptr traversal)
{
  SectionLog section(Logger::picking, "WindowImpl::pick");
  traversal->enterController(Controller_var(_this()));
  MonoGraphic::traverse(traversal);
  traversal->leaveController();
}
