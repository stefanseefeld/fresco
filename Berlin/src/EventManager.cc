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


EventManager::EventManager(ScreenImpl *s)
  : screen(s)
{
  focus.push_back(new NonPositionalFocus(0, screen)); // keyboard
  focus.push_back(new PositionalFocus(1, screen));    // mouse
}

EventManager::~EventManager()
{
  for (vector<FocusImpl *>::iterator i = focus.begin(); i != focus.end(); i++) delete *i;
}

bool EventManager::requestFocus(Controller_ptr c, Input::Device d)
{
  if (d < focus.size()) return focus[d]->request(c);
  return false;
}

void EventManager::nextEvent()
{
  ggi_event event;
  if (!drawable->nextEvent(event)) return; // repair
  switch (event.any.type)
    {
    case evKeyPress:
      {
	Input::Toggle toggle;
	toggle.actuation = Input::Toggle::press;
	toggle.number = event.key.sym;
	Input::Event event; event.length(1);
	event[0].dev = 0;
	event[0].attr.kselection(toggle);

	focus[0]->dispatch(event);
	break;
      }
    case evKeyRepeat:
      {
	Input::Toggle toggle;
	toggle.actuation = Input::Toggle::hold;
	toggle.number = event.key.sym;
	Input::Event event; event.length(1);
	event[0].dev = 0;
	event[0].attr.kselection(toggle);

	focus[0]->dispatch(event);
	break;
      }
    case evPtrRelative:
    case evPtrAbsolute:
      {
	if (event.any.type == evPtrRelative)
	  {
	    if (ptrPositionX + event.pmove.x >= 0 &&
		ptrPositionX + event.pmove.x < screen->width()) ptrPositionX += event.pmove.x;
	    if (ptrPositionY + event.pmove.y >= 0 &&
		ptrPositionY + event.pmove.y < screen->height()) ptrPositionY += event.pmove.y;	  
	  }
	else
	  {
	    ptrPositionX = event.pmove.x;
	    ptrPositionY = event.pmove.y;
	  }
	// absence of break statement here is intentional
	
      }
    case evPtrButtonPress:
    case evPtrButtonRelease:
      {
// 	Event::Pointer ptrEvent;	  
// 	ptrEvent.location.x = ptrPositionX;
// 	ptrEvent.location.y = ptrPositionY;	  
// 	ptrEvent.location.z = 0; // time being we're using non-3d mice.
	
// 	ptrEvent.buttonNumber = event.pbutton.button;	  
// 	ptrEvent.whatHappened = 
// 	  event.any.type == evPtrRelative ? Event::hold :
// 	  event.any.type == evPtrAbsolute ? Event::hold :
// 	  event.any.type == evPtrButtonPress ? Event::press :
// 	  event.any.type == evPtrButtonRelease ? Event::release : Event::hold;
// 	pfocus->dispatch(ptrEvent);
	break;
      }
    }
}

void EventManager::damage(Region_ptr r)
{
  for (vector<FocusImpl *>::iterator i = focus.begin(); i != focus.end(); i++) (*i)->damage(r);
}

