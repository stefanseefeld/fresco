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

#include "Widget/Panner.hh"
#include "Berlin/Logger.hh"

class PDrag : public Panner::Modifier
{
public:
  PDrag(BoundedRange_ptr x, BoundedRange_ptr y) : xvalue(BoundedRange::_duplicate(x)), yvalue(BoundedRange::_duplicate(y)) {}
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

Panner::Panner(BoundedRange_ptr xx, BoundedRange_ptr yy)
  : ControllerImpl(false),
    redirect(new PObserver(this)),
    _drag(new PDrag(xx, yy)),
    x(BoundedRange::_duplicate(xx)),
    y(BoundedRange::_duplicate(yy))
{
  BoundedRange::Settings settings = x->getSettings();
  offset[xaxis].lower = settings.lvalue/(settings.upper - settings.lower);
  offset[xaxis].upper = settings.uvalue/(settings.upper - settings.lower);
  settings = y->getSettings();
  offset[yaxis].lower = settings.lvalue/(settings.upper - settings.lower);
  offset[yaxis].upper = settings.uvalue/(settings.upper - settings.lower);
  x->attach(Observer_var(redirect->_this()));
  y->attach(Observer_var(redirect->_this()));
}

void Panner::init(Controller_ptr t)
{
  thumb = t;
  t->addParent(Graphic_var(_this()), 1);
  appendController(thumb);
}

void Panner::update(const CORBA::Any &)
{
  BoundedRange::Settings settings = x->getSettings();
  offset[xaxis].lower = (settings.lvalue - settings.lower)/(settings.upper - settings.lower);
  offset[xaxis].upper = (settings.uvalue - settings.lower)/(settings.upper - settings.lower);
  settings = y->getSettings();
  offset[yaxis].lower = (settings.lvalue - settings.lower)/(settings.upper - settings.lower);
  offset[yaxis].upper = (settings.uvalue - settings.lower)/(settings.upper - settings.lower);
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

void Panner::traverseThumb(Traversal_ptr traversal)
{
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
  traversal->traverseChild(thumb, 1, Region_var(allocation->_this()), Transform_var(transformation->_this()));
}
