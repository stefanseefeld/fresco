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

#include "BoundedValueImpl.hh"

using namespace Prague;
using namespace Fresco;

Berlin::CommandKit::BoundedValueImpl::BoundedValueImpl(Coord l, Coord u,
                               Coord v, Coord s,
                               Coord p) :
  my_l(l), my_u(u), my_v(v), my_s(s), my_p(p)
{ }

Berlin::CommandKit::BoundedValueImpl::~BoundedValueImpl()
{ }

Coord Berlin::CommandKit::BoundedValueImpl::lower()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_l;
}

void Berlin::CommandKit::BoundedValueImpl::lower(Coord l)
{
  {
    Prague::Guard<Mutex> guard(my_mutex);
    if (l == my_l) return;
    my_l = l;
    if (my_v < my_l) my_v = my_l;
  }
  CORBA::Any any;
  notify(any);
}

Coord Berlin::CommandKit::BoundedValueImpl::upper()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_u;
}

void Berlin::CommandKit::BoundedValueImpl::upper(Coord u)
{
  {
    Prague::Guard<Mutex> guard(my_mutex);
    if (u == my_u) return;
    my_u = u;
    if (my_v > my_u) my_v = my_u;
  }
  CORBA::Any any;
  notify(any);
}

Coord Berlin::CommandKit::BoundedValueImpl::step()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_s;
}

void Berlin::CommandKit::BoundedValueImpl::step(Coord s)
{
  Prague::Guard<Mutex> guard(my_mutex);
  my_s = s;
}

Coord Berlin::CommandKit::BoundedValueImpl::page()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_p;
}

void Berlin::CommandKit::BoundedValueImpl::page(Coord p)
{
  Prague::Guard<Mutex> guard(my_mutex);
  my_p = p;
}

void Berlin::CommandKit::BoundedValueImpl::forward()
{
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = my_v + my_s;
    if (t > my_u) t = my_u;
    if (t == my_v) return;
    my_v = t;
  }
  CORBA::Any any;
  any <<= my_v;
  notify(any);
}

void Berlin::CommandKit::BoundedValueImpl::backward()
{
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = my_v - my_s;
    if (t < my_l) t = my_l;
    if (t == my_v) return;
    my_v = t;
  }
  CORBA::Any any;
  any <<= my_v;
  notify(any);
}

void Berlin::CommandKit::BoundedValueImpl::fastforward()
{
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = my_v + my_p;
    if (t > my_u) t = my_u;
    if (t == my_v) return;
    my_v = t;
  }
  CORBA::Any any;
  any <<= my_v;
  notify(any);
}

void Berlin::CommandKit::BoundedValueImpl::fastbackward()
{
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = my_v - my_p;
    if (t < my_l) t = my_l;
    if (t == my_v) return;
    my_v = t;
  }
  CORBA::Any any;
  any <<= my_v;
  notify(any);
}

void Berlin::CommandKit::BoundedValueImpl::begin()
{
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = my_l;
    if (t == my_v) return;
    my_v = t;
  }
  CORBA::Any any;
  any <<= my_v;
  notify(any);
}


void Berlin::CommandKit::BoundedValueImpl::end()
{
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = my_u;
    if (t == my_v) return;
    my_v = t;
  }
  CORBA::Any any;
  any <<= my_v;
  notify(any);
}

void Berlin::CommandKit::BoundedValueImpl::value(Coord v)
{
  {
    Prague::Guard<Mutex> guard(my_mutex);
    if (v > my_u) v = my_u;
    else if (v < my_l) v = my_l;
    if (v == my_v) return;
    my_v = v;
  }
  CORBA::Any any;
  any <<= my_v;
  notify(any);
}

Coord Berlin::CommandKit::BoundedValueImpl::value()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_v;
}


void Berlin::CommandKit::BoundedValueImpl::adjust(Coord d)
{
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = my_v + d;
    if (t > my_u) t = my_u;
    else if (t < my_l) t = my_l;
    if (t == my_v) return;
    my_v = t;
  }
  CORBA::Any any;
  any <<= my_v;
  notify(any);
}
