/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Layout/ViewportImpl.hh"
#include "Berlin/SubjectImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Math.hh"
#include "Warsaw/Warsaw.hh"
#include "Warsaw/DrawTraversal.hh"
#include "Warsaw/DrawingKit.hh"
#include "Warsaw/PickTraversal.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/TransformImpl.hh"

using namespace Prague;

static const double epsilon = 10e-6;

class ViewportImpl::Adjustment : implements(BoundedRange), virtual public SubjectImpl
{
 public:
  Adjustment() : s(0.), p(0.) { settings.lower = settings.upper = settings.lvalue = settings.uvalue = 0.;}
  virtual ~Adjustment() {}
  virtual Settings getSettings();
  virtual Coord lower();
  virtual void lower(Coord);
  virtual Coord upper();
  virtual void upper(Coord);
  virtual Coord step();
  virtual void step(Coord);
  virtual Coord page();
  virtual void page(Coord);
  virtual Coord lvalue();
  virtual void lvalue(Coord);
  virtual Coord uvalue();
  virtual void uvalue(Coord);
  virtual void forward();
  virtual void backward();
  virtual void fastforward();
  virtual void fastbackward();
  virtual void begin();
  virtual void end();
  virtual void adjust(Coord);
 protected:
  Settings settings;
  Coord s, p;
  Mutex mutex;
};                                

BoundedRange::Settings ViewportImpl::Adjustment::getSettings()
{
  MutexGuard guard(mutex);
  return settings;
}

Coord ViewportImpl::Adjustment::lower()
{
  MutexGuard guard(mutex);
  return settings.lower;
}

void ViewportImpl::Adjustment::lower(Coord l)
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    if (l == settings.lower) return;
    settings.lower = l;
    settings.lvalue = max(settings.lvalue, settings.lower);
    settings.uvalue = max(settings.uvalue, settings.lower);
    any <<= settings;
  }
  notify(any);
}

Coord ViewportImpl::Adjustment::upper()
{
  MutexGuard guard(mutex);
  return settings.upper;
}

void ViewportImpl::Adjustment::upper(Coord u)
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    if (settings.upper == u) return;
    settings.upper = u;
    settings.lvalue = min(settings.lvalue, settings.upper);
    settings.uvalue = min(settings.uvalue, settings.upper);
    any <<= settings;
  }
  notify(any);
}

Coord ViewportImpl::Adjustment::step()
{
  MutexGuard guard(mutex);
  return s;
}

void ViewportImpl::Adjustment::step(Coord ss)
{
  MutexGuard guard(mutex);
  s = ss;
}

Coord ViewportImpl::Adjustment::page()
{
  MutexGuard guard(mutex);
  return p;
}

void ViewportImpl::Adjustment::page(Coord pp)
{
  MutexGuard guard(mutex);
  p = pp;
}

void ViewportImpl::Adjustment::forward()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = min(s, settings.upper - settings.uvalue);
    if (t <= 0.) return;
    settings.lvalue += t;
    settings.uvalue += t;
    any <<= settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::backward()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = min(s, settings.lvalue - settings.lower);
    if (t <= 0.) return;
    settings.lvalue -= t;
    settings.uvalue -= t;
    any <<= settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::fastforward()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = min(p, settings.upper - settings.uvalue);
    if (t <= 0.) return;
    settings.lvalue += t;
    settings.uvalue += t;
    any <<= settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::fastbackward()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = min(p, settings.lvalue - settings.lower);
    if (t <= 0.) return;
    settings.lvalue -= t;
    settings.uvalue -= t;
    any <<= settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::begin()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = settings.lvalue - settings.lower;
    if (t == 0.) return;
    settings.lvalue -= t;
    settings.uvalue -= t;
    any <<= settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::end()
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = settings.upper - settings.uvalue;
    if (t == 0.) return;
    settings.lvalue += t;
    settings.uvalue += t;
    any <<= settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::lvalue(Coord lv)
{
  CORBA::Any any;
  {
    lv = min(max(settings.lower, lv), settings.upper);
    MutexGuard guard(mutex);
    if (lv == settings.lvalue) return;
    settings.lvalue = lv;
    any <<= settings;
  }
  notify(any);
}

Coord ViewportImpl::Adjustment::lvalue()
{
  MutexGuard guard(mutex);
  return settings.lvalue;
}


