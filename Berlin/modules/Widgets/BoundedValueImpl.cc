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

Coord BoundedValueImpl::lower()
{
  Guard guard(myMutex);
  return l;
}

void BoundedValueImpl::lower(Coord ll)
{
  Guard guard(myMutex);
  if (ll == l) { myMutex.unlock(); return;}
  l = ll;
  if (v < l) v = l;
  notify();
}

Coord BoundedValueImpl::upper()
{
  Guard guard(myMutex);
  return u;
}

void BoundedValueImpl::upper(Coord uu)
{
  Guard guard(myMutex);
  if (uu == u) {myMutex.unlock(); return;}
  u = uu;
  if (v > u) v = u;
  notify();
}

Coord BoundedValueImpl::step()
{ 
  Guard guard(myMutex);
  return s;
}

void BoundedValueImpl::step(Coord ss)
{
  Guard guard(myMutex);
  s = ss;
}

Coord BoundedValueImpl::page()
{
  Guard guard(myMutex);
  return p;
}

void BoundedValueImpl::page(Coord pp)
{
  Guard guard(myMutex);
  p = pp;
}

void BoundedValueImpl::forward()
{
  Guard guard(myMutex);
  Coord t = v + s;
  if (t > u) t = u;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::backward()
{
  Guard guard(myMutex);
  Coord t = v - s;
  if (t < l) t = l;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::fastforward()
{
  Guard guard(myMutex);
  Coord t = v + p;
  if (t > u) t = u;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::fastbackward()
{
  Guard guard(myMutex);
  Coord t = v - p;
  if (t < l) t = l;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::begin()
{
  Guard guard(myMutex);
  Coord t = l;
  if (t == v) return;
  v = t;
  notify();
}


void BoundedValueImpl::end()
{
  Guard guard(myMutex);
  Coord t = u;
  if (t == v) return;
  v = t;
  notify();
}

void BoundedValueImpl::value(Coord vv)
{
  Guard guard(myMutex);
  if (vv > u) vv = u;
  else if (vv < l) vv = l;
  if (vv == v) return;
  v = vv;
  notify();
}

Coord BoundedValueImpl::value()
{
  Guard guard(myMutex);
  return v;
}


void BoundedValueImpl::adjust(Coord d)
{
  Guard guard(myMutex);
  Coord t = v + d;
  if (t > u) t = u;
  else if (t < l) t = l;
  if (t == v) return;
  v = t;
  notify();
}
