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

#include "Berlin/ScreenManager.hh"
#include "Berlin/DrawTraversalImpl.hh"
#include "Berlin/PickTraversalImpl.hh"
#include "Berlin/ScreenImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Drawing/openGL/GLDrawingKit.hh"
#include "Drawing/openGL/Pointer.hh"


static Mutex ggi_mutex;
static ggi_event event;

ScreenManager::ScreenManager(ScreenImpl *s, GLDrawingKit *d)
  : screen(s), drawing(d), visual(drawing->getVisual())
{
  pointer = new Pointer(visual);
}

ScreenManager::~ScreenManager()
{
  delete pointer;
}

void ScreenManager::damage(Region_ptr r)
{
  MutexGuard guard(damageMutex);
    RegionImpl *region = new RegionImpl;
    region->_obj_is_ready(CORBA::BOA::getBOA());
    region->copy(r);
    damages.push_back(region);
    //#ifdef DEBUG
    cout << "ScreenManager::damage region "
     	 << '(' << region->lower.x << ',' << region->lower.y << "),("
     	 << region->upper.x << ',' << region->upper.y << ')' << endl;
    //#endif

    // this injects a damage notice into the event queue, waking up
    // the sleeping event thread.

    // sadly it appears that GGI's event queue is not threadsafe, so
    // we must use a poll loop with a timeout. this is not totally
    // awful, it just means we are zooming through a short loop once
    // every 20000 microseconds. it doesn't take too much CPU time on my
    // machine, and if it takes too much on yours, hey, go fix GGI. 

    //     ggi_mutex.lock();
    //     ggi_event *damageEvent = new ggi_event;
    //     gettimeofday(&(damageEvent->any.time), NULL);
    //     damageEvent->any.type = evCommand;
    //     ggiEventSend (visual, damageEvent);    
    //     ggi_mutex.unlock();
}

void ScreenManager::repair()
{
    damageMutex.lock();
    DamageList tmp = damages;
    damages.erase(damages.begin(), damages.end());
    damageMutex.unlock();

    glClearColor(0,0,0,0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    for (DamageList::iterator i = tmp.begin(); i != tmp.end(); i++)
	{
	    DrawTraversalImpl *traversal = new DrawTraversalImpl(drawing, (*i)->_this());
	    traversal->_obj_is_ready(CORBA::BOA::getBOA());
	    screen->traverse(traversal->_this());
	    traversal->_dispose();
	    (*i)->_dispose();
	}
    
    glFinish();
//     ggiSetGCForeground(visual,255);
//     GGIMesaSwapBuffers();
}

void ScreenManager::nextEvent()
{

    ggi_event_mask mask = ggi_event_mask (emCommand | emKeyboard | emPtrMove | emPtrButtonPress | emPtrButtonRelease);
    timeval t;

    t.tv_sec = 0;
    t.tv_usec = 20000; 
    
    if (ggiEventPoll(visual, mask, &t)) {
	ggiEventRead(visual, &event, mask);
    } else {
      return;
    }

  CORBA::Any a;

  // we are being woken up by the damage subsystem
  if (event.any.origin == GII_EV_ORIGIN_SENDEVENT) return;

  // we can process this, it's a legitimate event.
  switch (event.any.type) {
  case evKeyPress:
  case evKeyRepeat: {      
      Event::Key ke;
      ke.theChar = event.key.sym;
      a <<= ke;
      break;
  }
  
  case evPtrAbsolute: {
      ptrPositionX = event.pmove.x;
      ptrPositionY = event.pmove.y;
      pointer->move(ptrPositionX, ptrPositionY);
      // absence of break statement here is intentional
  }
  case evPtrButtonPress:
  case evPtrButtonRelease: {
      Event::Pointer pe;	  
      pe.location.x = ptrPositionX;
      pe.location.y = ptrPositionY;	  
      pe.location.z = 0; // time being we're using non-3d mice.
      pe.buttonNumber = event.pbutton.button;	  
      pe.whatHappened = 
	  event.any.type == evPtrAbsolute ? Event::hold :
	  event.any.type == evPtrButtonPress ? Event::press :
	  event.any.type == evPtrButtonRelease ? Event::release : Event::hold;
      a <<= pe;
      break;
  }
  }

    PickTraversalImpl *traversal = new PickTraversalImpl(a, screen->getRegion());
    traversal->_obj_is_ready(CORBA::BOA::getBOA());
    screen->traverse(traversal->_this());
    traversal->_dispose();

}

void ScreenManager::run()
{
  while (true)
    {
      damageMutex.lock();
      int amountOfDamage = damages.size();
      damageMutex.unlock();
      if (amountOfDamage > 0)
	{
	  repair();
	} 
      nextEvent();
    }
}
