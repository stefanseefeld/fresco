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

EventManager::EventManager(ScreenImpl *s)
  : screen(s),
    focus(new FocusImpl(screen))
{}

EventManager::~EventManager() {}
void EventManager::requestFocus(Controller_ptr c) { focus->request(c);}

void EventManager::nextEvent()
{
  ggi_event event;
  if (!drawable->nextEvent(event)) return; // repair
  switch (event.any.type)
    {
    case evKeyPress:
    case evKeyRepeat:
      {      
	Event::Key key;
	key.theChar = event.key.sym;
	dispatch(key);
	break;
      }
    case evPtrRelative:
    case evPtrAbsolute:
      {
	if (event.any.type == evPtrRelative) {
	  if (ptrPositionX + event.pmove.x >= 0 &&
	      ptrPositionX + event.pmove.x < screen->width()) ptrPositionX += event.pmove.x;
	  if (ptrPositionY + event.pmove.y >= 0 &&
	      ptrPositionY + event.pmove.y < screen->height()) ptrPositionY += event.pmove.y;	  
	} else {
	  ptrPositionX = event.pmove.x;
	  ptrPositionY = event.pmove.y;
	}
	// absence of break statement here is intentional
      }
    case evPtrButtonPress:
    case evPtrButtonRelease:
      {
	Event::Pointer ptrEvent;	  
	ptrEvent.location.x = ptrPositionX;
	ptrEvent.location.y = ptrPositionY;	  
	ptrEvent.location.z = 0; // time being we're using non-3d mice.
	
	ptrEvent.buttonNumber = event.pbutton.button;	  
	ptrEvent.whatHappened = 
	  event.any.type == evPtrRelative ? Event::hold :
	  event.any.type == evPtrAbsolute ? Event::hold :
	  event.any.type == evPtrButtonPress ? Event::press :
	  event.any.type == evPtrButtonRelease ? Event::release : Event::hold;
	dispatch(ptrEvent);
	break;
      }
    }
}

void EventManager::damage(Region_ptr r) { focus->damage(r);}
void EventManager::dispatch(const Event::Pointer &pointer) { focus->dispatch(pointer);}
void EventManager::dispatch(const Event::Key &) {}

