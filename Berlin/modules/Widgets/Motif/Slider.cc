/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#include <Fresco/Transform.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/DrawTraversal.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Provider.hh>
#include <Berlin/TransformImpl.hh>
#include "Slider.hh"

using namespace Fresco;

using namespace Berlin::WidgetKit::Motif;

Slider::Slider(BoundedValue_ptr v, Axis a, const Fresco::Graphic::Requisition &r)
  : _requisition(r),
    _value(RefCount_var<BoundedValue>::increment(v)),
    _offset((_value->value() - _value->lower())/(_value->upper() - _value->lower())),
  _axis(a)
{
  Observer_var o = observer();
  _value->attach(o);
}

void Slider::init(Controller_ptr t)
{
  body(t);
  t->add_parent_graphic(Graphic_var(_this()), 0);
  append_controller(t);
}

void Slider::draw(DrawTraversal_ptr traversal)
{
  traverse_thumb(traversal);
}

void Slider::pick(PickTraversal_ptr traversal)
{
  if (traversal->intersects_allocation())
    {
      traversal->enter_controller(Controller_var(_this()));
      MonoGraphic::traverse(traversal);
      traverse_thumb(traversal);
      if (!traversal->picked()) traversal->hit();
      traversal->leave_controller();
    }
}

void Slider::allocate(Tag, const Allocation::Info &info)
{
  Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
  allocation->copy(info.allocation);
  if (_axis == xaxis)
    {
      Coord length = allocation->upper.x - allocation->lower.x - 240.;
      allocation->lower.x = _offset * length;
      allocation->upper.x = _offset * length + 240.;
    }
  else
    {
      Coord length = allocation->upper.y - allocation->lower.y - 240.;
      allocation->lower.y = _offset * length;
      allocation->upper.y = _offset * length + 240.;
    }
  allocation->lower.z = allocation->upper.z = 0.;
  allocation->normalize(info.transformation);
}

void Slider::extension(const Allocation::Info &a, Region_ptr r) { GraphicImpl::default_extension(a, r);}

void Slider::adjust(const OriginatedDelta &od)
{
  Vertex origin = od.origin;
  Vertex newpt = od.origin;
  newpt.x += od.delta.x;
  newpt.y += od.delta.y;
  
  _pickTrafo.inverse_transform_vertex(origin);
  _pickTrafo.inverse_transform_vertex(newpt);

  Coord delta;
  
  if (_axis == xaxis) {
    delta = newpt.x - origin.x;
    if (origin.x < 0.) {
      delta = std::max(origin.x + delta, 0.);
    } else if (origin.x > _length) {
      delta = std::min(origin.x + delta, 0.);
    }

    if (delta != 0.) _value->adjust(_scale * delta);
  } else if (_axis == yaxis) {
    delta = newpt.y - origin.y;
    if (origin.y < 0.) {
      delta = std::max(origin.y + delta, 0.);
    } else if (origin.y > _length) {
      delta = std::min(origin.y + delta, 0.);
    }
    if (delta != 0.) _value->adjust(_scale * delta);
  }
}

void Slider::update(const CORBA::Any &any)
{
//   need_redraw();
  any >>= _offset;
  _offset -= _value->lower();
  _offset /= (_value->upper() - _value->lower());
  need_redraw();
}

void Slider::traverse_thumb(Traversal_ptr traversal)
{
  Graphic_var child = body();
  if (CORBA::is_nil(child)) return;
  Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
  allocation->copy(Region_var(traversal->current_allocation()));
  Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
  tx->load_identity();
  Coord length;
  if (_axis == xaxis)
    {
      _length = allocation->upper.x - allocation->lower.x;
      length = allocation->upper.x - allocation->lower.x - 240.;
      allocation->lower.x = _offset * length;
      allocation->upper.x = _offset * length + 240.;
    }
  else if (_axis == yaxis)
    {
      _length = allocation->upper.y - allocation->lower.y;
      length = allocation->upper.y - allocation->lower.y - 240.;
      allocation->lower.y = _offset * length;
      allocation->upper.y = _offset * length + 240.;
    }
  allocation->lower.z = allocation->upper.z = 0.;
  allocation->normalize(Transform_var(tx->_this()));
  traversal->traverse_child(child, 0, Region_var(allocation->_this()), Transform_var(tx->_this()));
  _scale = (_value->upper() - _value->lower())/length;
  _pickTrafo.copy(traversal->current_transformation());
}
