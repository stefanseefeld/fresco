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
#include "Warsaw/BoundedRange.hh"
#include "Berlin/SubjectImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Math.hh"
#include "Warsaw/Warsaw.hh"
#include "Warsaw/Traversal.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/TransformImpl.hh"

using namespace Prague;

static const double epsilon = 10e-6;

class ViewportImpl::Adjustment : implements(BoundedRange), virtual public SubjectImpl
{
 public:
  Adjustment() : l(0.), u(0.), lv(0.), uv(0.), s(0.), p(0.) {}
  virtual ~Adjustment() {}
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
  void scrollTo(Coord);
 protected:
  Coord l, u, lv, uv;
  Coord s, p;
  Mutex mutex;
};                                

Coord ViewportImpl::Adjustment::lower()
{
  MutexGuard guard(mutex);
  return l;
}

void ViewportImpl::Adjustment::lower(Coord ll)
{
  {
    MutexGuard guard(mutex);
    if (ll == l) return;
    l = ll;
    if (lv < l) lv = l;
    if (uv < l) uv = l;
  }
  CORBA::Any any;
  notify(any);
}

Coord ViewportImpl::Adjustment::upper()
{
  MutexGuard guard(mutex);
  return u;
}

void ViewportImpl::Adjustment::upper(Coord uu)
{
  {
    MutexGuard guard(mutex);
    if (uu == u) return;
    u = uu;
    if (lv > u) lv = u;
    if (uv > u) uv = u;
  }
  CORBA::Any any;
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
  {
    MutexGuard guard(mutex);
    Coord t = uv + s > u ? u - uv : s;
    if (t <= 0.) return;
    lv += t;
    uv += t;
  }
  CORBA::Any any;
  notify(any);
}

void ViewportImpl::Adjustment::backward()
{
  {
    MutexGuard guard(mutex);
    Coord t = lv - s < l ? lv - l : s;
    if (t <= 0.) return;
    lv -= t;
    uv -= t;
  }
  CORBA::Any any;
  notify(any);
}

void ViewportImpl::Adjustment::fastforward()
{
  {
    MutexGuard guard(mutex);
    Coord t = uv + p > u ? u - uv : p;
    if (t <= 0.) return;
    lv += t;
    uv += t;
  }
  CORBA::Any any;
  notify(any);
}

void ViewportImpl::Adjustment::fastbackward()
{
  {
    MutexGuard guard(mutex);
    Coord t = lv - p < l ? lv - l : p;
    if (t <= 0.) return;
    lv -= t;
    uv -= t;
  }
  CORBA::Any any;
  notify(any);
}

void ViewportImpl::Adjustment::begin()
{
  {
    MutexGuard guard(mutex);
    Coord t = lv - l;
    if (t == 0.) return;
    lv -= t;
    uv -= t;
  }
  CORBA::Any any;
  notify(any);
}

void ViewportImpl::Adjustment::end()
{
  {
    MutexGuard guard(mutex);
    Coord t = u - uv;
    if (t == 0.) return;
    lv += t;
    uv += t;
  }
  CORBA::Any any;
  notify(any);
}

void ViewportImpl::Adjustment::lvalue(Coord vv)
{
  {
    MutexGuard guard(mutex);
    if (vv > u) vv = u;
    else if (vv < l) vv = l;
    if (vv == lv) return;
    lv = vv;
  }
  CORBA::Any any;
  notify(any);
}

Coord ViewportImpl::Adjustment::lvalue()
{
  MutexGuard guard(mutex);
  return lv;
}

void ViewportImpl::Adjustment::uvalue(Coord vv)
{
  {
    MutexGuard guard(mutex);
    if (vv > u) vv = u;
    else if (vv < l) vv = l;
    if (vv == uv) return;
    uv = vv;
  }
  CORBA::Any any;
  notify(any);
}

Coord ViewportImpl::Adjustment::uvalue()
{
  MutexGuard guard(mutex);
  return uv;
}

