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

TraversalImpl::~TraversalImpl()
{
}

Region_ptr TraversalImpl::current_allocation()
{
  Trace trace("TraversalImpl::current_allocation");
  return Region::_duplicate(_stack.back().allocation);
}

Transform_ptr TraversalImpl::current_transformation() 
{
  Trace trace("TraversalImpl::current_transformation");
  return _stack.back().transformation->_this();
}

Graphic_ptr TraversalImpl::current_graphic()
{
  Trace trace("TraversalImpl::current_graphic");
  return Graphic::_duplicate(_stack.back().graphic);
}

CORBA::Boolean TraversalImpl::bounds(Vertex &lower, Vertex &upper, Vertex &origin) 
{
  Trace trace("TraversalImpl::bounds");
  bool b = false;
  State &state = _stack.back();
  Region_ptr r = state.allocation;
  if (!CORBA::is_nil(r))
    {
      r->bounds(lower, upper);
      r->origin(origin);
      b = true;
    }
  return b;
}

void TraversalImpl::push(Graphic_ptr g, Tag id, Region_ptr r, TransformImpl *t)
{
  Trace trace("TraversalImpl::push");
  Lease_var<TransformImpl> tmp(t);
  _stack.push_back(State(g, id, r, tmp._retn()));
}

void TraversalImpl::pop()
{
  Trace trace("TraversalImpl::pop");
  _stack.erase(_stack.end() - 1);
}

void TraversalImpl::update()
{
  Trace trace("TraversalImpl::update");
  if (_stack.size() == 1) return;
  stack_t::iterator parent = _stack.begin();
  Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
  allocation->copy((*parent).allocation);
  Lease_var<TransformImpl> transformation(Provider<TransformImpl>::provide());
  transformation->copy(Transform_var((*parent).transformation->_this()));
  Allocation::Info info;
  info.allocation = allocation->_this();
  info.transformation = transformation->_this();
  for (stack_t::iterator child = parent + 1; child != _stack.end(); parent++, child++)
    {
      (*parent).graphic->allocate((*child).id, info);
      (*child).allocation->copy(info.allocation);
      (*child).transformation->copy(info.transformation);
    }
}
