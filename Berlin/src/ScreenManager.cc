/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include "Berlin/ScreenImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/EventManager.hh"
#include "Prague/Sys/FdSet.hh"
#include "Prague/Sys/Time.hh"
#include "Berlin/Logger.hh"
#include "Warsaw/Warsaw.hh"

using namespace Prague;

ScreenManager::ScreenManager(ScreenImpl *s, EventManager *em, DrawingKit_ptr d)
  : screen(s), emanager(em), drawing(DrawingKit::_duplicate(d)), drawable(GGI::drawable())
{
}

ScreenManager::~ScreenManager() {}
void ScreenManager::damage(Region_ptr r)
{
  MutexGuard guard(mutex);
  theDamage->mergeUnion(r);
  drawable->wakeup();
}

void ScreenManager::repair()
{
  mutex.lock();
  tmpDamage->copy(Region_var(theDamage->_this()));
  theDamage->clear();
  mutex.unlock();
  emanager->restore(Region_var(tmpDamage->_this()));
  traversal->init();
  screen->traverse(Traversal_var(traversal->_this()));
  traversal->finish();
  drawing->flush();
  drawable->flush();
  emanager->damage(Region_var(tmpDamage->_this()));
}

void ScreenManager::run()
{
  theDamage = new RegionImpl;
  tmpDamage = new RegionImpl;
  traversal = new DrawTraversalImpl(Graphic_var(screen->_this()),
				    Region_var(tmpDamage->_this()),
				    Transform_var(Transform::_nil()),
				    drawing);
  
  Prague::Time last;
  while (true)
    {
      mutex.lock();
      bool haveDamage = theDamage->defined();
      mutex.unlock();
      if (haveDamage)
	{
	  Prague::Time current = Prague::Time::currentTime();
	  if (current > last + Prague::Time(33))
	    {
	      repair();
	      last = current;
	    }
	}
      nextEvent();
    }
}
