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

BoundedValueImpl::BoundedValueImpl(Coord l, Coord u, Coord v, Coord s, Coord p)
  : _l(l), _u(u), _v(v), _s(s), _p(p)
{
};

BoundedValueImpl::~BoundedValueImpl()
{
};

Coord BoundedValueImpl::lower()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _l;
}

void BoundedValueImpl::lower(Coord l)
{
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (l == _l) return;
    _l = l;
    if (_v < _l) _v = _l;
  }
  CORBA::Any any;
  notify(any);
}

Coord BoundedValueImpl::upper()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _u;
}

void BoundedValueImpl::upper(Coord u)
{
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (u == _u) return;
    _u = u;
    if (_v > _u) _v = _u;
  }
  CORBA::Any any;
  notify(any);
}

Coord BoundedValueImpl::step()
{ 
  Prague::Guard<Mutex> guard(_mutex);
  return _s;
}

void BoundedValueImpl::step(Coord s)
{
  Prague::Guard<Mutex> guard(_mutex);
  _s = s;
}

Coord BoundedValueImpl::page()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _p;
}

void BoundedValueImpl::page(Coord p)
{
  Prague::Guard<Mutex> guard(_mutex);
  _p = p;
}

void BoundedValueImpl::forward()
{
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _v + _s;
    if (t > _u) t = _u;
    if (t == _v) return;
    _v = t;
  }
  CORBA::Any any;
  any <<= _v;
  notify(any);
}

void BoundedValueImpl::backward()
{
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _v - _s;
    if (t < _l) t = _l;
    if (t == _v) return;
    _v = t;
  }
  CORBA::Any any;
  any <<= _v;
  notify(any);
}

void BoundedValueImpl::fastforward()
{
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _v + _p;
    if (t > _u) t = _u;
    if (t == _v) return;
    _v = t;
  }
  CORBA::Any any;
  any <<= _v;
  notify(any);
}

void BoundedValueImpl::fastbackward()
{
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _v - _p;
    if (t < _l) t = _l;
    if (t == _v) return;
    _v = t;
  }
  CORBA::Any any;
  any <<= _v;
  notify(any);
}

void BoundedValueImpl::begin()
{
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _l;
    if (t == _v) return;
    _v = t;
  }
  CORBA::Any any;
  any <<= _v;
  notify(any);
}


void BoundedValueImpl::end()
{
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _u;
    if (t == _v) return;
    _v = t;
  }
  CORBA::Any any;
  any <<= _v;
  notify(any);
}

void BoundedValueImpl::value(Coord v)
{
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (v > _u) v = _u;
    else if (v < _l) v = _l;
    if (v == _v) return;
    _v = v;
  }
  CORBA::Any any;
  any <<= _v;
  notify(any);
}

Coord BoundedValueImpl::value()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _v;
}


void BoundedValueImpl::adjust(Coord d)
{
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _v + d;
    if (t > _u) t = _u;
    else if (t < _l) t = _l;
    if (t == _v) return;
    _v = t;
  }
  CORBA::Any any;
  any <<= _v;
  notify(any);
}
