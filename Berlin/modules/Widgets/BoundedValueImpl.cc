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

#include "Widget/BoundedValueImpl.hh"

BoundedValueImpl::BoundedValueImpl(Coord ll, Coord uu, Coord vv, Coord ss, Coord pp)
  : l(l), u(uu), v(vv), s(ss), p(pp)
{
};

BoundedValueImpl::~BoundedValueImpl()
{
};

Coord BoundedValueImpl::lower() { return l;}
void BoundedValueImpl::lower(Coord ll)
{
  if (ll == l) return;
  l = ll;
  if (v < l) v = l;
  notify();
}

Coord BoundedValueImpl::upper() { return u;}
void BoundedValueImpl::upper(Coord uu)
{
  if (uu == u) return;
  u = uu;
  if (v > u) v = u;
  notify();
}

Coord BoundedValueImpl::step() { return s;}
void BoundedValueImpl::step(Coord ss) { s = ss;}
Coord BoundedValueImpl::page() { return p;}
void BoundedValueImpl::page(Coord pp) { p = pp;}

void BoundedValueImpl::forward()
{
  Coord t = v + s;
  if (t > u) t = u;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::backward()
{
  Coord t = v - s;
  if (t < l) t = l;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::fastforward()
{
  Coord t = v + p;
  if (t > u) t = u;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::fastbackward()
{
  Coord t = v - p;
  if (t < l) t = l;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::begin()
{
  Coord t = l;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::end()
{
  Coord t = u;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::set(Coord vv)
{
  if (vv > u) vv = u;
  else if (vv < l) vv = l;
  if (vv == v) return;
  v = vv;
  notify();
}

void BoundedValueImpl::move(Coord d)
{
  Coord t = v + d;
  if (t > u) t = u;
  else if (t < l) t = l;
  if (t == v) return;
  v = t;
  notify();
}

