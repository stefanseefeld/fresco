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
  RegionImpl *region = new RegionImpl;
  region->_obj_is_ready(CORBA::BOA::getBOA());
  region->copy(r);
  damages.push_back(region);
#ifdef DEBUG
  cout << "ScreenManager::damage region "
       << '(' << region->lower.x << ',' << region->lower.y << "),("
       << region->upper.x << ',' << region->upper.y << ')' << endl;
#endif
}

void ScreenManager::repair()
{
  for (DamageList::iterator i = damages.begin(); i != damages.end(); i++)
    {
      DrawTraversalImpl *traversal = new DrawTraversalImpl(drawing, *i);
      traversal->_obj_is_ready(CORBA::BOA::getBOA());
      screen->traverse(traversal);
      traversal->_dispose();
      (*i)->_dispose();
    }
  damages.erase(damages.begin(), damages.end());
}

void ScreenManager::nextEvent()
{
  ggi_event_mask mask = ggi_event_mask (emKeyboard | emPtrMove | emPtrButtonPress | emPtrButtonRelease);
  ggiEventPoll(visual, mask, 0);
  ggi_event event;
  ggiEventRead(visual, &event, mask);

  CORBA::Any a;

  switch (event.any.type) {
  case evKeyPress:
  case evKeyRepeat: {      
      Event::Key ke;
      ke.theChar = event.key.sym;
      a <<= ke;
      cerr << "k";
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
//       cerr << "m";
      a <<= pe;
      break;
  }
  }
  PickTraversalImpl *traversal = new PickTraversalImpl(a, screen->getRegion());
  traversal->_obj_is_ready(CORBA::BOA::getBOA());
  screen->traverse(traversal);
  traversal->_dispose();
}

void ScreenManager::run()
{
  while (true)
    {
	if (damages.size()) repair();
	nextEvent();
    }
}
