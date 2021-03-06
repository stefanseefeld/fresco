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
#include <Berlin/RegionImpl.hh>
#include <Berlin/CommandImpl.hh>
#include "Panner.hh"
#include <utility>

using namespace Prague;
using namespace Fresco;
using namespace Berlin::WidgetKit::Motif;

Panner::Panner(BoundedRange_ptr xx, BoundedRange_ptr yy) :
    my_xvalue(RefCount_var<BoundedRange>::increment(xx)),
    my_yvalue(RefCount_var<BoundedRange>::increment(yy))
{
    BoundedRange::Settings settings = my_xvalue->state();
    my_offset[xaxis].lower = 
    settings.lvalue/(settings.upper - settings.lower);
    my_offset[xaxis].upper =
    settings.uvalue/(settings.upper - settings.lower);
    settings = my_yvalue->state();
    my_offset[yaxis].lower =
    settings.lvalue/(settings.upper - settings.lower);
    my_offset[yaxis].upper =
    settings.uvalue/(settings.upper - settings.lower);
    my_xvalue->attach(Observer_var(observer()));
    my_yvalue->attach(Observer_var(observer()));
}

void Panner::init(Controller_ptr t)
{
    body(t);
    t->add_parent_graphic(Graphic_var(_this()), 0);
    append_controller(t);
}

void Panner::draw(DrawTraversal_ptr traversal)
{ traverse_thumb(traversal); }

void Panner::pick(PickTraversal_ptr traversal)
{
    Trace trace("Panner::pick");
    if (traversal->intersects_allocation())
    {
    traversal->enter_controller(Controller_var(_this()));
    MonoGraphic::traverse(traversal);
    traverse_thumb(traversal);
    if (!traversal->picked()) traversal->hit();
    traversal->leave_controller();
    }
}

void Panner::allocate(Tag, const Allocation::Info &info)
{
    Impl_var<RegionImpl> allocation(new RegionImpl(info.allocation));
    Coord lower = allocation->lower.x;
    Coord scale = allocation->upper.x - allocation->lower.x;
    allocation->lower.x = lower + scale;
    allocation->upper.x = lower + scale;
    lower = allocation->lower.y;
    scale = allocation->upper.y - allocation->lower.y;
    allocation->lower.y = lower + scale;
    allocation->upper.y = lower + scale;
    allocation->lower.z = allocation->upper.z = 0.;
    
    allocation->normalize(info.transformation);
}

void Panner::adjust(const OriginatedDelta &od)
{
    Vertex origin = od.origin;
    Vertex newpt = od.origin;
    newpt.x += od.delta.x;
    newpt.y += od.delta.y;
    
    my_pickTrafo.inverse_transform_vertex(origin);
    my_pickTrafo.inverse_transform_vertex(newpt);
    
    Vertex delta;
    delta.x = newpt.x - origin.x;
    delta.y = newpt.y - origin.y;
    
    if (origin.x < 0.)
    delta.x = std::max(origin.x + delta.x, 0.);
    else if (origin.x > my_upperBounds.x)
    delta.x = std::min(origin.x + delta.x, 0.);
  
    if (origin.y < 0.)
    delta.y = std::max(origin.y + delta.y, 0.);
    else if (origin.y > my_upperBounds.y)
    delta.y = std::min(origin.y + delta.y, 0.);
  
    if (delta.x != 0.) my_xvalue->adjust(delta.x*my_scale.x);
    if (delta.y != 0.) my_yvalue->adjust(delta.y*my_scale.y);
}

void Panner::update(const CORBA::Any &)
{
    BoundedRange::Settings settings = my_xvalue->state();
    my_offset[xaxis].lower = (settings.lvalue - settings.lower)/
    (settings.upper - settings.lower);
    my_offset[xaxis].upper = (settings.uvalue - settings.lower)/
    (settings.upper - settings.lower);
    settings = my_yvalue->state();
    my_offset[yaxis].lower = (settings.lvalue - settings.lower)/
    (settings.upper - settings.lower);
    my_offset[yaxis].upper = (settings.uvalue - settings.lower)/
    (settings.upper - settings.lower);
    need_redraw();
}

void Panner::traverse_thumb(Traversal_ptr traversal)
{
    Graphic_var child = body();
    if (CORBA::is_nil(child)) return;
    Impl_var<RegionImpl>
    allocation(new RegionImpl(Region_var(traversal->
                         current_allocation())));
    Impl_var<TransformImpl> transformation(new TransformImpl);
    my_upperBounds.x = allocation->upper.x - allocation->lower.x;
    my_upperBounds.y = allocation->upper.y - allocation->lower.y;
    my_pickTrafo.copy(traversal->current_transformation());
    Coord lower = allocation->lower.x;
    Coord scale = allocation->upper.x - allocation->lower.x;
    allocation->lower.x = lower + scale*my_offset[xaxis].lower;
    allocation->upper.x = lower + scale*my_offset[xaxis].upper;
    lower = allocation->lower.y;
    my_scale.x = (my_xvalue->upper() - my_xvalue->lower())/scale;
    scale = allocation->upper.y - allocation->lower.y;
    allocation->lower.y = lower + scale*my_offset[yaxis].lower;
    allocation->upper.y = lower + scale*my_offset[yaxis].upper;
    allocation->lower.z = allocation->upper.z = 0.;
    allocation->normalize(Transform_var(transformation->_this()));
    my_scale.y = (my_yvalue->upper() - my_yvalue->lower())/scale;
    
    try
    {
    traversal->traverse_child (child, 0,
                   Region_var(allocation->_this()),
                   Transform_var(transformation->_this()));
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { body(Fresco::Graphic::_nil()); }
    catch (const CORBA::COMM_FAILURE &)
    { body(Fresco::Graphic::_nil()); }
}
