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
#include "Berlin/ScreenImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/EventManager.hh"
#include "Berlin/Pointer.hh"
#include "Prague/Sys/FdSet.hh"
#include "Prague/Sys/Time.hh"
#include "Berlin/Logger.hh"

// static Mutex ggi_mutex;
// static ggi_event event;

using namespace Prague;

ScreenManager::ScreenManager(ScreenImpl *s, EventManager *em, DrawingKit_ptr d)
  : screen(s), emanager(em), drawing(DrawingKit::_duplicate(d)), drawable(GGI::drawable())
{}
ScreenManager::~ScreenManager() {}
void ScreenManager::damage(Region_ptr r)
{
  SectionLog section("ScreenManager::damage");
  MutexGuard guard(mutex);
  RegionImpl *region = new RegionImpl(r);
  region->_obj_is_ready(CORBA::BOA::getBOA());
  damages.push_back(region);
  Logger::log(Logger::drawing) << "ScreenManager::damage region " << *region << endl;
  drawable->wakeup();
}

void ScreenManager::repair()
{
  SectionLog section("ScreenManager::repair");
  mutex.lock();
  dlist_t tmp = damages;
  damages.erase(damages.begin(), damages.end());
  mutex.unlock();
  
  for (dlist_t::iterator i = tmp.begin(); i != tmp.end(); i++)
    {
      // Logger::log(Logger::drawing) << "repairing region " << **i << endl;
//       cout << "repairing region " << **i << endl;
      DrawTraversalImpl *traversal = new DrawTraversalImpl(Graphic_var(screen->_this()),
 							   Region_var((*i)->_this()),
 							   Transform_var(Transform::_nil()),
 							   drawing);
//       drawing->clear((*i)->lower.x, (*i)->lower.y, (*i)->upper.x, (*i)->upper.y);
      traversal->_obj_is_ready(CORBA::BOA::getBOA());
      screen->traverse(Traversal_var(traversal->_this()));
      traversal->_dispose();
      emanager->damage(Region_var((*i)->_this()));
      (*i)->_dispose();
    }
}

void ScreenManager::run()
{
  Prague::Time last;
  while (true)
    {
      mutex.lock();
      size_t damage = damages.size();
      mutex.unlock();
      if (damage > 0)
	{
	  repair();
	  Prague::Time current = Prague::Time::currentTime();
	  if (current > last + Prague::Time(33))
	    {
// 	      drawing->sync();
	      drawable->flush();
	      //	      GGIMesaSwapBuffers();
	      last = current;
	    }
	}
      nextEvent();
    }
}
