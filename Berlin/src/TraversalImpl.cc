/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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
#include "Berlin/RegionImpl.hh"
#include "Berlin/Logger.hh"
#include "Warsaw/Allocation.hh"
#include "Warsaw/Graphic.hh"
#include "Warsaw/Region.hh"

TraversalImpl::TraversalImpl(Graphic_ptr g, Region_ptr r, Transform_ptr t)
{
  TransformImpl *transform = new TransformImpl;
  transform->_obj_is_ready(CORBA::BOA::getBOA());
  transform->copy(t);
  push(g, r, transform);
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
  return Region::_duplicate(stack.back().allocation);
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

void TraversalImpl::traverseChild(Graphic_ptr child, Region_ptr region, Transform_ptr t)
{
  SectionLog section(Logger::traversal, "TraversalImpl::traverseChild");
  if (CORBA::is_nil(region)) region = Region_var(allocation());
  TransformImpl *cumulative = new TransformImpl;
  cumulative->_obj_is_ready(_boa());
  cumulative->copy(transformation());
  if (!CORBA::is_nil(t)) cumulative->premultiply(t);
#if 1
  push(child, region, cumulative);
  child->traverse(Traversal_var(_this()));
  pop();
#else
  Allocation::Info_var info = new Allocation::Info;
  info->allocation = Region::_duplicate(region);
  info->transformation = cumulative->_this();
  RegionImpl *ext = new RegionImpl;
  ext->_obj_is_ready(_boa());
  child->extension(info, Region_var(ext->_this()));
  if (intersectsRegion(Region_var(ext->_this())))
      {
	push(child, region, cumulative);
	child->traverse(Traversal_var(_this()));
	pop();
      }
  ext->_dispose();
#endif
}

void TraversalImpl::push(Graphic_ptr g, Region_ptr r, TransformImpl *t)
{
  SectionLog section(Logger::traversal, "TraversalImpl::push");
  RegionImpl region(r, t->_this());
  State state;
  state.graphic = Graphic::_duplicate(g);
  state.allocation = Region::_duplicate(r);
  state.transformation = t;
  stack.push_back(state);
}

void TraversalImpl::pop()
{
  SectionLog section(Logger::traversal, "TraversalImpl::pop");
  State &state = *stack.rbegin();
  state.transformation->_dispose();
  stack.erase(stack.end() - 1);
}

// Graphic_ptr TraversalImpl::graphic()
// {
//   return Graphic::_duplicate(stack.back().graphic);
// }
