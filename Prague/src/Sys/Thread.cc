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
#include "Prague/Sys/Thread.hh"

using namespace Prague;

Thread::TTable Thread::table;
Mutex          Thread::globalMutex;

Mutex::Mutex(type t)
{
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
//   pthread_mutexattr_setkind_np(&attr, t);
  pthread_mutex_init(&mutex, &attr);
  pthread_mutexattr_destroy(&attr);
}

void *Thread::start(void *X)
{
  pthread_t me = pthread_self();
  {
    MutexGuard guard(globalMutex);
    table.push_back(TEntry(me, reinterpret_cast<Thread *>(X)));
  }
  reinterpret_cast<Thread *>(X)->execute();
  pthread_exit(0);
  {
    MutexGuard guard(globalMutex);
    for (TTable::iterator i = table.begin(); i != table.end(); i++)
      if ((*i).first == me)
	{
	  table.erase(i);
	  break;
	}
  }
  return 0;
}

bool Thread::delay(const Time &time)
{
// pthread_delay_np(&T);
  Time t(time);
  return select(0, 0, 0, 0, &t) == 0;
}

Thread *Thread::self()
{
  MutexGuard guard(globalMutex);
  pthread_t me = pthread_self();
  for (TTable::iterator i = table.begin(); i != table.end(); i++)
    if ((*i).first == me)
      return (*i).second;
  return 0;
}
