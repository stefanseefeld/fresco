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
}

void Panner::update(Subject_ptr, const CORBA::Any &)
{
  needRedraw();
}

void Panner::draw(DrawTraversal_ptr traversal)
{
  MonoGraphic::traverse(traversal);
  /*
   * now the thumb...
   */
}

void Panner::pick(PickTraversal_ptr traversal)
{
  SectionLog section("Panner::pick");
  if (grabbed(traversal->device()) || traversal->intersectsAllocation())
    {
      traversal->enterController(Controller_var(_this()));
      MonoGraphic::traverse(traversal);
      if (!grabbed(traversal->device()))
	{
	  /*
	   * try picking the thumb
	   */
	}
      if (!traversal->picked()) traversal->hit();
      traversal->leaveController();
    }
}

void Panner::allocate(Tag t, const Allocation::Info &info)
{
  /*
   * t == 0 is the body, t == 1 is the thumb
   */
}
