/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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

#include "Widget/Bevel.hh"

Bevel::Bevel(Coord t, Alignment x, Alignment y, bool h, bool v)
  : thickness(t), xalign(x), yalign(y), hmargin(h), vmargin(v)
{
  allocation = new RegionImpl;
  allocation->_obj_is_ready(CORBA::BOA::boa());
}

Bevel::~Bevel()
{
  allocation->_dispose();
}

void Bevel::request(Requisition &r)
{
  MonoGraphic::request(r);
  if (hmargin || vmargin)
    {
      Coord t = thickness + thickness;
      if (hmargin && r.x.defined)
	{
	  r.x.natural += t;
	  r.x.maximum += t;
	  r.x.minimum += t;
	}
      if (vmargin && r.y.defined)
	{
	  r.y.natural += t;
	  r.y.maximum += t;
	  r.y.minimum += t;
	}
    }
}

void Bevel::traverse(Traversal_ptr t)
{
  t->visit(this);
  if (!CORBA::is_nil(body()))
    {
      if (hmargin || vmargin)
	{
	  TransformImpl *tx = new TransformImpl;
	  tx->_obj_is_ready(_boa());
	  Allocation::Info a;
	  a.allocation = t->allocation();
	  a.transformation = tx->_this();
	  allocateChild(a);
	  t->traverseChild(body(), a.allocation, a.transformation);
	  tx->_dispose();
	}
      else MonoGraphic::traverse(t);
    }
}

void Bevel::extension(const Graphic::AllocationInfo &a, Region_ptr r)
{
  if (!CORBA::is_nil(a.allocation))
    defaultExtension(a, r);
  else
    MonoGraphic::extension(a, r);
}

void Bevel::allocateChild(Allocation::Info &info)
{
  {
    Vertex o;
    RegionImpl *region = new RegionImpl(info.allocation, Transform::_nil());
    region->_obj_is_ready(_boa());
    region->origin(o);
    region->lower.x -= o.x; region->upper.x -= o.x;
    region->lower.y -= o.y; region->upper.y -= o.y;
    region->lower.z -= o.z; region->upper.z -= o.z;
    info.transformation->translate(o);
    info.allocation->copy(region->_this());
    region->_dispose();
  }

  Requisition req;
  GraphicImpl::initRequisition(req);
  MonoGraphic::request(req);
  allocation->defined = true;
  Region::Allotment a;

  Vertex delta;
  info.allocation->span(xaxis, a);
  allocateSpan(req.x, a, hmargin ? thickness : 0, xalign);
  allocation->lower.x = -(a.end - a.begin) * a.align;
  allocation->upper.x = allocation->lower.x + a.length;
  allocation->xalign  = a.align;
  delta.x = a.begin - allocation->lower.x;

  info.allocation->span(yaxis, a);
  allocateSpan(req.y, a, vmargin ? thickness : 0, yalign);
  allocation->lower.y = -(a.end - a.begin) * a.align;
  allocation->upper.y = allocation->lower.y + a.length;
  allocation->yalign  = a.align;
  delta.y = a.begin - allocation->lower.y;
  delta.z = 0;

  info.allocation->copy(allocation);
  info.transformation->translate(delta);
}

void Bevel::allocateSpan(Graphic::Requirement &r, Region::Allotment &a, Coord margin, Alignment align)
{
//   Coord delta = 2*margin;
//   s.begin += a.align*delta, a.end -= a.align*delta;
//   Coord offset = margin;
//   if (r.defined)
//     {
//       if (a.end - a.begin > r.maximum)
// 	{
// 	  offset += align * (a.end - a.begin - r.maximum);
// 	  a.begin = a.align*r.maximum, a.end = (1. - a.align)*r.maximum;
// 	}
//     }
//   a.origin += offset * (1 - s.align - s.align);
//   a.begin = a.origin - s.align * s.length;
}

