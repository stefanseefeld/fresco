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
#include <Prague/Sys/FdSet.hh>
#include <Prague/Sys/Time.hh>
#include <Prague/Sys/Profiler.hh>
#include "Berlin/Logger.hh"
#include <Warsaw/IO.hh>

using namespace Prague;
using namespace Warsaw;

ScreenManager::ScreenManager(ScreenImpl *s, EventManager *em, DrawingKit_ptr d)
  : screen(s), emanager(em), drawing(DrawingKit::_duplicate(d)), drawable(Console::drawable())
{
}

ScreenManager::~ScreenManager() {}
void ScreenManager::damage(Region_ptr r)
{
  MutexGuard guard(mutex);
  theDamage->merge_union(r);
  Console::wakeup();
}

void ScreenManager::repair()
{
  Trace trace("ScreenManager::repair");
  //   Profiler prf("ScreenManager::repair");
  mutex.lock();
  tmpDamage->copy(Region_var(theDamage->_this()));
  theDamage->clear();
  mutex.unlock();
  emanager->restore(Region_var(tmpDamage->_this()));
  traversal->init();
  drawable->init();
  try { screen->traverse(Traversal_var(traversal->_this()));}
  catch (CORBA::OBJECT_NOT_EXIST &) { cerr << "ScreenManager: warning: corrupt scene graph !" << endl;}
  drawable->finish();
  traversal->finish();
  drawing->flush();
  {
    //     Profiler prf("Drawable::flush");
    Vertex l,u;
    tmpDamage->bounds(l,u);
    double xres = drawing->resolution(xaxis);
    double yres = drawing->resolution(yaxis);
    l.x *= xres;
    u.x *= xres;
    l.y *= yres;
    u.y *= yres;
    drawable->flush(l.x, l.y, u.x - l.x, u.y - l.y);
  }
  emanager->damage(Region_var(tmpDamage->_this()));
}

void ScreenManager::run()
{
  theDamage = new RegionImpl;
  tmpDamage = new RegionImpl;
  traversal = new DrawTraversalImpl(Graphic_var(screen->_this()),
				    Region_var(tmpDamage->_this()),
				    Transform::_nil(),
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
      emanager->next_event();
    }
}
