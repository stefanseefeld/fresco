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

#include <Fresco/config.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/Raster.hh>
#include <Fresco/IO.hh>
#include "DrawingStateImpl.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::ToolKit;

DrawingStateImpl::DrawingStateImpl() : my_enabled(0) { }
DrawingStateImpl::~DrawingStateImpl() { }

void DrawingStateImpl::traverse(Traversal_ptr traversal)
{
    Trace trace("DrawingStateImpl::traverse");
    traversal->visit(Graphic_var(_this()));
}

void DrawingStateImpl::draw(DrawTraversal_ptr traversal)
{
    Trace trace("DrawingStateImpl::draw");
    DrawingKit_var drawing = traversal->drawing();
    drawing->save();
    if (my_enabled & color) drawing->foreground(my_color);
    if (my_enabled & light) drawing->lighting(my_light);
    if (my_enabled & point) drawing->point_size(my_point);
    if (my_enabled & line) drawing->line_width(my_line);
    if (my_enabled & estyle) drawing->line_endstyle(my_estyle);
    if (my_enabled & fstyle) drawing->surface_fillstyle(my_fstyle);
    if (my_enabled & tex) drawing->texture(my_texture);
    MonoGraphic::traverse(traversal);
    drawing->restore();
}

void DrawingStateImpl::pick(PickTraversal_ptr traversal)
{
    Trace trace("DrawingStateImpl::pick");
    MonoGraphic::traverse(traversal);
}

Color DrawingStateImpl::foreground() { return my_color; }
void DrawingStateImpl::foreground(const Color &c)
{ my_color = c; my_enabled |= color;}
Color DrawingStateImpl::lighting() { return my_light; }
void DrawingStateImpl::lighting(const Color &l)
{ my_light = l; my_enabled |= light;}
Coord DrawingStateImpl::point_size() { return my_point; }
void DrawingStateImpl::point_size(Coord p)
{ my_point = p; my_enabled |= point; }
Coord DrawingStateImpl::line_width() { return my_line;}
void DrawingStateImpl::line_width(Coord l)
{ my_line = l; my_enabled |= line; }
DrawingKit::Endstyle DrawingStateImpl::line_endstyle() { return my_estyle;}
void DrawingStateImpl::line_endstyle(DrawingKit::Endstyle s)
{ my_estyle = s; my_enabled |= estyle; }
DrawingKit::Fillstyle DrawingStateImpl::surface_fillstyle()
{ return my_fstyle; }
void DrawingStateImpl::surface_fillstyle(DrawingKit::Fillstyle s)
{ my_fstyle = s; my_enabled |= fstyle; }
Raster_ptr DrawingStateImpl::texture()
{ return Raster::_duplicate(my_texture); }
void DrawingStateImpl::texture(Raster_ptr t)
{ my_texture = Raster::_duplicate(t); my_enabled |= tex; }
