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
  class SObserver : implements(Observer)
  {
  public:
    SObserver(Slider *s) : slider(s) {}
    void update(const CORBA::Any &any) { slider->update(any);}
  private:
    Slider *slider;
  };
  friend class SObserver;
  class Modifier : implements(Command) {};
public:
  Slider(BoundedValue_ptr, Axis, const Requisition &);
  void init(Controller_ptr);
  virtual void request(Requisition &r) { r = requisition;}
  virtual void update(const CORBA::Any &);
  virtual void draw(DrawTraversal_ptr);
  virtual void pick(PickTraversal_ptr);
  virtual void allocate(Tag, const Allocation::Info &);
  Command_ptr drag() { return _drag->_this();}
private:
  void traverseThumb(Traversal_ptr);
  Requisition requisition;
  Impl_var<SObserver> redirect;
  Impl_var<Modifier> _drag;
  BoundedValue_var range;
  Coord offset;
  Axis axis;
};

};

#endif /* _Motif_Slider_hh */