void Bevel::rect(Pencil_ptr p, Coord thickness,
		 Color_ptr light, Color_ptr medium, Color_ptr dark,
		 Coord left, Coord bottom, Coord right, Coord top)
{
  if (!CORBA::is_nil(medium))
    {
      setColor(p, medium);
      p->fillRect(left, bottom, right, top);
    }

  Coord left_inside = left + thickness;
  Coord bottom_inside = bottom + thickness;
  Coord right_inside = right - thickness;
  Coord top_inside = top - thickness;
  
  Vertex v[10];

  // left edge
  set_color(p, light);
  v[0].x = left; v[0].y = bottom;
  v[1].x = left; v[1].y = top;
  v[2].x = left_inside; v[2].y = top;
  v[3].x = left_inside; v[3].y = bottom;
  fill_path(p, v, 4);
  
  // top edge
  v[0].x = left_inside; v[0].y = top_inside;
  v[1].x = left_inside; v[1].y = top;
  v[2].x = right; v[2].y = top;
  v[3].x = right; v[3].y = top_inside;
  fill_path(p, v, 4);

  // right edge
  set_color(p, dark);
  v[0].x = right_inside; v[0].y = bottom_inside;
  v[1].x = right_inside; v[1].y = top_inside;
  v[2].x = right; v[2].y = top;
  v[3].x = right; v[3].y = bottom;

  // bottom edge (as part of same path)
  v[4].x = left; v[4].y = bottom;
  v[5].x = left_inside; v[5].y = bottom_inside;
  v[6].x = right_inside; v[6].y = bottom_inside;
  fill_path(p, v, 7);
}

//
// A bit of a misnomer to call these arrows; they are really beveled
// triangles.  The only tricky part is dropping the bevel down and to the
// right of the original triangle, which requires finding delta x,y for
// a given thickness and matching the slope of the triangle.
//

void Bevel::leftArrow(Pencil_ptr p, Coord thickness,
		      Color_ptr light, Color_ptr medium, Color_ptr dark,
		      Coord left, Coord bottom, Coord right, Coord top)
{
  Coord center_y = (bottom + top) * Coord(0.5);
  float slope = ((top - bottom) / (right - left)) * Coord(0.5);
  float delta_x = float(thickness / sqrt(slope * slope + 1.0f));
  float delta_y = slope * delta_x;

  Vertex v[10];

  setColor(p, medium);
  v[0].x = left; v[0].y = center_y;
  v[1].x = right; v[1].y = top;
  v[2].x = right; v[2].y = bottom;
  fill_path(p, v, 3);

  setColor(p, dark);
  v[0].x = right - thickness; v[0].y = bottom + thickness;
  v[1].x = v[0].x; v[1].y = top - thickness;
  v[2].x = right; v[2].y = top;
  v[3].x = right; v[3].y = bottom;
  fill_path(p, v, 4);

  v[0].x = left; v[1].y = center_y;
  v[1].x = left + thickness; v[1].y = center_y;
  v[2].x = right - thickness; v[2].y = bottom + thickness;
  v[3].x = right; v[3].y = bottom;
  fill_path(p, v, 4);

  setColor(p, light);
  v[0].x = left + delta_x; v[0].y = center_y - delta_y;
  v[1].x = left; v[1].y = center_y;
  v[2].x = right; v[2].y = top;
  v[3].x = right; v[3].y = top - thickness;
  fill_path(p, v, 4);
}

void Bevel::rightArrow(Pencil_ptr p, Coord thickness,
		       Color_ptr light, Color_ptr medium, Color_ptr dark,
		       Coord left, Coord bottom, Coord right, Coord top)
{
  Coord center_y = (bottom + top) * Coord(0.5);
  float slope = ((top - bottom) / (right - left)) * Coord(0.5);
  float delta_x = float(thickness / sqrt(slope * slope + 1.0f));
  float delta_y = slope * delta_x;

  Vertex v[10];

  set_color(p, medium);
  v[0].x = left; v[0].y = bottom;
  v[1].x = left; v[1].y = top;
  v[2].x = right; v[2].y = center_y;
  fill_path(p, v, 3);

  set_color(p, dark);
  v[0].x = left; v[0].y = bottom;
  v[1].x = left + thickness; v[1].y = bottom + thickness;
  v[2].x = right - thickness; v[2].y = center_y;
  v[3].x = right; v[3].y = center_y;
  fill_path(p, v, 4);

  set_color(p, light);
  v[0].x = left; v[0].y = bottom;
  v[1].x = left; v[1].y = top;
  v[2].x = left + thickness; v[2].y = top - thickness;
  v[3].x = left + delta_x; v[3].y = bottom + delta_y;
  fill_path(p, v, 4);

  v[0].x = left + thickness; v[0].y = top - thickness;
  v[1].x = left; v[1].y = top;
  v[2].x = right; v[2].y = center_y;
  v[3].x = right - delta_x; v[3].y = center_y - delta_y;
  fill_path(p, v, 4);
}

