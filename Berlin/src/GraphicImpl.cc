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
#include "Berlin/GraphicImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/AllocationImpl.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/Math.hh"
#include "Warsaw/Traversal.hh"

static double tol = 0.05;

static bool rotated (Transform_ptr t)
{
  Transform::Matrix m;
  t->storeMatrix(m);
  return (!Math::equal(m[0][1], 0., tol) || !Math::equal(m[1][0], 0., tol));
}

static void setSpan(RegionImpl &r, Axis a, Coord origin, Coord length)
{
  Coord begin = origin;
  Coord end = begin + length;
  r.valid = true;
  switch (a)
    {
    case xaxis:
      r.lower.x = begin;
      r.upper.x = end;
      break;
    case yaxis:
      r.lower.y = begin;
      r.upper.y = end;
      break;
    case zaxis:
      r.lower.z = begin;
      r.upper.z = end;
      break;
    }
}

static double computeSqueeze(const Graphic::Requirement &r, Coord length)
{
  double f;
  Coord nat = r.natural;
  if (length > nat && r.maximum > nat)
    f = (length - nat) / (r.maximum - nat);
  else if (length < nat && r.minimum < nat)
    f = (nat - length) / (nat - r.minimum);
  else
    f = 0;
  return f;
}

static void computeAllocations(Axis a, Graphic::Requisition &total,
			       CORBA::ULong n, Graphic::Requisition *requests, Region &given,
			       RegionImpl* result)
{
  Graphic::Requirement *r;
  Region::Allotment s;
  r = GraphicImpl::requirement(total, a);
  given.span(a, s);
  Coord length = s.end - s.begin;
  bool growing = length > r->natural;
  bool shrinking = length < r->natural;
  double f = computeSqueeze(*r, length);
  Coord p = 0.0;
  for (CORBA::ULong i = 0; i < n; i++)
    {
      r = GraphicImpl::requirement(requests[i], a);
      Coord cspan = r->natural;
      if (growing)
	cspan += Coord(f * (r->maximum - r->natural));
      else if (shrinking)
	cspan -= Coord(f * (r->natural - r->minimum));
      setSpan(result[i], a, p, cspan);
      p += cspan;
    }
}

static void compensate (double a, double &x, double &y)
{
  if (a > 0.0)
    {
      if (Math::equal(x, 0.0, 1.0e-6)) y = a * x;
      else
	{
	  double aspect = y/x;
	  if (aspect > a) y = a * x;
	  else if (aspect < a) x = y / a;
	}
    }
}

static void flexibleTransformRequest(Graphic::Requisition &req, Transform_ptr t)
{
  if (t->Identity()) return;
  if (t->Translation())
    {
      Transform::Matrix mat;
      t->storeMatrix(mat);
      Coord tx = mat[2][0];
      Coord ty = mat[2][1];

      req.x.align = -(-req.x.align * req.x.natural + tx) / req.x.natural;
      req.y.align = -(-req.y.align * req.y.natural + ty) / req.y.natural;
      return;
    }
  
  RegionImpl nat, maxi, mini;

  nat.xalign = req.x.align;
  nat.lower.x = -req.x.align * req.x.natural;
  nat.upper.x = nat.lower.x + req.x.natural;
  nat.yalign = req.y.align;
  nat.lower.y = -req.y.align * req.y.natural;
  nat.upper.y = nat.lower.y + req.y.natural;
  nat.lower.z = nat.upper.z = 0.0;
  nat.valid = true;

  maxi.xalign = req.x.align;
  maxi.lower.x = -req.x.align * req.x.maximum;
  maxi.upper.x = maxi.lower.x + req.x.maximum;
  maxi.yalign = req.y.align;
  maxi.lower.y = -req.y.align * req.y.maximum;
  maxi.upper.y = maxi.lower.y + req.y.maximum;
  maxi.lower.z = maxi.upper.z = 0.0;
  maxi.valid = true;

  mini.xalign = req.x.align;
  mini.lower.x = -req.x.align * req.x.minimum;
  mini.upper.x = mini.lower.x + req.x.minimum;
  mini.yalign = req.y.align;
  mini.lower.y = -req.y.align * req.y.minimum;
  mini.upper.y = mini.lower.y + req.y.minimum;
  mini.lower.z = mini.upper.z = 0.0;
  mini.valid = true;

  nat.applyTransform(t);
  maxi.applyTransform(t);
  mini.applyTransform(t);

  req.x.defined = true;
  req.x.natural = nat.upper.x - nat.lower.x;
  req.x.maximum = maxi.upper.x - maxi.lower.x;
  req.x.minimum = mini.upper.x - mini.lower.x;
  if (!Math::equal(req.x.natural, 0.0, 1.0e-6))
    req.x.align = -nat.lower.x / req.x.natural;
  else
    req.x.align = 0.0;

  req.y.defined = true;
  req.y.natural = nat.upper.y - nat.lower.y;
  req.y.maximum = maxi.upper.y - maxi.lower.y;
  req.y.minimum = mini.upper.y - mini.lower.y;
  if (!Math::equal(req.y.natural, 0.0, 1.0e-6))
    req.y.align = -nat.lower.y / req.y.natural;
  else
    req.y.align = 0.0;

  req.z.defined = false;
}

