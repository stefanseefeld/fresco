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

#include "Widget/Motif/Scrollbar.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Logger.hh"

using namespace Motif;

class Scrollbar::Dragger : implements(Command)
{
public:
  Dragger(BoundedRange_ptr v, Axis a) : value(BoundedRange::_duplicate(v)), axis(a) {}
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
  BoundedRange_var value;
  Axis axis;
};

Scrollbar::Scrollbar(BoundedRange_ptr v, Axis a, const Requisition &r)
  : ControllerImpl(false),
    requisition(r),
    redirect(new Observer(this)),
    _drag(new Dragger(v, a)),
    range(BoundedRange::_duplicate(v)),
    axis(a)
{
  BoundedRange::Settings settings = v->getSettings();
  offset.lower = settings.lvalue/(settings.upper - settings.lower);
  offset.upper = settings.uvalue/(settings.upper - settings.lower);
  v->attach(Observer_var(redirect->_this()));
}

void Scrollbar::init(Controller_ptr t)
{
  body(t);
  t->addParent(Graphic_var(_this()), 0);
  appendController(t);
}

void Scrollbar::update(const CORBA::Any &any)
{
  BoundedRange::Settings *settings;
  any >>= settings;
  offset.lower = (settings->lvalue - settings->lower)/(settings->upper - settings->lower);
  offset.upper = (settings->uvalue - settings->lower)/(settings->upper - settings->lower);
  needRedraw();
}

void Scrollbar::draw(DrawTraversal_ptr traversal)
{
  traverseThumb(traversal);
}

void Scrollbar::pick(PickTraversal_ptr traversal)
{
  SectionLog section("Scrollbar::pick");
  if (grabbed(traversal->device()) || traversal->intersectsAllocation())
    {
      traversal->enterController(Controller_var(_this()));
      MonoGraphic::traverse(traversal);
      if (!grabbed(traversal->device())) traverseThumb(traversal);
      if (!traversal->picked()) traversal->hit();
      traversal->leaveController();
    }
}

void Scrollbar::allocate(Tag, const Allocation::Info &info)
{
  Impl_var<RegionImpl> allocation(new RegionImpl(info.allocation));
  if (axis == xaxis)
    {
      Coord lower = allocation->lower.x;
      Coord scale = allocation->upper.x - allocation->lower.x;
      allocation->lower.x = lower + scale*offset.lower;
      allocation->upper.x = lower + scale*offset.upper;
    }
  else
    {
      Coord lower = allocation->lower.y;
      Coord scale = allocation->upper.y - allocation->lower.y;
      allocation->lower.y = lower + scale*offset.lower;
      allocation->upper.y = lower + scale*offset.upper;
    }
  allocation->lower.z = allocation->upper.z = 0.;
  allocation->normalize(info.transformation);
}

Command_ptr Scrollbar::drag() { return _drag->_this();}

void Scrollbar::traverseThumb(Traversal_ptr traversal)
{
  Graphic_var child = body();
  if (CORBA::is_nil(child)) return;
  Impl_var<RegionImpl> allocation(new RegionImpl(Region_var(traversal->allocation())));
  Impl_var<TransformImpl> transformation(new TransformImpl);
  if (axis == xaxis)
    {
      Coord lower = allocation->lower.x;
      Coord scale = allocation->upper.x - allocation->lower.x;
      allocation->lower.x = lower + scale*offset.lower;
      allocation->upper.x = lower + scale*offset.upper;
      allocation->lower.z = allocation->upper.z = 0.;
    }
  else if (axis == yaxis)
    {
      Coord lower = allocation->lower.y;
      Coord scale = allocation->upper.y - allocation->lower.y;
      allocation->lower.y = lower + scale*offset.lower;
      allocation->upper.y = lower + scale*offset.upper;
    }
  allocation->lower.z = allocation->upper.z = 0.;
  allocation->normalize(Transform_var(transformation->_this()));
  traversal->traverseChild(child, 0, Region_var(allocation->_this()), Transform_var(transformation->_this()));
}
