/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
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
#include "Berlin/RegionImpl.hh"
#include "Warsaw/Damage.hh"

Allocator::Allocator()
{
  requested = false;
  natural = new RegionImpl;
  natural->_obj_is_ready(CORBA::BOA::getBOA());
  extension = new RegionImpl;
  extension->_obj_is_ready(CORBA::BOA::getBOA());
}

Allocator::~Allocator()
{ 
  natural->_dispose();
  extension->_dispose();
}

void Allocator::request(Requisition &r)
{
  updateRequisition();
  r = requisition;
}

void Allocator::traverse(Traversal_ptr t)
{
  Traversal_var traversal = t;
  updateRequisition();
  Region_var a = traversal->allocation();
  if (!CORBA::is_nil(a))
    traversal->traverseChild(body(), Region::_duplicate(a), Transform::_nil());
  else
    traversal->traverseChild(body(), natural->_this(), Transform::_nil());
}

void Allocator::needResize()
{
  AllocationImpl *allocation = new AllocationImpl;
  allocation->_obj_is_ready(_boa());
  allocateParents(allocation->_this());
  RegionImpl *region = new RegionImpl;
  region->_obj_is_ready(_boa());
  if (extension->valid) region->copy(extension->_this());
  requested = false;
  updateRequisition();
  if (extension->valid) region->mergeUnion(extension->_this());
  if (region->valid) needDamage(region, allocation);
  allocation->_dispose();
}

void Allocator::allocateChild(Allocation::Info &i)
{
  updateRequisition();
  i.allocation->copy(natural->_this());
}

static void naturalAllocation(Graphic::Requisition &r, RegionImpl &natural)
{
  if (r.x.defined)
    {
      natural.xalign = r.x.align;
      natural.lower.x = -r.x.align * r.x.natural;
      natural.upper.x = natural.lower.x + r.x.natural;
      natural.valid = true;
    }
  if (r.y.defined)
    {
      natural.yalign = r.y.align;
      natural.lower.y = -r.y.align * r.y.natural;
      natural.upper.y = natural.lower.y + r.y.natural;
      natural.valid = true;
    }
  if (r.z.defined)
    {
      natural.zalign = r.z.align;
      natural.lower.z = -r.z.align * r.z.natural;
      natural.upper.z = natural.lower.z + r.z.natural;
      natural.valid = true;
    }
}

void Allocator::updateRequisition()
{
  if (!requested)
    {
      Graphic::Requisition r;
      GraphicImpl::initRequisition(r);
      MonoGraphic::request(r);
      requisition = r;
      ::naturalAllocation(requisition, *natural);
      requested = r.x.defined && r.y.defined; // && r.z.defined;
      extension->valid = false;
      Allocation::Info info;
      MonoGraphic::extension(info, extension->_this());
    }
}

void Allocator::needDamage(RegionImpl *e, Allocation_ptr a)
{
  Allocation_var allocation = a;
  RegionImpl *region = new RegionImpl;
  region->_obj_is_ready(_boa());
  for (long i = 0; i < allocation->size(); i++)
    {
      Allocation::Info_var info = allocation->get(i);
      if (!CORBA::is_nil(info->damaged))
 	{
 	  region->copy(e->_this());
	  region->applyTransform(Transform::_duplicate(info->transformation));
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
  requisition.x.maximum = fil;
  requisition.x.minimum = zero;
  requisition.y.maximum = fil;
  requisition.y.minimum = zero;
  requisition.z.maximum = fil;
  requisition.z.minimum = zero;
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
  i.allocation->copy(natural);
  tx->_dispose();
}

void TransformAllocator::traverse(Traversal_ptr t)
{
  Traversal_var traversal = t;
  TransformImpl *tx = new TransformImpl;
  tx->_obj_is_ready(_boa());
  updateRequisition();
  Vertex lower, upper, v;
  traversal->bounds(lower, upper, v);
  computeDelta(lower, upper, v);
  tx->translate(v);
  traversal->traverseChild(body(), natural->_this(), tx->_this());
  tx->_dispose();
}

void TransformAllocator::computeDelta(const Vertex &lower, const Vertex &upper, Vertex &delta)
{
  delta.x = (lower.x - natural->lower.x + xparent * (upper.x - lower.x) -
	     xchild * (natural->upper.x - natural->lower.x));
  delta.y = (lower.y - natural->lower.y + yparent * (upper.y - lower.y) -
	     ychild * (natural->upper.y - natural->lower.y));
  delta.z = (lower.z - natural->lower.z + zparent * (upper.z - lower.z) -
	     zchild * (natural->upper.z - natural->lower.z));
}
