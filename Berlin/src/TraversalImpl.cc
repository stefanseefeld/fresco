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
#include "Berlin/TraversalImpl.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/Providers.hh"
#include <Warsaw/Allocation.hh>
#include <Warsaw/Graphic.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/IO.hh>
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

TraversalImpl::TraversalImpl(Graphic_ptr g, Region_ptr r, Transform_ptr t)
{
  Lease<TransformImpl> transform;
  Providers::trafo.provide(transform);  
  transform->copy(t);
  push(g, 0, r, transform.release());
}

TraversalImpl::TraversalImpl(const TraversalImpl &t)
{
  //Trace trace("TraversalImpl::TraversalImpl copy ctor");
  for (stack_t::const_iterator i = t.stack.begin(); i != t.stack.end(); i++)
    {
      State state;
      state.graphic = Graphic::_duplicate((*i).graphic);
      state.tag = (*i).tag;
      state.allocation = Region::_duplicate((*i).allocation);
      Lease<TransformImpl> tmp;
      Providers::trafo.provide(tmp);
      state.transformation = tmp.release();
      state.transformation->copy((*i).transformation);
      stack.push_back(state);
    }
}

TraversalImpl::~TraversalImpl()
{
}

Region_ptr TraversalImpl::allocation()
{
  //Trace trace("TraversalImpl::allocation");
  return Region::_duplicate(stack.back().allocation);
}

Transform_ptr TraversalImpl::transformation() 
{
  //Trace trace("TraversalImpl::transformation");
  return stack.back().transformation->_this();
}

CORBA::Boolean TraversalImpl::bounds(Vertex &lower, Vertex &upper, Vertex &origin) 
{
  //Trace trace("TraversalImpl::bounds");
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

void TraversalImpl::traverseChild(Graphic_ptr child, Tag tag, 
				  Region_ptr region, Transform_ptr transform)
{
  //Trace trace("TraversalImpl::traverseChild");
  if (CORBA::is_nil(region)) region = Region_var(allocation());
  Lease<TransformImpl> cumulative;
  Providers::trafo.provide(cumulative);  
  cumulative->copy(transformation());
  if (!CORBA::is_nil(transform)) cumulative->premultiply(transform);
  push(child, tag, region, cumulative.release());
  child->traverse(Traversal_var(_this()));
  pop();
}

void TraversalImpl::push(Graphic_ptr g, Tag tag, Region_ptr r, TransformImpl *t)
{
  //Trace trace("TraversalImpl::push");
  //   cout << "TraversalImpl::push " << stack.size() << endl;
  //   cout << t->matrix();
  State state;
  state.graphic = Graphic::_duplicate(g);
  state.tag = tag;
  state.allocation = Region::_duplicate(r);
  state.transformation = t;
  stack.push_back(state);
}

void TraversalImpl::pop()
{
  //Trace trace("TraversalImpl::pop");
  if (!stack.empty()) Providers::trafo.adopt((stack.end() - 1)->transformation);
  stack.erase(stack.end() - 1);
}

void TraversalImpl::update()
{
  //Trace trace("TraversalImpl::update");
  if (stack.size() == 1) return;
  stack_t::iterator parent = stack.begin();
  Lease<RegionImpl> allocation;
  Providers::region.provide(allocation);  
  allocation->copy((*parent).allocation);
  Lease<TransformImpl> transformation;
  Providers::trafo.provide(transformation);  
  transformation->copy((*parent).transformation);
  Allocation::Info info;
  info.allocation = allocation->_this();
  info.transformation = transformation->_this();
  for (stack_t::iterator child = parent + 1; child != stack.end(); parent++, child++)
    {
      (*parent).graphic->allocate((*child).tag, info);
      (*child).allocation->copy(info.allocation);
      (*child).transformation->copy(info.transformation);
    }
}