static void fixedTransformRequest(Graphic::Requisition &req, Transform_ptr t)
{
  if (t->Identity()) return;
  if (t->Translation())
    {
      Transform::Matrix mat;
      t->storeMatrix(mat);
      Coord tx = mat[2][0];
      Coord ty = mat[2][1];

      req.x.align = -(-req.x.align * req.x.natural + tx) / req.x.natural;
      req.y.align = -(-req.y.align * req.y.natural + ty) / req.y.natural;
      return;
    }

  RegionImpl nat;

  nat.xalign = req.x.align;
  nat.lower.x = -req.x.align * req.x.natural;
  nat.upper.x = nat.lower.x + req.x.natural;
  nat.yalign = req.y.align;
  nat.lower.y = -req.y.align * req.y.natural;
  nat.upper.y = nat.lower.y + req.y.natural;
  nat.lower.z = nat.upper.z = Coord(0);
  nat.valid = true;

  nat.applyTransform(t);

  Coord x_nat_lead = -nat.lower.x;
  Coord x_nat_trail = nat.upper.x;

  Coord y_nat_lead = -nat.lower.y;
  Coord y_nat_trail = nat.upper.y;

  GraphicImpl::requireLeadTrail(req.x, x_nat_lead, x_nat_lead, x_nat_lead, 
				x_nat_trail, x_nat_trail, x_nat_trail);
  GraphicImpl::requireLeadTrail(req.y, y_nat_lead, y_nat_lead, y_nat_lead, 
				y_nat_trail, y_nat_trail, y_nat_trail);
}

/*****************************************************/

GraphicImpl::GraphicImpl() {}
GraphicImpl::~GraphicImpl() {}

Graphic_ptr GraphicImpl::body() { return Graphic::_nil();}
void GraphicImpl::body(Graphic_ptr) {}
void GraphicImpl::append(Graphic_ptr) {}
void GraphicImpl::prepend(Graphic_ptr) {}

void GraphicImpl::addParent(Graphic_ptr parent)
{
  Guard guard(parentMutex);
  parents.insert(parents.end(), pinfo(Graphic::_duplicate(parent), 1));
}

void GraphicImpl::removeParent(Graphic_ptr parent)
{
  Guard guard(parentMutex);
  plist_t::iterator i = parents.find(pinfo(parent));
  if (!--(*i).edges) parents.erase(i);
}

Transform_ptr GraphicImpl::transformation() { return Transform::_nil();}
void GraphicImpl::request(Requisition &) {}
void GraphicImpl::extension(const Allocation::Info &a, Region_ptr r) { GraphicImpl::defaultExtension(a, r);}
void GraphicImpl::shape(Region_ptr) {}

void GraphicImpl::traverse(Traversal_ptr t) { t->visit(this);}
void GraphicImpl::draw(DrawTraversal_ptr) {}
void GraphicImpl::pick(PickTraversal_ptr) {}

void GraphicImpl::allocate(Graphic_ptr, Allocation_ptr a) { allocateParents(a);}
void GraphicImpl::needRedraw()
{
  AllocationImpl *allocation = new AllocationImpl;
  allocation->_obj_is_ready(_boa());
  allocateParents(allocation->_this());
  for (CORBA::Long i = 0; i < allocation->size(); i++)
    {
      Allocation::Info *a = allocation->get(i);
      if (!CORBA::is_nil(a->damaged))
	{
	  RegionImpl *region = new RegionImpl;
	  region->_obj_is_ready(_boa());
	  extension(*a, region->_this());
	  if (region->valid) a->damaged->extend(region->_this());
	  region->_dispose();
	}
    }
  allocation->_dispose();
}