void ViewportImpl::Adjustment::adjust(Coord d)
{
  {
    MutexGuard guard(mutex);
    Coord t =
      uv + d > u ? u - uv :
      lv + d < l ? lv - l : d;
    if (t == 0.) return;
    lv += t;
    uv += t;
  }
  CORBA::Any any;
  notify(any);
}

void ViewportImpl::Adjustment::scrollTo(Coord vv)
{
  Coord delta = vv - lvalue();
  adjust(delta);
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
  xadjustment->block(true);
  yadjustment->block(true);
  needResize();
  xadjustment->block(false);
  yadjustment->block(false);
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
      /*
       * now simply traverse the child with it's desired allocation
       * and a suitable offset
       */
      Impl_var<RegionImpl> region(bodyAllocation(allocation));
      Impl_var<TransformImpl> transform(new TransformImpl);
      region->normalize(Transform_var(transform->_this()));
      traversal->traverseChild(child, 0, Region_var(region->_this()), Transform_var(transform->_this()));
    }
}

void ViewportImpl::needResize()
{
  /*
   * set adjustment's outer range according to the body size
   */
  requested = false;
  cacheRequisition();
}

void ViewportImpl::update(Subject_ptr subject, const CORBA::Any &)
{
  /*
   * we are only interested in changes concerning the outer range (body)
   * or the offset
   */
  Coord lotmp[2] = {xadjustment->lower(), yadjustment->lower()};
  Coord uptmp[2] = {xadjustment->upper(), yadjustment->upper()};
  Coord lvtmp[2] = {xadjustment->lvalue(), yadjustment->lvalue()};
  uv[xaxis] = xadjustment->uvalue(), uv[yaxis] = yadjustment->uvalue();
  bool clear = (lotmp[xaxis] != lo[xaxis] || lotmp[yaxis] != lo[yaxis] ||
		uptmp[xaxis] != up[xaxis] || uptmp[yaxis] != up[yaxis] ||
		lvtmp[xaxis] != lv[xaxis] || lvtmp[yaxis] != lv[yaxis]);
  lo[xaxis] = lotmp[xaxis], lo[yaxis] = lotmp[yaxis];
  up[xaxis] = uptmp[xaxis], up[yaxis] = uptmp[yaxis];
  lv[xaxis] = lvtmp[xaxis], lv[yaxis] = lvtmp[yaxis];
  if (clear) needRedraw();
}

void ViewportImpl::allocateChild(Allocation::Info &info)
{
  scrollTransform(info.transformation);
  Impl_var<RegionImpl> region(bodyAllocation(info.allocation));
  info.allocation->copy(Region_var(region->_this()));
  region->_dispose();
}

BoundedRange_ptr ViewportImpl::adjustment(Axis a)
{
  return a == xaxis ? xadjustment->_this() : yadjustment->_this();
}

void ViewportImpl::scrollTo(Axis a, Coord lower)
{
//   of[a] = lower;
//   needRedraw();
}

// Coord ViewportImpl::lower(Axis a) { return lo[a];}
// Coord ViewportImpl::length(Axis a) { return le[a];}
// Coord ViewportImpl::offset(Axis a) { return of[a];}
// Coord ViewportImpl::visible(Axis a) { return vi[a];}

void ViewportImpl::cacheRequisition()
//. retrieves requisition from body and updates adjustments
{
  if (!requested)
    {
      requested = true;
      MonoGraphic::request(requisition);
      Requirement &rx = requisition.x;
      Requirement &ry = requisition.y;

      lv[xaxis] = lo[xaxis] = rx.defined ? - rx.natural * rx.align : 0.;
      lv[yaxis] = lo[yaxis] = ry.defined ? - ry.natural * ry.align : 0.;

      uv[xaxis] = up[xaxis] = rx.defined ? lv[xaxis] + rx.natural : 0.;
      uv[yaxis] = up[yaxis] = ry.defined ? lv[yaxis] + ry.natural : 0.;
      if (rx.defined)
	{
	  xadjustment->lower(lo[xaxis]);
	  xadjustment->upper(up[xaxis]);
	}
      if (ry.defined)
	{
	  yadjustment->lower(lo[yaxis]);
	  yadjustment->upper(up[yaxis]);
	}
    }
}

