/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
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
#include <Warsaw/config.hh>
#include <Warsaw/Traversal.hh>
#include <Warsaw/Screen.hh>
#include <Warsaw/IO.hh>
#include "Berlin/Providers.hh"
#include "Berlin/GraphicImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/AllocationImpl.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/Math.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/Lease.hh"
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

static double tol = 0.005;

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
  if (length > r.natural && r.maximum > r.natural)
    return (length - r.natural) / (r.maximum - r.natural);
  else if (length < r.natural && r.minimum < r.natural)
    return (r.natural - length) / (r.natural - r.minimum);
  else
    return 0.;
}

/*
 * compare a requisition (total) with a given allocation (given) and then distribute it
 * to the individual children (result) based on the individual requisitions (requests)
 */
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

static void flexibleTransformRequest(Graphic::Requisition &req, Transform_ptr t)
{
  Trace trace("flexibleTransformRequest");
  if (t->Identity()) return;
  if (t->Translation())
    {
      Transform::Matrix mat;
      t->storeMatrix(mat);
      Coord tx = mat[0][3];
      Coord ty = mat[1][3];
      Coord tz = mat[2][3];

      req.x.align = (req.x.align * req.x.natural - tx) / req.x.natural;
      req.y.align = (req.y.align * req.y.natural - ty) / req.y.natural;
      req.z.align = (req.z.align * req.z.natural - tz) / req.z.natural;
      return;
    }
  
  if (!req.z.defined)
    {
      req.z.natural = req.z.maximum = req.z.minimum = 0.;
      req.z.align = 0;
      req.z.defined = true;
    }

  RegionImpl nat, maxi, mini;

  nat.xalign = req.x.align;
  nat.lower.x = -req.x.align * req.x.natural;
  nat.upper.x = nat.lower.x + req.x.natural;
  nat.yalign = req.y.align;
  nat.lower.y = -req.y.align * req.y.natural;
  nat.upper.y = nat.lower.y + req.y.natural;
  nat.zalign = req.z.align;
  nat.lower.z = -req.z.align * req.z.natural;
  nat.upper.z = nat.lower.z + req.z.natural;
  nat.valid = true;

  maxi.xalign = req.x.align;
  maxi.lower.x = -req.x.align * req.x.maximum;
  maxi.upper.x = maxi.lower.x + req.x.maximum;
  maxi.yalign = req.y.align;
  maxi.lower.y = -req.y.align * req.y.maximum;
  maxi.upper.y = maxi.lower.y + req.y.maximum;
  maxi.zalign = req.z.align;
  maxi.lower.z = -req.z.align * req.z.maximum;
  maxi.upper.z = maxi.lower.z + req.z.maximum;
  maxi.valid = true;

  mini.xalign = req.x.align;
  mini.lower.x = -req.x.align * req.x.minimum;
  mini.upper.x = mini.lower.x + req.x.minimum;
  mini.yalign = req.y.align;
  mini.lower.y = -req.y.align * req.y.minimum;
  mini.upper.y = mini.lower.y + req.y.minimum;
  mini.zalign = req.z.align;
  mini.lower.z = -req.z.align * req.z.minimum;
  mini.upper.z = mini.lower.z + req.z.minimum;
  mini.valid = true;

//   cout << "allocation before transform :\n\t" << nat << "\n\t" << mini << "\n\t" << maxi << endl;
  nat.applyTransform(t);
  maxi.applyTransform(t);
  mini.applyTransform(t);
//   cout << "allocation after transform :\n\t" << nat << "\n\t" << mini << "\n\t" << maxi << endl;

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

  req.z.defined = true;
  req.z.natural = nat.upper.z - nat.lower.z;
  req.z.maximum = maxi.upper.z - maxi.lower.z;
  req.z.minimum = mini.upper.z - mini.lower.z;
  if (!Math::equal(req.z.natural, 0.0, 1.0e-6))
    req.z.align = -nat.lower.z / req.z.natural;
  else
    req.z.align = 0.0;
}

