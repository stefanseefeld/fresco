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
#ifndef _ThreadQueue_hh
#define _ThreadQueue_hh

#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/Time.hh>
#include <queue>

namespace Prague
{

template <class T>
class Thread::Queue : private std::queue<T>
{
   typedef std::queue<T> rep_type;
public:
   Queue(size_t capacity) : my_free(capacity) {}
   void push(const T &t)
   {
      my_free.wait();
      Prague::Guard<Mutex> guard(my_mutex);
      rep_type::push(t);
      my_tasks.post();
   }
   T top()
   {
      Prague::Guard<Mutex> guard(my_mutex);
      return rep_type::front();
   }
   void pop()
   {
      my_tasks.wait();
      Prague::Guard<Mutex> guard(my_mutex);
      rep_type::pop();
      my_free.post();
   }
   size_t size() { Prague::Guard<Mutex> guard(my_mutex); return rep_type::size();}
protected:
private:
   Semaphore my_tasks;
   Semaphore my_free;
   Mutex     my_mutex;
};

};

#endif
