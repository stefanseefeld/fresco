/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1991, 1992, 1993, 1994 Alta Group of Cadence Design Systems
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
#include "Berlin/Math.hh"
#include "Layout/Geometry.hh"

static const Coord epsilon = 0.001;

inline static double square(double a) {	return a * a;}

static void transform(Coord radians, Coord x, Coord y, Coord &tx, Coord &ty)
{
  Coord c = Coord(cos(radians));
  Coord s = Coord(sin(radians));
  tx = x * c + y * (-s);
  ty = x * s + y * c;
}

Coord Geometry::Point::distance(const Point &p) const
{
  return Coord(sqrt(double(square(x - p.x) + square(y - p.y))));
}

bool Geometry::Line::contains(const Point &p, Coord bloat) const
{
  Coord l = Math::min(u.x, v.x) - bloat;
  Coord b = Math::min(u.y, v.y) - bloat;
  Coord r = Math::max(u.x, v.x) + bloat;
  Coord t = Math::max(u.y, v.y) + bloat;
  if (! (l <= p.x) && (p.x <= r) && (b <= p.y) && (p.y <= t))
    return false;

  Coord dx = u.x - v.x;
  Coord dy = u.y - v.y;
  Coord length = Coord(sqrt(dx*dx + dy*dy));
  Coord radians = (length <= epsilon ? Coord(0) : Coord(acos(dx/length)));
  if (dy > Coord(0))
    radians = -radians;

  Coord x, y;
  transform(radians, p.x - u.x, p.y - u.y, x, y);
  Coord l = -length - bloat;
  Coord b = -bloat;
  Coord r = bloat;
  Coord t = bloat;
  return l <= x && x <= r && b <= y && y <= t;
}

inline static int signum(Coord a)
{
  if (a < 0.) return -1;
  else if (a > 0.) return 1;
  else return 0;
}

static int same(const Geometry::Point &u, const Geometry::Point &v)
{
  Coord dx, dx1, dx2;
  Coord dy, dy1, dy2;
		
  dx = v.x - u.x;
  dy = v.y - u.y;
  dx1 = u.x - u.x;
  dy1 = u.y - u.y;
  dx2 = v.x - v.x;
  dy2 = v.y - v.y;
  
  return signum(dx*dy1 - dy*dx1) * signum(dx*dy2 - dy*dx2);
}

bool Geometry::Line::intersects(const Line &i) const
{
  return
    (l() <= i.r()) && (i.l() <= r()) && (b() <= i.t()) && (i.b() <= t()) &&
    (same(i.u, i.v) <= 0) && (same(u, v) <= 0);
}

bool Geometry::Rectangle::intersectsLine(const Line &i) const
{
  return
    contains(i.u) ||
    contains(i.v) ||
    i.intersects(Line(l, b, r, b)) ||
    i.intersects(Line(r, b, r, t)) ||
    i.intersects(Line(r, t, l, t)) ||
    i.intersects(Line(l, t, l, b));
}

Geometry::Polygon::Polygon(Point *p, int cc) : points(p), c(cc), normCount(0), norm(0) {}
Geometry::Polygon::~Polygon() { delete [] norm;}
void Geometry::Polygon::boundingBox(Rectangle &b) const
{
  b.l = b.r = points[0].x;
  b.b = b.t = points[0].y;
  for (int i = 1; i < c; ++i)
    {
      b.l = Math::min(b.l, points[i].x);
      b.b = Math::min(b.b, points[i].y);
      b.r = Math::max(b.r, points[i].x);
      b.t = Math::max(b.t, points[i].y);
    }
}
 
