/*+P
 * This file is part of OffiX,
 * a C++ API for the X Window System and Unix
 * Copyright (C) 1995-98  Stefan Seefeld
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
 -P*/
static char *rcsid = "$Id$";
#include "Prague/Sys/Thread.hh"

Thread::TTable Thread::table;
Mutex          Thread::mutex;

Mutex::Mutex(type t)
{
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_setkind_np(&attr, t);
  pthread_mutex_init(&mutex, &attr);
  pthread_mutexattr_destroy(&attr);
}

void *Thread::start(void *X)
{
  mutex.lock();
  pthread_t me = pthread_self();
  table.push_back(TEntry(me, reinterpret_cast<Thread *>(X)));
  mutex.unlock();
  reinterpret_cast<Thread *>(X)->execute();
  pthread_exit(0);
  mutex.lock();
  for (TTable::iterator i = table.begin(); i != table.end(); i++)
    if ((*i).first == me)
      {
	table.erase(i);
	break;
      }
  mutex.unlock();
  return 0;
}

Thread *Thread::self()
{
  MutexLocker ML(mutex);
  pthread_t me = pthread_self();
  for (TTable::iterator i = table.begin(); i != table.end(); i++)
    if ((*i).first == me)
      return (*i).second;
  return 0;
}
