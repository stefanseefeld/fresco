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
#include "Diamond.hh"
#include "Beveler.hh"

using namespace Fresco;

using namespace Berlin::ToolKit;

void InvisibleDiamond::draw(DrawTraversal_ptr traversal)
{
    Region_var allocation = traversal->current_allocation();
    Vertex u, l;
    allocation->bounds(l, u);
    DrawingKit_var drawing = traversal->drawing();
    
    drawing->save();
    if (drawing->surface_fillstyle() == DrawingKit::outlined)
    drawing->surface_fillstyle(DrawingKit::solid);
    
    Vertex center = {(u.x + l.x)/2, (u.y + l.y)/2, 0.};
    Vertex length = {(u.x - l.x), (u.y - l.y), 0.};
    Coord dx = thickness * sqrt(length.x * length.x /
                   (length.y * length.y) + 1.0);
    Coord dy = thickness * sqrt(length.y * length.y /
                   (length.x * length.x) + 1.0);
    
    Path path;
    path.shape = complex;
    path.nodes.length(5);
    if (fill)
    {
    path.nodes[0].x = center.x, path.nodes[0].y = l.y,
        path.nodes[0].z = 0;
    path.nodes[1].x = l.x, path.nodes[1].y = center.y,
        path.nodes[1].z = 0;
    path.nodes[2].x = center.x, path.nodes[2].y = u.y,
        path.nodes[2].z = 0;
    path.nodes[3].x = u.x, path.nodes[3].y = center.y,
        path.nodes[3].z = 0;
    path.nodes[4] = path.nodes[0];
    drawing->draw_path(path);
    }
    else
    {
    // top left
    path.nodes[0].x = center.x, path.nodes[0].y = u.y,
        path.nodes[0].z = 0;
    path.nodes[1].x = l.x, path.nodes[1].y = center.y,
        path.nodes[1].z = 0;
    path.nodes[2].x = l.x + dx, path.nodes[2].y = center.y,
        path.nodes[2].z = 0;
    path.nodes[3].x = center.x, path.nodes[3].y = l.y + dy,
        path.nodes[3].z = 0;
    path.nodes[4] = path.nodes[0];
    drawing->draw_path(path);

        // bottom left
    path.nodes[0].x = l.x, path.nodes[0].y = center.y,
        path.nodes[0].z = 0;
    path.nodes[1].x = center.x, path.nodes[1].y = u.y,
        path.nodes[1].z = 0;
    path.nodes[2].x = center.x, path.nodes[2].y = u.y - dy,
        path.nodes[2].z = 0;
    path.nodes[3].x = l.x + dx, path.nodes[3].y = center.y,
        path.nodes[3].z = 0;
    path.nodes[4] = path.nodes[0];
    drawing->draw_path(path);

    // bottom right
    path.nodes[0].x = center.x, path.nodes[0].y = u.y,
        path.nodes[0].z = 0;
    path.nodes[1].x = u.x, path.nodes[1].y = center.y,
        path.nodes[1].z = 0;
    path.nodes[2].x = u.x - dx, path.nodes[2].y = center.y,
        path.nodes[2].z = 0;
    path.nodes[3].x = center.x, path.nodes[3].y = u.y - dy,
        path.nodes[3].z = 0;
    path.nodes[4] = path.nodes[0];
    drawing->draw_path(path);

    // top right
    path.nodes[0].x = center.x, path.nodes[0].y = l.y,
        path.nodes[0].z = 0;
    path.nodes[1].x = center.x, path.nodes[1].y = l.y + dy,
        path.nodes[1].z = 0;
    path.nodes[2].x = u.x - dx, path.nodes[2].y = center.y,
        path.nodes[2].z = 0;
    path.nodes[3].x = u.x, path.nodes[3].y = center.y,
        path.nodes[3].z = 0;
    path.nodes[4] = path.nodes[0];
    drawing->draw_path(path);
    }
    drawing->restore();
}

void BeveledDiamond::draw(DrawTraversal_ptr traversal)
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

    switch (my_style)
    {
    case inset:
    Beveler::diamond(traversal, thickness, color, dark, light,
             l.x, u.x, l.y, u.y, fill);
    break;
    case outset:
    Beveler::diamond(traversal, thickness, color, light, dark,
             l.x, u.x, l.y, u.y, fill);
    break;
    case convex:
    Beveler::diamond(traversal, thickness/2, color, light, dark,
             l.x, u.x, l.y, u.y, false);
    l.x += thickness/2, u.x -= thickness/2,
        l.y += thickness/2, u.y -= thickness/2;
    Beveler::diamond(traversal, thickness/2, color, dark, light,
             l.x, u.x, l.y, u.y, fill);
    break;
    case concav:
    Beveler::diamond(traversal, thickness/2, color, dark, light,
             l.x, u.x, l.y, u.y, false);
    l.x += thickness/2, u.x -= thickness/2,
        l.y += thickness/2, u.y -= thickness/2;
    Beveler::diamond(traversal, thickness/2, color, light, dark,
             l.x, u.x, l.y, u.y, fill);
    break;
    }
    drawing->restore();
}

