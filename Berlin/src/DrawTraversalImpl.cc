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
#include "Berlin/DrawTraversalImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/ImplVar.hh"
#include "Warsaw/Graphic.hh"
#include "Warsaw/DrawingKit.hh"
#include "Warsaw/Region.hh"

DrawTraversalImpl::DrawTraversalImpl(Graphic_ptr g, Region_ptr r, Transform_ptr t, DrawingKit_ptr kit)
  : TraversalImpl(g, r, t),
    drawing(DrawingKit::_duplicate(kit)),
    clipping(Region::_duplicate(r))
{
  drawing->saveState();
  drawing->clipping(clipping);
}

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

void DrawTraversalImpl::traverseChild(Graphic_ptr g, Tag t, Region_ptr region, Transform_ptr transform)
{
//   Impl_var<TransformImpl> tx(new TransformImpl);
//   tx->copy(Transform_var(transformation()));
//   tx->premultiply(transform);
//   drawable->pushClipping(region, Transform_var(tx->_this()));
  drawing->saveState();
//   drawing->pushTransform(transform);
  TraversalImpl::traverseChild(g, t, region, transform);
  drawing->restoreState();
//   drawable->popClipping();
};

void DrawTraversalImpl::visit(Graphic_ptr g) { g->draw(DrawTraversal_var(_this()));}
DrawingKit_ptr DrawTraversalImpl::kit() { return DrawingKit::_duplicate(drawing);}
