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

#include "Widget/Panner.hh"
#include "Berlin/Logger.hh"

class Drag : public Panner::Modifier
{
public:
  Drag(BoundedRange_ptr x, BoundedRange_ptr y) : xvalue(x), yvalue(y) {}
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
  BoundedRange_var xvalue;
  BoundedRange_var yvalue;
};

Panner::Panner(BoundedRange_ptr x, BoundedRange_ptr y)
  : ControllerImpl(false), redirect(new PObserver(this)), _drag(new Drag(x, y))
{
}

void Panner::init(Controller_ptr t)
{
  thumb = t;
  t->addParent(Graphic_var(_this()), 1);
  appendController(thumb);
}

void Panner::update(Subject_ptr, const CORBA::Any &)
{
  BoundedRange::Settings settings = x->getSettings();
  offset[xaxis].lower = settings.lvalue/(settings.upper - settings.lower);
  offset[xaxis].upper = settings.uvalue/(settings.upper - settings.lower);
  settings = y->getSettings();
  offset[yaxis].lower = settings.lvalue/(settings.upper - settings.lower);
  offset[yaxis].upper = settings.uvalue/(settings.upper - settings.lower);
  needRedraw();
}

void Panner::draw(DrawTraversal_ptr traversal)
{
  MonoGraphic::traverse(traversal);
  traverseThumb(traversal);
}

void Panner::pick(PickTraversal_ptr traversal)
{
  SectionLog section("Panner::pick");
  if (grabbed(traversal->device()) || traversal->intersectsAllocation())
    {
      traversal->enterController(Controller_var(_this()));
      MonoGraphic::traverse(traversal);
      if (!grabbed(traversal->device())) traverseThumb(traversal);
      if (!traversal->picked()) traversal->hit();
      traversal->leaveController();
    }
}

void Panner::allocate(Tag t, const Allocation::Info &info)
{
  /*
   * t == 0 is the body, t == 1 is the thumb
   */
  if (t == 0) return;
  //. not yet implemented
}

void Panner::traverseThumb(Traversal_ptr traversal)
{
  Impl_var<RegionImpl> allocation(new RegionImpl(Region_var(traversal->allocation())));
  Impl_var<TransformImpl> transformation(new TransformImpl);
  Coord lower = allocation->lower.x;
  Coord scale = allocation->upper.x - allocation->lower.x;
  allocation->lower.x = lower + scale*allocation->lower.x;
  allocation->upper.x = lower + scale*allocation->upper.x;
  lower = allocation->lower.y;
  scale = allocation->upper.y - allocation->lower.y;
  allocation->lower.y = lower + scale*allocation->lower.y;
  allocation->upper.y = lower + scale*allocation->upper.y;
  allocation->lower.z = allocation->upper.z = 0.;
  allocation->normalize(Transform_var(transformation->_this()));
  traversal->traverseChild(thumb, 1, Region_var(allocation->_this()), Transform_var(transformation->_this()));
}