void ColoredDiamond::draw(DrawTraversal_ptr traversal)
{
    Region_var allocation = traversal->current_allocation();
    Vertex u, l;
    allocation->bounds(l, u);
    DrawingKit_var drawing = traversal->drawing();
    
    drawing->save();
    if (drawing->surface_fillstyle() == DrawingKit::outlined)
    drawing->surface_fillstyle(DrawingKit::solid);
    Color tmp = drawing->foreground();
    tmp.red = my_color.red;
    tmp.green = my_color.green;
    tmp.blue = my_color.blue;
    drawing->foreground(tmp);
    
    Vertex center = {(u.x + l.x)/2, (u.y + l.y)/2, 0.};
    Vertex length = {(u.x - l.x), (u.y - l.y), 0.};
    Coord dx = thickness * sqrt(length.x * length.x /
                (length.y * length.y) + 1.0);
    Coord dy = thickness * sqrt(length.y * length.y /
                (length.x * length.x) + 1.0);

    Path path;
    path.shape = complex;
    path.nodes.length(5);
    if (fill)
    {
    path.nodes[0].x = center.x, path.nodes[0].y = l.y,
        path.nodes[0].z = 0;
    path.nodes[1].x = l.x, path.nodes[1].y = center.y,
        path.nodes[1].z = 0;
    path.nodes[2].x = center.x, path.nodes[2].y = u.y,
        path.nodes[2].z = 0;
    path.nodes[3].x = u.x, path.nodes[3].y = center.y,
        path.nodes[3].z = 0;
    path.nodes[4] = path.nodes[0];
    drawing->draw_path(path);
    }
    else
    {
    // top left
    path.nodes[0].x = center.x, path.nodes[0].y = l.y,
        path.nodes[0].z = 0;
    path.nodes[1].x = l.x, path.nodes[1].y = center.y,
        path.nodes[1].z = 0;
    path.nodes[2].x = l.x + dx, path.nodes[2].y = center.y,
        path.nodes[2].z = 0;
    path.nodes[3].x = center.x, path.nodes[3].y = l.y + dy,
        path.nodes[3].z = 0;
    path.nodes[4] = path.nodes[0];
    drawing->draw_path(path);

    // bottom left
    path.nodes[0].x = l.x, path.nodes[0].y = center.y,
        path.nodes[0].z = 0;
    path.nodes[1].x = center.x, path.nodes[1].y = u.y,
        path.nodes[1].z = 0;
    path.nodes[2].x = center.x, path.nodes[2].y = u.y - dy,
        path.nodes[2].z = 0;
    path.nodes[3].x = l.x + dx, path.nodes[3].y = center.y,
        path.nodes[3].z = 0;
    path.nodes[4] = path.nodes[0];
    drawing->draw_path(path);

    // bottom right
    path.nodes[0].x = center.x, path.nodes[0].y = u.y,
        path.nodes[0].z = 0;
    path.nodes[1].x = u.x, path.nodes[1].y = center.y,
        path.nodes[1].z = 0;
    path.nodes[2].x = u.x - dx, path.nodes[2].y = center.y,
        path.nodes[2].z = 0;
    path.nodes[3].x = center.x, path.nodes[3].y = u.y - dy,
        path.nodes[3].z = 0;
    path.nodes[4] = path.nodes[0];
    drawing->draw_path(path);

    // top right
    path.nodes[0].x = center.x, path.nodes[0].y = l.y,
        path.nodes[0].z = 0;
    path.nodes[1].x = center.x, path.nodes[1].y = l.y + dy,
        path.nodes[1].z = 0;
    path.nodes[2].x = u.x - dx, path.nodes[2].y = center.y,
        path.nodes[2].z = 0;
    path.nodes[3].x = u.x, path.nodes[3].y = center.y,
        path.nodes[3].z = 0;
    path.nodes[4] = path.nodes[0];
    drawing->draw_path(path);
    }
    drawing->restore();
}

