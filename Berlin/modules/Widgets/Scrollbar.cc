/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.ca> 
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

#include "Widget/Scrollbar.hh"
#include "Berlin/Logger.hh"

class Drag : public Scrollbar::Modifier
{
public:
  Drag(BoundedRange_ptr v, Axis a) : value(v), axis(a) {}
  virtual void execute(const CORBA::Any &any)
  {
    Vertex *delta;
    if (any >>= delta)
      {
	if (xaxis && delta->x != 0.) value->adjust(delta->x);
	else if (yaxis && delta->y != 0.) value->adjust(delta->y);
      }
    else  cerr << "Drag::execute : wrong message type !" << endl;
  }
private:
  BoundedRange_var value;
  Axis axis;
};

Scrollbar::Scrollbar(BoundedRange_ptr v, Axis a)
  : ControllerImpl(false), redirect(new SObserver(this)), _drag(new Drag(v, a)), axis(a)
{
}

void Scrollbar::init(Controller_ptr t)
{
  thumb = t;
  t->addParent(Graphic_var(_this()), 1);
  appendController(thumb);
}

void Scrollbar::update(Subject_ptr, const CORBA::Any &)
{
  BoundedRange::Settings settings = range->getSettings();
  offset.lower = settings.lvalue/(settings.upper - settings.lower);
  offset.upper = settings.uvalue/(settings.upper - settings.lower);
  needRedraw();
}

void Scrollbar::draw(DrawTraversal_ptr traversal)
{
  MonoGraphic::traverse(traversal);
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

void Scrollbar::allocate(Tag t, const Allocation::Info &info)
{
  /*
   * t == 0 is the body, t == 1 is the thumb
   */
  if (t == 0) return;
  //. not yet implemented
}

void Scrollbar::traverseThumb(Traversal_ptr traversal)
{
  Impl_var<RegionImpl> allocation(new RegionImpl(Region_var(traversal->allocation())));
  Impl_var<TransformImpl> transformation(new TransformImpl);
  if (axis == xaxis)
    {
      Coord lower = allocation->lower.x;
      Coord scale = allocation->upper.x - allocation->lower.x;
      allocation->lower.x = lower + scale*allocation->lower.x;
      allocation->upper.x = lower + scale*allocation->upper.x;
      allocation->lower.z = allocation->upper.z = 0.;
    }
  else if (axis == yaxis)
    {
      Coord lower = allocation->lower.y;
      Coord scale = allocation->upper.y - allocation->lower.y;
      allocation->lower.y = lower + scale*allocation->lower.y;
      allocation->upper.y = lower + scale*allocation->upper.y;
      allocation->lower.z = allocation->upper.z = 0.;
    }
  allocation->normalize(Transform_var(transformation->_this()));
  traversal->traverseChild(thumb, 1, Region_var(allocation->_this()), Transform_var(transformation->_this()));
}
