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
#include "Berlin/DrawTraversalImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Providers.hh"
#include "Berlin/GGI.hh"
#include <Warsaw/Graphic.hh>
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/IO.hh>
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

DrawTraversalImpl::DrawTraversalImpl(Graphic_ptr g, Region_ptr r, Transform_ptr t, DrawingKit_ptr kit)
  : TraversalImpl(g, r, t),
    drawing(DrawingKit::_duplicate(kit)),
    clipping(Region::_duplicate(r)),
    id(new TransformImpl)
{
}

void DrawTraversalImpl::init()
{
  /*
   * initialize the different drawing kit attributes
   */
  drawing->saveState();
  drawing->clipping(clipping);
  Color black = {0., 0., 0., 1.};
  drawing->foreground(black);
  Color white = {1., 1., 1., 1.};
  drawing->lighting(white);
  drawing->transformation(Transform_var(id->_this()));
  drawing->surfaceFillstyle(DrawingKit::solid);
  Vertex l, u;
  clipping->bounds(l, u);
  /*
   * clear the background of the damaged region...
   */
  drawing->drawRect(l, u);
}

void DrawTraversalImpl::finish() { drawing->restoreState();}

DrawTraversalImpl::DrawTraversalImpl(const DrawTraversalImpl &t)
  : TraversalImpl(t),
    drawing(t.drawing),
    clipping(t.clipping)
{
//   drawing->clipping(clipping);
}

DrawTraversalImpl::~DrawTraversalImpl()
{
  drawing->restoreState();
  id->_dispose();
}

CORBA::Boolean DrawTraversalImpl::intersectsAllocation()
{
  Region_var r = allocation();
  Transform_var t = transformation();
  RegionImpl region(r, t);
  return region.intersects(clipping);
}
CORBA::Boolean DrawTraversalImpl::intersectsRegion(Region_ptr r)
{
  Transform_var t = transformation();
  RegionImpl region(r, t);
//   RegionImpl cl(clipping);
//   cout << "DrawTraversalImpl::intersectsRegion " << region << ' ' << clipping << endl;
  return region.intersects(clipping);
}

void DrawTraversalImpl::traverseChild(Graphic_ptr child, Tag tag, Region_ptr region, Transform_ptr transform)
{
  //  Trace trace("DrawTraversalImpl::traverseChild");
  if (CORBA::is_nil(region)) region = Region_var(allocation());
  Lease<TransformImpl> cumulative;
  Providers::trafo.provide(cumulative);
  cumulative->copy(transformation());
  if (!CORBA::is_nil(transform)) cumulative->premultiply(transform);
  drawing->transformation(cumulative->_this());
  //   drawable->clipping(region, Transform_var(tx->_this()));
  push(child, tag, region, cumulative.release());
  child->traverse(_this());
  pop();
};

void DrawTraversalImpl::visit(Graphic_ptr g) { g->draw(_this());}
DrawingKit_ptr DrawTraversalImpl::kit() { return DrawingKit::_duplicate(drawing);}