void ViewportImpl::Adjustment::uvalue(Coord uv)
{
  CORBA::Any any;
  {
    uv = min(max(settings.lower, uv), settings.upper);
    MutexGuard guard(mutex);
    if (settings.uvalue == uv) return;
    settings.uvalue = uv;
    any <<= settings;
  }
  notify(any);
}

Coord ViewportImpl::Adjustment::uvalue()
{
  MutexGuard guard(mutex);
  return settings.uvalue;
}


void ViewportImpl::Adjustment::adjust(Coord d)
{
  CORBA::Any any;
  {
    MutexGuard guard(mutex);
    Coord t = min(max(d, settings.lower - settings.lvalue), settings.upper - settings.uvalue);
    if (t == 0.) return;
    settings.lvalue += t;
    settings.uvalue += t;
    any <<= settings;
  }
  notify(any);
}

ViewportImpl::ViewportImpl()
  : requested(false)
{
  xadjustment = new Adjustment;
  xadjustment->_obj_is_ready(CORBA::BOA::getBOA());
  yadjustment = new Adjustment;
  yadjustment->_obj_is_ready(CORBA::BOA::getBOA());
}

ViewportImpl::~ViewportImpl()
{
  xadjustment->_dispose();
  yadjustment->_dispose();
}

void ViewportImpl::attachAdjustments()
{
  xadjustment->attach(Observer_var(_this()));
  yadjustment->attach(Observer_var(_this()));
}

void ViewportImpl::body(Graphic_ptr g)
{
  MonoGraphic::body(g);
//   xadjustment->block(true);
//   yadjustment->block(true);
  needResize();
//   xadjustment->block(false);
//   yadjustment->block(false);
  MonoGraphic::needResize();
}

Transform_ptr ViewportImpl::transformation() { return Transform::_nil();}

void ViewportImpl::request(Requisition &r)
{
  cacheRequisition();
  GraphicImpl::require(r.x, requisition.x.natural, 0., requisition.x.natural, requisition.x.align);
  GraphicImpl::require(r.y, requisition.y.natural, 0., requisition.y.natural, requisition.y.align);
  if(requisition.z.defined)
    GraphicImpl::require(r.z, requisition.z.natural, 0., requisition.z.natural, requisition.z.align);
}

void ViewportImpl::traverse(Traversal_ptr traversal)
{
  Graphic_var child = body();
  if (!CORBA::is_nil(child) && traversal->intersectsAllocation())
    {
      /*
       * first update the cached allocation and the adjustments
       */
      Region_var allocation = traversal->allocation();
      cacheAllocation(allocation);
      traversal->visit(Graphic_var(_this()));
    }
}

void ViewportImpl::draw(DrawTraversal_ptr traversal)
{
  /*
   * now simply traverse the child with it's desired allocation
   * and a suitable offset
   */
  Region_var allocation = traversal->allocation();
  Transform_var transformation = traversal->transformation();
  Impl_var<RegionImpl> clipping(new RegionImpl(allocation, transformation));
  DrawingKit_var dk = traversal->kit();
  dk->saveState();
  cout << "Viewport clip" << endl;
  dk->clipping(Region_var(clipping->_this()));

  Impl_var<RegionImpl> region(bodyAllocation(allocation));
  Impl_var<TransformImpl> transform(new TransformImpl);
  region->normalize(Transform_var(transform->_this()));
  traversal->traverseChild(child, 0, Region_var(region->_this()), Transform_var(transform->_this()));
  dk->restoreState();
  cout << "~Viewport clip" << endl;
}

void ViewportImpl::pick(PickTraversal_ptr traversal)
{
  /*
   * now simply traverse the child with it's desired allocation
   * and a suitable offset
   */
  Region_var allocation = traversal->allocation();
  Impl_var<RegionImpl> region(bodyAllocation(allocation));
  Impl_var<TransformImpl> transform(new TransformImpl);
  region->normalize(Transform_var(transform->_this()));
  traversal->traverseChild(child, 0, Region_var(region->_this()), Transform_var(transform->_this()));
}

void ViewportImpl::needResize()
{
  /*
   * set adjustment's outer range according to the body size
   */
  requested = false;
  cacheRequisition();
}

