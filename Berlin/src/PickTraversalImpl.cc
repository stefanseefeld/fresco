/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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
#include <Fresco/IO.hh>
#include "Berlin/PickTraversalImpl.hh"
#include "Berlin/PositionalFocus.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

PickTraversalImpl::PickTraversalImpl(Graphic_ptr g, Region_ptr r,
                     Transform_ptr t, PositionalFocus *f) :
    TraversalImpl(g, r, t),
    my_focus(f),
    my_cursor(0)
{
    Trace trace("PickTraversalImpl::PickTraversalImpl");
    my_this = POA_Fresco::PickTraversal::_this();
}

PickTraversalImpl::PickTraversalImpl(const PickTraversalImpl &traversal) :
    TraversalImpl(traversal),
    my_controllers(traversal.my_controllers),
    my_positions(traversal.my_positions),
    my_focus(traversal.my_focus),
    my_cursor(traversal.my_positions.back() - 1)
{
    my_this = POA_Fresco::PickTraversal::_this();
}

PickTraversalImpl::~PickTraversalImpl() { }

PickTraversalImpl &
PickTraversalImpl::operator = (const PickTraversalImpl &traversal)
{
    Trace trace("PickTraversalImpl::operator =");
    TraversalImpl::operator = (traversal);
    my_controllers = traversal.my_controllers;
    my_positions = traversal.my_positions;
    my_focus = traversal.my_focus;
    // the current graphic after a pick isn't the top most graphic in the
    // trail but the top most controller, as it's the controller which will
    // receive the event...
    my_cursor = traversal.my_positions.back() - 1;
    return *this;
}

PickTraversal_ptr PickTraversalImpl::_this()
{
    return Fresco::PickTraversal::_duplicate(my_this);
}

Region_ptr PickTraversalImpl::current_allocation()
{
    Trace trace("PickTraversalImpl::current_allocation");
    return get_allocation(my_cursor)->_this();
}

Transform_ptr PickTraversalImpl::current_transformation() 
{
    Trace trace("PickTraversalImpl::current_transformation");
    return get_transformation(my_cursor)->_this();
}

Graphic_ptr PickTraversalImpl::current_graphic()
{
    Trace trace("PickTraversalImpl::current_graphic");
    return Graphic::_duplicate(get_graphic(my_cursor));
}

void PickTraversalImpl::traverse_child(Graphic_ptr child, Tag tag,
                       Region_ptr region,
                       Transform_ptr transform)
{
    Trace trace("PickTraversalImpl::traverse_child");
    if (CORBA::is_nil(region)) region = Region_var(current_allocation());
    Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
    allocation->copy(region);
    Lease_var<TransformImpl> cumulative(Provider<TransformImpl>::provide());
    *cumulative = *get_transformation(my_cursor);
    if (!CORBA::is_nil(transform)) cumulative->premultiply(transform);
    push(child, tag, allocation, cumulative); // Keep ownership of cumulative!
    my_cursor++;
    try
    {
    child->traverse(my_this);
    }
    catch (...)
    {
    // Make sure cumulative does not go out of scope before the pop() ;-)
    my_cursor--;
    pop();
    throw;
    }
    my_cursor--;
    pop(); // cumulative still in scope... 
}

void PickTraversalImpl::visit(Fresco::Graphic_ptr g) { g->pick(my_this); }
Fresco::Traversal::order PickTraversalImpl::direction()
{ return Fresco::Traversal::down; }
CORBA::Boolean PickTraversalImpl::ok() { return !picked(); }

CORBA::Boolean PickTraversalImpl::intersects_allocation()
{
    Region_var region = current_allocation();
    return intersects_region(region);
}

void PickTraversalImpl::enter_controller(Controller_ptr c)
{
    Trace trace("PickTraversal::enter_controller");
    my_controllers.push_back(Controller::_duplicate(c));
    my_positions.push_back(size());
}

void PickTraversalImpl::leave_controller()
{
    Trace trace("PickTraversal::leave_controller");
    my_controllers.pop_back();
    my_positions.pop_back();
}

Focus_ptr PickTraversalImpl::get_focus()
{ return my_focus ? my_focus->_this() : Focus::_nil(); }
CORBA::Boolean PickTraversalImpl::forward()
{
    if (my_cursor + 1 < size()) { ++my_cursor; return true; }
    return false;
}

CORBA::Boolean PickTraversalImpl::backward()
{
    if (my_cursor > my_positions.back()) { --my_cursor; return true; }
    return false;
}
