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

#include <Widget/Bevel.hh>
#include <Warsaw/Traversal.hh>

Bevel::Bevel(Coord t, Alignment x, Alignment y, bool h, bool v)
  : thickness(t), xalign(x), yalign(y), hmargin(h), vmargin(v)
{
  allocation = new RegionImpl;
  allocation->_obj_is_ready(_boa());
}

Bevel::~Bevel()
{
  allocation->_dispose();
}

void Bevel::request(Requisition &requisition)
{
  MonoGraphic::request(requisition);
  if (hmargin || vmargin)
    {
      Coord t = thickness + thickness;
      if (hmargin && requisition.x.defined)
	{
	  requisition.x.natural += t;
	  requisition.x.maximum += t;
	  requisition.x.minimum += t;
	}
      if (vmargin && requisition.y.defined)
	{
	  requisition.y.natural += t;
	  requisition.y.maximum += t;
	  requisition.y.minimum += t;
	}
    }
}

void Bevel::traverse(Traversal_ptr traversal)
{
  traversal->visit(_this());
  if (!CORBA::is_nil(body()))
    {
      if (hmargin || vmargin)
	{
	  Allocation::Info a;
	  a.allocation = traversal->allocation();
	  allocateChild(a);
	  traversal->traverseChild(body(), a.allocation, a.transformation);
	}
      else
	MonoGraphic::traverse(traversal);
    }
}

void Bevel::extension(const Allocation::Info &a, Region_ptr r)
{
  if (!CORBA::is_nil(a.allocation))
    defaultExtension(a, r);
  else
    MonoGraphic::extension(a, r);
}

void Bevel::allocateChild(Allocation::Info &info)
{
  Requisition req;
  GraphicImpl::initRequisition(req);
  MonoGraphic::request(req);
  allocation->valid = true;
  Region::Allotment a;

  /*
   * same as Placement::normalTransform...
   */
  Vertex o;
  RegionImpl *r = new RegionImpl(info.allocation, Transform::_nil());
  r->_obj_is_ready(_boa());
  r->origin(o);
  r->lower.x -= o.x; r->upper.x -= o.x;
  r->lower.y -= o.y; r->upper.y -= o.y;
  r->lower.z -= o.z; r->upper.z -= o.z;
  info.transformation->translate(o);
  info.allocation->copy(r->_this());
  r->_dispose();
  
  Vertex delta;
  info.allocation->span(xaxis, a);
  allocateSpan(req.x, a, hmargin ? thickness : 0, xalign);
  allocation->lower.x = -(a.end - a.begin) * a.align;
  allocation->upper.x = allocation->lower.x + (a.end - a.begin);
  allocation->xalign = a.align;
  delta.x = a.begin - allocation->lower.x;

  info.allocation->span(yaxis, a);
  allocateSpan(req.y, a, vmargin ? thickness : 0, yalign);
  allocation->lower.y = -(a.end - a.begin) * a.align;
  allocation->upper.y = allocation->lower.y + (a.end - a.begin);
  allocation->yalign = a.align;
  delta.y = a.begin - allocation->lower.y;
  delta.z = 0;
  
  info.allocation->copy(allocation->_this());
  info.transformation->translate(delta);
}

void Bevel::allocateSpan(const Requirement &r, Region::Allotment &a, Coord margin, Alignment align)
{
  Coord length = a.end - a.begin - 2*margin;
  Coord offset = margin;
  if (r.defined)
    {
      if (length > r.maximum)
	{
	  offset += align * (length - r.maximum);
	  length = r.maximum;
	}
    }
  // FIXME !!!
//   Coord origin = offset * (1 - a.align - a.align);
//   a.begin = origin - a.align * length;
//   a.end = a.begin + length;
}

void Bevel::rect(DrawingKit_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		 Coord left, Coord bottom, Coord right, Coord top)
{
}

void Bevel::leftArrow(DrawingKit_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		      Coord left, Coord bottom, Coord right, Coord top)
{
}

void Bevel::rightArrow(DrawingKit_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		       Coord left, Coord bottom, Coord right, Coord top)
{
}

void Bevel::upArrow(DrawingKit_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		    Coord left, Coord bottom, Coord right, Coord top)
{
}

void Bevel::downArrow(DrawingKit_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		      Coord left, Coord bottom, Coord right, Coord top)
{
}

void Bevel::diamond(DrawingKit_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		    Coord left, Coord bottom, Coord right, Coord top)
{
}

void Bevel::circle(DrawingKit_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		   Coord left, Coord bottom, Coord right, Coord top)
{
}
