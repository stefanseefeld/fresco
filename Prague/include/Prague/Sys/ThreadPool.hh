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
#ifndef _ThreadPool_hh
#define _ThreadPool_hh

#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/ThreadQueue.hh>
#include <vector>

namespace Prague
{

  template <class Task, class Acceptor, class Handler>
  class ThreadPool
  {
      typedef std::vector<Thread *> tlist_t;
    public:
      ThreadPool(Thread::Queue<Task> &t, Acceptor &a, size_t s) :
        _tasks(t), _acceptor(a), _threads(s, 0)
      {
          for (tlist_t::iterator i = _threads.begin();
               i != _threads.end();
               ++i)
              (*i) = new Thread(run, this);
      }
      ~ThreadPool()
      {
          for (tlist_t::iterator i = _threads.begin();
               i != _threads.end();
               ++i)
              delete *i;
      }
      void start()
      {
          for (tlist_t::iterator i = _threads.begin();
               i != _threads.end();
               ++i)
              (*i)->start();
      }
    private:
      static void *run(void *X)
      {
          ThreadPool *_this = reinterpret_cast<ThreadPool *>(X);
          while (1)
          {
              Task task = _this->_tasks.top();
              _this->_tasks.pop();
              Handler *handler = _this->_acceptor.consume(task);
              handler->process();
              delete handler;
              Thread::testcancel();
          }
          return 0;
      }

      Thread::Queue<Task> &_tasks;
      Acceptor            &_acceptor;
      tlist_t              _threads;
  };

} // namespace

#endif /* _ThreadPool_hh */
