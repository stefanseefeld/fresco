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
#include "Layout/Placement.hh"
#include "Layout/LayoutManager.hh"

Placement::Placement(Graphic_ptr g, LayoutManager *l)
{
  body(g);
  layout = l;
  result = new RegionImpl;
}

Placement::~Placement()
{
  delete layout;
  CORBA::release(result);
}

void Placement::request(Requisition &r)
{
  MonoGraphic::request(r);
  layout->request(0, 0, r);
}

void Placement::allocateChild(Graphic::AllocationInfo &a)
{
  Region_ptr given = a.allocation;
  result->copy(given);
  Graphic::Requisition r;
  GraphicImpl::initRequisition(r);
  MonoGraphic::request(r);
  layout->allocate(1, &r, given, &result);

  TransformImpl tx;
  normalTransform(result, &tx);
  if (CORBA::is_nil(a.transformation))
    a.transformation = new TransformImpl;
  a.transformation->premultiply(&tx);
  given->copy(result);
}

void Placement::traverse(Traversal_ptr t)
{
//   Region_var given = t->allocation();
//   if (!CORBA::is_nil(given))
//     {
//       result->copy(given);
//       Graphic::Requisition r;
//       GraphicImpl::initRequisition(r);
//       MonoGraphic::request(r);
//       layout->allocate(1, &r, given, &result);
//       TransformImpl tx;
//       normalTransform(result, &tx);
//       Painter_var p = t->current_painter();
//       p->push_matrix();
//       p->premultiply(&tx);
//       t->traverse_child(offset_, result_);
//       p->pop_matrix();
//     }
//   else MonoGraphic::traverse(t);
}

void Placement::normalOrigin(RegionImpl *r, Vertex &o)
{
  r->origin(o);
  r->lower.x -= o.x; r->upper.x -= o.x;
  r->lower.y -= o.y; r->upper.y -= o.y;
  r->lower.z -= o.z; r->upper.z -= o.z;
}

void Placement::normalTransform(RegionImpl *r, TransformImpl *tx)
{
  Vertex o;
  normalOrigin(r, o);
  tx->translate(o);
}

LayoutLayer::LayoutLayer(Graphic_ptr between, Graphic_ptr under, Graphic_ptr over)
{
  body(between);
  under = Graphic::_duplicate(under);
  over = Graphic::_duplicate(over);
}

LayoutLayer::~LayoutLayer()
{
  CORBA::release(under);
  CORBA::release(over);
}

void LayoutLayer::traverse(Traversal_ptr t)
{
  if (!CORBA::is_nil(under)) under->traverse(t);
  MonoGraphic::traverse(t);
  if (!CORBA::is_nil(over)) over->traverse(t);
}
