/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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
#ifndef _Compositor_hh
#define _Compositor_hh

#include <Warsaw/config.hh>
#include <Warsaw/Graphic.hh>
#include <Warsaw/Region.hh>

declare_corba_ptr_type(DrawingKit)

class RegionImpl;

class Compositor
//. this is a strategy object for adjusting text layouts to compensate for font
//. misses or hinting. It plays a very similar role to a LayoutManager.
{
public:
  typedef RegionImpl **Allocations;
  virtual ~Compositor() {}
  virtual void request(long n, Graphic::Requisition *requests, DrawingKit_ptr dk, Graphic::Requisition &result) = 0;
  virtual void allocate(Graphic::Requisition &total,
			long n, Graphic::Requisition *requests, DrawingKit_ptr dk, Region_ptr given, Allocations result) = 0;
  static void setSpan(RegionImpl *r, Axis a, Coord origin, Coord length, Alignment align);
};

class LRCompositor : public Compositor
//. left to right compositor -- aligns vertically, tiles left to right
//. for now it ignores the DrawingKit parameter and does no compensation
//. no line breaking
{
public:
  virtual void request(long, Graphic::Requisition *, DrawingKit_ptr, Graphic::Requisition &);
  virtual void allocate(Graphic::Requisition &, long, Graphic::Requisition *, DrawingKit_ptr, Region_ptr, Allocations);    
  static Coord computeLength(const Graphic::Requirement &, const Region::Allotment &);
  static Coord computeSqueeze(const Graphic::Requirement &, Coord);
};

#endif
