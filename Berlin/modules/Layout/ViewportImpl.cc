/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
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

#include <Fresco/config.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/PickTraversal.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Math.hh>
#include <Berlin/Provider.hh>
#include <Berlin/TransformImpl.hh>
#include "ViewportImpl.hh"

using namespace Prague;
using namespace Fresco;
using namespace Layout;

static const double epsilon = 10e-6;

class ViewportImpl::Adjustment : public virtual POA_Fresco::BoundedRange,
		                 public SubjectImpl
{
 public:
  Adjustment();
  virtual ~Adjustment();
  virtual Fresco::BoundedRange::Settings state();
  virtual void state(const Fresco::BoundedRange::Settings &);
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
  virtual const char *object_name() { return "ViewportImpl::Adjustment";}
 private:
  Fresco::BoundedRange::Settings _settings;
  Coord                          _s;
  Coord                          _p;
  Mutex                          _mutex;
};                                

ViewportImpl::Adjustment::Adjustment()
  : _s(10.), _p(10.)
{
  _settings.lower = _settings.upper = _settings.lvalue = _settings.uvalue = 0.;
}

ViewportImpl::Adjustment::~Adjustment()
{
}

Fresco::BoundedRange::Settings ViewportImpl::Adjustment::state()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _settings;
}

void ViewportImpl::Adjustment::state(const Fresco::BoundedRange::Settings &s)
{
  Prague::Guard<Mutex> guard(_mutex);
  _settings = s;
}

Coord ViewportImpl::Adjustment::lower()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _settings.lower;
}

void ViewportImpl::Adjustment::lower(Coord l)
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (l == _settings.lower) return;
    _settings.lower = l;
    _settings.lvalue = std::max(_settings.lvalue, _settings.lower);
    _settings.uvalue = std::max(_settings.uvalue, _settings.lower);
    any <<= _settings;
  }
  notify(any);
}

Coord ViewportImpl::Adjustment::upper()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _settings.upper;
}

void ViewportImpl::Adjustment::upper(Coord u)
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (_settings.upper == u) return;
    _settings.upper = u;
    _settings.lvalue = std::min(_settings.lvalue, _settings.upper);
    _settings.uvalue = std::min(_settings.uvalue, _settings.upper);
    any <<= _settings;
  }
  notify(any);
}

Coord ViewportImpl::Adjustment::step()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _s;
}

void ViewportImpl::Adjustment::step(Coord s)
{
  Prague::Guard<Mutex> guard(_mutex);
  _s = s;
}

Coord ViewportImpl::Adjustment::page()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _p;
}

void ViewportImpl::Adjustment::page(Coord p)
{
  Prague::Guard<Mutex> guard(_mutex);
  _p = p;
}

void ViewportImpl::Adjustment::forward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = std::min(_s, _settings.upper - _settings.uvalue);
    if (t <= 0.) return;
    _settings.lvalue += t;
    _settings.uvalue += t;
    any <<= _settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::backward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = std::min(_s, _settings.lvalue - _settings.lower);
    if (t <= 0.) return;
    _settings.lvalue -= t;
    _settings.uvalue -= t;
    any <<= _settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::fastforward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = std::min(_p, _settings.upper - _settings.uvalue);
    if (t <= 0.) return;
    _settings.lvalue += t;
    _settings.uvalue += t;
    any <<= _settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::fastbackward()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = std::min(_p, _settings.lvalue - _settings.lower);
    if (t <= 0.) return;
    _settings.lvalue -= t;
    _settings.uvalue -= t;
    any <<= _settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::begin()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _settings.lvalue - _settings.lower;
    if (t == 0.) return;
    _settings.lvalue -= t;
    _settings.uvalue -= t;
    any <<= _settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::end()
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = _settings.upper - _settings.uvalue;
    if (t == 0.) return;
    _settings.lvalue += t;
    _settings.uvalue += t;
    any <<= _settings;
  }
  notify(any);
}

void ViewportImpl::Adjustment::lvalue(Coord lv)
{
  CORBA::Any any;
  {
    lv = std::min(std::max(_settings.lower, lv), _settings.upper);
    Prague::Guard<Mutex> guard(_mutex);
    if (lv == _settings.lvalue) return;
    _settings.lvalue = lv;
    any <<= _settings;
  }
  notify(any);
}

Coord ViewportImpl::Adjustment::lvalue()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _settings.lvalue;
}


void ViewportImpl::Adjustment::uvalue(Coord uv)
{
  CORBA::Any any;
  {
    uv = std::min(std::max(_settings.lower, uv), _settings.upper);
    Prague::Guard<Mutex> guard(_mutex);
    if (_settings.uvalue == uv) return;
    _settings.uvalue = uv;
    any <<= _settings;
  }
  notify(any);
}

