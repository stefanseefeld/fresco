/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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
#include <Fresco/Graphic.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/Region.hh>
#include <Fresco/IO.hh>
#include <Berlin/DrawTraversalImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Provider.hh>
#include <Berlin/Console.hh>

using namespace Prague;
using namespace Fresco;

DrawTraversalImpl::DrawTraversalImpl(Graphic_ptr g, Region_ptr r,
				     Transform_ptr t, DrawingKit_ptr kit) :
    TraversalImpl(g, r, t),
    my_drawing(DrawingKit::_duplicate(kit)),
    my_clipping(Region_var(current_allocation())),
    my_id(new TransformImpl)
{
    Trace trace("DrawTraversalImpl::DrawTraversalImpl");
    Color fg = {0., 0., 0., 1.};
    my_drawing->foreground(fg);
    Color white = {1., 1., 1., 1.};
    my_drawing->lighting(white);
    my_drawing->transformation(Transform_var(my_id->_this()));
    my_drawing->surface_fillstyle(DrawingKit::solid);
}

void DrawTraversalImpl::damage(Fresco::Region_ptr d)
{
    assert(size() == 1);
    get_allocation(0)->copy(d);
    my_drawing->clipping(my_clipping);
}

void DrawTraversalImpl::init()
{
    Trace trace("DrawTraversalImpl::init");
    my_this = _this();
    my_drawing->save();
    Vertex l, u;
    my_clipping->bounds(l, u);
    // clear the background of the damaged region...
    my_drawing->draw_rectangle(l, u);
#if 0
    my_drawing->flush();
    Console::drawable()->flush();
    sleep(1);
#endif
}

void DrawTraversalImpl::finish()
{
    Trace trace("DrawTraversalImpl::finish");
    my_drawing->restore();
}

DrawTraversalImpl::DrawTraversalImpl(const DrawTraversalImpl &traversal) :
    TraversalImpl(traversal),
    my_drawing(traversal.my_drawing),
    my_clipping(traversal.my_clipping)
{
//   drawing->clipping(clipping);
}

DrawTraversalImpl::~DrawTraversalImpl()
{
    my_drawing->restore();
}

CORBA::Boolean DrawTraversalImpl::intersects_allocation()
{
    Trace trace("DrawTraversalImpl::intersects_allocation");
    Region_var r = current_allocation();
    Transform_var t = current_transformation();
    Lease_var<RegionImpl> region( Provider<RegionImpl>::provide() );
    region->copy(r);
    region->apply_transform(t);
    return region->intersects(my_clipping);
}

CORBA::Boolean DrawTraversalImpl::intersects_region(Region_ptr r)
{
    RegionImpl region(r, get_transformation(size() - 1));
//    RegionImpl cl(clipping);
//    std::cout << "DrawTraversalImpl::intersects_region " << region << ' '
// 	        << my_clipping << std::endl;
    return region.intersects(my_clipping);
}

void DrawTraversalImpl::traverse_child(Graphic_ptr child, Tag tag,
				       Region_ptr region,
				       Transform_ptr transform)
{
    Trace trace("DrawTraversalImpl::traverse_child");
    if (CORBA::is_nil(region)) region = Region_var(current_allocation());
    Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
    allocation->copy(region);
    Lease_var<TransformImpl> cumulative(Provider<TransformImpl>::provide());
#if 0
    *cumulative = *get_transformation(size() - 1);
    if (!CORBA::is_nil(transform)) cumulative->premultiply(transform);
#elif 1
    cumulative->set_and_premult(get_transformation(size()-1), transform);
#elif 0
    Vertex lower, upper;
    region->bounds(lower, upper);
    *cumulative = *get_transformation(size()-1);
    cumulative->translate(lower);
#endif
    my_drawing->transformation(Transform_var(cumulative->_this()));
    // drawable->clipping(region, Transform_var(tx->_this()));
    push(child, tag, allocation, cumulative); // Keep ownership of cumulative!
    try
    {
	child->traverse(my_this);
    }
    catch (...)
    {
	// Make sure cumulative does not go out of scope before the pop() ;-)
	pop();
	throw;
    }
    pop(); // cumulative still in scope...
};

void DrawTraversalImpl::visit(Graphic_ptr g) { g->draw(my_this); }
Fresco::Traversal::order DrawTraversalImpl::direction()
{ return Fresco::Traversal::up; }
CORBA::Boolean DrawTraversalImpl::ok() { return true; }
DrawingKit_ptr DrawTraversalImpl::drawing()
{ return DrawingKit::_duplicate(my_drawing); }
