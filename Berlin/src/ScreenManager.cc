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

#include <Prague/Sys/FdSet.hh>
#include <Prague/Sys/Time.hh>
#include <Prague/Sys/Profiler.hh>
#include <Warsaw/config.hh>
#include <Warsaw/IO.hh>
#include "Berlin/ScreenImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Logger.hh"
#include "Berlin/ScreenManager.hh"
#include <strstream>

using namespace Prague;
using namespace Warsaw;

ScreenManager::ScreenManager(Graphic_ptr g, EventManager *em, DrawingKit_ptr d)
  : _screen(g), _emanager(em), _drawing(DrawingKit::_duplicate(d))
{
}

ScreenManager::~ScreenManager() {}
void ScreenManager::damage(Region_ptr r)
{
  Trace trace("ScreenManager::damage");
  Vertex l, u;
  r->bounds(l, u);
  Prague::Guard<Mutex> guard(_mutex);
  _theDamage->merge_union(r);
  Console::instance()->wakeup();
}

inline clock_t myclock()
{
  timeval tv;
  gettimeofday(&tv, 0);
  return tv.tv_sec * 1000000L + tv.tv_usec;
}

clock_t traverse_clock;

void ScreenManager::repair()
{
  Trace trace("ScreenManager::repair");
  Tracer::reset_clock();
  clock_t start = traverse_clock = myclock(), mid, mid2, mid3, end;
  // Profiler prf("ScreenManager::repair");
  _mutex.lock();
  _tmpDamage->copy(Region_var(_theDamage->_this()));
  _theDamage->clear();
  _mutex.unlock();

  // Place here for single-buffered Consoles:
  // The GGI/GL is singlebuffered, so this is what we do for now:-(
  _emanager->restore(Region_var(_tmpDamage->_this()));

  _traversal->damage(Region_var(_tmpDamage->_this()));
  _traversal->init();
  _drawing->start_traversal();
  mid = myclock();
  try
    {
      _screen->traverse(Traversal_var(_traversal->_this()));
    }
  catch (const CORBA::OBJECT_NOT_EXIST &)
    {
      std::cerr << "ScreenManager: warning: corrupt scene graph!" << std::endl;
    }
  catch (const CORBA::BAD_PARAM &)
    {
      std::cerr << "ScreenManager: caught bad parameter" << std::endl;
    }
  _drawing->finish_traversal();
  _traversal->finish();
  mid2 = myclock();
  
  // Place here for doublebuffered Consoles:
  // _emanager->restore(Region_var(_tmpDamage->_this()));
  _drawing->flush();

  end = myclock();
  _emanager->damage(Region_var(_tmpDamage->_this()));
  {
    std::ostrstream buf;
    buf << "ScreenManager::repair: took " << (end-start)/1000. << " : ";
    buf << (mid-start)/1000. << " " << (mid2-mid)/1000. << " ";
    buf << (end-mid2)/1000. << " ";
    buf << " ("<<1000000./(end-start+1)<<")" << std::endl << std::ends;

    Logger::log(Logger::drawing) << buf.str();
    Logger::log(Logger::lifecycle) << "Provider<Transform> pool size is " << Provider<TransformImpl>::size() << std::endl;
    Logger::log(Logger::lifecycle) << "Provider<Region> pool size is " << Provider<RegionImpl>::size() << std::endl;
  }
}

void ScreenManager::run()
{
  _theDamage = new RegionImpl;
  _tmpDamage = new RegionImpl;
  _traversal = new DrawTraversalImpl(_screen,
				     Region::_nil(),
				     Transform::_nil(),
				     _drawing);
  Prague::Time last;
  while (true)
    {
      _mutex.lock();
      bool haveDamage = _theDamage->defined();
      _mutex.unlock();
      if (haveDamage)
	{
	  Prague::Time current = Prague::Time::currentTime();
	  if (current > last + Prague::Time(33))
	    {
	      repair();
	      last = current;
	    }
	}
      _emanager->next_event();
    }
}
