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
#include "Warsaw/DrawTraversal.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/TransformImpl.hh"
#include "Widget/Slider.hh"

Slider::Slider()
  : ControllerImpl(false),
    current(0)
{}

void Slider::init(Controller_ptr t)
{
  thumb = Controller::_duplicate(t);
  if (!CORBA::is_nil(thumb))
    {
      thumb->addParent(Graphic_var(ControllerImpl::_this()), 1);
      appendController(thumb);
    }
}

void Slider::draw(DrawTraversal_ptr traversal)
{
  ControllerImpl::draw(traversal);
  Allocation::Info info;
  Region_var allocation = traversal->allocation();
  Impl_var<RegionImpl> region(new RegionImpl(allocation));
  Impl_var<TransformImpl> transformation(new TransformImpl);
  transformation->copy(Transform_var(traversal->transformation()));
  info.allocation = region;
  info.transformation = transformation;
  allocateThumb(info);
  if (traversal->intersectsRegion(info.allocation)) thumb->traverse(traversal);
}

void Slider::pick(PickTraversal_ptr traversal)
{
  Allocation::Info info;
  Region_var allocation = traversal->allocation();
  Impl_var<RegionImpl> region(new RegionImpl(allocation));
  Impl_var<TransformImpl> transformation(new TransformImpl);
  transformation->copy(Transform_var(traversal->transformation()));
  info.allocation = region;
  info.transformation = transformation;
  allocateThumb(info);
  if (traversal->intersectsRegion(info.allocation)) thumb->traverse(traversal);
  else ControllerImpl::pick(traversal);
}

void Slider::allocate(Tag tag, const Allocation::Info &info)
{
  if (!tag) ControllerImpl::allocate(tag, info);
  else allocateThumb(info);
}

void Slider::update(const CORBA::Any &) { needRedraw();}

void Slider::press(PickTraversal_ptr traversal, const Input::Event &event)
{
  current = stepper(traversal, event);
  current->press(traversal, event);
}

void Slider::release(PickTraversal_ptr traversal, const Input::Event &event)
{
  current->release(traversal, event);
  current = 0;
}

class Backward : public Slider::Modifier
{
public:
  Backward(BoundedValue_ptr v) : value(v) {}
  virtual void execute(const CORBA::Any &) { value->backward();}
private:
  BoundedValue_var value;
};

class Forward : public Slider::Modifier
{
public:
  Forward(BoundedValue_ptr v) : value(v) {}
  virtual void execute(const CORBA::Any &) { value->forward();}
private:
  BoundedValue_var value;
};

class CompositeModifier : public Slider::Modifier
{
 public:
  CompositeModifier(Slider::Modifier *f, Slider::Modifier *s)
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
  Slider::Modifier *first;
  Slider::Modifier *second;
};

Slider1D::Slider1D(Axis a)
  : offset(0),
    axis(a)
{
}

void Slider1D::init(Controller_ptr t, BoundedValue_ptr v)
{
  Slider::init(t);
  value = BoundedValue::_duplicate(v);
  observer = new Observer(this);
  value->attach(Observer_var(observer->_this()));
  backward = new Backward(value);
  forward = new Forward(value);
  backwardStepper = new Stepper;
  backwardStepper->action(backward);
  forwardStepper = new Stepper;
  forwardStepper->action(forward);
}

void Slider1D::allocateThumb(const Allocation::Info &info)
{
  Requisition req;
  thumb->request(req);
  Impl_var<RegionImpl> region(new RegionImpl);
  region->lower.x =  - req.x.align * req.x.natural;
  region->lower.y =  - req.y.align * req.y.natural;
  region->upper.x = (1. - req.x.align) * req.x.natural;
  region->upper.y = (1. - req.y.align) * req.y.natural;
  info.allocation->copy(Region_var(region->_this()));
  Vertex origin = {0., 0., 0.};
  if (axis == xaxis) origin.x += offset;
  else origin.y += offset;
  info.transformation->translate(origin);
}

Stepper *Slider1D::stepper(PickTraversal_ptr traversal, const Input::Event &event)
{
  Region_var allocation = traversal->allocation();
  Transform_var transformation = traversal->transformation();
  Vertex location = event[1].attr.location();
  transformation->inverseTransformVertex(location);
  Impl_var<RegionImpl> region(new RegionImpl(allocation));
  if ((axis == xaxis && location.x < region->lower.x + offset) ||
      (axis == yaxis && location.y < region->lower.y + offset))
    return backwardStepper;
  else return forwardStepper;
}

Slider2D::Slider2D()
{
}

void Slider2D::init(Controller_ptr t, BoundedValue_ptr xv, BoundedValue_ptr yv)
{
  Slider::init(t);
  Requisition r;
  GraphicImpl::initRequisition(r);
  thumb->request(r);
  thumbSize.x = r.x.defined ? r.x.natural : 0;
  thumbSize.y = r.y.defined ? r.y.natural : 0;
  thumbSize.z = r.z.defined ? r.z.natural : 0;

  xvalue = BoundedValue::_duplicate(xv);
  yvalue = BoundedValue::_duplicate(yv);
  xobserver = new Observer(this);
  yobserver = new Observer(this);
  xvalue->attach(Observer_var(xobserver->_this()));
  yvalue->attach(Observer_var(yobserver->_this()));
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

void Slider2D::allocateThumb(const Allocation::Info &info)
{
  cerr << "sorry, Slider2D::allocateThumb not yet implemented" << endl;
}

Stepper *Slider2D::stepper(PickTraversal_ptr traversal, const Input::Event &event)
{
  Region_var allocation = traversal->allocation();
  Transform_var transformation = traversal->transformation();
  Vertex location = event[1].attr.location();
  transformation->inverseTransformVertex(location);
  Impl_var<RegionImpl> region(new RegionImpl(allocation));
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
