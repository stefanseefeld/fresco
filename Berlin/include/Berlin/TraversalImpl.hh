/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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
#ifndef _TraversalImpl_h
#define _TraversalImpl_h

#include <Warsaw/config.hh>
#include <Warsaw/Traversal.hh>
#include <vector>

class TraversalImpl : implements(Traversal)
{
  struct State
  {
    Graphic_ptr graphic;
    GraphicOffset_ptr offset;
    Region_ptr allocation;
    Transform_ptr transformation;    
  };
public:
  TraversalImpl(Region_ptr);
  TraversalImpl(const TraversalImpl &);
  ~TraversalImpl();
  Region_ptr allocation();
  Transform_ptr transformation();
  CORBA::Boolean bounds(Vertex &, Vertex &, Vertex &);
  CORBA::Boolean intersects() = 0;
//   Traversal_ptr trail();
  void push(Graphic_ptr, GraphicOffset_ptr, Region_ptr, Transform_ptr);
  void pop();
  void traverseChild(GraphicOffset_ptr, Region_ptr, Transform_ptr);
  void visit(Graphic_ptr);
  order direction() = 0;
  CORBA::Boolean ok() = 0;
protected: // private: ??
  typedef vector<State> Stack;
  Stack stack;
};

#endif /* _TraversalImpl_h */
