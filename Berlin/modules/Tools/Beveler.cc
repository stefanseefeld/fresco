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
#include <Berlin/TransformImpl.hh>
#include <Berlin/Color.hh>
#include <Berlin/Logger.hh>
#include "Beveler.hh"
#include <cmath>

using namespace Fresco;

namespace Beveler
{

void rect(DrawTraversal_ptr traversal, Coord thickness, const Color &medium, const Color &light, const Color &dark,
	  Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
  Coord lefti = left + thickness;
  Coord righti = right - thickness;
  Coord topi = top + thickness;
  Coord bottomi = bottom - thickness;
  DrawingKit_var drawing = traversal->drawing();
  drawing->save();
  Path path;
  path.nodes.length(5);
  path.shape = convex;
  Vertex lower = {left, top, 0.};
  Vertex upper = {right, bottom, 0.};

  if (fill)
    {
      drawing->foreground(medium);
      drawing->draw_rectangle(lower, upper);
    }
  drawing->surface_fillstyle(DrawingKit::solid);
  /*
   * light (left and top) edges
   */
  drawing->foreground(light);
  if (light.alpha == 1.)
    {
      // fast path
      lower.x = left; lower.y = top;
      upper.x = lefti; upper.y = bottom;
      drawing->draw_rectangle(lower,upper);    
      lower.x = left; lower.y = top;
      upper.x = right; upper.y = topi;
      drawing->draw_rectangle(lower,upper);  
    }
  else
    {
      path.nodes[0].x = left, path.nodes[0].y = top, path.nodes[0].z = 0.;
      path.nodes[1].x = left, path.nodes[1].y = bottom, path.nodes[1].z = 0.;
      path.nodes[2].x = lefti, path.nodes[2].y = bottomi, path.nodes[2].z = 0.;
      path.nodes[3].x = lefti, path.nodes[3].y = topi, path.nodes[3].z = 0.;
      path.nodes[4].x = left, path.nodes[4].y = top, path.nodes[4].z = 0.;
      drawing->draw_path(path);

      path.nodes[0].x = lefti, path.nodes[0].y = topi, path.nodes[0].z = 0.;
      path.nodes[1].x = righti, path.nodes[1].y = topi, path.nodes[1].z = 0.;
      path.nodes[2].x = right, path.nodes[2].y = top, path.nodes[2].z = 0.;
      path.nodes[3].x = left, path.nodes[3].y = top, path.nodes[3].z = 0.;
      path.nodes[4].x = lefti, path.nodes[4].y = topi, path.nodes[4].z = 0.;
      drawing->draw_path(path);
    }
  
  /*
   * right and top (dark) edges
   */
  drawing->foreground(dark);
  path.nodes[0].x = right, path.nodes[0].y = top, path.nodes[0].z = 0.;
  path.nodes[1].x = right, path.nodes[1].y = bottom, path.nodes[1].z = 0.;
  path.nodes[2].x = righti, path.nodes[2].y = bottomi, path.nodes[2].z = 0.;
  path.nodes[3].x = righti, path.nodes[3].y = topi, path.nodes[3].z = 0.;
  path.nodes[4].x = right, path.nodes[4].y = top, path.nodes[4].z = 0.;
  drawing->draw_path(path);
  
  path.nodes[0].x = right, path.nodes[0].y = bottom, path.nodes[0].z = 0.;
  path.nodes[1].x = left, path.nodes[1].y = bottom, path.nodes[1].z = 0.;
  path.nodes[2].x = lefti, path.nodes[2].y = bottomi, path.nodes[2].z = 0.;
  path.nodes[3].x = righti, path.nodes[3].y = bottomi, path.nodes[3].z = 0.;
  path.nodes[4].x = right, path.nodes[4].y = bottom, path.nodes[4].z = 0.;
  drawing->draw_path(path);

  drawing->restore();
}

void leftArrow(DrawTraversal_ptr traversal, Coord thickness, const Color &medium, const Color &light, const Color &dark,
	       Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
  Vertex center = {(right + left)/2, (bottom + top)/2, 0.};
  Vertex length = {(right - left), (bottom - top), 0.};

  Coord slope = length.y / length.x / 2;
  Coord dx = thickness * std::sqrt(1/(slope * slope) + 1.0);
  Coord dy = thickness * (1 + slope);

  DrawingKit_var drawing = traversal->drawing();
  drawing->save();
  
  Path path;
  path.shape = convex;
  if (fill)
    {
      path.nodes.length(4);
      drawing->foreground(medium);
      path.nodes[0].x = right, path.nodes[0].y = bottom, path.nodes[0].z = 0;
      path.nodes[1].x = right, path.nodes[1].y = top, path.nodes[1].z = 0;
      path.nodes[2].x = left, path.nodes[2].y = center.y, path.nodes[2].z = 0;
      path.nodes[3] = path.nodes[0];
      drawing->draw_path(path);
    }
  path.nodes.length(5);
  /*
   * top
   */
  drawing->foreground(dark);
  path.nodes[0].x = left, path.nodes[0].y = center.y, path.nodes[0].z = 0.;
  path.nodes[1].x = left + dx, path.nodes[1].y = center.y, path.nodes[1].z = 0.;
  path.nodes[2].x = right - thickness, path.nodes[2].y = top + dy, path.nodes[2].z = 0;
  path.nodes[3].x = right, path.nodes[3].y = top, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * right
   */
  drawing->foreground(light);
  path.nodes[0].x = right, path.nodes[0].y = bottom, path.nodes[0].z = 0;
  path.nodes[1].x = right, path.nodes[1].y = top, path.nodes[1].z = 0;
  path.nodes[2].x = right - thickness, path.nodes[2].y = top + dy, path.nodes[2].z = 0;
  path.nodes[3].x = right - thickness, path.nodes[3].y = bottom - dy, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * bottom
   */
  path.nodes[0].x = left, path.nodes[0].y = center.y, path.nodes[0].z = 0;
  path.nodes[1].x = right, path.nodes[1].y = bottom, path.nodes[1].z = 0;
  path.nodes[2].x = right - thickness, path.nodes[2].y = bottom - dy, path.nodes[2].z = 0;
  path.nodes[3].x = left + dx, path.nodes[3].y = center.y, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  drawing->restore();
}

void rightArrow(DrawTraversal_ptr traversal, Coord thickness, const Color &medium, const Color &light, const Color &dark,
		Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
  Vertex center = {(right + left)/2, (bottom + top)/2, 0.};
  Vertex length = {(right - left), (bottom - top), 0.};
  Coord slope = length.y / length.x / 2;
  Coord dx = thickness * std::sqrt(1/(slope * slope) + 1.0);
  Coord dy = thickness * (1 + slope);

  DrawingKit_var drawing = traversal->drawing();
  drawing->save();

  Path path;
  path.shape = convex;
  if (fill)
    {
      path.nodes.length(4);
      drawing->foreground(medium);
      path.nodes[0].x = right, path.nodes[0].y = center.y, path.nodes[0].z = 0;
      path.nodes[1].x = left, path.nodes[1].y = top, path.nodes[1].z = 0;
      path.nodes[2].x = left, path.nodes[2].y = bottom, path.nodes[2].z = 0;
      path.nodes[3] = path.nodes[0];
      drawing->draw_path(path);
    }
  path.nodes.length(5);
  /*
   * bottom
   */
  drawing->foreground(light);
  path.nodes[0].x = left, path.nodes[0].y = bottom, path.nodes[0].z = 0;
  path.nodes[1].x = right, path.nodes[1].y = center.y, path.nodes[1].z = 0.;
  path.nodes[2].x = right - dx, path.nodes[2].y = center.y, path.nodes[2].z = 0.;
  path.nodes[3].x = left + thickness, path.nodes[3].y = bottom - dy, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * left
   */
  drawing->foreground(dark);
  path.nodes[0].x = left, path.nodes[0].y = top, path.nodes[0].z = 0;
  path.nodes[1].x = left, path.nodes[1].y = bottom, path.nodes[1].z = 0;
  path.nodes[2].x = left + thickness, path.nodes[2].y = bottom - dy, path.nodes[2].z = 0;
  path.nodes[3].x = left + thickness, path.nodes[3].y = top + dy, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * top
   */
  path.nodes[0].x = right, path.nodes[0].y = center.y, path.nodes[0].z = 0;
  path.nodes[1].x = left, path.nodes[1].y = top, path.nodes[1].z = 0;
  path.nodes[2].x = left + thickness, path.nodes[2].y = top + dy, path.nodes[2].z = 0;
  path.nodes[3].x = right - dx, path.nodes[3].y = center.y, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  drawing->restore();
}

void upArrow(DrawTraversal_ptr traversal, Coord thickness, const Color &medium, const Color &light, const Color &dark,
	     Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
  Vertex center = {(right + left)/2, (bottom + top)/2, 0.};
  Vertex length = {(right - left), (bottom - top), 0.};
  Coord slope = 2 * length.y / length.x;
  Coord dy = thickness * std::sqrt(slope * slope + 1.0);
  Coord dx = thickness * (1 + 1 / slope);

  DrawingKit_var drawing = traversal->drawing();
  drawing->save();

  Path path;
  path.shape = convex;
  if (fill)
    {
      path.nodes.length(4);
      drawing->foreground(medium);
      path.nodes[0].x = left, path.nodes[0].y = bottom, path.nodes[0].z = 0;
      path.nodes[1].x = right, path.nodes[1].y = bottom, path.nodes[1].z = 0;
      path.nodes[2].x = center.x, path.nodes[2].y = top, path.nodes[2].z = 0;
      path.nodes[3] = path.nodes[0];
      drawing->draw_path(path);
    }
  path.nodes.length(5);
  /*
   * left
   */
  drawing->foreground(light);
  path.nodes[0].x = center.x, path.nodes[0].y = top, path.nodes[0].z = 0;
  path.nodes[1].x = left, path.nodes[1].y = bottom, path.nodes[1].z = 0;
  path.nodes[2].x = left + dx, path.nodes[2].y = bottom - thickness, path.nodes[2].z = 0;
  path.nodes[3].x = center.x, path.nodes[3].y = top + dy, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * right
   */
  drawing->foreground(dark);
  path.nodes[0].x = center.x, path.nodes[0].y = top, path.nodes[0].z = 0;
  path.nodes[1].x = center.x, path.nodes[1].y = top + dy, path.nodes[1].z = 0;
  path.nodes[2].x = right - dx, path.nodes[2].y = bottom - thickness, path.nodes[2].z = 0;
  path.nodes[3].x = right, path.nodes[3].y = bottom, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * bottom
   */
  path.nodes[0].x = left, path.nodes[0].y = bottom, path.nodes[0].z = 0;
  path.nodes[1].x = right, path.nodes[1].y = bottom, path.nodes[1].z = 0;
  path.nodes[2].x = right - dx, path.nodes[2].y = bottom - thickness, path.nodes[2].z = 0;
  path.nodes[3].x = left + dx, path.nodes[3].y = bottom - thickness, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  drawing->restore();
}

void downArrow(DrawTraversal_ptr traversal, Coord thickness, const Color &medium, const Color &light, const Color &dark,
	       Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
  Vertex center = {(right + left)/2, (bottom + top)/2, 0.};
  Vertex length = {(right - left), (bottom - top), 0.};
  Coord slope = 2 * length.y / length.x;
  Coord dy = thickness * std::sqrt(slope * slope + 1.0);
  Coord dx = thickness * (1 + 1 / slope);

  DrawingKit_var drawing = traversal->drawing();
  drawing->save();

  Path path;
  path.shape = convex;
  if (fill)
    {
      path.nodes.length(4);
      drawing->foreground(medium);
      path.nodes[0].x = right, path.nodes[0].y = top, path.nodes[0].z = 0;
      path.nodes[1].x = left, path.nodes[1].y = top, path.nodes[1].z = 0;
      path.nodes[2].x = center.x, path.nodes[2].y = bottom, path.nodes[2].z = 0;
      path.nodes[3] = path.nodes[0];
      drawing->draw_path(path);
    }
  path.nodes.length(5);
  /*
   * right
   */
  drawing->foreground(light);
  path.nodes[0].x = right, path.nodes[0].y = top, path.nodes[0].z = 0;
  path.nodes[1].x = right - dx, path.nodes[1].y = top + thickness, path.nodes[1].z = 0;
  path.nodes[2].x = center.x, path.nodes[2].y = bottom - dy, path.nodes[2].z = 0;
  path.nodes[3].x = center.x, path.nodes[3].y = bottom, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * top
   */
  drawing->foreground(dark);
  path.nodes[0].x = right, path.nodes[0].y = top, path.nodes[0].z = 0;
  path.nodes[1].x = left, path.nodes[1].y = top, path.nodes[1].z = 0;
  path.nodes[2].x = left + dx, path.nodes[2].y = top + thickness, path.nodes[2].z = 0;
  path.nodes[3].x = right - dx, path.nodes[3].y = top + thickness, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * left
   */
  path.nodes[0].x = left, path.nodes[0].y = top, path.nodes[0].z = 0;
  path.nodes[1].x = center.x, path.nodes[1].y = bottom, path.nodes[1].z = 0;
  path.nodes[2].x = center.x, path.nodes[2].y = bottom - dy, path.nodes[2].z = 0;
  path.nodes[3].x = left + dx, path.nodes[3].y = top + thickness, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  drawing->restore();
}

void diamond(DrawTraversal_ptr traversal, Coord thickness, const Color &medium, const Color &light, const Color &dark,
	     Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
  Vertex center = {(right + left)/2, (bottom + top)/2, 0.};
  Vertex length = {(right - left), (bottom - top), 0.};
  Coord dx = thickness * std::sqrt(length.x * length.x / (length.y * length.y) + 1.0);
  Coord dy = thickness * std::sqrt(length.y * length.y / (length.x * length.x) + 1.0);

  DrawingKit_var drawing = traversal->drawing();
  drawing->save();

  Path path;
  path.shape = convex;
  path.nodes.length(5);
  if (fill)
    {
      drawing->foreground(medium);
      path.nodes[0].x = center.x, path.nodes[0].y = top, path.nodes[0].z = 0;
      path.nodes[1].x = left, path.nodes[1].y = center.y, path.nodes[1].z = 0;
      path.nodes[2].x = center.x, path.nodes[2].y = bottom, path.nodes[2].z = 0;
      path.nodes[3].x = right, path.nodes[3].y = center.y, path.nodes[3].z = 0;
      path.nodes[4] = path.nodes[0];
      drawing->draw_path(path);
    }
  /*
   * top left
   */
  drawing->foreground(dark);
  path.nodes[0].x = center.x, path.nodes[0].y = top, path.nodes[0].z = 0;
  path.nodes[1].x = left, path.nodes[1].y = center.y, path.nodes[1].z = 0;
  path.nodes[2].x = left + dx, path.nodes[2].y = center.y, path.nodes[2].z = 0;
  path.nodes[3].x = center.x, path.nodes[3].y = top + dy, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * top right
   */
  path.nodes[0].x = center.x, path.nodes[0].y = top, path.nodes[0].z = 0;
  path.nodes[1].x = center.x, path.nodes[1].y = top + dy, path.nodes[1].z = 0;
  path.nodes[2].x = right - dx, path.nodes[2].y = center.y, path.nodes[2].z = 0;
  path.nodes[3].x = right, path.nodes[3].y = center.y, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * bottom left
   */
  drawing->foreground(light);
  path.nodes[0].x = left, path.nodes[0].y = center.y, path.nodes[0].z = 0;
  path.nodes[1].x = center.x, path.nodes[1].y = bottom, path.nodes[1].z = 0;
  path.nodes[2].x = center.x, path.nodes[2].y = bottom - dy, path.nodes[2].z = 0;
  path.nodes[3].x = left + dx, path.nodes[3].y = center.y, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  /*
   * bottom right
   */
  path.nodes[0].x = center.x, path.nodes[0].y = bottom, path.nodes[0].z = 0;
  path.nodes[1].x = right, path.nodes[1].y = center.y, path.nodes[1].z = 0;
  path.nodes[2].x = right - dx, path.nodes[2].y = center.y, path.nodes[2].z = 0;
  path.nodes[3].x = center.x, path.nodes[3].y = bottom - dy, path.nodes[3].z = 0;
  path.nodes[4] = path.nodes[0];
  drawing->draw_path(path);
  drawing->restore();
}

void circle(DrawTraversal_ptr, Coord thickness, const Color &medium, const Color &light, const Color &dark,
	    Coord left, Coord bottom, Coord right, Coord top, bool fill)
{
}

};
