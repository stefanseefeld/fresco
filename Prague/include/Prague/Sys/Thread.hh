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
/* $Id$ */
#ifndef _Thread_hh
#define _Thread_hh

#include <Prague/Sys/Time.hh>
#include <pthread.h>
#include <vector>
#include <pair.h>

class Mutex
{
public:
  class result
  {
  public:
    result(int e) : error(e) { };
    operator bool () const { return error == 0; };
    operator int () const { return error; };
  private:
    int error;
  };
  enum type { fast = PTHREAD_MUTEX_FAST_NP,
	      recursive = PTHREAD_MUTEX_RECURSIVE_NP};
  Mutex() { pthread_mutex_init(&mutex, 0);}
  Mutex(type t);
  ~Mutex() { pthread_mutex_destroy(&mutex);}
  result lock() { return pthread_mutex_lock(&mutex);}
  result unlock() { return pthread_mutex_unlock(&mutex);}
  result trylock() { return pthread_mutex_trylock(&mutex);}
protected:
  pthread_mutex_t mutex;
};

class MutexGuard
{
public:
  MutexGuard(Mutex &m) : mutex(m) { mutex.lock();}
  ~MutexGuard() { mutex.unlock();}
private:
  Mutex &mutex;
};

class Condition : public Mutex
{
public:
  Condition() { pthread_cond_init(&condition, 0);}
  ~Condition() { pthread_cond_destroy(&condition);}
  result broadcast() { return pthread_cond_broadcast(&condition);}
  result signal() { return pthread_cond_signal(&condition);}
  result wait() { return pthread_cond_wait(&condition, &mutex);}
protected:
  pthread_cond_t condition;
};

class Thread
{
  typedef pair<pthread_t, Thread *> TEntry;
  typedef vector<TEntry> TTable;
public:
  Thread() : running(false) {}
  virtual ~Thread() { cancel(); wait();}
  void start() { if (pthread_create(&thread, 0, &start, this) == 0) running = true;}
  void wait() { pthread_join(thread, 0);}
  void cancel() { if (running) pthread_cancel(thread);}
  void exit() { if (running) pthread_exit(0);}
  static bool delay(const Time &);
  static Thread *self();
protected:
  virtual void execute() = 0;
private:
  static void *start(void *);
  pthread_t thread;
  bool running;
  static TTable table;
  static Mutex globalMutex;
};

#endif /* _Thread_hh */
