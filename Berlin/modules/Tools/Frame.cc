/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/Subject.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Provider.hh>
#include <Berlin/Color.hh>
#include "Frame.hh"
#include "Beveler.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::ToolKit;

Frame::Frame(Coord t, Frame::Renderer *r) :
    my_thickness(t), my_allocation(new RegionImpl), my_renderer(r)
{ }
Frame::~Frame() { Trace trace("Frame::~Frame"); }

void Frame::request(Fresco::Graphic::Requisition &requisition)
{
    MonoGraphic::request(requisition);
    Coord t = my_thickness + my_thickness;
    if (requisition.x.defined)
    {
	requisition.x.natural += t;
	requisition.x.maximum += t;
	requisition.x.minimum += t;
    }
    if (requisition.y.defined)
    {
	requisition.y.natural += t;
	requisition.y.maximum += t;
	requisition.y.minimum += t;
    }
}

void Frame::traverse(Traversal_ptr traversal)
{
    Trace trace(this, "Frame::traverse");
    if (!traversal->intersects_allocation()) return;
    traversal->visit(Graphic_var(_this()));
    Lease_var<RegionImpl> allocation(Provider<RegionImpl>::provide());
    allocation->copy(Region_var(traversal->current_allocation()));
    Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
    tx->load_identity();
  
    Allocation::Info info;
    info.allocation = allocation->_this();
    info.transformation = tx->_this();
    allocate(0, info);
    
    Graphic_var child = body();
    if (CORBA::is_nil(child)) return;
    try
    {
	traversal->traverse_child(child, 0,
				  info.allocation, info.transformation);
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { body(Fresco::Graphic::_nil()); }
    catch (const CORBA::COMM_FAILURE &)
    { body(Fresco::Graphic::_nil()); }
}

void Frame::extension(const Allocation::Info &info, Region_ptr region)
{
    if (!CORBA::is_nil(info.allocation)) default_extension(info, region);
    else MonoGraphic::extension(info, region);
}

void Frame::allocate(Tag, const Allocation::Info &info)
{
    Trace trace(this, "Frame::allocate");
    Fresco::Graphic::Requisition req;
    GraphicImpl::init_requisition(req);
    MonoGraphic::request(req);
    my_allocation->valid = true;
    Region::Allotment a;
    Vertex o;
    Lease_var<RegionImpl> region(Provider<RegionImpl>::provide());
    region->copy(info.allocation);

    region->normalize(o);
    info.transformation->translate(o);
    info.allocation->copy(Region_var(region->_this()));
  
    Vertex delta;
    info.allocation->span(xaxis, a);
    allocate_span(req.x, a, my_thickness, 0.);
    my_allocation->lower.x = -(a.end - a.begin) * a.align;
    my_allocation->upper.x = my_allocation->lower.x + (a.end - a.begin);
    my_allocation->xalign = a.align;
    delta.x = a.begin - my_allocation->lower.x;

    info.allocation->span(yaxis, a);
    allocate_span(req.y, a, my_thickness, 0.);
    my_allocation->lower.y = -(a.end - a.begin) * a.align;
    my_allocation->upper.y = my_allocation->lower.y + (a.end - a.begin);
    my_allocation->yalign = a.align;
    delta.y = a.begin - my_allocation->lower.y;
    delta.z = 0;
    
    my_allocation->lower.z = my_allocation->upper.z =
	my_allocation->zalign = 0.;
    
    info.allocation->copy(Region_var(my_allocation->_this()));
    info.transformation->translate(delta);
}

void Frame::draw(Fresco::DrawTraversal_ptr traversal)
{
    Trace trace(this, "Frame::draw");
    if (my_renderer) my_renderer->draw(traversal);
}

void Frame::allocate_span(const Fresco::Graphic::Requirement &r,
			  Region::Allotment &a, Coord margin,
			  Alignment align)
{
    a.begin += margin;
    a.end -= margin;
}

void InvisibleFrame::draw(DrawTraversal_ptr traversal)
{
    Region_var allocation = traversal->current_allocation();
    Vertex l, u;
    allocation->bounds(l, u);
    DrawingKit_var drawing = traversal->drawing();
    DrawingKit::Fillstyle style = drawing->surface_fillstyle();
    if (style != DrawingKit::outlined && fill)
	drawing->draw_rectangle(l, u);
    else if (fill)
    {
	drawing->save();
	drawing->surface_fillstyle(DrawingKit::solid);
	drawing->draw_rectangle(l, u);
	drawing->restore();
    }
    else
    {
	Vertex ltmp = l, utmp = u;
	utmp.y = ltmp.y + thickness;
	drawing->draw_rectangle(ltmp, utmp);
	ltmp.x = utmp.x - thickness, ltmp.y = utmp.y;
	utmp.y = u.y - thickness;
	drawing->draw_rectangle(ltmp, utmp);
	ltmp.x = l.x, utmp.x = l.x + thickness;
	drawing->draw_rectangle(ltmp, utmp);
	ltmp.y = u.y - thickness;
	utmp = u;
	drawing->draw_rectangle(ltmp, utmp);
    }
}

void Bevel::draw(DrawTraversal_ptr traversal)
{
    Region_var allocation = traversal->current_allocation();
    Vertex u, l;
    allocation->bounds(l, u);
    DrawingKit_var drawing = traversal->drawing();
    // drawing->transformation(traversal->current_transformation());
    Color color = drawing->foreground();
    Color light = brightness(color, my_bright);
    Color dark  = brightness(color,-my_bright);
    switch (my_style)
    {
    case inset:
	Beveler::rect(traversal, thickness, color, dark, light,
		      l.x, u.x, l.y, u.y, fill);
	break;
    case outset:
	Beveler::rect(traversal, thickness, color, light, dark,
		      l.x, u.x, l.y, u.y, fill);
	break;
    case convex:
	Beveler::rect(traversal, thickness/2, color, light, dark,
		      l.x, u.x, l.y, u.y, false);
	l.x += thickness/2, u.x -= thickness/2,
	    l.y += thickness/2, u.y -= thickness/2;
	Beveler::rect(traversal, thickness/2, color, dark, light,
		      l.x, u.x, l.y, u.y, fill);
	break;
    case concav:
	Beveler::rect(traversal, thickness/2, color, dark, light,
		      l.x, u.x, l.y, u.y, false);
	l.x += thickness/2, u.x -= thickness/2,
	    l.y += thickness/2, u.y -= thickness/2;
	Beveler::rect(traversal, thickness/2, color, light, dark,
		      l.x, u.x, l.y, u.y, fill);
	break;
    }
}

void ColoredFrame::draw(DrawTraversal_ptr traversal)
{
    Region_var allocation = traversal->current_allocation();
    Vertex l, u;
    allocation->bounds(l, u);
    DrawingKit_var drawing = traversal->drawing();
    DrawingKit::Fillstyle style = drawing->surface_fillstyle();
    drawing->save();
    Color tmp = drawing->foreground();
    tmp.red = my_color.red;
    tmp.green = my_color.green;
    tmp.blue = my_color.blue;
    drawing->foreground(tmp);
    if (style == DrawingKit::outlined)
	drawing->surface_fillstyle(DrawingKit::solid);
    if (fill)
	drawing->draw_rectangle(l, u);
    else
    {
	Vertex ltmp = l, utmp = u;
	utmp.y = ltmp.y + thickness;
	drawing->draw_rectangle(ltmp, utmp);
	ltmp.x = utmp.x - thickness, ltmp.y = utmp.y;
	utmp.y = u.y - thickness;
	drawing->draw_rectangle(ltmp, utmp);
	ltmp.x = l.x, utmp.x = l.x + thickness;
	drawing->draw_rectangle(ltmp, utmp);
	ltmp.y = u.y - thickness;
	utmp = u;
	drawing->draw_rectangle(ltmp, utmp);
    }
    drawing->restore();
}

