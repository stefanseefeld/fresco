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

Coord BoundedRangeImpl::lower()
{
  Guard guard(myMutex);
  return l;
}

void BoundedRangeImpl::lower(Coord ll)
{
  Guard guard(myMutex);
  if (ll == l) return;
  l = ll;
  if (lv < l) lv = l;
  if (uv < l) uv = l;
  notify();
}

Coord BoundedRangeImpl::upper()
{
  Guard guard(myMutex);
  return u;
}

void BoundedRangeImpl::upper(Coord uu)
{
  Guard guard(myMutex);
  if (uu == u) return;
  u = uu;
  if (lv > u) lv = u;
  if (uv > u) uv = u;
  notify();
}

Coord BoundedRangeImpl::step()
{
  Guard guard(myMutex);
  return s;
}

void BoundedRangeImpl::step(Coord ss)
{
  Guard guard(myMutex);
  s = ss;
}

Coord BoundedRangeImpl::page()
{
  Guard guard(myMutex);
  return p;
}

void BoundedRangeImpl::page(Coord pp)
{
  Guard guard(myMutex);
  p = pp;
}

void BoundedRangeImpl::forward()
{
  Guard guard(myMutex);
  Coord t = uv + s > u ? u - uv : s;
  if (t <= 0.) return;
  lv += t;
  uv += t;
  notify();
}

void BoundedRangeImpl::backward()
{
  Guard guard(myMutex);
  Coord t = lv - s < l ? lv - l : s;
  if (t <= 0.) return;
  lv -= t;
  uv -= t;
  notify();
}

void BoundedRangeImpl::fastforward()
{
  Guard guard(myMutex);
  Coord t = uv + p > u ? u - uv : p;
  if (t <= 0.) return;
  lv += t;
  uv += t;
  notify();
}

void BoundedRangeImpl::fastbackward()
{
  Guard guard(myMutex);
  Coord t = lv - p < l ? lv - l : p;
  if (t <= 0.) return;
  lv -= t;
  uv -= t;
  notify();
}

void BoundedRangeImpl::begin()
{
  Guard guard(myMutex);
  Coord t = lv - l;
  if (t == 0.) return;
  lv -= t;
  uv -= t;
  notify();
}

void BoundedRangeImpl::end()
{
  Guard guard(myMutex);
  Coord t = u - uv;
  if (t == 0.) return;
  lv += t;
  uv += t;
  notify();
}

void BoundedRangeImpl::lvalue(Coord vv)
{
  Guard guard(myMutex);
  if (vv > u) vv = u;
  else if (vv < l) vv = l;
  if (vv == lv) return;
  lv = vv;
  notify();
}

Coord BoundedRangeImpl::lvalue()
{
  Guard guard(myMutex);
  return lv;
}


void BoundedRangeImpl::uvalue(Coord vv)
{
  Guard guard(myMutex);
  if (vv > u) vv = u;
  else if (vv < l) vv = l;
  if (vv == uv) return;
  uv = vv;
  notify();
}

Coord BoundedRangeImpl::uvalue()
{
  Guard guard(myMutex);
  return uv;
}


void BoundedRangeImpl::adjust(Coord d)
{
  Guard guard(myMutex);
  Coord t =
    uv + d > u ? u - uv :
    lv + d < l ? lv - l : d;
  if (t == 0.) return;
  lv += t;
  uv += t;
  notify();
}
