/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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
#include <Warsaw/config.hh>
#include <Warsaw/Allocation.hh>
#include <Warsaw/Graphic.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/IO.hh>
#include <Prague/Sys/Tracer.hh>
#include "Berlin/Provider.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/RefCountVar.hh"
#include "Berlin/TraversalImpl.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/RegionImpl.hh"

using namespace Prague;
using namespace Warsaw;

TraversalImpl::TraversalImpl(Graphic_ptr g, Region_ptr r, Transform_ptr t)
{
  Trace trace("TraversalImpl::TraversalImpl");
  Lease_var<TransformImpl> transform(Provider<TransformImpl>::provide());
  transform->copy(t);
  push(g, 0, r, transform._retn());
}

TraversalImpl::TraversalImpl(const TraversalImpl &t)
{
  Trace trace("TraversalImpl::TraversalImpl copy ctor");
  for (stack_t::const_iterator i = t.stack.begin(); i != t.stack.end(); i++)
    {
      State state;
      state.graphic = Graphic::_duplicate((*i).graphic);
      state.id = (*i).id;
      state.allocation = Region::_duplicate((*i).allocation);
      state.transformation = Provider<TransformImpl>::provide();
      state.transformation->copy(Transform_var((*i).transformation->_this()));
      stack.push_back(state);
    }
}

TraversalImpl::~TraversalImpl()
{
}

Region_ptr TraversalImpl::allocation()
{
  Trace trace("TraversalImpl::allocation");
  return Region::_duplicate(stack.back().allocation);
}

Transform_ptr TraversalImpl::transformation() 
{
  Trace trace("TraversalImpl::transformation");
  return stack.back().transformation->_this();
}

CORBA::Boolean TraversalImpl::bounds(Vertex &lower, Vertex &upper, Vertex &origin) 
{
  Trace trace("TraversalImpl::bounds");
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

void TraversalImpl::traverse_child(Graphic_ptr child, Tag tag, Region_ptr region, Transform_ptr transform)
{
  Trace trace("TraversalImpl::traverse_child");
  if (CORBA::is_nil(region)) region = Region_var(allocation());
  Lease_var<TransformImpl> cumulative(Provider<TransformImpl>::provide());
  cumulative->copy(Transform_var(transformation()));
  if (!CORBA::is_nil(transform)) cumulative->premultiply(transform);
  push(child, tag, region, cumulative._retn());
  try { child->traverse(Traversal_var(_this()));}
  catch (...) { pop(); throw;}
  pop(); 
}

void TraversalImpl::push(Graphic_ptr g, Tag id, Region_ptr r, TransformImpl *t)
{
  Trace trace("TraversalImpl::push");
  State state;
  state.graphic = Graphic::_duplicate(g);
  state.id = id;
  state.allocation = Region::_duplicate(r);
  state.transformation = t;
  stack.push_back(state);
}

void TraversalImpl::pop()
{
  Trace trace("TraversalImpl::pop");
  Provider<TransformImpl>::adopt((stack.end() - 1)->transformation);
  stack.erase(stack.end() - 1);
}

void TraversalImpl::update()
{
  Trace trace("TraversalImpl::update");
  if (stack.size() == 1) return;
  stack_t::iterator parent = stack.begin();
  Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
  allocation->copy((*parent).allocation);
  Lease_var<TransformImpl> transformation(Provider<TransformImpl>::provide());
  transformation->copy(Transform_var((*parent).transformation->_this()));
  Allocation::Info info;
  info.allocation = allocation->_this();
  info.transformation = transformation->_this();
  for (stack_t::iterator child = parent + 1; child != stack.end(); parent++, child++)
    {
      (*parent).graphic->allocate((*child).id, info);
      (*child).allocation->copy(info.allocation);
      (*child).transformation->copy(info.transformation);
    }
}
