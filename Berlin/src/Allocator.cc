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
#include "Berlin/AllocationImpl.hh"
#include "Warsaw/Traversal.hh"

Allocator::Allocator()
{
  requested = false;
  nat = new RegionImpl;
  nat->_obj_is_ready(CORBA::BOA::getBOA());
  ext = new RegionImpl;
  ext->_obj_is_ready(CORBA::BOA::getBOA());
}

Allocator::~Allocator()
{ 
  nat->_dispose();
  ext->_dispose();
}

void Allocator::request(Requisition &r)
{
  updateRequisition();
  r = req;
}

void Allocator::traverse(Traversal_ptr t)
{
  updateRequisition();
  Region_var a = t->allocation();
  if (!CORBA::is_nil(a))
    t->traverseChild(body(), a, Transform::_nil());
  else
    t->traverseChild(body(), nat, Transform::_nil());
}

void Allocator::needResize()
{
  AllocationImpl *allocation = new AllocationImpl;
  allocation->_obj_is_ready(_boa());
  allocateParents(allocation->_this());
  RegionImpl *region = new RegionImpl;
  region->_obj_is_ready(_boa());
  if (ext->valid) region->copy(ext);
  requested = false;
  updateRequisition();
  if (ext->valid) region->mergeUnion(ext);
  if (region->valid) needDamage(region, allocation);
  allocation->_dispose();
}

void Allocator::allocateChild(Allocation::Info &i)
{
  updateRequisition();
  i.allocation->copy(nat);
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
      requested = r.x.defined && r.y.defined; // && r.z.defined;
      ext->valid = false;
      Allocation::Info a;
      MonoGraphic::extension(a, ext);
    }
}

void Allocator::needDamage(RegionImpl *ext, Allocation_ptr allocation)
{
  RegionImpl *region = new RegionImpl;
  region->_obj_is_ready(_boa());
  for (long i = 0; i < allocation->size(); i++)
    {
      Allocation::Info *info = allocation->get(i);
      if (!CORBA::is_nil(info->damaged))
 	{
 	  region->copy(ext);
	  region->applyTransform(info->transformation);
  	  info->damaged->extend(region->_this());
 	}
    }
}

TransformAllocator::TransformAllocator(Alignment xp, Alignment yp, Alignment zp, Alignment xc, Alignment yc, Alignment zc)
  : xparent(xp), yparent(yp), zparent(zp), xchild(xc), ychild(yc), zchild(zc)
{}

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

void TransformAllocator::allocateChild(Allocation::Info &i)
{
  Vertex lower, upper, delta;
  TransformImpl *tx = new TransformImpl;
  tx->_obj_is_ready(_boa());

  Allocator::allocateChild(i);
  i.allocation->bounds(lower, upper);
  computeDelta(lower, upper, delta);
  tx->translate(delta);
  i.transformation->premultiply(tx->_this());
  i.allocation->copy(nat);
  tx->_dispose();
}

void TransformAllocator::traverse(Traversal_ptr t)
{
  TransformImpl *tx = new TransformImpl;
  tx->_obj_is_ready(_boa());
  updateRequisition();
  Vertex lower, upper, v;
  t->bounds(lower, upper, v);
  computeDelta(lower, upper, v);
  tx->translate(v);
  t->traverseChild(body(), nat->_this(), tx->_this());
  tx->_dispose();
}

void TransformAllocator::computeDelta(const Vertex &lower, const Vertex &upper, Vertex &delta)
{
  delta.x = (lower.x - nat->lower.x +
	     xparent * (upper.x - lower.x) -
	     xchild * (nat->upper.x - nat->lower.x));
  delta.y = (lower.y - nat->lower.y +
	     yparent * (upper.y - lower.y) -
	     ychild * (nat->upper.y - nat->lower.y));
  delta.z = (lower.z - nat->lower.z +
	     zparent * (upper.z - lower.z) -
	     zchild * (nat->upper.z - nat->lower.z));
}
