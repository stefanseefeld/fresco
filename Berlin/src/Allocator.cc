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
#include "Berlin/Allocator.hh"
#include "Berlin/TransformImpl.hh"

Allocator::Allocator()
{
  requested = false;
  nat = new RegionImpl;
  ext = new RegionImpl;
}

Allocator::~Allocator()
{ 
  CORBA::release(nat);
  CORBA::release(ext);
}

void Allocator::request(Requisition &r)
{
  updateRequisition();
  r = req;
}

void Allocator::allocations(AllocationInfoSeq &a)
{
  updateRequisition();
  MonoGraphic::allocations(a);
}

void Allocator::allocateChild(Graphic::AllocationInfo &i)
{
  updateRequisition();
  if (CORBA::is_nil(i.allocation))
    i.allocation = new RegionImpl;
  i.allocation->copy(nat);
}

void Allocator::traverse(Traversal_ptr t)
{
//   updateRequisition();
//   Region_var a = t->allocation();
//   if (!CORBA::is_nil(a))
//     t->traverseChild(offset, a);
//   else
//     t->traverseChild(offset, nat);
}

void Allocator::needResize()
{
  Graphic::AllocationInfoSeq alist;
  allocations(alist);
  RegionImpl region;
  if (ext->valid) region.copy(ext);
  requested = false;
  updateRequisition();
  if (ext->valid) region.mergeUnion(ext);
  if (region.valid) needDamage(&region, alist);
  MonoGraphic::needResize();
}

static void naturalAllocation(Graphic::Requisition &r, RegionImpl &nat)
{
  if (r.x.defined)
    {
      nat.xalign = r.x.align;
      nat.lower.x = -r.x.align * r.x.natural;
      nat.upper.x = nat.lower.x + r.x.natural;
      nat.valid = true;
    }
  if (r.y.defined)
    {
      nat.yalign = r.y.align;
      nat.lower.y = -r.y.align * r.y.natural;
      nat.upper.y = nat.lower.y + r.y.natural;
      nat.valid = true;
    }
  if (r.z.defined)
    {
      nat.zalign = r.z.align;
      nat.lower.z = -r.z.align * r.z.natural;
      nat.upper.z = nat.lower.z + r.z.natural;
      nat.valid = true;
    }
}

void Allocator::updateRequisition()
{
  if (!requested)
    {
      Graphic::Requisition r;
      GraphicImpl::initRequisition(r);
      MonoGraphic::request(r);
      req = r;
      ::naturalAllocation(req, *nat);
      // FIXME: make sure every thing defines .z otherwise we'll have
      // to update things far too often ...
      requested = (r.x.defined && r.y.defined); // && r.z.defined;
      ext->valid = false;
      Graphic::AllocationInfo a;
      MonoGraphic::extension(a, ext);
    }
}

void Allocator::needDamage(RegionImpl *ext, const Graphic::AllocationInfoSeq &a)
{
  RegionImpl r;
  double dot = 1.;
  for (ulong i = 0; i < a.length(); i++)
    {
      const Graphic::AllocationInfo &info = a[i];
//       if (!CORBA::is_nil(info.damaged) && CORBA::is_nil(info.allocation))
// 	{
// 	  r.copy(ext);
// 	  if (!CORBA::is_nil(info.transformation))
// 	    r.applyTransform(info.transformation);
//  	  info.damaged->extend(&r);
// 	}
    }
}

TransformAllocator::TransformAllocator(Alignment xp, Alignment yp, Alignment zp,
				       Alignment xc, Alignment yc, Alignment zc)
{
  x_parent = xp;
  y_parent = yp;
  z_parent = zp;
  x_child = xc;
  y_child = yc;
  z_child = zc;
}

TransformAllocator::~TransformAllocator() {}

void TransformAllocator::request(Requisition &r)
{
  Allocator::request(r);
  Coord fil = Coord(1000000.0);
  Coord zero = Coord(0.0);
  r.x.maximum = fil;
  r.x.minimum = zero;
  r.y.maximum = fil;
  r.y.minimum = zero;
  r.z.maximum = fil;
  r.z.minimum = zero;
  req.x.maximum = fil;
  req.x.minimum = zero;
  req.y.maximum = fil;
  req.y.minimum = zero;
  req.z.maximum = fil;
  req.z.minimum = zero;
}

void TransformAllocator::allocateChild(Graphic::AllocationInfo &i)
{
  Vertex lower, upper, delta;
  TransformImpl tx;

  Allocator::allocateChild(i);
  if (CORBA::is_nil(i.transformation))
    i.transformation = new TransformImpl;
  i.allocation->bounds(lower, upper);
  computeDelta(lower, upper, delta);
  tx.translate(delta);
  i.transformation->premultiply(&tx);
  i.allocation->copy(nat);
}

void TransformAllocator::traverse(Traversal_ptr t)
{
//   TransformImpl tx;
//   updateRequisition();
//   Painter_var p = t->current_painter();
//   Vertex lower, upper, v;
//   t->bounds(lower, upper, v);
//   computeDelta(lower, upper, v);
//   tx.translate(v);
//   p->pushMatrix();
//   p->premultiply(&tx);
//   t->traverseChild(offset_, nat_);
//   p->pop_matrix();
}

void TransformAllocator::computeDelta(const Vertex &lower, const Vertex &upper, Vertex &delta)
{
  delta.x = (lower.x - nat->lower.x +
	     x_parent * (upper.x - lower.x) -
	     x_child * (nat->upper.x - nat->lower.x));
  delta.y = (lower.y - nat->lower.y +
	     y_parent * (upper.y - lower.y) -
	     y_child * (nat->upper.y - nat->lower.y));
  delta.z = (lower.z - nat->lower.z +
	     z_parent * (upper.z - lower.z) -
	     z_child * (nat->upper.z - nat->lower.z));
}
