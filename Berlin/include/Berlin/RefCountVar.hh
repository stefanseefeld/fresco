/*$Id$
 *
 * This source file is a part of the Fresco Project.
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
#ifndef _Berlin_RefCountVar_hh
#define _Berlin_RefCountVar_hh

#include <Fresco/config.hh>
#include <Fresco/Types.hh>

//.RefCount_var is a smart pointer to be used in conjunction with
//.RefCountBase objects. The smart pointer allows you to manage reference
//.counting more simply, by automating the increment() and decrement() calls
//.for various operations.
//.
//.When a raw pointer type is given to the smart pointer, either in the
//.constructor or the assignment operator, then ownership of the reference is
//.transferred to the smart pointer. Programmatically this is accomplished by
//.not increasing the reference count. This is in contrast to passing another
//.smart pointer, in which case the reference count will be incremented,
//.to the objectrepresenting a duplicated reference to the object.
//.
//.Whenever the smart pointer loses or removes its reference to an object,
//.either through destruction of the smart pointer or an assignment operator,
//.it will automatically decrement() the object. The exception to this is the
//._retn() method which forwards the _retn() call to the object then removes
//.its local reference without decrementing.
//.
//.@see RefCountBaseImpl
template <typename T>
class RefCount_var
{
  //.Brings the _ptr_type of T into this scope.
  typedef typename T::_ptr_type T_ptr;

  //.Brings the _var_type of T into this scope.
  typedef typename T::_var_type T_var;

public:

  //.Constructor that takes a pointer to T. No reference increment is done in
  //.this constructor, so the reference to the object represented by the
  //.pointer is transferred to the smart pointer.
  RefCount_var(T_ptr tt = T::_nil()) : t(tt) {}

  //.Constructor that takes another RefCount_var to T. In this case a
  //.reference increment *is* done.
  RefCount_var(const RefCount_var<T> &o)
    : t(o.t)
  {
    if (!CORBA::is_nil(t))
      try {t->increment();}
      catch (const CORBA::OBJECT_NOT_EXIST &) { t = T::_nil();}
      catch (const CORBA::COMM_FAILURE &) { t = T::_nil();}
  }

  //.Destructor - decrements reference count to object.
  ~RefCount_var()
  {
    if (!CORBA::is_nil(t))
      try {t->decrement();}
      catch (const CORBA::OBJECT_NOT_EXIST &) {}
      catch (const CORBA::COMM_FAILURE &) {}
  }

  //.Assignment operator. Copies the given smart pointer into this one,
  //.decreasing the reference count on the current object and increasing the
  //.reference count on the new one. The returned reference is to this smart
  //.pointer.
  RefCount_var<T> &operator = (const RefCount_var<T> &o)
  {
    if (&o != this)
      {
	if (!CORBA::is_nil(t))
	  try {t->decrement();}
	  catch (const CORBA::OBJECT_NOT_EXIST &) {}
	  catch (const CORBA::COMM_FAILURE &) {}
	t = o.t;
	if (!CORBA::is_nil(t))
	  try {t->increment();}
	  catch (const CORBA::OBJECT_NOT_EXIST &) { t = T::_nil();}
	  catch (const CORBA::COMM_FAILURE &) { t = T::_nil();}
      }
    return *this;
  }

  //.Assignment operator that takes a T pointer. Decreases the reference count
  //.to the current object, but does not increase the reference count to the
  //.passed pointer - in effect transferring the reference to this smart
  //.pointer.
  RefCount_var<T> &operator = (T_ptr tt)
  {
    if (!CORBA::is_nil(t))
      try { t->decrement();}
      catch (const CORBA::OBJECT_NOT_EXIST &) {}
      catch (const CORBA::COMM_FAILURE &) {}
    t = tt;
    return *this;
  }

  //.Member access operator, returns the referenced object.
  T_ptr operator->() const { return t;}

  //.Cast operator, returns the referenced object.
  operator T_ptr () const { return t;}

  //.Transfers control of the object to the caller. The _retn() method is called
  //.on the contained object and the return value of that call is returned.
  //.Before returning this smart pointer's reference to the object is removed
  //.*without* decreasing the reference count, so that the reference is
  //.transferred to the return
  //.value.
  T_ptr _retn() { T_ptr tmp = t._retn(); t = T::_nil(); return tmp;}

  //.Forwards the increment() call to the given object, if the object is not
  //.nil. Returns either the object or a _duplicate(), depending on the value
  //.of 'dup'.
  static T_ptr increment(T_ptr t, bool dup = true)
  {
    if (!CORBA::is_nil(t)) t->increment();
    return dup ? T::_duplicate(t) : t;
  }
private:
  T_var t;
};

#endif
