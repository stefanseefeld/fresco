/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#include "Warsaw/config.hh"
#include "Warsaw/Transform.hh"
#include "Warsaw/PickTraversal.hh"
#include "Berlin/RegionImpl.hh"
#include "Widget/Slider.hh"

BVController::BVController(Controller_ptr t)
  : ControllerImpl(false),
    thumb(Controller::_duplicate(t)),
    current(0)
{}

void BVController::update(Subject_ptr) { needRedraw();}

void BVController::press(PickTraversal_ptr traversal, const Event::Pointer *pointer)
{
  current = stepper(traversal, pointer);
  current->press(traversal, pointer);
}

void BVController::release(PickTraversal_ptr traversal, const Event::Pointer *pointer)
{
  current->release(traversal, pointer);
  current = 0;
}

class Backward : public BVController::Modifier
{
public:
  Backward(BoundedValue_ptr v) : value(v) {}
  virtual void execute(const CORBA::Any &) { value->backward();}
private:
  BoundedValue_var value;
};

class Forward : public BVController::Modifier
{
public:
  Forward(BoundedValue_ptr v) : value(v) {}
  virtual void execute(const CORBA::Any &) { value->forward();}
private:
  BoundedValue_var value;
};

class CompositeModifier : public BVController::Modifier
{
 public:
  CompositeModifier(BVController::Modifier *f, BVController::Modifier *s)
    : first(f), second(s) {}
  ~CompositeModifier()
    {
      delete second;
      delete first;
    }
  virtual void execute(const CORBA::Any &any)
    {
      /*
       * FIXME: we need to block updates so that only one redraw request occures
       * -stefan
       */
      first->execute(any);
      second->execute(any);
    }
 private:
  BVController::Modifier *first;
  BVController::Modifier *second;
};

Slider::Slider(Controller_ptr thumb, Axis a)
  : BVController(thumb),
    offset(0),
    axis(a)
{
}

void Slider::init(BoundedValue_ptr v)
{
  value = BoundedValue::_duplicate(v);
  backward = new Backward(value);
  forward = new Forward(value);
  backwardStepper = new Stepper;
  backwardStepper->action(backward);
  forwardStepper = new Stepper;
  forwardStepper->action(forward);
}

Stepper *Slider::stepper(PickTraversal_ptr traversal, const Event::Pointer *pointer)
{
  Region_var allocation = traversal->allocation();
  Transform_var transformation = traversal->transformation();
  Vertex location = pointer->location;
  transformation->inverseTransformVertex(location);
  Impl_var<RegionImpl> region(new RegionImpl(allocation, Transform_var(Transform::_nil())));
  if ((axis == xaxis && location.x < region->lower.x + offset) ||
      (axis == yaxis && location.y < region->lower.y + offset))
    return backwardStepper;
  else return forwardStepper;
}

XYSlider::XYSlider(Controller_ptr thumb)
  : BVController(thumb)
{
  Requisition r;
  GraphicImpl::initRequisition(r);
  thumb->request(r);
  thumbSize.x = r.x.defined ? r.x.natural : 0;
  thumbSize.y = r.y.defined ? r.y.natural : 0;
  thumbSize.z = r.z.defined ? r.z.natural : 0;
}

void XYSlider::init(BoundedValue_ptr xv, BoundedValue_ptr yv)
{
  xvalue = BoundedValue::_duplicate(xv);
  yvalue = BoundedValue::_duplicate(yv);
  modifiers[0] = new Backward(xvalue);
  modifiers[1] = new Forward(xvalue);
  modifiers[2] = new Backward(yvalue);
  modifiers[3] = new Forward(yvalue);
  modifiers[4] = new CompositeModifier(new Backward(xvalue), new Backward(yvalue));
  modifiers[5] = new CompositeModifier(new Forward(xvalue), new Backward(yvalue));
  modifiers[6] = new CompositeModifier(new Backward(xvalue), new Forward(yvalue));
  modifiers[7] = new CompositeModifier(new Forward(xvalue), new Forward(yvalue));
  for (unsigned int i = 0; i != 8; i++)
    {
       steppers[i] = new Stepper;
       steppers[i]->action(modifiers[i]);
    }
}

Stepper *XYSlider::stepper(PickTraversal_ptr traversal, const Event::Pointer *pointer)
{
  Region_var allocation = traversal->allocation();
  Transform_var transformation = traversal->transformation();
  Vertex location = pointer->location;
  transformation->inverseTransformVertex(location);
  Impl_var<RegionImpl> region(new RegionImpl(allocation, Transform_var(Transform::_nil())));
  if (location.x < region->lower.x + xoffset)
    {
      if (location.y < region->lower.y + yoffset) return steppers[lefttop];
      else if (location.y < region->lower.y + yoffset + thumbSize.y) return steppers[left];
      else return steppers[leftbottom];
    }
  else if (location.x < region->lower.x + xoffset + thumbSize.x)
    {
      if (location.y < region->lower.y + yoffset) return steppers[top];
      // impossible since else thumb would handle the event
      // else if (location.y < region->lower.y + offset + thumbSize.y) return stepper[left];
      else return steppers[bottom];
    }
  else if (location.y < region->lower.y + yoffset) return steppers[righttop];
  else if (location.y < region->lower.y + yoffset + thumbSize.y) return steppers[right];
  else return steppers[rightbottom];
}