static void fixedTransformRequest(Graphic::Requisition &req, Transform_ptr t)
{
  Trace trace("fixedTransformRequest");
  if (t->Identity()) return;
  if (t->Translation())
    {
      Transform::Matrix mat;
      t->storeMatrix(mat);
      Coord tx = mat[0][3];
      Coord ty = mat[1][3];
      Coord tz = mat[2][3];

      req.x.align = (req.x.align * req.x.natural - tx) / req.x.natural;
      req.y.align = (req.y.align * req.y.natural - ty) / req.y.natural;
      req.z.align = (req.z.align * req.z.natural - tz) / req.z.natural;
      return;
    }

  if (!req.z.defined)
    {
      req.z.natural = req.z.maximum = req.z.minimum = 0.;
      req.z.align = 0;
      req.z.defined = true;
    }

  RegionImpl nat;

  nat.xalign = req.x.align;
  nat.lower.x = -req.x.align * req.x.natural;
  nat.upper.x = nat.lower.x + req.x.natural;
  nat.yalign = req.y.align;
  nat.lower.y = -req.y.align * req.y.natural;
  nat.upper.y = nat.lower.y + req.y.natural;
  nat.zalign = req.z.align;
  nat.lower.z = -req.z.align * req.z.natural;
  nat.upper.z = nat.lower.z + req.z.natural;
  nat.valid = true;
//   cout << "allocation before transform :" << nat << endl;
  nat.applyTransform(t);
//   cout << "allocation after transform :" << nat << endl;
  Coord xlead = -nat.lower.x;
  Coord xtrail = nat.upper.x;

  Coord ylead = -nat.lower.y;
  Coord ytrail = nat.upper.y;

  Coord zlead = -nat.lower.z;
  Coord ztrail = nat.upper.z;

  GraphicImpl::requireLeadTrail(req.x, xlead, xlead, xlead, xtrail, xtrail, xtrail);
  GraphicImpl::requireLeadTrail(req.y, ylead, ylead, ylead, ytrail, ytrail, ytrail);
  GraphicImpl::requireLeadTrail(req.z, zlead, zlead, zlead, ztrail, ztrail, ztrail);
}

/*****************************************************/

GraphicImpl::GraphicImpl() {}
GraphicImpl::~GraphicImpl() {}

Graphic_ptr GraphicImpl::body() { return Graphic::_nil();}
void GraphicImpl::body(Graphic_ptr) {}
void GraphicImpl::append(Graphic_ptr) {}
void GraphicImpl::prepend(Graphic_ptr) {}
void GraphicImpl::remove(Tag) {}

void GraphicImpl::addParent(Graphic_ptr parent, Tag tag)
{
  MutexGuard guard(parentMutex);
  Edge edge;
  edge.parent = Graphic::_duplicate(parent);
  edge.id = tag;
  parents.push_back(edge);
}

void GraphicImpl::removeParent(Graphic_ptr parent, Tag tag)
{
  MutexGuard guard(parentMutex);
  for (plist_t::iterator i = parents.begin(); i != parents.end(); i++)
    if ((*i).id == tag && (*i).parent->_is_equivalent(parent))
      {
	parents.erase(i);
	break;
      }
}

/*
 * the following two methods need to be implemented...
 */
Graphic::Iterator_ptr GraphicImpl::firstChild() { return Iterator::_nil();}
Graphic::Iterator_ptr GraphicImpl::lastChild() { return Iterator::_nil();}

/*
 * these are default implementations of the layout, picking and drawing protocol
 * which are *intended* to be overridden in children of Graphic, if you want
 * them to actually do anything remotely exciting.
 */

Transform_ptr GraphicImpl::transformation() { return Transform::_nil();}
void GraphicImpl::request(Requisition &) {}
void GraphicImpl::extension(const Allocation::Info &a, Region_ptr r) { GraphicImpl::defaultExtension(a, r);}
void GraphicImpl::shape(Region_ptr) {}

void GraphicImpl::traverse(Traversal_ptr traversal) { traversal->visit(Graphic_var(_this()));}
void GraphicImpl::draw(DrawTraversal_ptr) {}
void GraphicImpl::pick(PickTraversal_ptr) {}