void GraphicImpl::needRedrawRegion(Region_ptr r)
{
  if (r->defined())
    {
      AllocationImpl *allocation = new AllocationImpl;
      allocation->_obj_is_ready(_boa());
      allocateParents(allocation->_this());
      RegionImpl *dr = new RegionImpl;
      dr->_obj_is_ready(_boa());
      for (CORBA::Long i = 0; i < allocation->size(); i++)
	{
	  Allocation::Info *a = allocation->get(i);
 	  if (!CORBA::is_nil(a->damaged))
 	    {
 	      dr->copy(r);
 	      dr->applyTransform(a->transformation);
 	      a->damaged->extend(dr->_this());
 	    }
	}
      dr->_dispose();
      allocation->_dispose();
    }
}

void GraphicImpl::needResize()
{
  Guard guard(parentMutex);
  for (plist_t::iterator i = parents.begin(); i != parents.end(); i++)
    (*i).parent->needResize();
}

void GraphicImpl::initRequisition(Graphic::Requisition &r)
{
  r.x.defined = false;
  r.y.defined = false;
  r.z.defined = false;
  r.preserve_aspect = false;
}

void GraphicImpl::defaultRequisition(Graphic::Requisition &r)
{
  Coord zero = Coord(0.0);
  require(r.x, zero, zero, zero, zero);
  require(r.y, zero, zero, zero, zero);
  require(r.z, zero, zero, zero, zero);
  r.preserve_aspect = false;
}

void GraphicImpl::require(Graphic::Requirement &r, Coord natural, Coord stretch, Coord shrink, Coord alignment)
{
  r.defined = true;
  r.natural = natural;
  r.maximum = natural + stretch;
  r.minimum = natural - shrink;
  r.align = alignment;
}

void GraphicImpl::requireLeadTrail(Graphic::Requirement &r,
				   Coord natural_lead, Coord max_lead, Coord min_lead,
				   Coord natural_trail, Coord max_trail, Coord min_trail)
{
  Coord zero = Coord(0);
  r.defined = true;
  natural_lead = Math::max(min_lead, Math::min(max_lead, natural_lead));
  max_lead = Math::max(max_lead, natural_lead);
  min_lead = Math::min(min_lead, natural_lead);
  natural_trail = Math::max(min_trail, Math::min(max_trail, natural_trail));
  max_trail = Math::max(max_trail, natural_trail);
  min_trail = Math::min(min_trail, natural_trail);
  r.natural = natural_lead + natural_trail;
  if (natural_lead == zero)
    {
      r.minimum = min_trail;
      r.maximum = max_trail;
      r.align = Coord(0);
    }
  else if (natural_trail == zero)
    {
      r.minimum = min_lead;
      r.maximum = max_lead;
      r.align = Coord(1);
    }
  else
    {
      r.minimum = r.natural * Math::max(min_lead / natural_lead, min_trail / natural_trail);
      r.maximum = r.natural * Math::min(max_lead / natural_lead, max_trail / natural_trail);
      if (r.natural == zero)
	r.align = zero;
      else
	r.align = natural_lead / r.natural;
    }
}

Graphic::Requirement *GraphicImpl::requirement(Graphic::Requisition &r, Axis a)
{
  Graphic::Requirement *req;
  switch (a)
    {
    case xaxis: req = &r.x; break;
    case yaxis: req = &r.y; break;
    case zaxis: req = &r.z; break;
    default: req = 0; break;
    }
  return req;
}

void GraphicImpl::defaultExtension (const Allocation::Info &a, Region_ptr r)
{
  if (!CORBA::is_nil(a.allocation))
    {
      if (CORBA::is_nil(a.transformation))
	r->mergeUnion(a.allocation);
      else
	{
	  RegionImpl *tmp = new RegionImpl(a.allocation, a.transformation);
	  tmp->_obj_is_ready(CORBA::BOA::getBOA());
	  r->mergeUnion(tmp->_this());
	  tmp->_dispose();
	}
    }
}

RegionImpl GraphicImpl::naturalAllocation (Graphic_ptr g)
{
  Requisition r;
  GraphicImpl::initRequisition(r);
  RegionImpl nat;

  g->request(r);
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
      nat.lower.z = -r.z.align * r.z.natural;
      nat.upper.z = nat.lower.z + r.z.natural;
      nat.zalign = r.z.align;
      nat.valid = true;
    }
  return nat;
}

void GraphicImpl::transformRequest (Graphic::Requisition& req, Transform_ptr tx)
{
  if (CORBA::is_nil(tx) || tx->Identity()) { return;}
  if (Math::equal(req.x.natural, req.x.maximum, tol) &&
      Math::equal(req.y.natural, req.y.maximum, tol) &&
      Math::equal(req.x.natural, req.x.minimum, tol) &&
      Math::equal(req.y.natural, req.y.minimum, tol))
    fixedTransformRequest(req, tx);
  else
    flexibleTransformRequest(req, tx);
}

