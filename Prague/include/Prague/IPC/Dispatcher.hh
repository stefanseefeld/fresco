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
#ifndef _Dispatcher_hh
#define _Dispatcher_hh

#include <Prague/Sys/Signal.hh>
#include <Prague/Sys/FdSet.hh>
#include <Prague/Sys/ThreadPool.hh>
#include <Prague/IPC/Agent.hh>
#include <vector>
#include <map>

namespace Prague
{

class Dispatcher
{
  typedef vector<Agent *> alist_t;
  typedef pair<Agent *, Agent::iomask_t> task;
  typedef vector<task> tlist_t;
  typedef map<int, Agent *> dictionary_t;

  struct Handler
  //. Handler is responsible for calling a specific method
  //. (determined by the mask) on the agent
  {
    Handler(Agent *a, Agent::iomask_t m) : agent(a), mask(m) {}
    void process();
    Agent *agent;
    Agent::iomask_t mask;
  };
  struct Acceptor
  {
    Handler *consume(const task &t) const { return new Handler(t.first, t.second);}
  };
  struct Cleaner { ~Cleaner();};
  friend struct Cleaner;
public:
  static Dispatcher *instance();
  void bind(int, Agent *, Agent::iomask_t);
  void release(int);
  void release(Agent *);
  void wait();
private:
  Dispatcher();
  virtual ~Dispatcher();
  static void *dispatch(void *);
  static Dispatcher *dispatcher;
  static Cleaner cleaner;
  static Mutex  singletonMutex;
  Signal::Notifier *notifier;
  Mutex         mutex;
  FdSet         rfds;
  FdSet         wfds;
  FdSet         xfds;
  alist_t       agents;
  dictionary_t  rchannel;
  dictionary_t  wchannel;
  dictionary_t  echannel;
  Thread::Queue<task> tasks;
  Acceptor      acceptor;
  ThreadPool<task, Acceptor, Handler> workers;
  Thread        server;
};

};

#endif /* _Dispatcher_hh */

