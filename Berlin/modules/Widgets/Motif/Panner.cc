/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Widget/Motif/Panner.hh"
#include <Berlin/RegionImpl.hh>
#include <Berlin/CommandImpl.hh>
#include <Prague/Sys/Tracer.hh>

using namespace Prague;
using namespace Warsaw;
using namespace Motif;

class Panner::Dragger : public CommandImpl
{
public:
  Dragger(BoundedRange_ptr x, BoundedRange_ptr y)
    : xvalue(RefCount_var<BoundedRange>::increment(x)), yvalue(RefCount_var<BoundedRange>::increment(y)) {}
  virtual void execute(const CORBA::Any &any)
  {
    Vertex *delta;
    if (any >>= delta)
      {
	if (delta->x != 0.) xvalue->adjust(delta->x);
	if (delta->y != 0.) yvalue->adjust(delta->y);
      }
    else  cerr << "Drag::execute : wrong message type !" << endl;
  }
private:
  RefCount_var<BoundedRange> xvalue;
  RefCount_var<BoundedRange> yvalue;
};

Panner::Panner(BoundedRange_ptr xx, BoundedRange_ptr yy)
  : ControllerImpl(false),
    translateX(new Observer(this)),
    translateY(new Observer(this)),
    _drag(new Dragger(xx, yy)),
    x(RefCount_var<BoundedRange>::increment(xx)),
    y(RefCount_var<BoundedRange>::increment(yy))
{
  BoundedRange::Settings settings = x->state();
  offset[xaxis].lower = settings.lvalue/(settings.upper - settings.lower);
  offset[xaxis].upper = settings.uvalue/(settings.upper - settings.lower);
  settings = y->state();
  offset[yaxis].lower = settings.lvalue/(settings.upper - settings.lower);
  offset[yaxis].upper = settings.uvalue/(settings.upper - settings.lower);
  x->attach(Observer_var(translateX->_this()));
  y->attach(Observer_var(translateY->_this()));
}

void Panner::init(Controller_ptr t)
{
  body(t);
  t->add_parent_graphic(Graphic_var(_this()), 0);
  append_controller(t);
}

void Panner::update(const CORBA::Any &)
{
  BoundedRange::Settings settings = x->state();
  offset[xaxis].lower = (settings.lvalue - settings.lower)/(settings.upper - settings.lower);
  offset[xaxis].upper = (settings.uvalue - settings.lower)/(settings.upper - settings.lower);
  settings = y->state();
  offset[yaxis].lower = (settings.lvalue - settings.lower)/(settings.upper - settings.lower);
  offset[yaxis].upper = (settings.uvalue - settings.lower)/(settings.upper - settings.lower);
  need_redraw();
}

void Panner::draw(DrawTraversal_ptr traversal)
{
  traverse_thumb(traversal);
}

void Panner::pick(PickTraversal_ptr traversal)
{
  Trace trace("Panner::pick");
  if (grabbed(traversal->device()) || traversal->intersects_allocation())
    {
      traversal->enter_controller(Controller_var(_this()));
      MonoGraphic::traverse(traversal);
      if (!grabbed(traversal->device())) traverse_thumb(traversal);
      if (!traversal->picked()) traversal->hit();
      traversal->leave_controller();
    }
}

void Panner::allocate(Tag, const Allocation::Info &info)
{
  Impl_var<RegionImpl> allocation(new RegionImpl(info.allocation));
  Coord lower = allocation->lower.x;
  Coord scale = allocation->upper.x - allocation->lower.x;
  allocation->lower.x = lower + scale*offset[xaxis].lower;
  allocation->upper.x = lower + scale*offset[xaxis].upper;
  lower = allocation->lower.y;
  scale = allocation->upper.y - allocation->lower.y;
  allocation->lower.y = lower + scale*offset[yaxis].lower;
  allocation->upper.y = lower + scale*offset[yaxis].upper;
  allocation->lower.z = allocation->upper.z = 0.;
  
  allocation->normalize(info.transformation);
}

Command_ptr Panner::drag() { return _drag->_this();}

void Panner::traverse_thumb(Traversal_ptr traversal)
{
  Graphic_var child = body();
  if (CORBA::is_nil(child)) return;
  Impl_var<RegionImpl> allocation(new RegionImpl(Region_var(traversal->allocation())));
  Impl_var<TransformImpl> transformation(new TransformImpl);
  Coord lower = allocation->lower.x;
  Coord scale = allocation->upper.x - allocation->lower.x;
  allocation->lower.x = lower + scale*offset[xaxis].lower;
  allocation->upper.x = lower + scale*offset[xaxis].upper;
  lower = allocation->lower.y;
  scale = allocation->upper.y - allocation->lower.y;
  allocation->lower.y = lower + scale*offset[yaxis].lower;
  allocation->upper.y = lower + scale*offset[yaxis].upper;
  allocation->lower.z = allocation->upper.z = 0.;
  allocation->normalize(Transform_var(transformation->_this()));
  traversal->traverse_child(child, 0, Region_var(allocation->_this()), Transform_var(transformation->_this()));
}
