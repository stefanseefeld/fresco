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
using namespace Warsaw;

inline void deactivate(PortableServer::Servant servant)
{
  Prague::Trace trace("deactivate");
  PortableServer::POA_var poa = servant->_default_POA();
  PortableServer::ObjectId *oid = poa->servant_to_id(servant);
  poa->deactivate_object(*oid);
  delete oid;
}

EventManager::EventManager(ScreenImpl *s)
  : screen(s)
{
  Trace trace("EventManager::EventManager");
  drawable = Console::drawable();
  Impl_var<FocusImpl> f(new NonPositionalFocus(0, screen));
  focus.push_back(f._retn()); // keyboard
  f = new PositionalFocus(1, screen);
  focus.push_back(f._retn());    // mouse
}

EventManager::~EventManager()
{
  for (flist_t::iterator i = focus.begin(); i != focus.end(); i++) deactivate(*i);
}

bool EventManager::request_focus(Controller_ptr c, Input::Device d)
{
  Trace trace("EventManager::request_focus");
  if (d < focus.size()) return focus[d]->request(c);
  return false;
}

void EventManager::next_event()
{
  Trace trace("EventManager::next_event");
  Input::Event *e = Console::next_event();
  if (!e) return; // repair
  Input::Event_var event(e);
  /*
   * the first item determines which focus to send this event to
   */
  try { if (event->length()) focus[event[0].dev]->dispatch(event);}
  catch (CORBA::OBJECT_NOT_EXIST &) { cerr << "EventManager: warning: corrupt scene graph !" << endl;}
}

void EventManager::restore(Region_ptr r)
{
  for (flist_t::iterator i = focus.begin(); i != focus.end(); i++) (*i)->restore(r);
}

void EventManager::damage(Region_ptr r)
{
  for (flist_t::iterator i = focus.begin(); i != focus.end(); i++) (*i)->damage(r);
}

