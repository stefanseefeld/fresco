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
#include <Prague/Sys/Tracer.hh>
#include "Berlin/SubjectImpl.hh"
#include <algorithm>
#include <functional>

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

SubjectImpl::SubjectImpl() : my_blocked(false) { }

void SubjectImpl::attach(Observer_ptr observer)
{
    Trace trace(this, "SubjectImpl::attach");
    Prague::Guard<Mutex> guard(my_observerMutex);
    my_observers.push_back(Fresco::Observer::_duplicate(observer));
}

namespace
{
  struct Id_eq : public std::unary_function<Fresco::Identifiable_ptr, bool>
  {
      Id_eq(Fresco::Identifiable_ptr i) : id(i) {}
      bool operator()(const Fresco::Identifiable_ptr i) const
      { return id->is_identical(i); }
      Fresco::Identifiable_ptr id;
  };
} // namespace

void SubjectImpl::detach(Observer_ptr observer)
{
    Trace trace(this, "SubjectImpl::detach");
    Prague::Guard<Mutex> guard(my_observerMutex);
    my_observers.erase(find_if(my_observers.begin(), my_observers.end(),
                               Id_eq(observer)));
}


void SubjectImpl::block(CORBA::Boolean blocked)
{
    Prague::Guard<Mutex> guard(my_mutex);
    my_blocked = blocked;
}

void SubjectImpl::notify()
{ this->notify(CORBA::Any()); }

void SubjectImpl::notify(const CORBA::Any &change)
{
    Trace trace(this, "SubjectImpl::notify");
    Prague::Guard<Mutex> guard(my_mutex);
    if (!my_blocked)
    {
        Prague::Guard<Mutex> guard(my_observerMutex);
        for(olist_t::iterator i = my_observers.begin();
            i != my_observers.end();
            ++i)
            try { (*i)->update(change);}
            catch (const CORBA::OBJECT_NOT_EXIST &)
            { *i = Observer::_nil(); }
            catch (const CORBA::COMM_FAILURE &)
            { *i = Observer::_nil(); }
            catch (const CORBA::TRANSIENT &)
            { *i = Observer::_nil(); }
    }
}
