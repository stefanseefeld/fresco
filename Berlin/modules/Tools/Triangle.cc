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
#include "Tool/Triangle.hh"
#include "Tool/Beveler.hh"

void InvisibleTriangle::draw(DrawTraversal_ptr traversal)
{
  Region_var allocation = traversal->allocation();
  Vertex l, u;
  allocation->bounds(l, u);
  DrawingKit_var drawing = traversal->kit();
  DrawingKit::Fillstyle style = drawing->surfaceFillstyle();
  if (style != DrawingKit::outlined && fill)
    {
      Path path;
      path.length(4);
      switch (direction)
	{
	case ToolKit::left:
	  path[0].x = l.x, path[0].y = (l.y + u.y)/2, path[0].z = 0;
	  path[1].x = u.x, path[1].y = l.y, path[1].z = 0;
	  path[2].x = u.x, path[2].y = u.y, path[2].z = 0;
	  path[3] = path[0];
	  break;
	case ToolKit::right:
	  path[0].x = l.x, path[0].y = l.y, path[0].z = 0;
	  path[1].x = u.x, path[1].y = (l.y + u.y)/2, path[1].z = 0;
	  path[2].x = l.x, path[2].y = u.y, path[2].z = 0;
	  path[3] = path[0];
	  break;
	case ToolKit::up:
	  path[0].x = l.x, path[0].y = u.y, path[0].z = 0;
	  path[1].x = (l.x + u.x)/2, path[1].y = l.y, path[1].z = 0;
	  path[2].x = u.x, path[2].y = u.y, path[2].z = 0;
	  path[3] = path[0];
	  break;
	case ToolKit::down:
	  path[0].x = l.x, path[0].y = l.y, path[0].z = 0;
	  path[1].x = (l.x + u.x)/2, path[1].y = u.y, path[1].z = 0;
	  path[2].x = l.x, path[2].y = l.y, path[2].z = 0;
	  path[3] = path[0];
	  break;
	}
      drawing->drawPath(path);
    }
  else if (fill)
    {
      drawing->saveState();
      drawing->surfaceFillstyle(DrawingKit::solid);
      Path path;
      path.length(4);
      switch (direction)
	{
	case ToolKit::left:
	  path[0].x = l.x, path[0].y = (l.y + u.y)/2, path[0].z = 0;
	  path[1].x = u.x, path[1].y = l.y, path[1].z = 0;
	  path[2].x = u.x, path[2].y = u.y, path[2].z = 0;
	  path[3] = path[0];
	  break;
	case ToolKit::right:
	  path[0].x = l.x, path[0].y = l.y, path[0].z = 0;
	  path[1].x = u.x, path[1].y = (l.y + u.y)/2, path[1].z = 0;
	  path[2].x = l.x, path[2].y = u.y, path[2].z = 0;
	  path[3] = path[0];
	  break;
	case ToolKit::up:
	  path[0].x = l.x, path[0].y = u.y, path[0].z = 0;
	  path[1].x = (l.x + u.x)/2, path[1].y = l.y, path[1].z = 0;
	  path[2].x = u.x, path[2].y = u.y, path[2].z = 0;
	  path[3] = path[0];
	  break;
	case ToolKit::down:
	  path[0].x = l.x, path[0].y = l.y, path[0].z = 0;
	  path[1].x = (l.x + u.x)/2, path[1].y = u.y, path[1].z = 0;
	  path[2].x = l.x, path[2].y = l.y, path[2].z = 0;
	  path[3] = path[0];
	  break;
	}      
      drawing->drawPath(path);
      drawing->restoreState();
    }
  else
    {
      Color color = drawing->foreground();
      switch (direction)
	{
	case ToolKit::left:
	  Beveler::leftArrow(traversal, thickness, color, color, color, l.x, u.x, l.y, u.y, fill);
	  break;
	case ToolKit::right:
	  break;
	  Beveler::leftArrow(traversal, thickness, color, color, color, l.x, u.x, l.y, u.y, fill);
	case ToolKit::up:
	  break;
	  Beveler::leftArrow(traversal, thickness, color, color, color, l.x, u.x, l.y, u.y, fill);
	case ToolKit::down:
	  break;
	  Beveler::leftArrow(traversal, thickness, color, color, color, l.x, u.x, l.y, u.y, fill);
	}
    }
}

