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

#include <Fresco/config.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/Subject.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Color.hh>
#include "Triangle.hh"
#include "Beveler.hh"

using namespace Fresco;

using namespace Berlin::ToolKit;

void InvisibleTriangle::draw(DrawTraversal_ptr traversal)
{
    Region_var allocation = traversal->current_allocation();
    Vertex l, u;
    allocation->bounds(l, u);
    DrawingKit_var drawing = traversal->drawing();
    DrawingKit::Fillstyle style = drawing->surface_fillstyle();
    if (style != DrawingKit::outlined && fill)
    {
    Path path;
    path.shape = convex;
    path.nodes.length(4);
    switch (my_direction)
    {
    case Fresco::ToolKit::left:
        path.nodes[0].x = l.x, path.nodes[0].y = (l.y + u.y)/2,
        path.nodes[0].z = 0;
        path.nodes[1].x = u.x, path.nodes[1].y = l.y,
        path.nodes[1].z = 0;
        path.nodes[2].x = u.x, path.nodes[2].y = u.y,
        path.nodes[2].z = 0;
        path.nodes[3] = path.nodes[0];
        break;
    case Fresco::ToolKit::right:
        path.nodes[0].x = l.x, path.nodes[0].y = l.y,
        path.nodes[0].z = 0;
        path.nodes[1].x = u.x, path.nodes[1].y = (l.y + u.y)/2,
        path.nodes[1].z = 0;
        path.nodes[2].x = l.x, path.nodes[2].y = u.y,
        path.nodes[2].z = 0;
        path.nodes[3] = path.nodes[0];
        break;
    case Fresco::ToolKit::up:
        path.nodes[0].x = l.x, path.nodes[0].y = u.y,
        path.nodes[0].z = 0;
        path.nodes[1].x = (l.x + u.x)/2, path.nodes[1].y = l.y,
        path.nodes[1].z = 0;
        path.nodes[2].x = u.x, path.nodes[2].y = u.y,
        path.nodes[2].z = 0;
        path.nodes[3] = path.nodes[0];
        break;
    case Fresco::ToolKit::down:
        path.nodes[0].x = l.x, path.nodes[0].y = l.y,
        path.nodes[0].z = 0;
        path.nodes[1].x = (l.x + u.x)/2, path.nodes[1].y = u.y,
        path.nodes[1].z = 0;
        path.nodes[2].x = l.x, path.nodes[2].y = l.y,
        path.nodes[2].z = 0;
        path.nodes[3] = path.nodes[0];
        break;
    }
    drawing->draw_path(path);
    }
    else if (fill)
    {
    drawing->save();
    drawing->surface_fillstyle(DrawingKit::solid);
    Path path;
    path.shape = convex;
    path.nodes.length(4);
    switch (my_direction)
    {
    case Fresco::ToolKit::left:
        path.nodes[0].x = l.x, path.nodes[0].y = (l.y + u.y)/2,
        path.nodes[0].z = 0;
        path.nodes[1].x = u.x, path.nodes[1].y = l.y,
        path.nodes[1].z = 0;
        path.nodes[2].x = u.x, path.nodes[2].y = u.y,
        path.nodes[2].z = 0;
        path.nodes[3] = path.nodes[0];
        break;
    case Fresco::ToolKit::right:
        path.nodes[0].x = l.x, path.nodes[0].y = l.y,
        path.nodes[0].z = 0;
        path.nodes[1].x = u.x, path.nodes[1].y = (l.y + u.y)/2,
        path.nodes[1].z = 0;
        path.nodes[2].x = l.x, path.nodes[2].y = u.y,
        path.nodes[2].z = 0;
        path.nodes[3] = path.nodes[0];
        break;
    case Fresco::ToolKit::up:
        path.nodes[0].x = l.x, path.nodes[0].y = u.y,
        path.nodes[0].z = 0;
        path.nodes[1].x = (l.x + u.x)/2, path.nodes[1].y = l.y,
        path.nodes[1].z = 0;
        path.nodes[2].x = u.x, path.nodes[2].y = u.y,
        path.nodes[2].z = 0;
        path.nodes[3] = path.nodes[0];
        break;
    case Fresco::ToolKit::down:
        path.nodes[0].x = l.x, path.nodes[0].y = l.y,
        path.nodes[0].z = 0;
        path.nodes[1].x = (l.x + u.x)/2, path.nodes[1].y = u.y,
        path.nodes[1].z = 0;
        path.nodes[2].x = l.x, path.nodes[2].y = l.y,
        path.nodes[2].z = 0;
        path.nodes[3] = path.nodes[0];
        break;
    }      
    drawing->draw_path(path);
    drawing->restore();
    }
    else
    {
    Color color = drawing->foreground();
    switch (my_direction)
    {
    case Fresco::ToolKit::left:
        Beveler::leftArrow(traversal, thickness, color, color, color,
                   l.x, u.x, l.y, u.y, fill);
        break;
    case Fresco::ToolKit::right:
        break;
        Beveler::leftArrow(traversal, thickness, color, color, color,
                   l.x, u.x, l.y, u.y, fill);
    case Fresco::ToolKit::up:
        break;
        Beveler::leftArrow(traversal, thickness, color, color, color,
                   l.x, u.x, l.y, u.y, fill);
    case Fresco::ToolKit::down:
        break;
        Beveler::leftArrow(traversal, thickness, color, color, color, 
                   l.x, u.x, l.y, u.y, fill);
    }
    }
}

