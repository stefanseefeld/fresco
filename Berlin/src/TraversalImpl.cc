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
{
  TransformImpl *transform = new TransformImpl;
  transform->_obj_is_ready(CORBA::BOA::getBOA());
  push(Graphic::_nil(), Region::_duplicate(r), transform);
}

TraversalImpl::TraversalImpl(const TraversalImpl &t)
{
  for (stack_t::const_iterator i = t.stack.begin(); i != t.stack.end(); i++)
    {
      State state;
      state.graphic = Graphic::_duplicate((*i).graphic);
      state.allocation = Region::_duplicate((*i).allocation);
      TransformImpl *transform = new TransformImpl;
      transform->_obj_is_ready(CORBA::BOA::getBOA());
      transform->copy((*i).transformation);
      state.transformation = transform;
      stack.push_back(state);
    }
}

TraversalImpl::~TraversalImpl()
{
  for (stack_t::const_iterator i = stack.begin(); i != stack.end(); i++)
    (*i).transformation->_dispose();
}

Region_ptr TraversalImpl::allocation()
{
  return stack.back().allocation;
}

Transform_ptr TraversalImpl::transformation() 
{
  return stack.back().transformation->_this();
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

void TraversalImpl::traverseChild(Graphic_ptr g, Region_ptr a, Transform_ptr t)
{
  if (CORBA::is_nil(a)) a = allocation();
  TransformImpl *cumulative = new TransformImpl;
  cumulative->_obj_is_ready(_boa());
  cumulative->copy(transformation());
  if (!CORBA::is_nil(t)) cumulative->premultiply(t);
  push(g, a, cumulative);
  g->traverse(_this());
  pop();
}

void TraversalImpl::push(Graphic_ptr g, Region_ptr r, TransformImpl *t)
{
  State state;
  state.graphic = Graphic::_duplicate(g);
  state.allocation = Region::_duplicate(r);
  state.transformation = t;
  stack.push_back(state);
}

void TraversalImpl::pop()
{
  State &state = *stack.rbegin();
  CORBA::release(state.graphic);
  CORBA::release(state.allocation);
  state.transformation->_dispose();
  stack.erase(stack.end() - 1);
}
