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

Thread::table Thread::threads;
Mutex         Thread::mutex;

Mutex::Mutex(type t)
{
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
//   pthread_mutexattr_setkind_np(&attr, t);
  pthread_mutex_init(this, &attr);
  pthread_mutexattr_destroy(&attr);
}

void *Thread::start(void *X)
{
  Thread *thread = reinterpret_cast<Thread *>(X);
  append(pthread_self(), thread);
  void *ret = thread->p(thread->arg);
  pthread_exit(0);
  remove(pthread_self());
  return ret;
}

bool Thread::delay(const Time &time)
{
// pthread_delay_np(&T);
  Time t(time);
  return select(0, 0, 0, 0, &t) == 0;
}

void Thread::append(pthread_t tid, Thread *thread)
{
  MutexGuard guard(mutex);
  threads.push_back(pair<pthread_t, Thread *>(tid, thread));
}

void Thread::remove(pthread_t tid)
{
  MutexGuard guard(mutex);
  for (table::iterator i = threads.begin(); i != threads.end(); i++)
    if ((*i).first == tid)
      {
	threads.erase(i);
	break;
      }
}

Thread *Thread::find(pthread_t tid)
{
  MutexGuard guard(mutex);
  for (table::iterator i = threads.begin(); i != threads.end(); i++)
    if ((*i).first == tid)
      return (*i).second;
  return 0;
}