void GraphicImpl::allocate(Tag, const Allocation::Info &) {}
void GraphicImpl::allocations(Allocation_ptr allocation)
{
  MutexGuard guard(parentMutex);
  CORBA::Long begin = allocation->size();
  for (plist_t::iterator i = parents.begin(); i != parents.end(); i++)
    {
      (*i).parent->allocations(allocation);      
      CORBA::Long end = allocation->size();
      for (CORBA::Long j = begin; j != end; j++)
	{
	  const Allocation::Info_var info = allocation->get(j);
	  (*i).parent->allocate((*i).id, info);
	}
      begin = end;
    }
#if 0
  for (CORBA::Long i = 0; i != allocation->size(); i++)
    {
      Allocation::Info_var info = allocation->get(i);
      Region_var r = info->allocation;
      Transform_var t = info->transformation;
      RegionImpl region(r, t);
      Logger::log(Logger::drawing) << "allocation at " << region << endl;
    }
#endif
}

/*
 * this is the method which causes DrawTraversals to get queued up to run over
 * the scene graph.  It does so by retrieving a list of all the current
 * graphic's Allocation::infos (places on the screen where the graphic appears)
 * and then sequentially extending the provided "damaged areas" with the
 * current graphic's own allocated region. As the damaged regions are extended,
 * they queue DrawTraversals in the ScreenManager, which will send them down to
 * redraw this node when an appropriate time comes 
 */
void GraphicImpl::needRedraw()
{
  // Trace trace("GraphicImpl::needRedraw");
  Lease<AllocationImpl> allocation;
  Providers::alloc.provide(allocation);
  allocation->clear();
  allocations(Allocation_var(allocation->_this()));
  Lease<RegionImpl> region;
  Providers::region.provide(region);
  CORBA::Long size = allocation->size();
  for (CORBA::Long i = 0; i < size; i++)
    {
      const Allocation::Info_var info = allocation->get(i);
      region->valid = false;
      extension(info, Region_var(region->_this()));
      if (region->valid) info->root->damage(Region_var(region->_this()));
    }
}

/* this does almost exactly the same as needRedraw(), only it extends the
 * parent-supplied damage region by a user-supplied subregion of the current
 * graphic. It does this by copying and then transforming the user-supplied
 * region to fit within the transformation of each Allocation::info received
 * from the parents 
 */
void GraphicImpl::needRedrawRegion(Region_ptr region)
{
  Trace trace("GraphicImpl::needRedrawRegion");
  if (region->defined())
    {
      Lease<AllocationImpl> allocation;
      Providers::alloc.provide(allocation);
      allocation->clear();
      allocations(Allocation_var(allocation->_this()));
      Lease<RegionImpl> dr;
      Providers::region.provide(dr);
      for (CORBA::Long i = 0; i < allocation->size(); i++)
	{
	  Allocation::Info_var info = allocation->get(i);
	  dr->copy(region);
	  dr->applyTransform(info->transformation);
	  info->root->damage(Region_var(dr->_this()));
	}
    }
}

