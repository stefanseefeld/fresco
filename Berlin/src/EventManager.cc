/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
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

#include <Prague/Sys/Tracer.hh>
#include <Berlin/ScreenImpl.hh>
#include <Berlin/NonPositionalFocus.hh>
#include <Berlin/PositionalFocus.hh>
#include <Berlin/Vertex.hh>
#include <Berlin/EventManager.hh>

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

inline void EventManager::activate(FocusImpl *focus)
{
  Prague::Trace trace("EventManager::activate");
  PortableServer::POA_var poa = focus->_default_POA();
  PortableServer::ObjectId *oid = poa->activate_object(focus);
  focus->_remove_ref();
  delete oid;
  focus->activate_composite();
}

inline void EventManager::deactivate(FocusImpl *focus)
{
  Prague::Trace trace("EventManager::deactivate");
  PortableServer::POA_var poa = focus->_default_POA();
  PortableServer::ObjectId *oid = poa->servant_to_id(focus);
  poa->deactivate_object(*oid);
  delete oid;
}

EventManager::EventManager(Controller_ptr root, Region_ptr allocation)
{
  Trace trace("EventManager::EventManager");
  FocusImpl *keyboard = new NonPositionalFocus(0, root);
  FocusImpl *mouse = new PositionalFocus(1, root, allocation);
  activate(keyboard);
  activate(mouse);
  my_foci.push_back(keyboard);
  my_foci.push_back(mouse);
}

EventManager::~EventManager()
{
  for (flist_t::iterator i = my_foci.begin();
       i != my_foci.end(); ++i)
      deactivate(*i);
}

bool EventManager::request_focus(Controller_ptr c, Input::Device d)
{
    Trace trace("EventManager::request_focus");
    if (d < my_foci.size()) return my_foci[d]->request(c);
    return false;
}

void EventManager::next_event()
{
    Trace trace("EventManager::next_event");
    Input::Event *e = Console::instance()->next_event(); // take ownership!
    if (!e) return; // repair
    Input::Event_var event(e); // event owns memory now and will free it.
    // the first item determines which focus to send this event to
    try
    {
    if (event->length()) my_foci[event[0].dev]->dispatch(event);
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    {
    std::cerr << "EventManager: warning: corrupt scene graph!"
          << std::endl;
    }
    catch (const CORBA::BAD_PARAM &)
    {
    std::cerr << "EventManager: caught bad parameter." << std::endl;
    }
}

void EventManager::restore(Region_ptr r)
{
    for (flist_t::iterator i = my_foci.begin();
     i != my_foci.end();
     ++i)
    (*i)->restore(r);
}

void EventManager::damage(Region_ptr r)
{
    for (flist_t::iterator i = my_foci.begin();
     i != my_foci.end();
     ++i)
    (*i)->damage(r);
}