void ViewportImpl::cacheAllocation(Region_ptr allocation)
{
  if (!CORBA::is_nil(allocation))
    {
//       cacheRequisition();
      Region::Allotment xa, ya;
//       Coord xlength, ylength;
//       Requirement &rx = requisition.x;
//       Requirement &ry = requisition.y;
      allocation->span(xaxis, xa);
      allocation->span(yaxis, ya);

//       xlength = rx.natural;
// // 	} else {
// // 	    xlength = Math::min(  // Constrain span b/w min,max. 
// // 	        Math::max(xspan.length, rx.minimum), rx.maximum
// // 	    );
// // 	}
//       ylength = ry.natural;
// // 	} else {
// // 	    ylength = Math::min(
// // 	        Math::max(yspan.length, ry.minimum), ry.maximum
// // 	    );
// // 	}
//       if (! Math::equal(xlength, le[xaxis], epsilon))
// 	{
// 	  Coord margin = xlength - le[xaxis];
// 	  lo[xaxis] -= (margin * rx.align);
// 	  le[xaxis] = xlength;
// 	}
//       if (! Math::equal(ylength, le[yaxis], epsilon))
// 	{
// 	  Coord margin = ylength - le[yaxis];
// 	  lo[yaxis] -= (margin * ry.align);
// 	  le[yaxis] = ylength;
// 	}
	
      if (! Math::equal(xa.end - xa.begin, uv[xaxis] - lv[xaxis], epsilon))
 	{
// 	  Coord margin = xa.end - xa.begin - vi[xaxis];
 	  uv[xaxis] = lv[xaxis] + xa.end - xa.begin;
 	  xadjustment->uvalue(uv[xaxis]);
	}
      if (! Math::equal(ya.end - ya.begin, uv[yaxis] - lv[yaxis], epsilon))
 	{
// 	  Coord margin = ya.end - ya.begin - vi[yaxis];
 	  uv[yaxis] = ya.end - ya.begin;
 	  yadjustment->uvalue(uv[yaxis]);
	}
//       CORBA::Any any;
// //       xadjustment->notify(any);
// //       yadjustment->notify(any);
    }
}

RegionImpl *ViewportImpl::bodyAllocation(Region_ptr)
{
//   if (!CORBA::is_nil(a))
//     {
  RegionImpl *ca = new RegionImpl();
  ca->lower.x = -lv[xaxis] - lo[xaxis];
  ca->lower.y = -lv[yaxis] - lo[yaxis];
  ca->lower.z = 0.;
  ca->upper.x = -uv[xaxis] - up[xaxis];
  ca->upper.y = -uv[yaxis] - up[yaxis];
  ca->upper.z = 0.;

//       Coord margin;
//       margin = (up[xaxis] - lo[xaxis] - (xa.end - xa.begin));
//       ca->lower.x -= (margin * xa.align);
//       ca->upper.x = ca->lower.x + le[xaxis];
	
//       margin = (up[yaxis] - lo[yaxis] - (ya.end - ya.begin));
//       ca->lower.y -= (margin * ya.align);
//       ca->upper.y = ca->lower.y + le[yaxis];
//       return ca;
//     }
  return ca;
}

void ViewportImpl::scrollTransform(Transform_ptr tx)
{
  Vertex v;
  Requirement &rx = requisition.x;
  Requirement &ry = requisition.y;
//   v.x = (le[xaxis] - vi[xaxis]) * rx.align - of[xaxis] - lo[xaxis];
//   v.y = (le[yaxis] - vi[yaxis]) * ry.align - of[yaxis] - lo[yaxis];
//   v.z = Coord(0);
  v.x = lv[xaxis] - lo[xaxis];
  v.y = lv[yaxis] - lo[yaxis];
  v.z = 0.;
  tx->translate(v);
}	
