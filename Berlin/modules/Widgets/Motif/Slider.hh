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
#ifndef _Motif_Slider_hh
#define _Motif_Slider_hh

#include <Warsaw/config.hh>
#include <Warsaw/Command.hh>
#include <Warsaw/BoundedValue.hh>
#include <Berlin/ControllerImpl.hh>
#include <Berlin/ImplVar.hh>

namespace Motif
{

class Slider : public ControllerImpl
{
protected:
  class Observer : implements(Observer)
  {
  public:
    Observer(Slider *s) : slider(s) {}
    void update(const CORBA::Any &any) { slider->update(any);}
  private:
    Slider *slider;
  };
  friend class Observer;
  class Modifier : implements(Command) {};
public:
  Slider();
  void init(Controller_ptr);
  virtual void update(const CORBA::Any &);
  virtual void draw(DrawTraversal_ptr);
  virtual void pick(PickTraversal_ptr);
  virtual void allocate(Tag, const Allocation::Info &);
//protected:
  virtual void allocateThumb(const Allocation::Info &) = 0;
  virtual Controller_ptr getStepper(PickTraversal_ptr, const Input::Event &) = 0;
  virtual void press(PickTraversal_ptr, const Input::Event &);
  virtual void release(PickTraversal_ptr, const Input::Event &);
  Controller_var    thumb;
private:
  Controller_var    stepper;
};

class Slider1D : public Slider
{
public:
  Slider1D(Axis);
  void init(Controller_ptr, BoundedValue_ptr);
//protected:
  void allocateThumb(const Allocation::Info &);
  Controller_var *getStepper(PickTraversal_ptr, const Input::Event &);
private:
  BoundedValue_var   value;
  Impl_var<Observer> observer; 
  Impl_var<Modifier> backward;
  Impl_var<Modifier> forward;
  Controller_var     backwardStepper;
  Controller_var     forwardStepper;
  Coord              offset;
  Axis               axis;
};

class Slider2D : public Slider
{
  enum { left, right, top, bottom, lefttop, righttop, leftbottom, rightbottom};
public:
  Slider2D();
  void init(Controller_ptr, BoundedValue_ptr, BoundedValue_ptr);
//protected:
  void allocateThumb(const Allocation::Info &);
  Controller_var getStepper(PickTraversal_ptr, const Input::Event &);
private:
  BoundedValue_var   xvalue;
  BoundedValue_var   yvalue;
  Impl_var<Observer> xobserver; 
  Impl_var<Observer> yobserver; 
  Impl_var<Modifier> modifiers[8];
  Controller_var     steppers[8];
  Coord              xoffset;
  Coord              yoffset;
  Vertex             thumbSize;
};

};

#endif /* _Motif_Slider_hh */