Coord ViewportImpl::Adjustment::uvalue()
{
  Prague::Guard<Mutex> guard(_mutex);
  return _settings.uvalue;
}


void ViewportImpl::Adjustment::adjust(Coord d)
{
  CORBA::Any any;
  {
    Prague::Guard<Mutex> guard(_mutex);
    Coord t = std::min(std::max(d, _settings.lower - _settings.lvalue), _settings.upper - _settings.uvalue);
    if (t == 0.) return;
    _settings.lvalue += t;
    _settings.uvalue += t;
    any <<= _settings;
  }
  notify(any);
}

ViewportImpl::ViewportImpl() : _requested(false) {}
ViewportImpl::~ViewportImpl() {}

void ViewportImpl::body(Graphic_ptr g)
{
  MonoGraphic::body(g);
  need_resize();
  MonoGraphic::need_resize();
}

Transform_ptr ViewportImpl::transformation() { return Transform::_nil();}

void ViewportImpl::request(Fresco::Graphic::Requisition &r)
{
  cache_requisition();
  GraphicImpl::require(r.x, _requisition.x.natural, 0., _requisition.x.natural, _requisition.x.align);
  GraphicImpl::require(r.y, _requisition.y.natural, 0., _requisition.y.natural, _requisition.y.align);
  if(_requisition.z.defined)
    GraphicImpl::require(r.z, _requisition.z.natural, 0., _requisition.z.natural, _requisition.z.align);
}

void ViewportImpl::traverse(Traversal_ptr traversal)
{
  Graphic_var child = body();
  if (!CORBA::is_nil(child) && traversal->intersects_allocation())
    {
      /*
       * first update the cached allocation and the adjustments
       */
      Region_var allocation = traversal->current_allocation();
      cache_allocation(allocation);
      traversal->visit(Graphic_var(_this()));
    }
}

void ViewportImpl::draw(DrawTraversal_ptr traversal)
{
  /*
   * now simply traverse the child with it's desired allocation
   * and a suitable offset
   */
  Region_var allocation = traversal->current_allocation();
  Transform_var transformation = traversal->current_transformation();

  Lease_var<RegionImpl> clipping(Provider<RegionImpl>::provide());
  clipping->copy(allocation);
  if (!CORBA::is_nil(transformation) && !transformation->identity())
    clipping->apply_transform(transformation);

  DrawingKit_var drawing = traversal->drawing();
  drawing->save();
  drawing->clipping(Region_var(clipping->_this()));

  Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
  Lease_var<RegionImpl> b(Provider<RegionImpl>::provide());
  body_allocation(allocation, b);
  region->copy(Region_var(b->_this()));

  Lease_var<TransformImpl> transform(Provider<TransformImpl>::provide());
  transform->load_identity();

  region->normalize(Transform_var(transform->_this()));
  try { traversal->traverse_child (_child.peer, _child.localId, Region_var(region->_this()), Transform_var(transform->_this()));}
  catch (const CORBA::OBJECT_NOT_EXIST &) { body(Fresco::Graphic::_nil());}
  catch (const CORBA::COMM_FAILURE &) { body(Fresco::Graphic::_nil());}
  drawing->restore();
}

void ViewportImpl::pick(PickTraversal_ptr traversal)
{
  /*
   * now simply traverse the child with it's desired allocation
   * and a suitable offset
   */
  Region_var allocation = traversal->current_allocation();
  Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
  Lease_var<RegionImpl> b(Provider<RegionImpl>::provide());
  body_allocation(allocation, b);
  region->copy(Region_var(b->_this()));

  Lease_var<TransformImpl> transform(Provider<TransformImpl>::provide());
  transform->load_identity();

  region->normalize(Transform_var(transform->_this()));
  try { traversal->traverse_child (_child.peer, _child.localId, Region_var(region->_this()), Transform_var(transform->_this()));}
  catch (const CORBA::OBJECT_NOT_EXIST &) { body(Fresco::Graphic::_nil());}
  catch (const CORBA::COMM_FAILURE &) { body(Fresco::Graphic::_nil());}
}

void ViewportImpl::need_resize()
{
  /*
   * set adjustment's outer range according to the body size
   */
  _requested = false;
  cache_requisition();
  need_redraw();
}

void ViewportImpl::update(const CORBA::Any &)
{
  /*
   * we are only interested in changes concerning the outer range (body)
   * or the offset
   */
  Fresco::BoundedRange::Settings x = _xadjustment->state();
  Fresco::BoundedRange::Settings y = _yadjustment->state();
  bool damage = (x.lower != _settings[xaxis].lower || y.lower != _settings[yaxis].lower ||
		 x.upper != _settings[xaxis].upper || y.upper != _settings[yaxis].upper ||
		 x.lvalue != _settings[xaxis].lvalue || y.lvalue != _settings[yaxis].lvalue);
  _settings[xaxis].lvalue = x.lvalue;
  _settings[xaxis].uvalue = x.uvalue;
  _settings[yaxis].lvalue = y.lvalue;
  _settings[yaxis].uvalue = y.uvalue;
  if (damage) need_redraw();
}

