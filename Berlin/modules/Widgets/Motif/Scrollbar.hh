/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
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

#include <Fresco/config.hh>
#include <Fresco/BoundedRange.hh>
#include <Berlin/RefCountVar.hh>
#include "Adjustable.hh"

namespace Motif
{

class Scrollbar : public Adjustable
{
  struct Offset
  {
    Fresco::Coord lower;
    Fresco::Coord upper;
  }; 
public:
  Scrollbar(Fresco::BoundedRange_ptr, Fresco::Axis, const Fresco::Graphic::Requisition &);
  void init(Fresco::Controller_ptr);
  virtual void request(Fresco::Graphic::Requisition &r) { r = _requisition;}
  virtual void draw(Fresco::DrawTraversal_ptr);
  virtual void pick(Fresco::PickTraversal_ptr);
  virtual void allocate(Fresco::Tag, const Fresco::Allocation::Info &);
protected:
  virtual void update(const CORBA::Any &any);
  virtual void adjust(const Fresco::OriginatedDelta &);
private:
  void traverse_thumb(Fresco::Traversal_ptr);
  Fresco::Graphic::Requisition _requisition;
  RefCount_var<Fresco::BoundedRange> _value;
  Offset _offset;
  Fresco::Axis _axis;
  TransformImpl _pickTrafo; // transformation at the last pick traversal.
  double _length;
  double _scale;
};

};

#endif