void Bevel::upArrow(Pencil_ptr p, Coord thickness,
		    Color_ptr light, Color_ptr medium, Color_ptr dark,
		    Coord left, Coord bottom, Coord right, Coord top)
{
  Coord center_x = (left + right) * Coord(0.5);
  float slope = Coord(2) * ((top - bottom) / (right - left));
  float delta_x = float(thickness / sqrt(slope * slope + 1.0f));
  float delta_y = slope * delta_x;

  Vertex v[10];

  set_color(p, medium);
  v[0].x = left; v[0].y = bottom;
  v[1].x = center_x; v[1].y = top;
  v[2].x = right; v[2].y = bottom;
  fill_path(p, v, 3);

  set_color(p, dark);
  v[0].x = left; v[0].y = bottom;
  v[1].x = right; v[1].y = bottom;
  v[2].x = right - thickness; v[2].y = bottom + thickness;
  v[3].x = left + thickness; v[3].y = v[2].y;
  fill_path(p, v, 4);

  v[0].x = center_x; v[0].y = top - thickness;
  v[1].x = center_x; v[1].y = top;
  v[2].x = right; v[2].y = bottom;
  v[3].x = right - thickness; v[3].y = bottom + thickness;
  fill_path(p, v, 4);

  set_color(p, light);
  v[0].x = left; v[0].y = bottom;
  v[1].x = left + delta_x; v[1].y = bottom;
  v[2].x = center_x + delta_x; v[2].y = top - delta_y;
  v[3].x = center_x; v[3].y = top;
  fill_path(p, v, 4);
}

void Bevel::downArrow(Pencil_ptr p, Coord thickness,
		      Color_ptr light, Color_ptr medium, Color_ptr dark,
		      Coord left, Coord bottom, Coord right, Coord top)
{
  Coord center_x = (left + right) * Coord(0.5);
  float slope = Coord(2) * ((top - bottom) / (right - left));
  float delta_x = float(thickness / sqrt(slope * slope + 1.0f));
  float delta_y = slope * delta_x;

  Vertex v[10];

  set_color(p, medium);
  v[0].x = left; v[0].y = top;
  v[1].x = right; v[1].y = top;
  v[2].x = center_x; v[2].y = bottom;
  fill_path(p, v, 3);

  set_color(p, dark);
  v[0].x = center_x; v[0].y = bottom;
  v[1].x = center_x; v[1].y = bottom + thickness;
  v[2].x = right - thickness; v[2].y = top - thickness;
  v[3].x = right; v[3].y = top;
  fill_path(p, v, 4);

  set_color(p, light);
  v[0].x = left; v[0].y = top;
  v[1].x = center_x; v[1].y = bottom;
  v[2].x = center_x + delta_x; v[2].y = bottom + delta_y;
  v[3].x = left + thickness; v[3].y = top - thickness;
  fill_path(p, v, 4);

  v[0].x = left; v[0].y = top;
  v[1].x = right; v[1].y = top;
  v[2].x = right - delta_x; v[2].y = top - delta_y;
  v[3].x = left + thickness; v[3].y = top - thickness;
  fill_path(p, v, 4);
}

void Bevel::diamond(Pencil_ptr p, Coord thickness,
		    Color_ptr light, Color_ptr medium, Color_ptr dark,
		    Coord left, Coord bottom, Coord right, Coord top)
{
  Coord x_mid = (left + right) * Coord(0.5);
  Coord y_mid = (bottom + top) * Coord(0.5);
  Coord left_inside = left + thickness;
  Coord top_inside = top - thickness;
  Coord right_inside = right - thickness;
  Coord bottom_inside = bottom + thickness;

  Vertex v[10];

  // interior of diamond
  set_color(p, medium);
  v[0].x = left; v[0].y = y_mid;
  v[1].x = x_mid; v[1].y = top;
  v[2].x = right; v[2].y = y_mid;
  v[3].x = x_mid; v[3].y = bottom;
  fill_path(p, v, 4);

  // lower half
  set_color(p, dark);
  v[0].x = left; v[0].y = y_mid;
  v[1].x = x_mid; v[1].y = bottom;
  v[2].x = right; v[2].y = y_mid;
  v[3].x = right_inside; v[3].y = y_mid;
  v[4].x = x_mid; v[4].y = bottom_inside;
  v[5].x = left_inside; v[5].y = y_mid;
  fill_path(p, v, 6);

  // upper half
  set_color(p, light);
  v[0].x = left; v[0].y = y_mid;
  v[1].x = x_mid; v[1].y = top;
  v[2].x = right; v[2].y = y_mid;
  v[3].x = right_inside; v[3].y = y_mid;
  v[4].x = x_mid; v[4].y = top_inside;
  v[5].x = left_inside; v[5].y = y_mid;
  fill_path(p, v, 6);
}
