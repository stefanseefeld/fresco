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

#include "Widget/BoundedRangeImpl.hh"

BoundedRangeImpl::BoundedRangeImpl(Coord ll, Coord uu, Coord lvv, Coord uvv, Coord ss, Coord pp)
  : l(l), u(uu), lv(lvv), uv(uvv), s(ss), p(pp)
{
};

BoundedRangeImpl::~BoundedRangeImpl()
{
};

Coord BoundedRangeImpl::lower() { return l;}
void BoundedRangeImpl::lower(Coord ll)
{
    myMutex.lock();
    if (ll == l) { myMutex.unlock(); return;}
    l = ll;
    if (lv < l) lv = l;
    if (uv < l) uv = l;
    myMutex.unlock();
    notify();
}

Coord BoundedRangeImpl::upper() { return u;}
void BoundedRangeImpl::upper(Coord uu)
{
    myMutex.lock();
    if (uu == u) {myMutex.unlock(); return;}
    u = uu;
    if (lv > u) lv = u;
    if (uv > u) uv = u;
    myMutex.unlock();
    notify();
}

Coord BoundedRangeImpl::step()
{
  myMutex.lock();
  Coord tmp = s;
  myMutex.unlock();
  return tmp;
}

void BoundedRangeImpl::step(Coord ss)
{
  myMutex.lock();
  s = ss;
  myMutex.unlock();
}

Coord BoundedRangeImpl::page()
{
  myMutex.lock();
  Coord tmp = p;
  myMutex.unlock();
  return tmp;
}

void BoundedRangeImpl::page(Coord pp)
{
  myMutex.lock();
  p = pp;
  myMutex.unlock();
}

void BoundedRangeImpl::forward()
{
    myMutex.lock();
    Coord t = uv + s > u ? u - uv : s;
    if (t <= 0.) { myMutex.unlock(); return;}
    lv += t;
    uv += t;
    myMutex.unlock();
    notify();
}

void BoundedRangeImpl::backward()
{
    myMutex.lock();
    Coord t = lv - s < l ? lv - l : s;
    if (t <= 0.) { myMutex.unlock(); return;}
    lv -= t;
    uv -= t;
    myMutex.unlock();
    notify();
}

void BoundedRangeImpl::fastforward()
{
    myMutex.lock();
    Coord t = uv + p > u ? u - uv : p;
    if (t <= 0.) { myMutex.unlock(); return;}
    lv += t;
    uv += t;
    myMutex.unlock();
    notify();
}

void BoundedRangeImpl::fastbackward()
{
    myMutex.lock();
    Coord t = lv - p < l ? lv - l : p;
    if (t <= 0.) { myMutex.unlock(); return;}
    lv -= t;
    uv -= t;
    myMutex.unlock();
    notify();
}

void BoundedRangeImpl::begin()
{
    myMutex.lock();
    Coord t = lv - l;
    if (t == 0.) { myMutex.unlock(); return;}
    lv -= t;
    uv -= t;
    myMutex.unlock();
    notify();
}

void BoundedRangeImpl::end()
{
    myMutex.lock();
    Coord t = u - uv;
    if (t == 0.) { myMutex.unlock(); return;}
    lv += t;
    uv += t;
    myMutex.unlock();
    notify();
}

void BoundedRangeImpl::lvalue(Coord vv)
{
    myMutex.lock();
    if (vv > u) vv = u;
    else if (vv < l) vv = l;
    if (vv == lv) { myMutex.unlock(); return;}
    lv = vv;
    myMutex.unlock();

    notify();
}

Coord BoundedRangeImpl::lvalue()
{
    myMutex.lock();
    Coord tmp = lv;
    myMutex.unlock();
    return tmp;
}


void BoundedRangeImpl::uvalue(Coord vv)
{
    myMutex.lock();
    if (vv > u) vv = u;
    else if (vv < l) vv = l;
    if (vv == uv) {myMutex.unlock(); return;}
    uv = vv;
    myMutex.unlock();

    notify();
}

Coord BoundedRangeImpl::uvalue()
{
    myMutex.lock();
    Coord tmp = uv;
    myMutex.unlock();
    return tmp;
}


void BoundedRangeImpl::adjust(Coord d)
{
  myMutex.lock();
  Coord t =
    uv + d > u ? u - uv :
    lv + d < l ? lv - l : d;
  if (t == 0.) { myMutex.unlock(); return;}
  lv += t;
  uv += t;
  myMutex.unlock();
  notify();
}

