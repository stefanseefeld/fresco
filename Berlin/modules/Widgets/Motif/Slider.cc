/*$Id$
 *
 * This source file is a part of the Berlin Project.
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
#include "Widget/Motif/Slider.hh"
#include <Warsaw/config.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/PickTraversal.hh>
#include <Warsaw/DrawTraversal.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/TransformImpl.hh>
#include <Warsaw/Warsaw.hh>

using namespace Motif;

class Slider::Dragger : implements(Command)
{
public:
  Dragger(BoundedValue_ptr v, Axis a) : value(BoundedValue::_duplicate(v)), axis(a) {}
  virtual void execute(const CORBA::Any &any)
  {
    Vertex *delta;
    if (any >>= delta)
      {
	if (axis == xaxis && delta->x != 0.) value->adjust(delta->x);
	else if (axis == yaxis && delta->y != 0.) value->adjust(delta->y);
      }
    else  cerr << "Drag::execute : wrong message type !" << endl;
  }
private:
  BoundedValue_var value;
  Axis axis;
};

Slider::Slider(BoundedValue_ptr v, Axis a, const Requisition &r)
  : ControllerImpl(false),
    requisition(r),
    redirect(new Observer(this)),
    _drag(new Dragger(v, a)),
    value(BoundedValue::_duplicate(v)),
    offset(v->value()),
    axis(a)
{
  v->attach(Observer_var(redirect->_this()));
}

void Slider::init(Controller_ptr t)
{
  body(t);
  t->addParent(Graphic_var(_this()), 0);
  appendController(t);
}

void Slider::update(const CORBA::Any &any)
{
  any >>= offset;
  offset /= (value->upper() - value->lower());
  needRedraw();
}

void Slider::draw(DrawTraversal_ptr traversal)
{
  traverseThumb(traversal);
}

void Slider::pick(PickTraversal_ptr traversal)
{
  if (grabbed(traversal->device()) || traversal->intersectsAllocation())
    {
      traversal->enterController(Controller_var(_this()));
      MonoGraphic::traverse(traversal);
      if (!grabbed(traversal->device())) traverseThumb(traversal);
      if (!traversal->picked()) traversal->hit();
      traversal->leaveController();
    }
}

void Slider::allocate(Tag, const Allocation::Info &info)
{
  Impl_var<RegionImpl> allocation(new RegionImpl(info.allocation));
  if (axis == xaxis)
    {
      Coord length = allocation->upper.x - allocation->lower.x - 200.;
      allocation->lower.x = offset * length;
      allocation->upper.x = offset * length + 200.;
    }
  else
    {
      Coord length = allocation->upper.y - allocation->lower.y - 200.;
      allocation->lower.y = offset * length;
      allocation->upper.y = offset * length + 200.;
    }
  allocation->lower.z = allocation->upper.z = 0.;
  allocation->normalize(info.transformation);
}

Command_ptr Slider::drag() { return _drag->_this();}

void Slider::traverseThumb(Traversal_ptr traversal)
{
  Graphic_var child = body();
  if (CORBA::is_nil(child)) return;
  Impl_var<RegionImpl> allocation(new RegionImpl(Region_var(traversal->allocation())));
  Impl_var<TransformImpl> transformation(new TransformImpl);
  if (axis == xaxis)
    {
      Coord length = allocation->upper.x - allocation->lower.x - 200.;
      allocation->lower.x = offset * length;
      allocation->upper.x = offset * length + 200.;
    }
  else if (axis == yaxis)
    {
      Coord length = allocation->upper.y - allocation->lower.y - 200.;
      allocation->lower.y = offset * length;
      allocation->upper.y = offset * length + 200.;
    }
  allocation->lower.z = allocation->upper.z = 0.;
  allocation->normalize(Transform_var(transformation->_this()));
  traversal->traverseChild(child, 0, Region_var(allocation->_this()), Transform_var(transformation->_this()));
}
