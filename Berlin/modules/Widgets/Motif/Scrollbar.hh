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
#ifndef _Motif_Scrollbar_hh
#define _Motif_Scrollbar_hh

#include <Warsaw/config.hh>
#include <Warsaw/Command.hh>
#include <Warsaw/BoundedRange.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ObserverImpl.hh>
#include <Berlin/ControllerImpl.hh>
#include <Berlin/RefCountVar.hh>

namespace Motif
{

class Scrollbar : public ControllerImpl
{
  struct Offset
  {
    Warsaw::Coord lower;
    Warsaw::Coord upper;
  }; 
  class Observer : public ObserverImpl
  {
  public:
    Observer(Scrollbar *s) : scrollbar(s) {}
    void update(const CORBA::Any &any) { scrollbar->update(any);}
  private:
    Scrollbar *scrollbar;
  };
  friend class Observer;
  class Dragger;
public:
  Scrollbar(Warsaw::BoundedRange_ptr, Warsaw::Axis, const Warsaw::Graphic::Requisition &);
  void init(Warsaw::Controller_ptr);
  virtual void request(Warsaw::Graphic::Requisition &r) { r = requisition;}
  virtual void update(const CORBA::Any &);
  virtual void draw(Warsaw::DrawTraversal_ptr);
  virtual void pick(Warsaw::PickTraversal_ptr);
  virtual void allocate(Warsaw::Tag, const Warsaw::Allocation::Info &);
  Warsaw::Command_ptr drag();
private:
  void traverseThumb(Warsaw::Traversal_ptr);
  Warsaw::Graphic::Requisition requisition;
  Impl_var<Observer> translate;
  Impl_var<Dragger> _drag;
  RefCount_var<Warsaw::BoundedRange> range;
  Offset offset;
  Warsaw::Axis axis;
};

};

#endif
