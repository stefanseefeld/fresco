/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _RegionImpl_hh
#define _RegionImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Region.hh>
#include <Berlin/ServantBase.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/Vertex.hh>
#include <Berlin/Math.hh>
#include <Berlin/Provider.hh>
#include <iostream>

class RegionImpl : public virtual POA_Warsaw::Region,
                   public virtual ServantBase
{
public:
  RegionImpl();
  RegionImpl(const RegionImpl &);
  RegionImpl(Warsaw::Region_ptr);
  RegionImpl(Warsaw::Region_ptr, Warsaw::Transform_ptr);
  virtual ~RegionImpl();

  virtual CORBA::Boolean defined();
  virtual CORBA::Boolean contains(const Warsaw::Vertex &);
  virtual CORBA::Boolean containsPlane(const Warsaw::Vertex &, Warsaw::Axis a);
  virtual CORBA::Boolean intersects(Warsaw::Region_ptr);
  virtual void copy(Warsaw::Region_ptr);
  virtual void mergeIntersect(Warsaw::Region_ptr);
  virtual void mergeUnion(Warsaw::Region_ptr);
  virtual void subtract(Warsaw::Region_ptr);
  virtual void applyTransform(Warsaw::Transform_ptr);
  virtual void bounds(Warsaw::Vertex &, Warsaw::Vertex &);
  virtual void center(Warsaw::Vertex &);
  virtual void origin(Warsaw::Vertex &);
  virtual void span(Warsaw::Axis, Warsaw::Region::Allotment &);
  virtual void outline(Warsaw::Path_out);

  void clear();

public:
  void normalize(Warsaw::Vertex &);
  void normalize(Warsaw::Transform_ptr);
  bool valid;
  Warsaw::Vertex lower, upper;
  Warsaw::Alignment xalign, yalign, zalign;

  static void mergeMin(Warsaw::Vertex &, const Warsaw::Vertex &);
  static void mergeMax(Warsaw::Vertex &, const Warsaw::Vertex &);
  static Warsaw::Coord spanAlign(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  static Warsaw::Coord spanOrigin(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
};

inline Warsaw::Coord RegionImpl::spanOrigin(Warsaw::Coord lower, Warsaw::Coord upper, Warsaw::Coord align)
{
  Warsaw::Coord orig;
  if (Math::equal(lower, upper, 1e-4)) orig = 0.;
  else orig = lower + align * (upper - lower);
  return orig;
}

inline Warsaw::Coord RegionImpl::spanAlign(Warsaw::Coord lower, Warsaw::Coord upper, Warsaw::Coord origin)
{
  Warsaw::Coord s;
  if (Math::equal(lower, upper, 1e-4)) s = 0.;
  else s = (origin - lower) / (upper - lower);
  return s;
}

inline void RegionImpl::mergeMin(Warsaw::Vertex &v0, const Warsaw::Vertex &v)
{
  v0.x = Math::min(v0.x, v.x);
  v0.y = Math::min(v0.y, v.y);
  v0.z = Math::min(v0.z, v.z);
}

inline void RegionImpl::mergeMax(Warsaw::Vertex &v0, const Warsaw::Vertex &v)
{
  v0.x = Math::max(v0.x, v.x);
  v0.y = Math::max(v0.y, v.y);
  v0.z = Math::max(v0.z, v.z);
}

inline void RegionImpl::normalize(Warsaw::Vertex &o)
{
  o.x = spanOrigin(lower.x, upper.x, xalign);
  o.y = spanOrigin(lower.y, upper.y, yalign);
  o.z = spanOrigin(lower.z, upper.z, zalign);
  lower -= o;
  upper -= o;
}

inline void RegionImpl::normalize(Warsaw::Transform_ptr t)
{
  Warsaw::Vertex o;
  normalize(o);
  if (!CORBA::is_nil(t)) t->translate(o);
}

ostream &operator << (ostream &, const RegionImpl &);

#endif