void ViewportImpl::activate_composite()
{
  Adjustment *adjustment = new Adjustment;
  activate(adjustment);
  _xadjustment = RefCount_var<BoundedRange>::increment(adjustment->_this(), false);
  _xadjustment->attach(Observer_var(_this()));
  adjustment = new Adjustment;
  activate(adjustment);
  _yadjustment = RefCount_var<BoundedRange>::increment(adjustment->_this(), false);
  _yadjustment->attach(Observer_var(_this()));
}

void ViewportImpl::allocate_child(Allocation::Info &info)
{
  scroll_transform(info.transformation);
  Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
  Lease_var<RegionImpl> b(Provider<RegionImpl>::provide());
  body_allocation(info.allocation, b);
  region->copy(Region_var(b->_this()));
  info.allocation->copy(Region_var(region->_this()));
}

BoundedRange_ptr ViewportImpl::adjustment(Axis a)
{
  // FIXME: What about the zaxis? I know... it is not really useful
  //        but it is allowed for input and should not just return
  //        the value for the yaxis. -- tobias
  return a == xaxis ? RefCount_var<BoundedRange>::increment(_xadjustment) : RefCount_var<BoundedRange>::increment(_yadjustment);
}

void ViewportImpl::cache_requisition()
//. retrieves requisition from body and updates adjustments
{
  if (!_requested)
    {
      _requested = true;
      MonoGraphic::request(_requisition);
      Fresco::Graphic::Requirement &rx = _requisition.x;
      Fresco::Graphic::Requirement &ry = _requisition.y;

      _settings[xaxis].lvalue = _settings[xaxis].lower = rx.defined ? - rx.natural * rx.align : 0.;
      _settings[xaxis].uvalue = _settings[xaxis].upper = rx.defined ? _settings[xaxis].lvalue + rx.natural : 0.;
      if (rx.defined)
	{
	  _xadjustment->lower(_settings[xaxis].lower);
	  _xadjustment->upper(_settings[xaxis].upper);
	}
      _settings[yaxis].lvalue = _settings[yaxis].lower = ry.defined ? - ry.natural * ry.align : 0.;
      _settings[yaxis].uvalue = _settings[yaxis].upper = ry.defined ? _settings[yaxis].lvalue + ry.natural : 0.;
      if (ry.defined)
	{
	  _yadjustment->lower(_settings[yaxis].lower);
	  _yadjustment->upper(_settings[yaxis].upper);
	}
    }
}

void ViewportImpl::cache_allocation(Region_ptr allocation)
{
  if (!CORBA::is_nil(allocation))
    {
      Region::Allotment xa, ya;
      allocation->span(xaxis, xa);
      allocation->span(yaxis, ya);

      if (! Math::equal(xa.end - xa.begin, _settings[xaxis].uvalue - _settings[xaxis].lvalue, epsilon))
 	{
 	  _settings[xaxis].uvalue = _settings[xaxis].lvalue + xa.end - xa.begin;
 	  _xadjustment->uvalue(_settings[xaxis].uvalue);
	}
      if (! Math::equal(ya.end - ya.begin, _settings[yaxis].uvalue - _settings[yaxis].lvalue, epsilon))
 	{
 	  _settings[yaxis].uvalue = ya.end - ya.begin;
 	  _yadjustment->uvalue(_settings[yaxis].uvalue);
	}
    }
}

void ViewportImpl::body_allocation(Region_ptr, RegionImpl *ca)
{
  /*
   * FIXME!! : this implementation ignores completely the body alignment...
   */
  ca->valid = true;
  ca->lower.x = -(_settings[xaxis].lvalue - _settings[xaxis].lower);
  ca->lower.y = -(_settings[yaxis].lvalue - _settings[yaxis].lower);
  ca->lower.z = 0.;
  ca->upper.x = -(_settings[xaxis].lvalue - _settings[xaxis].upper);
  ca->upper.y = -(_settings[yaxis].lvalue - _settings[yaxis].upper);
  ca->upper.z = 0.;
  ca->xalign = ca->yalign = ca->yalign = 0.;
}

void ViewportImpl::scroll_transform(Transform_ptr tx)
{
  Vertex v;
  v.x = _settings[xaxis].lvalue - _settings[xaxis].lower;
  v.y = _settings[yaxis].lvalue - _settings[yaxis].lower;
  v.z = 0.;
  tx->translate(v);
}
