/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org>
 * Copyright (C) 2003 Tobias Hunger <tobias@fresco.org>
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
#ifndef _Prague_Dispatcher_hh
#define _Prague_Dispatcher_hh

#include <Prague/Sys/FdSet.hh>
#include <Prague/Sys/ThreadPool.hh>
#include <Prague/IPC/Agent.hh>
#include <vector>
#include <map>
#include <stdexcept>
#include <unistd.h>

namespace Prague
{

  //. Dispatcher multiplexes i/o events to registered Agents. Together with
  //. the Agents, it implements the Reactor pattern.
  //. This implementation uses a thread pool for the actual callbacks.
  class Dispatcher
  {
    public:
      //. Dispatcher being a singleton, return the instance.
      static Dispatcher *instance();
      //. bind an Agent to events according to the provided filedescriptor fd,
      //. and the mask
      void bind(Agent *, int fd, Agent::iomask mask) throw(std::invalid_argument);
      //. release an Agent from channel fd, or the whole Agent, if fd is -1
      void release(Agent *, int fd = -1);
    private:
      struct task;
      typedef std::map<int, task *> repository_t;
      //. Handler is responsible for calling a specific method
      //. (determined by the mask) on the agent
      struct Handler
      {
          Handler(task *tt) : t(tt) { }
          void process() { dispatcher->process(t); }
          task *t;
      };
      friend struct Handler;
      struct Acceptor { Handler *consume(task *t) const { return new Handler(t); } };
      struct Cleaner { ~Cleaner(); };
      friend struct Cleaner;
      typedef Thread::Queue<task *> Queue;
      typedef ThreadPool<task *, Acceptor, Handler> Pool;

      Dispatcher();
      virtual ~Dispatcher();

      void release(Agent *, int, repository_t::iterator, repository_t::iterator);

      void wait();
      void notify() { char const *c = "c"; write(my_wakeup[1], c, 1); }
      static void *run(void *);
      void dispatch(task *);
      void process(task *);
      void deactivate(task *);
      void activate(task *);

      static Dispatcher *dispatcher;
      static Mutex  singletonMutex;
      static Cleaner cleaner;

      Mutex        my_mutex;
      FdSet        my_rfds;
      FdSet        my_wfds;
      FdSet        my_xfds;
      repository_t my_rchannel;
      repository_t my_wchannel;
      repository_t my_xchannel;
      int          my_wakeup[2];
      Queue        my_tasks;
      Acceptor     my_acceptor;
      Pool         my_workers;
      Thread       my_server;
  };

} // namespace

#endif
