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
#include "Berlin/Provider.hh"
#include "Berlin/Console.hh"
#include <Warsaw/Graphic.hh>
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/IO.hh>
#include <Prague/Sys/Tracer.hh>

using namespace Prague;
using namespace Warsaw;

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
  drawing->save();
  drawing->clipping(clipping);
  Color fg = {0., 0., 0., 1.};
  drawing->foreground(fg);
  Color white = {1., 1., 1., 1.};
  drawing->lighting(white);
  drawing->transformation(Transform_var(id->_this()));
  drawing->surface_fillstyle(DrawingKit::solid);
  Vertex l, u;
  clipping->bounds(l, u);
  /*
   * clear the background of the damaged region...
   */
  drawing->draw_rectangle(l, u);
#if 0
  drawing->flush();
  Console::drawable()->flush();
  sleep(1);
#endif
}

void DrawTraversalImpl::finish() { drawing->restore();}

DrawTraversalImpl::DrawTraversalImpl(const DrawTraversalImpl &t)
  : TraversalImpl(t),
    drawing(t.drawing),
    clipping(t.clipping)
{
//   drawing->clipping(clipping);
}

DrawTraversalImpl::~DrawTraversalImpl()
{
  drawing->restore();
//  id->_dispose();
}

CORBA::Boolean DrawTraversalImpl::intersects_allocation()
{
  Region_var r = allocation();
  Transform_var t = transformation();
  RegionImpl region(r, t);
  return region.intersects(clipping);
}

CORBA::Boolean DrawTraversalImpl::intersects_region(Region_ptr r)
{
  Transform_var t = transformation();
  RegionImpl region(r, t);
//   RegionImpl cl(clipping);
//   cout << "DrawTraversalImpl::intersectsRegion " << region << ' ' << clipping << endl;
  return region.intersects(clipping);
}

void DrawTraversalImpl::traverse_child(Graphic_ptr child, Tag tag, Region_ptr region, Transform_ptr transform)
{
  Trace trace("DrawTraversalImpl::traverse_child");
  if (CORBA::is_nil(region)) region = Region_var(allocation());
  Lease_var<TransformImpl> cumulative(Provider<TransformImpl>::provide());
  cumulative->copy(Transform_var(transformation()));
  if (!CORBA::is_nil(transform)) cumulative->premultiply(transform);
  drawing->transformation(Transform_var(cumulative->_this()));
  //   drawable->clipping(region, Transform_var(tx->_this()));
  push(child, tag, region, cumulative._retn());
  try { child->traverse(Traversal_var(_this()));}
  catch (...) { pop(); throw;}
  pop(); 
};

void DrawTraversalImpl::visit(Graphic_ptr g) { g->draw(DrawTraversal_var(_this()));}
DrawingKit_ptr DrawTraversalImpl::kit() { return DrawingKit::_duplicate(drawing);}
