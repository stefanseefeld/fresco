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
#ifndef _Berlin_SubjectImpl_hh
#define _Berlin_SubjectImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Subject.hh>
#include <Fresco/Observer.hh>
#include <Prague/Sys/Thread.hh>
#include "Berlin/RefCountBaseImpl.hh"
#include "Berlin/IdentifiableImpl.hh"
#include <vector>

class SubjectImpl : public virtual POA_Fresco::Subject,
		    public virtual RefCountBaseImpl,
                    public virtual IdentifiableImpl
{
  typedef std::vector<Fresco::Observer_var> olist_t;
public:
  SubjectImpl();
  void attach(Fresco::Observer_ptr);
  void detach(Fresco::Observer_ptr);
  void notify(const CORBA::Any &);
  virtual void notify();
  void block(CORBA::Boolean);  
private:
  olist_t        _observers;
  CORBA::Boolean _blocked;
  Prague::Mutex  _mutex;
  Prague::Mutex  _observerMutex;
};

#endif 
