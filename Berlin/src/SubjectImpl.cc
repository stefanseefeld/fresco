/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include "Berlin/SubjectImpl.hh"
#include <Prague/Sys/Tracer.hh>
#include <algorithm>
#include <functional>

using namespace Prague;
using namespace Warsaw;

SubjectImpl::SubjectImpl() : blocked(false) {}

void SubjectImpl::attach(Observer_ptr o)
{
  Trace trace("SubjectImpl::attach");
  MutexGuard guard(observerMutex);
  observers.push_back(Warsaw::Observer::_duplicate(o));
}

struct Id_eq : public unary_function<Warsaw::Identifiable_ptr, bool>
{
  Id_eq(Warsaw::Identifiable_ptr i) : id(i) {}
  bool operator()(const Warsaw::Identifiable_ptr i) const { return id->is_identical(i);}
  Warsaw::Identifiable_ptr id;
};

void SubjectImpl::detach(Observer_ptr o)
{
  Trace trace("SubjectImpl::detach");
  MutexGuard guard(observerMutex);
  observers.erase(find_if(observers.begin(), observers.end(), Id_eq(o)));
}


void SubjectImpl::block(CORBA::Boolean b)
{
  MutexGuard guard(mutex);
  blocked = b;
}

void SubjectImpl::notify()
{
  this->notify(CORBA::Any());
}

void SubjectImpl::notify(const CORBA::Any &change)
{
  Trace trace("SubjectImpl::notify");
  MutexGuard guard(mutex);
  if (!blocked)
    {
      MutexGuard guard(observerMutex);
      for(vector<Observer_var>::iterator i = observers.begin(); i != observers.end(); i++)
	try { (*i)->update(change);}
        catch (const CORBA::OBJECT_NOT_EXIST &) { *i = Observer::_nil();}
	catch (const CORBA::COMM_FAILURE &) { *i = Observer::_nil();}
    }
}
