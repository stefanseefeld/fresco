#ifndef _Lease_hh
#define _Lease_hh

/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 graydon hoare <graydon@pobox.com> 
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

#include <stack>
#include "Berlin/GraphicImpl.hh"
#include <Prague/Sys/Thread.hh>

// this header defines an interface to "leasable" impl_var's, such that
// you can borrow one just for a moment, use it, and return it when you're
// done. it also provides a simple cache object you can use elsewhere
// if you want more explicit control.

template <class T> class Cache {
protected:
  stack<T> objs;
  Prague::Mutex mutex;
public:
  inline bool fetch(T& ref) {
    Prague::MutexGuard guard(mutex);
    if (objs.empty()) return false;
    ref = objs.top(); // copy constructor on ref
    objs.pop();
    return true;
  }
  inline void stash(T &ref) {
    Prague::MutexGuard guard(mutex);
    objs.push(ref);
  }
};


template <class T> class Lease {
 public:
  class Provider {
  protected:
    Cache<T *> cache;    
  public:
    inline void adopt(T *impl) {
      cache.stash(impl);
    }
    
    inline void provide(Lease<T> &L) {
      T *impl;
      if (cache.fetch(impl)) {
	Lease newlease(impl,this,false);	
	L = newlease;
      } else {
	impl = new T();
	Lease newlease(impl,this,true);	
	L = newlease;
      }
    }
  };
  

  Lease(Lease<T> &i) : t(i.release()), p(i.p) {}
  explicit Lease(T *tt = 0, Provider<T> *pp  = 0, 
		 bool activate = true) : t(tt), p(pp) { 
    if ((t != 0) && activate) t->_obj_is_ready(CORBA::BOA::getBOA());
  }
  Lease &operator = (Lease<T> &i) { if (&i != this) { 
    p = i.p; if (t) p->adopt(t); t = i.release();} return *this;
  }

  ~Lease() { if (t) p->adopt(t);}
  T *get() const { return t;}
  T &operator *() const { return *t;}
  T *operator->() const { return  t;}
  operator T *() const { return  t;}
  T *release() { T *tmp = t; t = 0; return tmp;}
  void reset(T *tt = 0) { if (t) p->adopt(t); t = tt; t->_obj_is_ready(CORBA::BOA::getBOA());}
private:
  T *t;
  Provider<T> *p;
};

#endif
