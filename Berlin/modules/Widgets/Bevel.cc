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

#include "Widget/Bevel.hh"
#include "Warsaw/DrawTraversal.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/Color.hh"
#include "Berlin/Logger.hh"

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
// 	  requisition.x.align = ((requisition.x.natural - 2*t)*requisition.x.align + t)/requisition.x.natural;
	}
      if (vmargin && requisition.y.defined)
	{
	  requisition.y.natural += t;
	  requisition.y.maximum += t;
	  requisition.y.minimum += t;
// 	  requisition.y.align = ((requisition.y.natural - 2*t)*requisition.y.align + t)/requisition.y.natural;
	}
    }
//   cout << "Bevel::request " << requisition.x.align << ' ' << requisition.y.align << endl;
}

void Bevel::traverse(Traversal_ptr traversal)
{
  SectionLog section("Bevel::traverse");
  /*
   * cheap and dirty cull test -stefan
   */
//   if (!traversal->intersectsAllocation()) return;
  traversal->visit(Graphic_var(_this()));
  Graphic_var child = body();
  if (!CORBA::is_nil(child))
    {
      if (hmargin || vmargin)
	{
	  Impl_var<RegionImpl> allocation(new RegionImpl(Region_var(traversal->allocation())));
	  Impl_var<TransformImpl> tx(new TransformImpl);
	  Allocation::Info info;
	  info.allocation = allocation->_this();
	  info.transformation = tx->_this();
	  allocate(0, info);
	  traversal->traverseChild(child, 0, info.allocation, info.transformation);
	}
      else MonoGraphic::traverse(traversal);
    }
}

void Bevel::extension(const Allocation::Info &info, Region_ptr region)
{
  if (!CORBA::is_nil(info.allocation)) defaultExtension(info, region);
  else MonoGraphic::extension(info, region);
}

void Bevel::allocate(Tag, const Allocation::Info &info)
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
  Impl_var<RegionImpl> region(new RegionImpl(info.allocation));
  region->normalize(o);
  info.transformation->translate(o);
  info.allocation->copy(Region_var(region->_this()));
  
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
  
  info.allocation->copy(Region_var(allocation->_this()));
  info.transformation->translate(delta);
}

void Bevel::allocateSpan(const Requirement &r, Region::Allotment &a, Coord margin, Alignment align)
{
//   a.align = ((a.end - a.begin)*a.align - margin)/(a.end - a.begin - 2*margin);
  a.begin += margin;
  a.end -= margin;
}

void Bevel::rect(DrawTraversal_ptr dt, Coord thickness, const Color &medium, const Color &light, const Color &dark,
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

void Bevel::leftArrow(DrawTraversal_ptr dt, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		      Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
}

void Bevel::rightArrow(DrawTraversal_ptr dt, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		       Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
}

void Bevel::upArrow(DrawTraversal_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		    Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
}

void Bevel::downArrow(DrawTraversal_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		      Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
}

void Bevel::diamond(DrawTraversal_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		    Coord left, Coord right, Coord top, Coord bottom, bool fill)
{
}

void Bevel::circle(DrawTraversal_ptr, Coord thickness, const Color &light, const Color &medium, const Color &dark,
		   Coord left, Coord bottom, Coord right, Coord top, bool fill)
{
}
