/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org>
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
#include "Prague/Sys/Thread.hh"
#include <unistd.h>

using namespace Prague;

const void   *Thread::CANCELED = PTHREAD_CANCELED;
pthread_key_t Thread::self_key;
pthread_key_t Thread::id_key;
Mutex         Thread::id_mutex;
unsigned long Thread::counter = 0;
Thread       *Thread::main = 0;
Thread::Guard Thread::guard;

void id_deallocator(void *id) { delete reinterpret_cast<unsigned long *>(id); }

//Mutex::Mutex(type t)
//{
//  pthread_mutexattr_t attr;
//  pthread_mutexattr_init(&attr);
//  pthread_mutex_init(&impl, &attr);
//  pthread_mutexattr_destroy(&attr);
//}

Thread::Guard::Guard()
{
    pthread_key_create(&Thread::self_key, 0);
    pthread_key_create(&Thread::id_key, id_deallocator);
    pthread_t pt = pthread_self();
    Thread::main = new Thread(pt);
    pthread_setspecific(Thread::self_key, Thread::main);
    id_mutex.lock();
    pthread_setspecific(Thread::id_key, new unsigned long (counter++));
    id_mutex.unlock();
}

Thread::Guard::~Guard() { delete Thread::main; }

Thread::Thread(proc pp, void *a, priority_t prio) :
  my_proc(pp),
  my_arg(a),
  my_priority(prio),
  my_state(READY),
  my_detached(false)
{ }

Thread::Thread(pthread_t pt) :
  my_proc(0),
  my_arg(0),
  my_thread(pt),
  my_priority(NORMAL),
  my_state(RUNNING),
  my_detached(false)
{ }

Thread::~Thread()
{
    if (this != self() && state() != READY)
    {
        cancel();
        if (!my_detached) join(0);
    }
}

void Thread::start() throw (Exception)
{
    Prague::Guard<Mutex> guard(my_mutex);
    if ((my_state) != READY) throw Exception("thread already running");
    if (pthread_create(&my_thread, 0, &start, this) != 0) throw Exception("can't create thread");
    else my_state = RUNNING;
}

void Thread::join(void **status) throw (Exception)
{
    {
        Prague::Guard<Mutex> guard(my_mutex);
        if (my_state == READY) throw Exception("can't join ready thread");
        if (this == self()) throw Exception("can't join thread 'self'");
        if (my_detached) throw Exception("can't join detached thread");
    }
    void *s;
    pthread_join(my_thread, &s);
    Prague::Guard<Mutex> guard(my_mutex);
    my_state = READY;
    if (status) *status = s;
}

void Thread::cancel()
{
    if (this != self() && state() == RUNNING)
      pthread_cancel(my_thread);
}

void Thread::detach()
{
    my_mutex.lock();
    my_detached = true;
    my_mutex.unlock();
    pthread_detach(my_thread);
}

void Thread::exit(void *r)
{
    Thread *me = self();
    if (me)
    {
        Prague::Guard<Mutex> guard(me->my_mutex);
        me->my_state = TERMINATED;
    }
    pthread_exit(r);
}

void *Thread::start(void *X)
{
    Thread *thread = reinterpret_cast<Thread *>(X);
    pthread_setspecific(self_key, thread);
    id_mutex.lock();
    pthread_setspecific(id_key, new unsigned long (counter++));
    id_mutex.unlock();
    return thread->my_proc(thread->my_arg);
}

bool Thread::delay(const Time &time)
{
    Time t(time);
    return select(0, 0, 0, 0, &t) == 0;
}
