/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org>
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

#include "BoundedRangeImpl.hh"
#include <algorithm>

using namespace Prague;
using namespace Fresco;

Berlin::CommandKit::BoundedRangeImpl::BoundedRangeImpl(Coord l, Coord u,
                                                       Coord lv, Coord uv,
                                                       Coord s, Coord p) :
    my_s(s), my_p(p)
{
  my_settings.lower = l;
  my_settings.upper = u;
  my_settings.lvalue = lv;
  my_settings.uvalue = uv;
}

Berlin::CommandKit::BoundedRangeImpl::~BoundedRangeImpl() { }

BoundedRange::Settings Berlin::CommandKit::BoundedRangeImpl::state()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_settings;
}

void Berlin::CommandKit::BoundedRangeImpl::state(const Fresco::BoundedRange::Settings &s)
{
  Prague::Guard<Mutex> guard(my_mutex);
  my_settings = s;
}

Coord Berlin::CommandKit::BoundedRangeImpl::lower()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_settings.lower;
}

void Berlin::CommandKit::BoundedRangeImpl::lower(Coord l)
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(my_mutex);
    if (l == my_settings.lower) return;
    my_settings.lower = l;
    my_settings.lvalue = std::max(my_settings.lvalue, my_settings.lower);
    my_settings.uvalue = std::max(my_settings.uvalue, my_settings.lower);
    any <<= my_settings;
  }
  notify(any);
}

Coord Berlin::CommandKit::BoundedRangeImpl::upper()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_settings.upper;
}

void Berlin::CommandKit::BoundedRangeImpl::upper(Coord u)
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(my_mutex);
    if (my_settings.upper == u) return;
    my_settings.upper = u;
    my_settings.lvalue = std::min(my_settings.lvalue, my_settings.upper);
    my_settings.uvalue = std::min(my_settings.uvalue, my_settings.upper);
    any <<= my_settings;
  }
  notify(any);
}

Coord Berlin::CommandKit::BoundedRangeImpl::step()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_s;
}

void Berlin::CommandKit::BoundedRangeImpl::step(Coord s)
{
  Prague::Guard<Mutex> guard(my_mutex);
  my_s = s;
}

Coord Berlin::CommandKit::BoundedRangeImpl::page()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_p;
}

void Berlin::CommandKit::BoundedRangeImpl::page(Coord p)
{
  Prague::Guard<Mutex> guard(my_mutex);
  my_p = p;
}

void Berlin::CommandKit::BoundedRangeImpl::forward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = std::min(my_s, my_settings.upper - my_settings.uvalue);
    if (t <= 0.) return;
    my_settings.lvalue += t;
    my_settings.uvalue += t;
    any <<= my_settings;
  }
  notify(any);
}

void Berlin::CommandKit::BoundedRangeImpl::backward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = std::min(my_s, my_settings.lvalue - my_settings.lower);
    if (t <= 0.) return;
    my_settings.lvalue -= t;
    my_settings.uvalue -= t;
    any <<= my_settings;
  }
  notify(any);
}

void Berlin::CommandKit::BoundedRangeImpl::fastforward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = std::min(my_p, my_settings.upper - my_settings.uvalue);
    if (t <= 0.) return;
    my_settings.lvalue += t;
    my_settings.uvalue += t;
    any <<= my_settings;
  }
  notify(any);
}

void Berlin::CommandKit::BoundedRangeImpl::fastbackward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = std::min(my_p, my_settings.lvalue - my_settings.lower);
    if (t <= 0.) return;
    my_settings.lvalue -= t;
    my_settings.uvalue -= t;
    any <<= my_settings;
  }
  notify(any);
}

void Berlin::CommandKit::BoundedRangeImpl::begin()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = my_settings.lvalue - my_settings.lower;
    if (t == 0.) return;
    my_settings.lvalue -= t;
    my_settings.uvalue -= t;
    any <<= my_settings;
  }
  notify(any);
}

void Berlin::CommandKit::BoundedRangeImpl::end()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = my_settings.upper - my_settings.uvalue;
    if (t == 0.) return;
    my_settings.lvalue += t;
    my_settings.uvalue += t;
    any <<= my_settings;
  }
  notify(any);
}

void Berlin::CommandKit::BoundedRangeImpl::lvalue(Coord lv)
{
  CORBA::Any any;
  {
    lv = std::min(std::max(my_settings.lower, lv), my_settings.upper);
    Prague::Guard<Mutex> guard(my_mutex);
    if (lv == my_settings.lvalue) return;
    my_settings.lvalue = lv;
    any <<= my_settings;
  }
  notify(any);
}

Coord Berlin::CommandKit::BoundedRangeImpl::lvalue()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_settings.lvalue;
}


void Berlin::CommandKit::BoundedRangeImpl::uvalue(Coord uv)
{
  CORBA::Any any;
  {
    uv = std::min(std::max(my_settings.lower, uv), my_settings.upper);
    Prague::Guard<Mutex> guard(my_mutex);
    if (my_settings.uvalue == uv) return;
    my_settings.uvalue = uv;
  }
  notify(any);
}

Coord Berlin::CommandKit::BoundedRangeImpl::uvalue()
{
  Prague::Guard<Mutex> guard(my_mutex);
  return my_settings.uvalue;
}


void Berlin::CommandKit::BoundedRangeImpl::adjust(Coord d)
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(my_mutex);
    Coord t = std::min(std::max(d, my_settings.lower - my_settings.lvalue),
                       my_settings.upper - my_settings.uvalue);
    if (t == 0.) return;
    my_settings.lvalue += t;
    my_settings.uvalue += t;
    any <<= my_settings;
  }
  notify(any);
}
