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
#include <Berlin/ControllerImpl.hh>
#include <Berlin/ImplVar.hh>

namespace Motif
{

class Scrollbar : public ControllerImpl
{
  struct Offset
  {
    Coord lower;
    Coord upper;
  }; 
  class SObserver : implements(Observer)
  {
  public:
    SObserver(Scrollbar *s) : scrollbar(s) {}
    void update(const CORBA::Any &any) { scrollbar->update(any);}
  private:
    Scrollbar *scrollbar;
  };
  friend class SObserver;
  class Modifier : implements(Command) {};
public:
  Scrollbar(BoundedRange_ptr, Axis);
  void init(Controller_ptr);
  virtual void update(const CORBA::Any &);
  virtual void draw(DrawTraversal_ptr);
  virtual void pick(PickTraversal_ptr);
  virtual void allocate(Tag, const Allocation::Info &);
  Command_ptr drag() { return _drag->_this();}
private:
  void traverseThumb(Traversal_ptr);
  Controller_var thumb;
  Impl_var<SObserver> redirect;
  Impl_var<Modifier> _drag;
  BoundedRange_var range;
  Offset offset;
  Axis axis;
};

};

#endif /* _Motif_Scrollbar_hh */
