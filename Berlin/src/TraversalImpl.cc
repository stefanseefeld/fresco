/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
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
#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/Allocation.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/Region.hh>
#include <Fresco/IO.hh>
#include "Berlin/Provider.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/RefCountVar.hh"
#include "Berlin/TraversalImpl.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/RegionImpl.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

TraversalImpl::TraversalImpl(Graphic_ptr g, Region_ptr a, Transform_ptr t)
{
    Trace trace("TraversalImpl::TraversalImpl");
    Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
    allocation->copy(a);
    Lease_var<TransformImpl> transform(Provider<TransformImpl>::provide());
    transform->copy(t);
    push(g, 0, allocation._retn(), transform._retn());
}

TraversalImpl::TraversalImpl(const TraversalImpl &traversal) :
    my_stack(traversal.size())
{
    Trace trace("TraversalImpl::TraversalImpl(const TraversalImpl &)");
    // explicitely copy the stack so we are the owner and can delete it
    // in the destructor
    my_stack.reserve(traversal.my_stack.size());
    stack_t::iterator i = my_stack.begin();
    stack_t::const_iterator j = traversal.my_stack.begin();
    for (; i != my_stack.end(); ++i, ++j)
    {
    (*i).graphic = Fresco::Graphic::_duplicate((*j).graphic);
    (*i).id      = (*j).id;
    (*i).allocation = Provider<RegionImpl>::provide();
    *(*i).allocation = *(*j).allocation;
    (*i).transformation = Provider<TransformImpl>::provide();
    *(*i).transformation = *(*j).transformation;
    };
}

TraversalImpl::~TraversalImpl()
{
    clear();
    State &state = my_stack.front();
    CORBA::release(state.graphic);
    Provider<RegionImpl>::adopt(state.allocation);
    Provider<TransformImpl>::adopt(state.transformation);
}

TraversalImpl &TraversalImpl::operator = (const TraversalImpl &traversal)
{
    Trace trace("TraversalImpl::operator = (const TraversalImpl &)");
    clear();
    // explicitely copy the stack so we are the owner and can delete it
    // in the destructor
    my_stack.resize(traversal.my_stack.size());
    stack_t::iterator i = my_stack.begin();
    stack_t::const_iterator j = traversal.my_stack.begin();
    if (i == my_stack.end() || j == traversal.my_stack.end()) return *this;
    for (++i, ++j; i != my_stack.end(); ++i, ++j)
    {
    (*i).graphic = Fresco::Graphic::_duplicate((*j).graphic);
    (*i).id      = (*j).id;
    (*i).allocation = Provider<RegionImpl>::provide();
    *(*i).allocation = *(*j).allocation;
    (*i).transformation = Provider<TransformImpl>::provide();
    *(*i).transformation = *(*j).transformation;
    };
    return *this;
}

Region_ptr TraversalImpl::current_allocation()
{
    Trace trace("TraversalImpl::current_allocation");
    return my_stack.back().allocation->_this();
}

Transform_ptr TraversalImpl::current_transformation() 
{
    Trace trace("TraversalImpl::current_transformation");
    return my_stack.back().transformation->_this();
}

Graphic_ptr TraversalImpl::current_graphic()
{
    Trace trace("TraversalImpl::current_graphic");
    return Graphic::_duplicate(my_stack.back().graphic);
}

CORBA::Boolean TraversalImpl::bounds(Vertex &lower, Vertex &upper,
                     Vertex &origin) 
{
    Trace trace("TraversalImpl::bounds");
    my_stack.back().allocation->bounds(lower, upper);
    return true;
}

void TraversalImpl::push(Graphic_ptr g, Tag id, RegionImpl *r, TransformImpl *t)
{
    Trace trace("TraversalImpl::push");
    // We do not own anything but we push onto the stack.
    // Exception: The transformation at the very first push. That won't get
    // popped, so that's OK;-)
    my_stack.push_back(State(g, id, r, t));
}

void TraversalImpl::pop()
{
    Trace trace("TraversalImpl::pop");
    // We do not own anything, so we don't clean up after ourselves.
    my_stack.erase(my_stack.end() - 1);
}

void TraversalImpl::update()
{
    Trace trace("TraversalImpl::update");
    if (my_stack.size() == 1) return;
    stack_t::iterator parent = my_stack.begin();
    Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
    *allocation = *(*parent).allocation;
    Lease_var<TransformImpl>
    transformation(Provider<TransformImpl>::provide());
    *transformation = *(*parent).transformation;
    Allocation::Info info;
    info.allocation = allocation->_this();
    info.transformation = transformation->_this();
    for (stack_t::iterator child = parent + 1;
     child != my_stack.end();
     ++parent, ++child)
    {
    // recompute the allocation info for the child, given the (just
    // updated) allocation for the parent
    (*parent).graphic->allocate((*child).id, info);
    *(*child).allocation = *allocation;
    *(*child).transformation = *transformation;
    }
}

void TraversalImpl::clear()
{
    // DO NOT CALL DURING A TRAVERSAL.
    
    // After the Traversal is done it is empty anyway (except for the
    // very first push done in the constructor), so we won't
    // delete anything we do not own. If there is something left, then
    // we were a momento, a deep copy of another partial
    // Traversal: We own everything and must release it on our
    // own.
    if (my_stack.begin() == my_stack.end()) return;
    for (stack_t::iterator i = my_stack.begin() + 1; i != my_stack.end(); ++i)
    {
    CORBA::release((*i).graphic);
    Provider<RegionImpl>::adopt((*i).allocation);
    Provider<TransformImpl>::adopt((*i).transformation);
    }
    my_stack.erase(my_stack.begin() + 1, my_stack.end());
}
