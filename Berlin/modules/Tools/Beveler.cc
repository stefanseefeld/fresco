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

#include "Warsaw/DrawTraversal.hh"
#include "Warsaw/DrawingKit.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/Color.hh"
#include "Berlin/Logger.hh"
#include "Tool/Beveler.hh"

namespace Beveler
{

void rect(DrawTraversal_ptr dt, Coord thickness, const Color &medium, const Color &light, const Color &dark,
	  Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
  Coord lefti = left + thickness;
  Coord righti = right - thickness;
  Coord topi = top + thickness;
  Coord bottomi = bottom - thickness;
  DrawingKit_var dk = dt->kit();
  dk->saveState();
  Path path;
  path.length(5);
  if (fill)
    {
      Vertex lower = {left, top, 0.};
      Vertex upper = {right, bottom, 0.};
      dk->foreground(medium);
      dk->drawRect(lower, upper);
    }
  dk->surfaceFillstyle(DrawingKit::solid);
  /*
   * light edges
   */
  dk->foreground(light);
  /*
   * left edge
   */
  path[0].x = left, path[0].y = top, path[0].z = 0.;
  path[1].x = lefti, path[1].y = topi, path[1].z = 0.;
  path[2].x = lefti, path[2].y = bottomi, path[2].z = 0.;
  path[3].x = left, path[3].y = bottom, path[3].z = 0.;
  path[4].x = left, path[4].y = top, path[4].z = 0.;
  dk->drawPath(path);
  /*
   * top edge
   */
  path[0].x = left, path[0].y = top, path[0].z = 0.;
  path[1].x = right, path[1].y = top, path[1].z = 0.;
  path[2].x = righti, path[2].y = topi, path[2].z = 0.;
  path[3].x = lefti, path[3].y = topi, path[3].z = 0.;
  path[4].x = left, path[4].y = top, path[4].z = 0.;
  dk->drawPath(path);
  /*
   * dark edges
   */
  dk->foreground(dark);
  /*
   * right edge
   */
  path[0].x = right, path[0].y = top, path[0].z = 0.;
  path[1].x = right, path[1].y = bottom, path[1].z = 0.;
  path[2].x = righti, path[2].y = bottomi, path[2].z = 0.;
  path[3].x = righti, path[3].y = topi, path[3].z = 0.;
  path[4].x = right, path[4].y = top, path[4].z = 0.;
  dk->drawPath(path);
  /*
   * bottom edge
   */
  path[0].x = left, path[0].y = bottom, path[0].z = 0.;
  path[1].x = lefti, path[1].y = bottomi, path[1].z = 0.;
  path[2].x = righti, path[2].y = bottomi, path[2].z = 0.;
  path[3].x = right, path[3].y = bottom, path[3].z = 0.;
  path[4].x = left, path[4].y = bottom, path[4].z = 0.;
  dk->drawPath(path);
  dk->restoreState();
}

void leftArrow(DrawTraversal_ptr dt, Coord thickness, const Color &light, const Color &medium, const Color &dark,
	       Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
}

void rightArrow(DrawTraversal_ptr dt, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
}

void upArrow(DrawTraversal_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
	     Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
}

void downArrow(DrawTraversal_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
	       Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
}

void diamond(DrawTraversal_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
	     Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
}

void circle(DrawTraversal_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
	    Coord left, Coord bottom, Coord right, Coord top, bool fill)
{
}

};
