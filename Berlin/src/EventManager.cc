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

#include "Berlin/EventManager.hh"
#include "Berlin/PickTraversalImpl.hh"
#include "Berlin/ScreenImpl.hh"
#include "Berlin/Logger.hh"

EventManager::EventManager(ScreenImpl *s)
  : screen(s)
{
  focus = new FocusImpl;
  focus->_obj_is_ready(CORBA::BOA::getBOA());
}

EventManager::~EventManager()
{
  focus->_dispose();
}

void EventManager::requestFocus(Controller_ptr c)
{
  SectionLog section(Logger::focus, "EventManager::requestFocus(Controller_ptr)");
  c->receiveFocus(Focus_var(focus->_this()));
}

void EventManager::requestFocus(PickTraversalImpl *t, Controller_ptr c)
{
  SectionLog section(Logger::focus, "EventManager::requestFocus(PickTraversalImpl *, Controller_ptr)");
  c->receiveFocus(Focus_var(focus->_this()));
}

void EventManager::dispatchInput(const Event::Pointer &pointer)
{
  SectionLog section(Logger::main, "EventManager::dispatchInput(Pointer)");
  /*
   * try to find a potential receiver for the event
   */
  PickTraversalImpl *traversal = new PickTraversalImpl(Graphic_var(screen->_this()),
						       Region_var(screen->getRegion()),
						       pointer, this);
  traversal->_obj_is_ready(CORBA::BOA::getBOA());
  screen->traverse(Traversal_var(traversal->_this()));
  /*
   * has the traversal been picked ? then handle the event
   */
  PickTraversal_var picked = traversal->picked();
  if (!CORBA::is_nil(picked))
    {
      SectionLog section(Logger::main, "picked controller non zero");
      CORBA::Any any;
      any <<= pointer;
      Controller_var(picked->receiver())->handle(picked, any);
    }
  traversal->_dispose();
}

void EventManager::dispatchInput(const Event::Key &)
{
  SectionLog section(Logger::main, "EventManager::dispatchInput(Key)");
}

