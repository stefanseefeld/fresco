/*$Id$
 *
 * This source file is a part of the Berlin Project.
 *
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 *
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
#include "Berlin/TraversalImpl.hh"
#include "Berlin/TransformImpl.hh"
#include "Warsaw/Graphic.hh"

TraversalImpl::TraversalImpl(Region_ptr r)
//   : stack(20)
{
  push(0, 0, r, 0);
}

TraversalImpl::TraversalImpl(const TraversalImpl &t)
//   : stack(20)
{
  for (Stack::const_iterator i = t.stack.begin(); i != t.stack.end(); i++)
    {
      const State &state = *i;
      State s;
      s.graphic = Graphic::_duplicate(state.graphic);
      s.offset = GraphicOffset::_duplicate(state.offset);
      if (CORBA::is_nil(s.graphic) && !CORBA::is_nil(s.offset))
 	s.graphic = s.offset->Child();
      s.allocation = Region::_duplicate(state.allocation);
      s.transformation = Transform::_duplicate(state.transformation);
      stack.push_back(s);
    }
}

TraversalImpl::~TraversalImpl()
{
  for (Stack::iterator i = stack.begin(); i != stack.end(); i++)
    {
      State &state = *i;
      CORBA::release(state.graphic);
      CORBA::release(state.offset);
      CORBA::release(state.allocation);
      CORBA::release(state.transformation);
    }
}

Region_ptr TraversalImpl::allocation() 
{
  return stack.back().allocation;
}

Transform_ptr TraversalImpl::transformation() 
{
  return stack.back().transformation;
}

CORBA::Boolean TraversalImpl::bounds(Vertex &lower, Vertex &upper, Vertex &origin) 
{
  bool b = false;
  State &state = stack.back();
  Region_ptr r = state.allocation;
  if (!CORBA::is_nil(r))
    {
      r->bounds(lower, upper);
      r->origin(origin);
      b = true;
    }
  return b;
}

// CORBA::Boolean visible() 
// {
//   return true;
// }

void TraversalImpl::traverseChild(GraphicOffset_ptr o, Region_ptr allocation, Transform_ptr transformation)
{
  if (CORBA::is_nil(allocation))
    allocation = this->allocation();
  TransformImpl *cumulative = new TransformImpl;
  cumulative->_obj_is_ready(_boa());
  cumulative->copy(stack.back().transformation);
  cumulative->premultiply(transformation);
  push(o->Child(), o, allocation, cumulative->_this());
  o->traverse(this);
  pop();
}

void TraversalImpl::visit(Graphic_ptr) {}

// Traversal_ptr TraversalImpl::trail() { return new TraversalImpl(*this);}

void TraversalImpl::push(Graphic_ptr g, GraphicOffset_ptr o, Region_ptr r, Transform_ptr t)
{
  State state;
  state.graphic = Graphic::_duplicate(g);
  state.offset = GraphicOffset::_duplicate(o);
  state.allocation = Region::_duplicate(r);
  state.transformation = Transform::_duplicate(t);
  stack.push_back(state);
}

void TraversalImpl::pop()
{
  State &state = *stack.rbegin();
  CORBA::release(state.graphic);
  CORBA::release(state.offset);
  CORBA::release(state.allocation);
  CORBA::release(state.transformation);
  stack.erase(stack.end());
}

// TraversalImpl::State *TraversalImpl::top() { return stack.size() ? *stack.begin() : 0;}
