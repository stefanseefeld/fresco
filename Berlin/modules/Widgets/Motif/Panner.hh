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
#include <Warsaw/BoundedRange.hh>
#include <Berlin/RefCountVar.hh>
#include "Widget/Motif/Adjustable.hh"

namespace Motif
{

class Panner : public Adjustable
{
  struct Offset
  {
    Warsaw::Coord lower;
    Warsaw::Coord upper;
  }; 
public:
  Panner(Warsaw::BoundedRange_ptr, Warsaw::BoundedRange_ptr);
  void init(Warsaw::Controller_ptr);
  virtual void draw(Warsaw::DrawTraversal_ptr);
  virtual void pick(Warsaw::PickTraversal_ptr);
  virtual void allocate(Warsaw::Tag, const Warsaw::Allocation::Info &);
protected:
  virtual void update(const CORBA::Any &any);
  virtual void adjust(const Warsaw::OriginatedDelta &);
private:
  void traverse_thumb(Warsaw::Traversal_ptr);
  RefCount_var<Warsaw::BoundedRange> _xvalue;
  RefCount_var<Warsaw::BoundedRange> _yvalue;
  Offset _offset[2];
};

};

#endif
