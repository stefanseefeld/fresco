/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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

#include <Prague/Sys/FdSet.hh>
#include <Prague/Sys/Time.hh>
#include <Fresco/IO.hh>
#include "Berlin/ScreenImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Logger.hh"
#include "Berlin/ScreenManager.hh"
#include <Prague/Sys/Thread.hh>
#include <sstream>

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

ScreenManager::ScreenManager(Graphic_ptr g, EventManager *em,
			     DrawingKit_ptr d) :
    my_screen(g), 
    my_emanager(em), 
    my_drawing(DrawingKit::_duplicate(d)),
    my_thread(&ScreenManager::run_thread, this)
{ }

ScreenManager::~ScreenManager() { }
void ScreenManager::damage(Region_ptr r)
{
    Trace trace("ScreenManager::damage");
    Vertex l, u;
    r->bounds(l, u);
    Prague::Guard<Mutex> guard(my_mutex);
    my_theDamage->merge_union(r);
    Console::instance()->wakeup();
}

namespace Berlin
{

  inline clock_t myclock()
  {
      timeval tv;
      gettimeofday(&tv, 0);
      return tv.tv_sec * 1000000L + tv.tv_usec;
  }

  clock_t traverse_clock;
}

void ScreenManager::repair()
{
    Trace trace("ScreenManager::repair");
    Tracer::reset_clock();
    clock_t start = traverse_clock = myclock(), mid, mid2, mid3, end;
    {
	Guard<Mutex> guard(my_mutex);
	my_tmpDamage->copy(Region_var(my_theDamage->_this()));
	my_theDamage->clear();
    }

    // Place here for single-buffered Consoles:
    // The GGI/GL is singlebuffered, so this is what we do for now:-(
    my_emanager->restore(Region_var(my_tmpDamage->_this()));

    my_traversal->damage(Region_var(my_tmpDamage->_this()));
    my_traversal->init();
    my_drawing->start_traversal(Traversal_var(my_traversal->_this()));
    mid = myclock();
    try
    {
	my_screen->traverse(Traversal_var(my_traversal->_this()));
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    {
      std::cerr << "ScreenManager: warning: corrupt scene graph!"
		<< std::endl;
    }
    catch (const CORBA::BAD_PARAM &)
    {
	std::cerr << "ScreenManager: caught bad parameter" << std::endl;
    }
    my_drawing->finish_traversal();
    my_traversal->finish();
    mid2 = myclock();
  
    // Place here for doublebuffered Consoles:
    // _emanager->restore(Region_var(my_tmpDamage->_this()));
    my_drawing->flush();

    end = myclock();
    my_emanager->damage(Region_var(my_tmpDamage->_this()));
    {
	std::ostringstream buf;
	buf << "ScreenManager::repair: took " << (end-start)/1000. << " : ";
	buf << (mid-start)/1000. << " " << (mid2-mid)/1000. << " ";
	buf << (end-mid2)/1000. << " ";
	buf << " ("<<1000000./(end-start+1)<<")" << std::endl << std::ends;

	Logger::log(Logger::drawing) << buf.str();
	Logger::log(Logger::lifecycle) << "Provider<Transform> pool size is "
				       << Provider<TransformImpl>::size()
				       << std::endl;
	Logger::log(Logger::lifecycle) << "Provider<Region> pool size is "
				       << Provider<RegionImpl>::size()
				       << std::endl;
    }
}

void ScreenManager::start() { my_thread.start(); }

void *ScreenManager::run_thread(void *X)
{
    ScreenManager * const s = reinterpret_cast<ScreenManager*>(X);
    s->run();
}

void ScreenManager::run()
{
    my_theDamage = new RegionImpl;
    my_tmpDamage = new RegionImpl;
    my_traversal = new DrawTraversalImpl(my_screen,
					 Region::_nil(),
					 Transform::_nil(),
					 my_drawing);
    Prague::Time last;
    while (true)
    {
	bool haveDamage;
	{
	    Guard<Mutex> guard(my_mutex);
	    haveDamage = my_theDamage->defined();
	}
	if (haveDamage)
	{
	    Prague::Time current = Prague::Time::currentTime();
	    if (current > last + Prague::Time(33))
	    {
		repair();
		last = current;
	    }
	}
	my_emanager->next_event();
    }
}
