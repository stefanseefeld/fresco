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
#include <Berlin/CommandImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Provider.hh>
#include <Berlin/TransformImpl.hh>

using namespace Warsaw;
using namespace Motif;

class Slider::Dragger : public CommandImpl
{
public:
  Dragger(BoundedValue_ptr v, Axis a) : value(RefCount_var<BoundedValue>::increment(v)), scale(1.), axis(a) {}
  void set_scale(Coord s) { scale = s;}
  virtual void execute(const CORBA::Any &any)
  {
    Vertex *delta;
    if (any >>= delta)
      {
	if (axis == xaxis && delta->x != 0.) value->adjust(scale*delta->x);
	else if (axis == yaxis && delta->y != 0.) value->adjust(scale*delta->y);
      }
    else  cerr << "Drag::execute : wrong message type !" << endl;
  }
private:
  RefCount_var<BoundedValue> value;
  Coord scale;
  Axis axis;
};

Slider::Slider(BoundedValue_ptr v, Axis a, const Warsaw::Graphic::Requisition &r)
  : ControllerImpl(false),
    requisition(r),
    translate(new Observer(this)),
    _drag(new Dragger(v, a)),
    value(RefCount_var<BoundedValue>::increment(v)),
    offset((v->value() - v->lower())/(v->upper() - v->lower())),
    axis(a)
{
  v->attach(Observer_var(translate->_this()));
}

void Slider::init(Controller_ptr t)
{
  body(t);
  t->add_parent_graphic(Graphic_var(_this()), 0);
  append_controller(t);
}

void Slider::update(const CORBA::Any &any)
{
//   need_redraw();
  any >>= offset;
  offset -= value->lower();
  offset /= (value->upper() - value->lower());
  need_redraw();
}

void Slider::draw(DrawTraversal_ptr traversal)
{
  traverse_thumb(traversal);
}

void Slider::pick(PickTraversal_ptr traversal)
{
  if (grabbed(traversal->device()) || traversal->intersects_allocation())
    {
      traversal->enter_controller(Controller_var(_this()));
      MonoGraphic::traverse(traversal);
      if (!grabbed(traversal->device())) traverse_thumb(traversal);
      if (!traversal->picked()) traversal->hit();
      traversal->leave_controller();
    }
}

void Slider::allocate(Tag, const Allocation::Info &info)
{
  Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
  allocation->copy(info.allocation);
  if (axis == xaxis)
    {
      Coord length = allocation->upper.x - allocation->lower.x - 240.;
      allocation->lower.x = offset * length;
      allocation->upper.x = offset * length + 240.;
    }
  else
    {
      Coord length = allocation->upper.y - allocation->lower.y - 240.;
      allocation->lower.y = offset * length;
      allocation->upper.y = offset * length + 240.;
    }
  allocation->lower.z = allocation->upper.z = 0.;
  allocation->normalize(info.transformation);
}

void Slider::extension(const Allocation::Info &a, Region_ptr r) { GraphicImpl::default_extension(a, r);}

Command_ptr Slider::drag() { return _drag->_this();}

void Slider::traverse_thumb(Traversal_ptr traversal)
{
  Graphic_var child = body();
  if (CORBA::is_nil(child)) return;
  Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
  allocation->copy(Region_var(traversal->allocation()));
  Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
  tx->load_identity();
  Coord length;
  if (axis == xaxis)
    {
      length = allocation->upper.x - allocation->lower.x - 240.;
      allocation->lower.x = offset * length;
      allocation->upper.x = offset * length + 240.;
    }
  else if (axis == yaxis)
    {
      length = allocation->upper.y - allocation->lower.y - 240.;
      allocation->lower.y = offset * length;
      allocation->upper.y = offset * length + 240.;
    }
  allocation->lower.z = allocation->upper.z = 0.;
  allocation->normalize(Transform_var(tx->_this()));
  traversal->traverse_child(child, 0, Region_var(allocation->_this()), Transform_var(tx->_this()));
  _drag->set_scale((value->upper() - value->lower())/length);
}
