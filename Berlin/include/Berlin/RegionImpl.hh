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
#ifndef _RegionImpl_hh
#define _RegionImpl_hh

#include <Warsaw/Region.hh>

class RegionImpl : public virtual _sk_Region
{
public:
  RegionImpl();
  RegionImpl(Region_ptr, Transform_ptr);
  virtual ~RegionImpl();

  virtual CORBA::Boolean defined();
  virtual CORBA::Boolean contains(const Vertex &);
  virtual CORBA::Boolean containsPlane(const Vertex &, Axis a);
  virtual CORBA::Boolean intersects(Region_ptr);
  virtual void copy(Region_ptr);
  virtual void mergeIntersect(Region_ptr);
  virtual void mergeUnion(Region_ptr);
  virtual void subtract(Region_ptr);
  virtual void applyTransform(Transform_ptr);
  virtual void bounds(Vertex &, Vertex &);
  virtual void center(Vertex &);
  virtual void origin(Vertex &);
  virtual void span(Axis, Region::Allotment &);
  virtual void outline(Path *&);
public:
  bool valid;
  Vertex lower, upper;
  Alignment xalign, yalign, zalign;

  static void mergeMin(Vertex &, const Vertex &);
  static void mergeMax(Vertex &, const Vertex &);
  static Coord spanAlign(Coord, Coord, Coord);
  static Coord spanOrigin(Coord, Coord, Coord);
};

#endif /* _RegionImpl_hh */
