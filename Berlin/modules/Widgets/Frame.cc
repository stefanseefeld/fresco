/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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

#include <Widget/Frame.hh>
#include <Warsaw/Traversal.hh>
#include <Berlin/Color.hh>

Frame::Frame(const Color &c, type ty, Coord t, bool f, double xa, double ya, bool hm, bool vm)
  : Bevel(t, xa, ya, hm, vm), color(c), filled(f), mode(ty)
{
}

Frame::~Frame() {}

void Frame::draw(DrawTraversal_ptr dt)
{
  Region_var allocation = dt->allocation();
  Vertex u, l;
  allocation->bounds(l, u);
  Color light, dark;
  switch (mode)
    {
    case inset:
      light = brightness(color, 0.5);
      dark = brightness(color, -0.5);
      break;
    case outset:
      light = brightness(color,-0.5);
      dark = brightness(color,  0.5);
      break;
    case outline:
      light = brightness(color,-1.0);
      dark = brightness(color,-1.0);
      break;
    }
  Bevel::rect(dt, thickness, color, light, dark, l.x, u.x, l.y, u.y);
}