void ViewportImpl::update(Subject_ptr, const CORBA::Any &)
{
  /*
   * we are only interested in changes concerning the outer range (body)
   * or the offset
   */
  BoundedRange::Settings x = xadjustment->getSettings();
  BoundedRange::Settings y = yadjustment->getSettings();
  bool damage = (x.lower != settings[xaxis].lower || y.lower != settings[yaxis].lower ||
		 x.upper != settings[xaxis].upper || y.upper != settings[yaxis].upper ||
		 x.lvalue != settings[xaxis].lvalue || y.lvalue != settings[yaxis].lvalue);
  settings[xaxis].lvalue = x.lvalue;
  settings[xaxis].uvalue = x.uvalue;
  settings[yaxis].lvalue = y.lvalue;
  settings[yaxis].uvalue = y.uvalue;
  if (damage) needRedraw();
}

void ViewportImpl::allocateChild(Allocation::Info &info)
{
  scrollTransform(info.transformation);
  Impl_var<RegionImpl> region(bodyAllocation(info.allocation));
  info.allocation->copy(Region_var(region->_this()));
}

BoundedRange_ptr ViewportImpl::adjustment(Axis a)
{
  return a == xaxis ? xadjustment->_this() : yadjustment->_this();
}

void ViewportImpl::cacheRequisition()
//. retrieves requisition from body and updates adjustments
{
  if (!requested)
    {
      requested = true;
      MonoGraphic::request(requisition);
      Requirement &rx = requisition.x;
      Requirement &ry = requisition.y;

      settings[xaxis].lvalue = settings[xaxis].lower = rx.defined ? - rx.natural * rx.align : 0.;
      settings[xaxis].uvalue = settings[xaxis].upper = rx.defined ? settings[xaxis].lvalue + rx.natural : 0.;
      if (rx.defined)
	{
	  xadjustment->lower(settings[xaxis].lower);
	  xadjustment->upper(settings[xaxis].upper);
	}
      settings[yaxis].lvalue = settings[yaxis].lower = ry.defined ? - ry.natural * ry.align : 0.;
      settings[yaxis].uvalue = settings[yaxis].upper = ry.defined ? settings[yaxis].lvalue + ry.natural : 0.;
      if (ry.defined)
	{
	  yadjustment->lower(settings[yaxis].lower);
	  yadjustment->upper(settings[yaxis].upper);
	}
    }
}

void ViewportImpl::cacheAllocation(Region_ptr allocation)
{
  if (!CORBA::is_nil(allocation))
    {
      Region::Allotment xa, ya;
      allocation->span(xaxis, xa);
      allocation->span(yaxis, ya);

      if (! Math::equal(xa.end - xa.begin, settings[xaxis].uvalue - settings[xaxis].lvalue, epsilon))
 	{
 	  settings[xaxis].uvalue = settings[xaxis].lvalue + xa.end - xa.begin;
 	  xadjustment->uvalue(settings[xaxis].uvalue);
	}
      if (! Math::equal(ya.end - ya.begin, settings[yaxis].uvalue - settings[yaxis].lvalue, epsilon))
 	{
 	  settings[yaxis].uvalue = ya.end - ya.begin;
 	  yadjustment->uvalue(settings[yaxis].uvalue);
	}
    }
}

RegionImpl *ViewportImpl::bodyAllocation(Region_ptr)
{
  /*
   * FIXME!! : this implementation ignores completely the body alignment...
   */
  RegionImpl *ca = new RegionImpl();
  ca->valid = true;
  ca->lower.x = -(settings[xaxis].lvalue - settings[xaxis].lower);
  ca->lower.y = -(settings[yaxis].lvalue - settings[yaxis].lower);
  ca->lower.z = 0.;
  ca->upper.x = -(settings[xaxis].lvalue - settings[xaxis].upper);
  ca->upper.y = -(settings[yaxis].lvalue - settings[yaxis].upper);
  ca->upper.z = 0.;
  ca->xalign = ca->yalign = ca->yalign = 0.;
  return ca;
}

void ViewportImpl::scrollTransform(Transform_ptr tx)
{
  Vertex v;
  v.x = settings[xaxis].lvalue - settings[xaxis].lower;
  v.y = settings[yaxis].lvalue - settings[yaxis].lower;
  v.z = 0.;
  tx->translate(v);
}
