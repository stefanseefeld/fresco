/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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
#include "Berlin/RegionImpl.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/Math.hh"

RegionImpl::RegionImpl()
{
  Coord zero = Coord(0.0);
  valid = false;
  lower.x = lower.y = zero;
  upper.x = upper.y = zero;
  xalign = yalign = zalign = zero;
  lower.z = Coord(-1e6);
  upper.z = Coord(1e6);
}

RegionImpl::RegionImpl(Region_ptr a, Transform_ptr t)
{
  RegionImpl::copy(a);
  if (!CORBA::is_nil(t) && !t->Identity())
    RegionImpl::applyTransform(t);
}

RegionImpl::~RegionImpl() {}

CORBA::Boolean RegionImpl::defined() { return valid;}

CORBA::Boolean RegionImpl::contains(const Vertex &v)
{
  return (valid &&
	  v.x >= lower.x && v.x <= upper.x &&
	  v.y >= lower.y && v.y <= upper.y
	  //v.z >= lower.z && v.z <= upper.z
	  );
}

CORBA::Boolean RegionImpl::containsPlane(const Vertex &v, Axis a)
{
  bool b = false;
  if (valid)
    {
      switch (a)
	{
	case xaxis:
	  b = (v.y >= lower.y && v.y <= upper.y &&
	       v.z >= lower.z && v.z <= upper.z);
	  break;
	case yaxis:
	  b = (v.x >= lower.x && v.x <= upper.x &&
	       v.z >= lower.z && v.z <= upper.z);
	  break;
	case zaxis:
	  b = (v.x >= lower.x && v.x <= upper.x &&
	       v.y >= lower.y && v.y <= upper.y);
	  break;
	}
    }
  return b;
}

CORBA::Boolean RegionImpl::intersects(Region_ptr r)
{
  bool b = false;
  if (valid)
    {
      Vertex l, u;
      r->bounds(l, u);
      b = (u.x >= lower.x && l.x <= upper.x &&
	   u.y >= lower.y && l.y <= upper.y
	   //u.z >= lower.z && l.z <= upper.z
	   );
    }
  return b;
}

void RegionImpl::copy(Region_ptr r)
{
  if (!CORBA::is_nil(r) && r->defined())
    {
      Region::Allotment x, y, z;
      r->span(xaxis, x);
      r->span(yaxis, y);
      r->span(zaxis, z);
      valid = true;
      lower.x = x.begin;
      lower.y = y.begin;
      lower.z = z.begin;
      upper.x = x.end;
      upper.y = y.end;
      upper.z = z.end;
      xalign = x.align;
      yalign = y.align;
      zalign = z.align;
//       notify();
    }
}

void RegionImpl::mergeIntersect(Region_ptr r)
{
  if (r->defined())
    {
      if (valid)
	{
	  Vertex l, u;
	  r->bounds(l, u);
	  mergeMax(lower, l);
	  mergeMin(upper, u);
        }
      else copy(r);
//       notify();
    }
}

void RegionImpl::mergeUnion(Region_ptr r)
{
  if (r->defined())
    {
      if (valid)
	{
	  Vertex l, u;
	  r->bounds(l, u);
	  mergeMin(lower, l);
	  mergeMax(upper, u);
        }
      else copy(r);
//       notify();
    }
}

void RegionImpl::subtract(Region_ptr)
{
  // not implemented
//   notify();
}

void RegionImpl::applyTransform(Transform_ptr t)
{
  if (valid)
    {
      Vertex o;

      origin(o);
      t->transformVertex(o);
      Transform::Matrix m;
      t->storeMatrix(m);

      Coord w = upper.x - lower.x;
      Coord h = upper.y - lower.y;

      Vertex center;
      center.x = Coord((upper.x + lower.x) * 0.5);
      center.y = Coord((upper.y + lower.y) * 0.5);

      // transform the center

      t->transformVertex(center);

      // optimized computation of new width and height
      Coord nw = Coord(Math::abs(w * m[0][0]) + Math::abs(h * m[1][0]));
      Coord nh = Coord(Math::abs(w * m[0][1]) + Math::abs(h * m[1][1]));

      // form the new box
      lower.x = Coord(center.x - nw * 0.5);
      upper.x = Coord(center.x + nw * 0.5);
      lower.y = Coord(center.y - nh * 0.5);
      upper.y = Coord(center.y + nh * 0.5);

      if (!Math::equal(nw, Coord(0), 1e-4)) xalign = (o.x - lower.x) / nw;
      if (!Math::equal(nh, Coord(0), 1e-4)) yalign = (o.y - lower.y) / nh;
//       notify();
    }
}

Coord RegionImpl::spanAlign(Coord lower, Coord upper, Coord origin)
{
  Coord s;
  if (Math::equal(lower, upper, 1e-4)) s = Coord(0.0);
  else s = Coord((origin - lower) / (upper - lower));
  return s;
}

void RegionImpl::bounds(Vertex &l, Vertex &u)
{
//   fresco_assert(valid);
  l = lower;
  u = upper;
}

void RegionImpl::center(Vertex &c)
{
//   fresco_assert(valid);
  c.x = (lower.x + upper.x) * 0.5;
  c.y = (lower.y + upper.y) * 0.5;
  c.z = 0.0;
}

void RegionImpl::origin(Vertex &v)
{
//   fresco_assert(valid);
  v.x = spanOrigin(lower.x, upper.x, xalign);
  v.y = spanOrigin(lower.y, upper.y, yalign);
  v.z = spanOrigin(lower.z, upper.z, zalign);
}

Coord RegionImpl::spanOrigin(Coord lower, Coord upper, Coord align)
{
  Coord orig;
  if (Math::equal(lower, upper, 1e-4)) orig = Coord(0.0);
  else orig = lower + align * (upper - lower);
  return orig;
}

void RegionImpl::span(Axis a, Region::Allotment &s)
{
//   fresco_assert(valid);
  switch (a)
    {
    case xaxis:
      s.begin = lower.x;
      s.end = upper.x;
      s.align = xalign;
      break;
    case yaxis:
      s.begin = lower.y;
      s.end = upper.y;
      s.align = yalign;
      break;
    case zaxis:
      s.begin = lower.z;
      s.end = upper.z;
      s.align = zalign;
      break;
    }
//   s.length = s.end - s.begin;
//   s.origin = s.begin + s.align * s.length;
}

// void RegionImpl::notify() {}

void RegionImpl::mergeMin(Vertex &v0, const Vertex &v)
{
  v0.x = Math::min(v0.x, v.x);
  v0.y = Math::min(v0.y, v.y);
  //v0.z = Math::min(v0.z, v.z);
}

void RegionImpl::mergeMax(Vertex &v0, const Vertex &v)
{
  v0.x = Math::max(v0.x, v.x);
  v0.y = Math::max(v0.y, v.y);
  //v0.z = Math::max(v0.z, v.z);
}

void RegionImpl::outline(Path *&p)
{
};
