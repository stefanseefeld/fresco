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
#ifndef _SubjectImpl_hh
#define _SubjectImpl_hh

#include "Warsaw/config.hh"
#include "Warsaw/Subject.hh"
#include "Berlin/CloneableImpl.hh"
#include "Berlin/Thread.hh"
#include <list>

class SubjectImpl : implements(Subject)
{
public:
  SubjectImpl();
  void attach(Observer_ptr);
  void detach(Observer_ptr);
  void notify(const CORBA::Any &whatChanged);
  virtual void notify();
  void block(CORBA::Boolean b);  
protected:
  list<Observer_var> observers;
  CORBA::Boolean blocked;
  Mutex observerMutex;
  Mutex myMutex;
};

#endif /* _SubjectImpl_hh */
