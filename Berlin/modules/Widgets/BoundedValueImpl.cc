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
  myMutex.lock();
  if (ll == l) { myMutex.unlock(); return;}
  l = ll;
  if (v < l) v = l;
  myMutex.unlock();
  notify();
}

Coord BoundedValueImpl::upper()
{
  myMutex.lock();
  Coord tmp = u;
  myMutex.unlock();
  return tmp;
}

void BoundedValueImpl::upper(Coord uu)
{
  myMutex.lock();
  if (uu == u) {myMutex.unlock(); return;}
  u = uu;
  if (v > u) v = u;
  myMutex.unlock();
  notify();
}

Coord BoundedValueImpl::step()
{ 
  myMutex.lock();
  Coord tmp = s;
  myMutex.unlock();
  return tmp;
}

void BoundedValueImpl::step(Coord ss)
{
  myMutex.lock();
  s = ss;
  myMutex.unlock();
}

Coord BoundedValueImpl::page()
{
  myMutex.lock();
  Coord tmp = p;
  myMutex.unlock();
  return tmp;
}

void BoundedValueImpl::page(Coord pp)
{
  myMutex.lock();
  p = pp;
  myMutex.unlock();
}

void BoundedValueImpl::forward()
{
  myMutex.lock();
  Coord t = v + s;
  if (t > u) t = u;
  if (t == v) {myMutex.unlock(); return;}
  v = t;
  myMutex.unlock();
  notify();
}

void BoundedValueImpl::backward()
{
  myMutex.lock();
  Coord t = v - s;
  if (t < l) t = l;
  if (t == v) {myMutex.unlock(); return;}
  v = t;
  myMutex.unlock();
  notify();
}

void BoundedValueImpl::fastforward()
{
  myMutex.lock();
  Coord t = v + p;
  if (t > u) t = u;
  if (t == v) {myMutex.unlock(); return;}
  v = t;
  myMutex.unlock();
  notify();
}

void BoundedValueImpl::fastbackward()
{
  myMutex.lock();
  Coord t = v - p;
  if (t < l) t = l;
  if (t == v) {myMutex.unlock(); return;}
  v = t;
  myMutex.unlock();
  notify();
}

void BoundedValueImpl::begin()
{
  myMutex.lock();
  Coord t = l;
  if (t == v) {myMutex.unlock(); return; }
  v = t;
  myMutex.unlock();
  notify();
}


void BoundedValueImpl::end()
{
  myMutex.lock();
  Coord t = u;
  if (t == v) {myMutex.unlock(); return; }
  v = t;
  myMutex.unlock();
  notify();
}

void BoundedValueImpl::value(Coord vv)
{
  myMutex.lock();
  if (vv > u) vv = u;
  else if (vv < l) vv = l;
  if (vv == v) {myMutex.unlock(); return;}
  v = vv;
  myMutex.unlock();
  notify();
}

Coord BoundedValueImpl::value()
{
  myMutex.lock();
  Coord tmp = v;
  myMutex.unlock();
  return tmp;
}


void BoundedValueImpl::adjust(Coord d)
{
  myMutex.lock();
  Coord t = v + d;
  if (t > u) t = u;
  else if (t < l) t = l;
  if (t == v) {myMutex.unlock(); return;}
  v = t;
  myMutex.unlock();
  notify();
}
