/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 graydon hoare <graydon@fresco.org> 
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Berlin_Provider_hh
#define _Berlin_Provider_hh

#include <Berlin/ImplVar.hh>
#include <Prague/Sys/Thread.hh>
#include <stack>
#include <cassert>

namespace Berlin
{

  template <typename T>
  struct Initializer
  {
      static void initialize(T *) { }
  };

  //.a global pool for transient objects
  template <typename T, typename I = Initializer<T> >
  class Provider
  {
    public:
      static T *provide();
      static void adopt(T *t);
      static size_t size() { return pool.size(); }
    private:
      static void activate(T *);
      static void deactivate(T *);
      static std::stack<T *> pool;
      static Prague::Mutex mutex;
  };

  template <typename T, typename C>
  std::stack<T *> Provider<T, C>::pool;
  template <typename T, typename C>
  Prague::Mutex Provider<T, C>::mutex;
  
  template <typename T, typename I>
  inline void Provider<T, I>::activate(T *t)
  {
      Prague::Trace trace("Provider<T>::activate");
      PortableServer::POA_var poa = t->_default_POA();
      PortableServer::ObjectId *oid = poa->activate_object(t);
      t->_remove_ref();
      delete oid;
  }

  template <typename T, typename I>
  inline void Provider<T, I>::deactivate(T *t)
  {
      Prague::Trace trace("Provider<T>::deactivate");
      PortableServer::POA_var poa = t->_default_POA();
      PortableServer::ObjectId *oid = poa->servant_to_id(t);
      poa->deactivate_object(*oid);
      delete oid;
  }
  
  template <typename T, typename I>
  inline T *Provider<T, I>::provide()
  {
      Prague::Trace trace("Provider<T>::provide");
      T *t = 0;
      Prague::Guard<Prague::Mutex> guard(mutex);
      if (!pool.empty())
      {
	  t = pool.top();
	  pool.pop();
      }
      else
      {
	  t = new T();
	  activate(t);
      }
      t->my_active = true;
      I::initialize(t);
      return t;
  }
  
  template <typename T, typename I>
  inline void Provider<T, I>::adopt(T *t)
  {
      Prague::Trace trace("Provider<T>::adopt");
      assert(t->my_active);
      t->my_active = false;
      Prague::Guard<Prague::Mutex> guard(mutex);
      pool.push(t);
  }
  
  //.Lease_var is a smart pointer to be used in conjunction with
  //.Provider. It will give the wrapped object back to the provider
  //.in its destructor
  template <typename T, typename I = Initializer<T> >
  class Lease_var
  {
    public:
      explicit Lease_var(T *tt) : t(tt) {}
      Lease_var(Lease_var<T, I> &i) : t(i._retn()) {}
      ~Lease_var() { if (t) Provider<T, I>::adopt(t);}
      Lease_var<T> &operator = (Lease_var<T, I> &i) { if (&i != this) { if (t) Provider<T, I>::adopt(t); t = i._retn();} return *this;}  
      T &operator *() const { return *t;}
      T *operator->() const { return  t;}
      operator T *() const { return  t;}
      T *_retn() { T *tmp = t; t = 0; return tmp;}
    private:
      T *t;
  };

} // namespace

#endif