bool Geometry::Polygon::contains(const Point &p, Coord bloat) const
{
  if (normCount == 0)
    {
//       Polygon &self = *(Polygon*)this;
      Polygon &self = *const_cast<Polygon *>(this);
      self.normalize();
    }
 
  int count = 0;
  Point p0(Coord(0), Coord(0));
  bool cury_sign = norm[0].y >= p.y;
 
  for (int i = 0; i < normCount - 2; ++i)
    {
      Line l(norm[i].x - p.x, norm[i].y - p.y, norm[i+1].x - p.x, norm[i+1].y - p.y);
 
      if (l.contains(p0, bloat)) return true;
      bool nexty_sign = l.v.y >= 0.;
 
      if (nexty_sign != cury_sign)
	{
	  bool curx_sign = l.u.x >= Coord(0);
	  bool nextx_sign = l.v.x >= Coord(0);
 
	  if (curx_sign && nextx_sign)
	    {
	      ++count;
	    }
	  else if (curx_sign || nextx_sign)
	    {
	      Coord dx = l.v.x - l.u.x;
	      Coord dy = l.v.y - l.u.y;
 
	      if (dy >= Coord(0))
		{
		  if (l.u.x * dy > l.u.y * dx)
		    ++count;
		}
	      else
		{
		  if (l.u.x * dy < l.u.y * dx)
		    ++count;
		}
	    }
	}
      cury_sign = nexty_sign;
    }
  return count % 2 == 1;
}
 
bool Geometry::Polygon::intersects(const Line &l) const
{
  Rectangle b;
  bool intersects = false;
 
  if (normCount == 0)
    {
      Polygon& self = *const_cast<Polygon *>(this);
      self.normalize();
    }
 
  boundingBox(b);
  if (b.intersects(l))
    {
      Polygon p(norm_, normCount_ - 1);
      intersects = p.intersects(l) || contains(l.u, Coord(0)) || contains(l.v, Coord(0));
    }
 
  return intersects;
}
 
bool Geometry::Polygon::intersects(const Rectangle &ub) const
{
  Rectangle b;
  boundingBox(b);
  if (! b.intersects(ub))
    return false;
  if (b.within(ub))
    return true;
 
  Line bottom(ub.l, ub.b, ub.r, ub.b);
  if (intersects(bottom))
    return true;
 
  Line right(ub.r, ub.b, ub.r, ub.t);
  if (intersects(right))
    return true;
 
  Line top(ub.r, ub.t, ub.l, ub.t);
  if (intersects(top))
    return true;
 
  Line left(ub.l, ub.t, ub.l, ub.b);
  return intersects(left);
}
 
bool Geometry::Polygon::intersects(const Polygon &p) const
{
  int count = p.count();
  if ((count > 0) && contains(p[0], 0.))
    return true;
  if ((c > 0) && p.contains(points[0], 0.))
    return true;
  for (int i = 0; i < count; ++i)
    {
      if (intersects(Line(p[i], p[(i + 1) % count])))
	return true;
    }
  return false;
}
 
static int LowestLeft(const Geometry::Point *points, int count)
{
  int lowestLeft = 0;
  Coord lx = points[0].x;
  Coord ly = points[0].y;
  for (int i = 1; i < count; ++i)
    {
      if (points[i].y < ly || (points[i].y == ly && points[i].x < lx))
	{
	  lowestLeft = i;
	  lx = points[i].x;
	  ly = points[i].y;
	}
    }
  return lowestLeft;
}

void Geometry::Polygon::normalize()
{
  if (c != 0)
    {
      register int i, newcount = 1;
      int lowestLeft, limit = c;
 
      if (points[0].x == points[c - 1].x && points[0].y == points[c - 1].y) --limit;
      lowestLeft = LowestLeft(points, limit);
      normCount = limit + 2;
      norm = new Point[normCount];
 
      for (i = lowestLeft; i < limit; ++i, ++newcount)
	{
	  norm[newcount].x = points[i].x;
	  norm[newcount].y = points[i].y;
	}
      for (i = 0; i < lowestLeft; ++i, ++newcount)
	{
	  norm[newcount].x = points[i].x;
	  norm[newcount].y = points[i].y;
	}
 
      norm[newcount].x = norm[1].x;
      norm[newcount].y = norm[1].y;
      --newcount;
      norm[0].x = norm[newcount].x;
      norm[0].y = norm[newcount].y;
    }
}
