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

#include "Berlin/EventManager.hh"
#include "Berlin/ScreenImpl.hh"
#include "Berlin/NonPositionalFocus.hh"
#include "Berlin/PositionalFocus.hh"
#include "Berlin/Vertex.hh"
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

EventManager::EventManager(ScreenImpl *s)
  : screen(s), drawable(Console::drawable())
{
  Trace trace("EventManager::EventManager");
  focus.push_back(activate(new NonPositionalFocus(0, screen))); // keyboard
  focus.push_back(activate(new PositionalFocus(1, screen)));    // mouse
}

EventManager::~EventManager()
{
  for (flist_t::iterator i = focus.begin(); i != focus.end(); i++) deactivate(*i);
}

bool EventManager::requestFocus(Controller_ptr c, Input::Device d)
{
  if (d < focus.size()) return focus[d]->request(c);
  return false;
}

void EventManager::nextEvent()
{
  Trace trace("EventManager::nextEvent");
  Input::Event *e = Console::nextEvent();
  if (!e) return; // repair
  Input::Event_var event(e);
  /*
   * the first item determines which focus to send this event to
   */
  if (event->length()) focus[event[0].dev]->dispatch(event);
}

void EventManager::restore(Region_ptr r)
{
  for (flist_t::iterator i = focus.begin(); i != focus.end(); i++) (*i)->restore(r);
}

void EventManager::damage(Region_ptr r)
{
  for (flist_t::iterator i = focus.begin(); i != focus.end(); i++) (*i)->damage(r);
}

