/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#include <Berlin/Provider.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/CommandImpl.hh>
#include "Scrollbar.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin::WidgetKit::Motif;

Scrollbar::Scrollbar(BoundedRange_ptr v, Axis a,
		     const Fresco::Graphic::Requisition &r) :
    my_requisition(r),
    my_value(RefCount_var<BoundedRange>::increment(v)),
    my_axis(a)
{
    Trace trace("Scrollbar::Scrollbar");
    BoundedRange::Settings settings = my_value->state();
    my_offset.lower = settings.lvalue/(settings.upper - settings.lower);
    my_offset.upper = settings.uvalue/(settings.upper - settings.lower);
    my_value->attach(Observer_var(observer()));
}

void Scrollbar::init(Controller_ptr t)
{
    Trace trace("Scrollbar::init");
    body(t);
    t->add_parent_graphic(Graphic_var(_this()), 0);
    append_controller(t);
}

void Scrollbar::draw(DrawTraversal_ptr traversal)
{ traverse_thumb(traversal); }

void Scrollbar::pick(PickTraversal_ptr traversal)
{
//   if (grabbed(traversal->device()) ||
//       traversal->intersects_allocation())
    if (traversal->intersects_allocation())
    {
	traversal->enter_controller(Controller_var(_this()));
	MonoGraphic::traverse(traversal);
//       if (!grabbed(traversal->device())) traverse_thumb(traversal);
	traverse_thumb(traversal);
	if (!traversal->picked()) traversal->hit();
	traversal->leave_controller();
    }
}

void Scrollbar::allocate(Tag, const Allocation::Info &info)
{
    Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
    allocation->copy(info.allocation);
    if (my_axis == xaxis)
    {
	Coord lower = allocation->lower.x;
	Coord scale = allocation->upper.x - allocation->lower.x;
	allocation->lower.x = lower + scale*my_offset.lower;
	allocation->upper.x = lower + scale*my_offset.upper;
    }
    else
    {
	Coord lower = allocation->lower.y;
	Coord scale = allocation->upper.y - allocation->lower.y;
	allocation->lower.y = lower + scale*my_offset.lower;
	allocation->upper.y = lower + scale*my_offset.upper;
    }
    allocation->lower.z = allocation->upper.z = 0.;
    allocation->normalize(info.transformation);
}

void Scrollbar::adjust(const OriginatedDelta &od)
{
    Vertex origin = od.origin;
    Vertex newpt = od.origin;
    newpt.x += od.delta.x;
    newpt.y += od.delta.y;
    
    my_pickTrafo.inverse_transform_vertex(origin);
    my_pickTrafo.inverse_transform_vertex(newpt);
    
    Coord delta;
    
    if (my_axis == xaxis)
    {
	delta = newpt.x - origin.x;
	if (origin.x < 0.)
	    delta = std::max(origin.x + delta, 0.);
	else if (origin.x > my_length)
	    delta = std::min(origin.x + delta, 0.);
	
    }
    else if (my_axis == yaxis)
    {
	delta = newpt.y - origin.y;
	if (origin.y < 0.)
	    delta = std::max(origin.y + delta, 0.);
	else if (origin.y > my_length)
	    delta = std::min(origin.y + delta, 0.);
    }
    if (delta != 0.) my_value->adjust(my_scale*delta);
}

void Scrollbar::update(const CORBA::Any &any)
{
    BoundedRange::Settings *settings;
    any >>= settings;
    my_offset.lower = (settings->lvalue - settings->lower)/
	(settings->upper - settings->lower);
    my_offset.upper = (settings->uvalue - settings->lower)/
	(settings->upper - settings->lower);
    need_redraw();
}

void Scrollbar::traverse_thumb(Traversal_ptr traversal)
{
    Graphic_var child = body();
    if (CORBA::is_nil(child)) return;
    Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
    allocation->copy(Region_var(traversal->current_allocation()));
    Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
    tx->load_identity();
    if (my_axis == xaxis)
    {
	Coord lower = allocation->lower.x;
	Coord scale = allocation->upper.x - allocation->lower.x;
	my_length = scale;
	allocation->lower.x = lower + scale*my_offset.lower;
	allocation->upper.x = lower + scale*my_offset.upper;
	allocation->lower.z = allocation->upper.z = 0.;
    }
    else if (my_axis == yaxis)
    {
	Coord lower = allocation->lower.y;
	Coord scale = allocation->upper.y - allocation->lower.y;
	my_length = scale;
	allocation->lower.y = lower + scale*my_offset.lower;
	allocation->upper.y = lower + scale*my_offset.upper;
    }
    allocation->lower.z = allocation->upper.z = 0.;
    allocation->normalize(Transform_var(tx->_this()));
    my_scale = (my_value->upper() - my_value->lower())/my_length;
    my_pickTrafo.copy(traversal->current_transformation());
    try
    {
	traversal->traverse_child(child, 0,
				  Region_var(allocation->_this()),
				  Transform_var(tx->_this()));
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { body(Fresco::Graphic::_nil()); }
    catch (const CORBA::COMM_FAILURE &)
    { body(Fresco::Graphic::_nil()); }
}