void GraphicImpl::needResize()
{
  MutexGuard guard(parentMutex);
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

void GraphicImpl::defaultExtension (const Allocation::Info &info, Region_ptr region)
{
  if (!CORBA::is_nil(info.allocation))
    {
      if (CORBA::is_nil(info.transformation))
	region->mergeUnion(info.allocation);
      else
	{
	  Lease<RegionImpl> tmp;
	  Providers::region.provide(tmp);
	  tmp->clear();
	  tmp->copy(info.allocation);
	  if (!CORBA::is_nil(info.transformation) && !info.transformation->Identity())
	    tmp->applyTransform(info.transformation);	  
	  region->mergeUnion(Region_var(tmp->_this()));
	}
    }
}

void GraphicImpl::naturalAllocation (Graphic_ptr g, RegionImpl &nat)
{
  Requisition r;
  GraphicImpl::initRequisition(r);

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
}

void GraphicImpl::transformRequest (Graphic::Requisition& req, Transform_ptr tx)
{
  if (CORBA::is_nil(tx) || tx->Identity()) return;
  if (Math::equal(req.x.natural, req.x.maximum, tol) &&
      Math::equal(req.y.natural, req.y.maximum, tol) &&
      Math::equal(req.z.natural, req.z.maximum, tol) &&
      Math::equal(req.x.natural, req.x.minimum, tol) &&
      Math::equal(req.y.natural, req.y.minimum, tol) &&
      Math::equal(req.z.natural, req.z.minimum, tol))
    fixedTransformRequest(req, tx);
  else
    flexibleTransformRequest(req, tx);
}

static void compensate(Coord a, Coord &x, Coord &y)
{
  if (a > 0.)
    {
      if (Math::equal(x, 0., 1.0e-6)) y = a * x;
      else
	{
	  Coord aspect = y/x;
	  if (aspect > a) y = a * x;
	  else if (aspect < a) x = y / a;
	}
    }
}

/*
 * the point here is to take <region> as a given allocation and produce an allocation for the child
 * given a requisition and a transformation.
 *
 *   +-----x-+
 *   | Rp / \|
 *   |   /  /|
 *   |  /Rc/ |
 *   | /  /  |
 *   |/  /   |
 *   |\ /    |
 *   +-x-----+
 */
Vertex GraphicImpl::transformAllocate(RegionImpl &region, const Graphic::Requisition &_req, Transform_ptr t)
{
  Trace trace("GraphicImpl::transformAllocation");
  Vertex delta;
  delta.x = delta.y = delta.z = 0.;

  Requisition req = _req;
  if (!req.z.defined)
    {
      req.z.natural = req.z.maximum = req.z.minimum = 0.;
      req.z.align = region.zalign;
      req.z.defined = true;
    }

  if (!rotated(t))
    {
      Lease<TransformImpl> tx;
      Providers::trafo.provide(tx);
      tx->copy(t);
      tx->invert();
      region.applyTransform(tx);
      region.xalign = req.x.align;
      region.yalign = req.y.align;
      region.zalign = req.z.align;
    }
  else
    {
      Vertex center;
      center.x = (region.lower.x + region.upper.x) * 0.5;
      center.y = (region.lower.y + region.upper.y) * 0.5;
      center.z = (region.lower.z + region.upper.z) * 0.5;
      Transform::Matrix m;
      t->storeMatrix(m);
      Graphic::Requisition r[3], total;
      GraphicImpl::initRequisition(r[0]);
      GraphicImpl::initRequisition(r[1]);
      GraphicImpl::initRequisition(r[2]);
      GraphicImpl::initRequisition(total);	
   
      RegionImpl a[3];
//       Coord a0 = -1; Coord a1 = -1; Coord a2 = -1;
//       if (!Math::equal(m[0][0], 0.0, tol)) a0 = Math::abs(m[1][0] / m[0][0]);
//       if (!Math::equal(m[0][1], 0.0, tol)) a1 = Math::abs(m[1][1] / m[0][1]);

      r[0].x.natural = Math::abs(req.x.natural*m[0][0]);
      r[0].x.maximum = Math::abs(req.x.maximum*m[0][0]);
      r[0].x.minimum = Math::abs(req.x.minimum*m[0][0]);
      r[0].x.align = 0.;
      r[0].x.defined = true;
      r[0].y.natural = Math::abs(req.x.natural*m[1][0]);
      r[0].y.maximum = Math::abs(req.x.maximum*m[1][0]);
      r[0].y.minimum = Math::abs(req.x.minimum*m[1][0]);
      r[0].y.align = 0.;
      r[0].y.defined = true;
      r[0].z.natural = Math::abs(req.x.natural*m[2][0]);
      r[0].z.maximum = Math::abs(req.x.maximum*m[2][0]);
      r[0].z.minimum = Math::abs(req.x.minimum*m[2][0]);
      r[0].z.align = 0.;
      r[0].z.defined = true;

      r[1].x.natural = Math::abs(req.y.natural*m[0][1]);
      r[1].x.maximum = Math::abs(req.y.maximum*m[0][1]);
      r[1].x.minimum = Math::abs(req.y.minimum*m[0][1]);
      r[1].x.align = 0.;
      r[1].x.defined = true;
      r[1].y.natural = Math::abs(req.y.natural*m[1][1]);
      r[1].y.maximum = Math::abs(req.y.maximum*m[1][1]);
      r[1].y.minimum = Math::abs(req.y.minimum*m[1][1]);
      r[1].y.align = 0.;
      r[1].y.defined = true;
      r[1].z.natural = Math::abs(req.y.natural*m[2][1]);
      r[1].z.maximum = Math::abs(req.y.maximum*m[2][1]);
      r[1].z.minimum = Math::abs(req.y.minimum*m[2][1]);
      r[1].z.align = 0.;
      r[1].z.defined = true;

      r[2].x.natural = Math::abs(req.z.natural*m[0][2]);
      r[2].x.maximum = Math::abs(req.z.maximum*m[0][2]);
      r[2].x.minimum = Math::abs(req.z.minimum*m[0][2]);
      r[2].x.align = 0.;
      r[2].x.defined = true;
      r[2].y.natural = Math::abs(req.z.natural*m[1][2]);
      r[2].y.maximum = Math::abs(req.z.maximum*m[1][2]);
      r[2].y.minimum = Math::abs(req.z.minimum*m[1][2]);
      r[2].y.align = 0.;
      r[2].y.defined = true;
      r[2].z.natural = Math::abs(req.z.natural*m[2][2]);
      r[2].z.maximum = Math::abs(req.z.maximum*m[2][2]);
      r[2].z.minimum = Math::abs(req.z.minimum*m[2][2]);
      r[2].z.align = 0.;
      r[2].z.defined = true;

      total.x.natural = r[0].x.natural + r[1].x.natural + r[2].x.natural;
      total.x.maximum = r[0].x.maximum + r[1].x.maximum + r[2].x.natural;
      total.x.minimum = r[0].x.minimum + r[1].x.minimum + r[2].x.natural;
      total.x.defined = true;
      total.y.natural = r[0].y.natural + r[1].y.natural + r[2].y.natural;
      total.y.maximum = r[0].y.maximum + r[1].y.maximum + r[2].y.natural;
      total.y.minimum = r[0].y.minimum + r[1].y.minimum + r[2].y.natural;
      total.y.defined = true;
      total.z.natural = r[0].z.natural + r[1].z.natural + r[2].z.natural;
      total.z.maximum = r[0].z.maximum + r[1].z.maximum + r[2].z.natural;
      total.z.minimum = r[0].z.minimum + r[1].z.minimum + r[2].z.natural;
      total.z.defined = true;

      computeAllocations(xaxis, total, 3, r, region, a);
      computeAllocations(yaxis, total, 3, r, region, a);
      computeAllocations(zaxis, total, 3, r, region, a);
      Coord x0 = a[0].upper.x - a[0].lower.x;
      Coord y0 = a[0].upper.y - a[0].lower.y;
      Coord z0 = a[0].upper.z - a[0].lower.z;
      Coord x1 = a[1].upper.x - a[1].lower.x;
      Coord y1 = a[1].upper.y - a[1].lower.y;
      Coord z1 = a[1].upper.z - a[1].lower.z;
      Coord x2 = a[2].upper.x - a[2].lower.x;
      Coord y2 = a[2].upper.y - a[2].lower.y;
      Coord z2 = a[2].upper.z - a[2].lower.z;
      //compensate(a0, x0, y0);
      //compensate(a1, x1, y1);
      //compensate(a2, x2, y2);

      Coord lx = sqrt(x0*x0 + y0*y0 + z0*z0)/sqrt(m[0][0]*m[0][0] + m[1][0]*m[1][0] + m[2][0]*m[2][0]);
      Coord ly = sqrt(x1*x1 + y1*y1 + z1*z1)/sqrt(m[0][1]*m[0][1] + m[1][1]*m[1][1] + m[2][1]*m[2][1]);
      Coord lz = sqrt(x2*x2 + y2*y2 + z2*z2)/sqrt(m[0][2]*m[0][2] + m[1][2]*m[1][2] + m[2][2]*m[2][2]);

      region.xalign = req.x.align;
      region.yalign = req.y.align;
      region.zalign = req.z.align;
      t->inverseTransformVertex(center);

      delta.x = center.x - lx * 0.5 - region.lower.x;
      delta.y = center.y - ly * 0.5 - region.lower.y;
      delta.z = center.z - lz * 0.5 - region.lower.z;
      region.lower.x = -region.xalign * lx;
      region.lower.y = -region.yalign * ly;
      region.lower.z = -region.zalign * lz;
      region.upper.x = region.lower.x + lx;
      region.upper.y = region.lower.y + ly;
      region.upper.z = region.lower.z + lz;
    }
  return delta;
}