void BeveledTriangle::draw(DrawTraversal_ptr traversal)
{
    Region_var allocation = traversal->current_allocation();
    Vertex u, l;
    allocation->bounds(l, u);
    DrawingKit_var drawing = traversal->drawing();
    Color color = drawing->foreground();
    Color light = brightness(color,-my_bright);
    Color dark  = brightness(color, my_bright);
    
    drawing->save();
    if (drawing->surface_fillstyle() == DrawingKit::outlined)
    drawing->surface_fillstyle(DrawingKit::solid);

    switch (my_direction)
    {
    case Fresco::ToolKit::left:
    switch (my_style)
    {
    case inset:
        Beveler::leftArrow(traversal, thickness, color, dark, light,
                   l.x, u.x, l.y, u.y, fill);
        break;
    case outset:
        Beveler::leftArrow(traversal, thickness, color, light, dark,
                   l.x, u.x, l.y, u.y, fill);
        break;
    case convex:
        Beveler::leftArrow(traversal, thickness/2, color, light, dark,
                   l.x, u.x, l.y, u.y, false);
        l.x += thickness/2, u.x -= thickness/2,
        l.y += thickness/2, u.y -= thickness/2;
        Beveler::leftArrow(traversal, thickness/2, color, dark, light,
                   l.x, u.x, l.y, u.y, fill);
        break;
    case concav:
        Beveler::leftArrow(traversal, thickness/2, color, dark, light,
                   l.x, u.x, l.y, u.y, false);
        l.x += thickness/2, u.x -= thickness/2,
        l.y += thickness/2, u.y -= thickness/2;
        Beveler::leftArrow(traversal, thickness/2, color, light, dark,
                   l.x, u.x, l.y, u.y, fill);
        break;
    }
    break;
    case Fresco::ToolKit::right:
    switch (my_style)
    {
    case inset:
        Beveler::rightArrow(traversal, thickness, color, dark, light,
                l.x, u.x, l.y, u.y, fill);
        break;
    case outset:
        Beveler::rightArrow(traversal, thickness, color, light, dark,
                l.x, u.x, l.y, u.y, fill);
        break;
    case convex:
        Beveler::rightArrow(traversal, thickness/2, color, light, dark,
                l.x, u.x, l.y, u.y, false);
        l.x += thickness/2, u.x -= thickness/2,
        l.y += thickness/2, u.y -= thickness/2;
        Beveler::rightArrow(traversal, thickness/2, color, dark, light,
                l.x, u.x, l.y, u.y, fill);
        break;
    case concav:
        Beveler::rightArrow(traversal, thickness/2,    color, dark, light,
                l.x, u.x, l.y, u.y, false);
        l.x += thickness/2, u.x -= thickness/2,
        l.y += thickness/2, u.y -= thickness/2;
        Beveler::rightArrow(traversal, thickness/2, color, light, dark,
                l.x, u.x, l.y, u.y, fill);
        break;
    }
    break;
    case Fresco::ToolKit::up:
    switch (my_style)
    {
    case inset:
        Beveler::upArrow(traversal, thickness, color, light, dark,
                 l.x, u.x, l.y, u.y, fill);
        break;
    case outset:
        Beveler::upArrow(traversal, thickness, color, dark, light,
                 l.x, u.x, l.y, u.y, fill);
        break;
    case convex:
        Beveler::upArrow(traversal, thickness/2, color, dark, light,
                 l.x, u.x, l.y, u.y, false);
        l.x += thickness/2, u.x -= thickness/2,
        l.y += thickness/2, u.y -= thickness/2;
        Beveler::upArrow(traversal, thickness/2, color, light, dark,
                 l.x, u.x, l.y, u.y, fill);
        break;
    case concav:
        Beveler::upArrow(traversal, thickness/2, color, light, dark,
                 l.x, u.x, l.y, u.y, false);
        l.x += thickness/2, u.x -= thickness/2,
        l.y += thickness/2, u.y -= thickness/2;
        Beveler::upArrow(traversal, thickness/2, color, dark, light,
                 l.x, u.x, l.y, u.y, fill);
      break;
    }
    break;
    case Fresco::ToolKit::down:
    switch (my_style)
    {
    case inset:
        Beveler::downArrow(traversal, thickness, color, dark, light,
                   l.x, u.x, l.y, u.y, fill);
        break;
    case outset:
        Beveler::downArrow(traversal, thickness, color, light, dark,
                   l.x, u.x, l.y, u.y, fill);
        break;
    case convex:
        Beveler::downArrow(traversal, thickness/2, color, light, dark,
                   l.x, u.x, l.y, u.y, false);
        l.x += thickness/2, u.x -= thickness/2,
        l.y += thickness/2, u.y -= thickness/2;
        Beveler::downArrow(traversal, thickness/2, color, dark, light,
                   l.x, u.x, l.y, u.y, fill);
        break;
    case concav:
        Beveler::downArrow(traversal, thickness/2, color, dark, light,
                   l.x, u.x, l.y, u.y, false);
        l.x += thickness/2, u.x -= thickness/2,
        l.y += thickness/2, u.y -= thickness/2;
        Beveler::downArrow(traversal, thickness/2, color, light, dark,
                   l.x, u.x, l.y, u.y, fill);
        break;
    }
    break;
    }
    drawing->restore();
}

void ColoredTriangle::draw(DrawTraversal_ptr traversal)
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
    if (fill) drawing->draw_rectangle(l, u);
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