void BeveledTriangle::draw(DrawTraversal_ptr traversal)
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

  switch (direction)
    {
    case ToolKit::left:
      switch (style)
	{
	case inset:
	  Beveler::leftArrow(traversal, thickness, color, dark, light, l.x, u.x, l.y, u.y, fill);
	  break;
	case outset:
	  Beveler::leftArrow(traversal, thickness, color, light, dark, l.x, u.x, l.y, u.y, fill);
	  break;
	case convex:
	  Beveler::leftArrow(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, false);
	  l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
	  Beveler::leftArrow(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, fill);
	  break;
	case concav:
	  Beveler::leftArrow(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, false);
	  l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
	  Beveler::leftArrow(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, fill);
	  break;
	}
      break;
    case ToolKit::right:
      switch (style)
	{
	case inset:
	  Beveler::rightArrow(traversal, thickness, color, dark, light, l.x, u.x, l.y, u.y, fill);
	  break;
	case outset:
	  Beveler::rightArrow(traversal, thickness, color, light, dark, l.x, u.x, l.y, u.y, fill);
	  break;
	case convex:
	  Beveler::rightArrow(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, false);
	  l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
	  Beveler::rightArrow(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, fill);
      break;
	case concav:
	  Beveler::rightArrow(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, false);
	  l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
	  Beveler::rightArrow(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, fill);
	  break;
	}
      break;
    case ToolKit::up:
      switch (style)
	{
	case inset:
	  Beveler::upArrow(traversal, thickness, color, light, dark, l.x, u.x, l.y, u.y, fill);
	  break;
	case outset:
	  Beveler::upArrow(traversal, thickness, color, dark, light, l.x, u.x, l.y, u.y, fill);
	  break;
	case convex:
	  Beveler::upArrow(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, false);
	  l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
	  Beveler::upArrow(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, fill);
	  break;
	case concav:
	  Beveler::upArrow(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, false);
	  l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
	  Beveler::upArrow(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, fill);
	  break;
	}
      break;
    case ToolKit::down:
      switch (style)
	{
	case inset:
	  Beveler::downArrow(traversal, thickness, color, dark, light, l.x, u.x, l.y, u.y, fill);
	  break;
	case outset:
	  Beveler::downArrow(traversal, thickness, color, light, dark, l.x, u.x, l.y, u.y, fill);
	  break;
	case convex:
	  Beveler::downArrow(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, false);
	  l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
	  Beveler::downArrow(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, fill);
	  break;
	case concav:
	  Beveler::downArrow(traversal, thickness/2, color, dark, light, l.x, u.x, l.y, u.y, false);
	  l.x += thickness/2, u.x -= thickness/2, l.y += thickness/2, u.y -= thickness/2;
	  Beveler::downArrow(traversal, thickness/2, color, light, dark, l.x, u.x, l.y, u.y, fill);
	  break;
	}
      break;
    }
  drawing->restoreState();
}

void ColoredTriangle::draw(DrawTraversal_ptr traversal)
{
  Region_var allocation = traversal->allocation();
  Vertex l, u;
  allocation->bounds(l, u);
  DrawingKit_var drawing = traversal->kit();
  DrawingKit::Fillstyle style = drawing->surfaceFillstyle();
  drawing->saveState();
  Color tmp = drawing->foreground();
  tmp.red = color.red;
  tmp.green = color.green;
  tmp.blue = color.blue;
  drawing->foreground(tmp);
  if (style == DrawingKit::outlined) drawing->surfaceFillstyle(DrawingKit::solid);
  if (fill) drawing->drawRect(l, u);
  else
    {
      Vertex ltmp = l, utmp = u;
      utmp.y = ltmp.y + thickness;
      drawing->drawRect(ltmp, utmp);
      ltmp.x = utmp.x - thickness, ltmp.y = utmp.y;
      utmp.y = u.y - thickness;
      drawing->drawRect(ltmp, utmp);
      ltmp.x = l.x, utmp.x = l.x + thickness;
      drawing->drawRect(ltmp, utmp);
      ltmp.y = u.y - thickness;
      utmp = u;
      drawing->drawRect(ltmp, utmp);
    }
  drawing->restoreState();
}

