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
#ifndef _Motif_Panner_hh
#define _Motif_Panner_hh

#include <Warsaw/config.hh>
#include <Warsaw/Command.hh>
#include <Warsaw/BoundedRange.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ControllerImpl.hh>

namespace Motif
{

class Panner : public ControllerImpl
{
  struct Offset
  {
    Coord lower;
    Coord upper;
  }; 
  class Observer : public ObserverImpl
  {
  public:
    Observer(Panner *p) : panner(p) {}
    void update(const CORBA::Any &any) { panner->update(any);}
  private:
    Panner *panner;
  };
  friend class Observer;
  class Dragger;
public:
  Panner(BoundedRange_ptr, BoundedRange_ptr);
  void init(Controller_ptr);
  virtual void update(const CORBA::Any &);
  virtual void draw(DrawTraversal_ptr);
  virtual void pick(PickTraversal_ptr);
  virtual void allocate(Tag, const Allocation::Info &);
  Command_ptr drag();
private:
  void traverseThumb(Traversal_ptr);
  Impl_var<Observer> redirect;
  Impl_var<Dragger> _drag;
  BoundedRange_var x;
  BoundedRange_var y;
  Offset offset[2];
};

};

#endif /* _Motif_Panner_hh */
