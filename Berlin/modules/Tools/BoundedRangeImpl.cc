/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.ca> 
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

#include "Widget/BoundedRangeImpl.hh"
#include <algorithm>

using namespace Prague;

BoundedRangeImpl::BoundedRangeImpl(Coord l, Coord u, Coord lv, Coord uv, Coord ss, Coord pp)
  : s(ss), p(pp)
{
  settings.lower = l;
  settings.upper = u;
  settings.lvalue = lv;
  settings.uvalue = uv;
};

BoundedRangeImpl::~BoundedRangeImpl()
{
};

BoundedRange::Settings BoundedRangeImpl::getSettings()
{
  MutexGuard guard(mutex);
  return settings;
}

Coord BoundedRangeImpl::lower()
{
  MutexGuard guard(mutex);
  return settings.lower;
}

void BoundedRangeImpl::lower(Coord l)
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    if (l == settings.lower) return;
    settings.lower = l;
    settings.lvalue = max(settings.lvalue, settings.lower);
    settings.uvalue = max(settings.uvalue, settings.lower);
    any <<= settings;
  }
  notify(any);
}

Coord BoundedRangeImpl::upper()
{
  MutexGuard guard(mutex);
  return settings.upper;
}

void BoundedRangeImpl::upper(Coord u)
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    if (settings.upper == u) return;
    settings.upper = u;
    settings.lvalue = min(settings.lvalue, settings.upper);
    settings.uvalue = min(settings.uvalue, settings.upper);
    any <<= settings;
  }
  notify(any);
}

Coord BoundedRangeImpl::step()
{
  MutexGuard guard(mutex);
  return s;
}

void BoundedRangeImpl::step(Coord ss)
{
  MutexGuard guard(mutex);
  s = ss;
}

Coord BoundedRangeImpl::page()
{
  MutexGuard guard(mutex);
  return p;
}

void BoundedRangeImpl::page(Coord pp)
{
  MutexGuard guard(mutex);
  p = pp;
}

void BoundedRangeImpl::forward()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = min(s, settings.upper - settings.uvalue);
    if (t <= 0.) return;
    settings.lvalue += t;
    settings.uvalue += t;
    any <<= settings;
  }
  notify(any);
}

void BoundedRangeImpl::backward()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = min(s, settings.lvalue - settings.lower);
    if (t <= 0.) return;
    settings.lvalue -= t;
    settings.uvalue -= t;
    any <<= settings;
  }
  notify(any);
}

void BoundedRangeImpl::fastforward()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = min(p, settings.upper - settings.uvalue);
    if (t <= 0.) return;
    settings.lvalue += t;
    settings.uvalue += t;
    any <<= settings;
  }
  notify(any);
}

void BoundedRangeImpl::fastbackward()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = min(p, settings.lvalue - settings.lower);
    if (t <= 0.) return;
    settings.lvalue -= t;
    settings.uvalue -= t;
    any <<= settings;
  }
  notify(any);
}

void BoundedRangeImpl::begin()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = settings.lvalue - settings.lower;
    if (t == 0.) return;
    settings.lvalue -= t;
    settings.uvalue -= t;
    any <<= settings;
  }
  notify(any);
}

void BoundedRangeImpl::end()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = settings.upper - settings.uvalue;
    if (t == 0.) return;
    settings.lvalue += t;
    settings.uvalue += t;
    any <<= settings;
  }
  notify(any);
}

void BoundedRangeImpl::lvalue(Coord lv)
{
  CORBA::Any any;
  {
    lv = min(max(settings.lower, lv), settings.upper);
    MutexGuard guard(mutex);
    if (lv == settings.lvalue) return;
    settings.lvalue = lv;
    any <<= settings;
  }
  notify(any);
}

Coord BoundedRangeImpl::lvalue()
{
  MutexGuard guard(mutex);
  return settings.lvalue;
}


void BoundedRangeImpl::uvalue(Coord uv)
{
  CORBA::Any any;
  {
    uv = min(max(settings.lower, uv), settings.upper);
    MutexGuard guard(mutex);
    if (settings.uvalue == uv) return;
    settings.uvalue = uv;
  }
  notify(any);
}

Coord BoundedRangeImpl::uvalue()
{
  MutexGuard guard(mutex);
  return settings.uvalue;
}


void BoundedRangeImpl::adjust(Coord d)
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = min(max(d, settings.lower - settings.lvalue), settings.upper - settings.uvalue);
    if (t == 0.) return;
    settings.lvalue += t;
    settings.uvalue += t;
    any <<= settings;
  }
  notify(any);
}
