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
#include "Warsaw/Graphic.hh"
#include "Warsaw/Drawable.hh"
#include "Warsaw/DrawingKit.hh"
#include "Warsaw/Region.hh"

DrawTraversalImpl::DrawTraversalImpl(DrawingKit_ptr kit, Region_ptr r)
  : TraversalImpl(r), drawingkit(kit), drawable(drawingkit->getDrawable()), clipping(r) {}
DrawTraversalImpl::DrawTraversalImpl(const DrawTraversalImpl &t)
  : TraversalImpl(t), drawingkit(t.drawingkit), drawable(t.drawable), clipping(drawable->clipping()) {}
DrawTraversalImpl::~DrawTraversalImpl() {}

CORBA::Boolean DrawTraversalImpl::intersects()
{
  return clipping->intersects(allocation());
}

void DrawTraversalImpl::visit(Graphic_ptr g)
{
  g->draw(_this());
  CORBA::release(g);
}

DrawingKit_ptr DrawTraversalImpl::kit()
{
  return DrawingKit::_duplicate(drawingkit);
}
