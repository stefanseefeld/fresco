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
#include "Berlin/ScreenImpl.hh"
#include "Berlin/Logger.hh"
#include "Berlin/NonPositionalFocus.hh"
#include "Berlin/PositionalFocus.hh"
#include "Berlin/Logger.hh"


EventManager::EventManager(ScreenImpl *s)
  : screen(s)
{
  focus.push_back(new NonPositionalFocus(0, screen)); // keyboard
  focus.push_back(new PositionalFocus(1, screen));    // mouse
  focus[0]->_obj_is_ready(CORBA::BOA::getBOA());
  focus[1]->_obj_is_ready(CORBA::BOA::getBOA());
}

EventManager::~EventManager()
{
  for (vector<FocusImpl *>::iterator i = focus.begin(); i != focus.end(); i++) (*i)->_dispose();
}

bool EventManager::requestFocus(Controller_ptr c, Input::Device d)
{
  if (d < focus.size()) return focus[d]->request(c);
  return false;
}

void EventManager::nextEvent()
{
  SectionLog section("EventManager::nextEvent");
  ggi_event e;
  if (!GGI::drawable()->nextEvent(e)) return; // repair
  Input::Event event;
  switch (e.any.type)
    {
    case evKeyPress:
      {
	Input::Toggle toggle;
	toggle.actuation = Input::Toggle::press;
	toggle.number = e.key.sym;
	event.length(1);
	event[0].dev = 0;
	event[0].attr.kselection(toggle);
	break;
      }
    case evKeyRepeat:
      {
	Input::Toggle toggle;
	toggle.actuation = Input::Toggle::hold;
	toggle.number = e.key.sym;
	event.length(1);
	event[0].dev = 0;
	event[0].attr.kselection(toggle);
	break;
      }
    case evPtrRelative:
    case evPtrAbsolute:
      {
	if (e.any.type == evPtrRelative)
	  {
	    if (ptrPositionX + e.pmove.x >= 0 &&
		ptrPositionX + e.pmove.x < screen->width()) ptrPositionX += e.pmove.x;
	    if (ptrPositionY + e.pmove.y >= 0 &&
		ptrPositionY + e.pmove.y < screen->height()) ptrPositionY += e.pmove.y;	  
	  }
	else
	  {
	    ptrPositionX = e.pmove.x;
	    ptrPositionY = e.pmove.y;
	  }
	Input::Position position;
	position.x = ptrPositionX;
	position.y = ptrPositionY;
	position.z = 0; // time being we're using non-3d mice.
	event.length(1);
	event[0].dev = 1;
	event[0].attr.location(position);
	break;
      }
    case evPtrButtonPress:
    case evPtrButtonRelease:
      {
	Input::Position position;
	position.x = ptrPositionX;
	position.y = ptrPositionY;
	position.z = 0; // time being we're using non-3d mice.
	Input::Toggle toggle;
	if (e.any.type == evPtrButtonPress)
	  toggle.actuation = Input::Toggle::press;
	else
	  toggle.actuation = Input::Toggle::release;
 	toggle.number = e.pbutton.button;	  
	event.length(2);
	event[0].dev = 1;
	event[0].attr.location(position);	
	event[1].dev = 1;
	event[1].attr.kselection(toggle);
	break;
      }
    }
  /*
   * the first item determines which focus to send this event to
   */
  if (event.length()) focus[event[0].dev]->dispatch(event);
}

void EventManager::damage(Region_ptr r)
{
  for (vector<FocusImpl *>::iterator i = focus.begin(); i != focus.end(); i++) (*i)->damage(r);
}

