/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include <Prague/Sys/Thread.hh>
#include <Berlin/SubjectImpl.hh>
#include "Widget/Motif/Paned.hh"

using namespace Prague;
using namespace Warsaw;
using namespace Motif;

class Paned::Adjustment : public virtual POA_Warsaw::BoundedValue,
	                  public SubjectImpl

{
public:
  Adjustment(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  virtual ~Adjustment();
  virtual Warsaw::Coord lower();
  virtual void lower(Warsaw::Coord);
  virtual Warsaw::Coord upper();
  virtual void upper(Warsaw::Coord);
  virtual Warsaw::Coord step();
  virtual void step(Warsaw::Coord);
  virtual Warsaw::Coord page();
  virtual void page(Warsaw::Coord);
  virtual Warsaw::Coord value();
  virtual void value(Warsaw::Coord);

  virtual void forward();
  virtual void backward();
  virtual void fastforward();
  virtual void fastbackward();
  virtual void begin();
  virtual void end();
  virtual void adjust(Warsaw::Coord);
private:
  Warsaw::Coord _l;
  Warsaw::Coord _u;
  Warsaw::Coord _v;
  Warsaw::Coord _s;
  Warsaw::Coord _p;
  Prague::Mutex _mutex;
};

Paned::Adjustment::Adjustment(Coord l, Coord u, Coord v, Coord s, Coord p)
  : _l(l), _u(u), _v(v), _s(s), _p(p)
{
};

Paned::Adjustment::~Adjustment()
{
};

Coord Paned::Adjustment::lower()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _l;
}

void Paned::Adjustment::lower(Coord l)
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

Coord Paned::Adjustment::upper()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _u;
}

void Paned::Adjustment::upper(Coord u)
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

Coord Paned::Adjustment::step()
{ 
  Prague::Guard<Mutex> guard(_mutex);
  return _s;
}

void Paned::Adjustment::step(Coord s)
{
  Prague::Guard<Mutex> guard(_mutex);
  _s = s;
}

Coord Paned::Adjustment::page()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _p;
}

void Paned::Adjustment::page(Coord p)
{
  Prague::Guard<Mutex> guard(_mutex);
  _p = p;
}

void Paned::Adjustment::forward()
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

void Paned::Adjustment::backward()
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

void Paned::Adjustment::fastforward()
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

void Paned::Adjustment::fastbackward()
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

void Paned::Adjustment::begin()
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


void Paned::Adjustment::end()
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

void Paned::Adjustment::value(Coord v)
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

Coord Paned::Adjustment::value()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _v;
}


void Paned::Adjustment::adjust(Coord d)
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

Paned::Paned(Axis a, Alignment al) : ControllerImpl(false), _axis(a), _alignment(al), _adjustment(new Adjustment(0, 1, 0, 0.01, 0.1))
{
}

Paned::~Paned()
{
}

void Paned::init(Graphic_ptr left, Graphic_ptr right)
{
}

BoundedValue_ptr Paned::adjustment() { return _adjustment->_this();}

void Paned::traverse(Warsaw::Traversal_ptr)
{
}

void Paned::allocate(Warsaw::Tag, const Warsaw::Allocation::Info &)
{
}
