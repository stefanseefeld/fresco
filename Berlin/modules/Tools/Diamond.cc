/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Warsaw/config.hh"
#include "Warsaw/DrawTraversal.hh"
#include "Warsaw/DrawingKit.hh"
#include "Warsaw/Subject.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/Logger.hh"
#include "Berlin/Color.hh"
#include "Tool/Diamond.hh"
#include "Tool/Beveler.hh"

void InvisibleDiamond::draw(DrawTraversal_ptr traversal)
{
  Region_var allocation = traversal->allocation();
  Vertex u, l;
  allocation->bounds(l, u);
  DrawingKit_var drawing = traversal->kit();

  drawing->saveState();
  if (drawing->surfaceFillstyle() == DrawingKit::outlined)
    drawing->surfaceFillstyle(DrawingKit::solid);

  Vertex center = {(u.x + l.x)/2, (u.y + l.y)/2, 0.};
  Vertex length = {(u.x - l.x), (u.y - l.y), 0.};
  Coord dx = thickness * sqrt(length.x * length.x / (length.y * length.y) + 1.0);
  Coord dy = thickness * sqrt(length.y * length.y / (length.x * length.x) + 1.0);

  Path path;
  path.length(5);
  if (fill)
    {
      path[0].x = center.x, path[0].y = l.y, path[0].z = 0;
      path[1].x = l.x, path[1].y = center.y, path[1].z = 0;
      path[2].x = center.x, path[2].y = u.y, path[2].z = 0;
      path[3].x = u.x, path[3].y = center.y, path[3].z = 0;
      path[4] = path[0];
      drawing->drawPath(path);
    }
  else
    {
      /*
       * top left
       */
      path[0].x = center.x, path[0].y = u.y, path[0].z = 0;
      path[1].x = l.x, path[1].y = center.y, path[1].z = 0;
      path[2].x = l.x + dx, path[2].y = center.y, path[2].z = 0;
      path[3].x = center.x, path[3].y = l.y + dy, path[3].z = 0;
      path[4] = path[0];
      drawing->drawPath(path);
      /*
       * bottom left
       */
      path[0].x = l.x, path[0].y = center.y, path[0].z = 0;
      path[1].x = center.x, path[1].y = u.y, path[1].z = 0;
      path[2].x = center.x, path[2].y = u.y - dy, path[2].z = 0;
      path[3].x = l.x + dx, path[3].y = center.y, path[3].z = 0;
      path[4] = path[0];
      drawing->drawPath(path);
      /*
       * bottom right
       */
      path[0].x = center.x, path[0].y = u.y, path[0].z = 0;
      path[1].x = u.x, path[1].y = center.y, path[1].z = 0;
      path[2].x = u.x - dx, path[2].y = center.y, path[2].z = 0;
      path[3].x = center.x, path[3].y = u.y - dy, path[3].z = 0;
      path[4] = path[0];
      drawing->drawPath(path);
      /*
       * top right
       */
      path[0].x = center.x, path[0].y = l.y, path[0].z = 0;
      path[1].x = center.x, path[1].y = l.y + dy, path[1].z = 0;
      path[2].x = u.x - dx, path[2].y = center.y, path[2].z = 0;
      path[3].x = u.x, path[3].y = center.y, path[3].z = 0;
      path[4] = path[0];
      drawing->drawPath(path);
    }
  drawing->restoreState();
}

void BeveledDiamond::draw(DrawTraversal_ptr traversal)
{
  Region_var allocation = traversal->allocation();
  Vertex u, l;
  allocation->bounds(l, u);
  DrawingKit_var drawing = traversal->kit();
  Color color = drawing->foreground();
  Color light = brightness(color,-bright);
  Color dark  = brightness(color, bright);

  drawing->saveState();
  if (drawing->surfaceFillstyle() == DrawingKit::outlined)
    drawing->surfaceFillstyle(DrawingKit::solid);

  switch (style)
    {
    case inset:
      Beveler::diamond(traversal, thickness, color, dark, light, l.x, u.x, l.y, u.y, fill);
      break;
    case outset:
      Beveler::diamond(traversal, thickness, color, light, dark, l.x, u.x, l.y, u.y, fill);
      break;
    case convex:
      Beveler::diamond(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, false);
      l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
      Beveler::diamond(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, fill);
      break;
    case concav:
      Beveler::diamond(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, false);
      l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
      Beveler::diamond(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, fill);
      break;
    }
  drawing->restoreState();
}

void ColoredDiamond::draw(DrawTraversal_ptr traversal)
{
  Region_var allocation = traversal->allocation();
  Vertex u, l;
  allocation->bounds(l, u);
  DrawingKit_var drawing = traversal->kit();

  drawing->saveState();
  if (drawing->surfaceFillstyle() == DrawingKit::outlined)
    drawing->surfaceFillstyle(DrawingKit::solid);
  Color tmp = drawing->foreground();
  tmp.red = color.red;
  tmp.green = color.green;
  tmp.blue = color.blue;
  drawing->foreground(tmp);

  Vertex center = {(u.x + l.x)/2, (u.y + l.y)/2, 0.};
  Vertex length = {(u.x - l.x), (u.y - l.y), 0.};
  Coord dx = thickness * sqrt(length.x * length.x / (length.y * length.y) + 1.0);
  Coord dy = thickness * sqrt(length.y * length.y / (length.x * length.x) + 1.0);

  Path path;
  path.length(5);
  if (fill)
    {
      path[0].x = center.x, path[0].y = l.y, path[0].z = 0;
      path[1].x = l.x, path[1].y = center.y, path[1].z = 0;
      path[2].x = center.x, path[2].y = u.y, path[2].z = 0;
      path[3].x = u.x, path[3].y = center.y, path[3].z = 0;
      path[4] = path[0];
      drawing->drawPath(path);
    }
  else
    {
      /*
       * top left
       */
      path[0].x = center.x, path[0].y = l.y, path[0].z = 0;
      path[1].x = l.x, path[1].y = center.y, path[1].z = 0;
      path[2].x = l.x + dx, path[2].y = center.y, path[2].z = 0;
      path[3].x = center.x, path[3].y = l.y + dy, path[3].z = 0;
      path[4] = path[0];
      drawing->drawPath(path);
      /*
       * bottom left
       */
      path[0].x = l.x, path[0].y = center.y, path[0].z = 0;
      path[1].x = center.x, path[1].y = u.y, path[1].z = 0;
      path[2].x = center.x, path[2].y = u.y - dy, path[2].z = 0;
      path[3].x = l.x + dx, path[3].y = center.y, path[3].z = 0;
      path[4] = path[0];
      drawing->drawPath(path);
      /*
       * bottom right
       */
      path[0].x = center.x, path[0].y = u.y, path[0].z = 0;
      path[1].x = u.x, path[1].y = center.y, path[1].z = 0;
      path[2].x = u.x - dx, path[2].y = center.y, path[2].z = 0;
      path[3].x = center.x, path[3].y = u.y - dy, path[3].z = 0;
      path[4] = path[0];
      drawing->drawPath(path);
      /*
       * top right
       */
      path[0].x = center.x, path[0].y = l.y, path[0].z = 0;
      path[1].x = center.x, path[1].y = l.y + dy, path[1].z = 0;
      path[2].x = u.x - dx, path[2].y = center.y, path[2].z = 0;
      path[3].x = u.x, path[3].y = center.y, path[3].z = 0;
      path[4] = path[0];
      drawing->drawPath(path);
    }
  drawing->restoreState();
}

