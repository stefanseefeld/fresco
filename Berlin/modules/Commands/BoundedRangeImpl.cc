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

BoundedRangeImpl::BoundedRangeImpl(Coord l, Coord u, Coord lv, Coord uv, Coord s, Coord p)
  : _s(s), _p(p)
{
  _settings.lower = l;
  _settings.upper = u;
  _settings.lvalue = lv;
  _settings.uvalue = uv;
};

BoundedRangeImpl::~BoundedRangeImpl()
{
};

BoundedRange::Settings BoundedRangeImpl::state()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _settings;
}

void BoundedRangeImpl::state(const Fresco::BoundedRange::Settings &s)
{
  Prague::Guard<Mutex> guard(_mutex);
  _settings = s;
}

Coord BoundedRangeImpl::lower()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _settings.lower;
}

void BoundedRangeImpl::lower(Coord l)
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (l == _settings.lower) return;
    _settings.lower = l;
    _settings.lvalue = std::max(_settings.lvalue, _settings.lower);
    _settings.uvalue = std::max(_settings.uvalue, _settings.lower);
    any <<= _settings;
  }
  notify(any);
}

Coord BoundedRangeImpl::upper()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _settings.upper;
}

void BoundedRangeImpl::upper(Coord u)
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (_settings.upper == u) return;
    _settings.upper = u;
    _settings.lvalue = std::min(_settings.lvalue, _settings.upper);
    _settings.uvalue = std::min(_settings.uvalue, _settings.upper);
    any <<= _settings;
  }
  notify(any);
}

Coord BoundedRangeImpl::step()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _s;
}

void BoundedRangeImpl::step(Coord s)
{
  Prague::Guard<Mutex> guard(_mutex);
  _s = s;
}

Coord BoundedRangeImpl::page()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _p;
}

void BoundedRangeImpl::page(Coord p)
{
  Prague::Guard<Mutex> guard(_mutex);
  _p = p;
}

void BoundedRangeImpl::forward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = std::min(_s, _settings.upper - _settings.uvalue);
    if (t <= 0.) return;
    _settings.lvalue += t;
    _settings.uvalue += t;
    any <<= _settings;
  }
  notify(any);
}

void BoundedRangeImpl::backward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = std::min(_s, _settings.lvalue - _settings.lower);
    if (t <= 0.) return;
    _settings.lvalue -= t;
    _settings.uvalue -= t;
    any <<= _settings;
  }
  notify(any);
}

void BoundedRangeImpl::fastforward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = std::min(_p, _settings.upper - _settings.uvalue);
    if (t <= 0.) return;
    _settings.lvalue += t;
    _settings.uvalue += t;
    any <<= _settings;
  }
  notify(any);
}

void BoundedRangeImpl::fastbackward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = std::min(_p, _settings.lvalue - _settings.lower);
    if (t <= 0.) return;
    _settings.lvalue -= t;
    _settings.uvalue -= t;
    any <<= _settings;
  }
  notify(any);
}

void BoundedRangeImpl::begin()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _settings.lvalue - _settings.lower;
    if (t == 0.) return;
    _settings.lvalue -= t;
    _settings.uvalue -= t;
    any <<= _settings;
  }
  notify(any);
}

void BoundedRangeImpl::end()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _settings.upper - _settings.uvalue;
    if (t == 0.) return;
    _settings.lvalue += t;
    _settings.uvalue += t;
    any <<= _settings;
  }
  notify(any);
}

void BoundedRangeImpl::lvalue(Coord lv)
{
  CORBA::Any any;
  {
    lv = std::min(std::max(_settings.lower, lv), _settings.upper);
    Prague::Guard<Mutex> guard(_mutex);
    if (lv == _settings.lvalue) return;
    _settings.lvalue = lv;
    any <<= _settings;
  }
  notify(any);
}

Coord BoundedRangeImpl::lvalue()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _settings.lvalue;
}


void BoundedRangeImpl::uvalue(Coord uv)
{
  CORBA::Any any;
  {
    uv = std::min(std::max(_settings.lower, uv), _settings.upper);
    Prague::Guard<Mutex> guard(_mutex);
    if (_settings.uvalue == uv) return;
    _settings.uvalue = uv;
  }
  notify(any);
}

Coord BoundedRangeImpl::uvalue()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _settings.uvalue;
}


void BoundedRangeImpl::adjust(Coord d)
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = std::min(std::max(d, _settings.lower - _settings.lvalue), _settings.upper - _settings.uvalue);
    if (t == 0.) return;
    _settings.lvalue += t;
    _settings.uvalue += t;
    any <<= _settings;
  }
  notify(any);
}