Vertex GraphicImpl::transformAllocate(RegionImpl &region, const Graphic::Requisition &req, Transform_ptr t)
{
  Vertex delta;
  delta.x = Coord(0); delta.y = Coord(0); delta.z = Coord(0);
  if (!rotated(t))
    {
      TransformImpl tx;
      tx.copy(t);
      tx.invert();
      region.applyTransform(&tx);
      region.xalign = req.x.align;
      region.yalign = req.y.align;
      region.zalign = req.z.align;
    }
  else
    {
      Vertex center;
      double x_len, y_len;
      center.x = (region.lower.x + region.upper.x) * 0.5;
      center.y = (region.lower.y + region.upper.y) * 0.5;

      Transform::Matrix m;
      t->storeMatrix(m);

      Graphic::Requisition r[2], total;
      GraphicImpl::initRequisition(r[0]);	
      GraphicImpl::initRequisition(r[1]);	
      GraphicImpl::initRequisition(total);	
   
      RegionImpl a[2];
      double a0 = -1; double a1 = -1;
      if (!Math::equal(m[0][0], 0.0, tol)) a0 = Math::abs(m[0][1] / m[0][0]);
      if (!Math::equal(m[1][0], 0.0, tol)) a1 = Math::abs(m[1][1] / m[1][0]);

      r[0].x.natural = Math::abs(req.x.natural*m[0][0]);
      r[0].x.maximum = Math::abs(req.x.maximum*m[0][0]);
      r[0].x.minimum = Math::abs(req.x.minimum*m[0][0]);
      r[0].x.defined = true;
      r[0].y.natural = Math::abs(req.x.natural*m[0][1]);
      r[0].y.maximum = Math::abs(req.x.maximum*m[0][1]);
      r[0].y.minimum = Math::abs(req.x.minimum*m[0][1]);
      r[0].y.defined = true;

      r[1].x.natural = Math::abs(req.y.natural*m[1][0]);
      r[1].x.maximum = Math::abs(req.y.maximum*m[1][0]);
      r[1].x.minimum = Math::abs(req.y.minimum*m[1][0]);
      r[1].x.defined = true;
      r[1].y.natural = Math::abs(req.y.natural*m[1][1]);
      r[1].y.maximum = Math::abs(req.y.maximum*m[1][1]);
      r[1].y.minimum = Math::abs(req.y.minimum*m[1][1]);
      r[1].y.defined = true;

      total.x.natural = r[0].x.natural + r[1].x.natural;
      total.x.maximum = r[0].x.maximum + r[1].x.maximum;
      total.x.minimum = r[0].x.minimum + r[1].x.minimum;
      total.x.defined = true;
      total.y.natural = r[0].y.natural + r[1].y.natural;
      total.y.maximum = r[0].y.maximum + r[1].y.maximum;
      total.y.minimum = r[0].y.minimum + r[1].y.minimum;
      total.y.defined = true;

      computeAllocations(xaxis, total, 2, r, region, a);
      computeAllocations(yaxis, total, 2, r, region, a);

      double x0, y0, x1, y1;
      x0 = a[0].upper.x - a[0].lower.x;
      y0 = a[0].upper.y - a[0].lower.y;
      x1 = a[1].upper.x - a[1].lower.x;
      y1 = a[1].upper.y - a[1].lower.y;
      compensate(a0, x0, y0);
      compensate(a1, x1, y1);

      x_len = sqrt(x0*x0 + y0*y0)/sqrt(m[0][0]*m[0][0]+m[0][1]*m[0][1]);
      y_len = sqrt(x1*x1 + y1*y1)/sqrt(m[1][0]*m[1][0]+m[1][1]*m[1][1]);

      region.xalign = req.x.align;
      region.yalign = req.y.align;
      region.zalign = req.z.align;

      t->inverseTransformVertex(center);
      delta.x = Coord(center.x - x_len*0.5 - region.lower.x);
      delta.y = Coord(center.y - y_len*0.5 - region.lower.y);

      region.upper.x = Coord(region.lower.x + x_len);
      region.upper.y = Coord(region.lower.y + y_len);
    }
  return delta;
}

void GraphicImpl::allocateParents(Allocation_ptr a)
{
  Guard guard(parentMutex);
  for (plist_t::iterator i = parents.begin(); i != parents.end(); i++)
    (*i).parent->allocate(_this(), a);
}
