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
#include "Berlin/PickTraversalImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Warsaw/Graphic.hh"

PickTraversalImpl::PickTraversalImpl(const Vertex &v, Region_ptr r)
  : TraversalImpl(r), point(v)
{
}

PickTraversalImpl::PickTraversalImpl(const PickTraversalImpl &t)
  : TraversalImpl(t), point(t.point)
{
}

PickTraversalImpl::~PickTraversalImpl()
{
}

CORBA::Boolean PickTraversalImpl::ok()
{
  return true;
}

CORBA::Boolean PickTraversalImpl::intersects()
{
  RegionImpl region(stack.back().allocation, transformation());
  return region.contains(point);
}

void PickTraversalImpl::visit(Graphic_ptr g)
{
  PickTraversal_ptr pt = this->_this();
  g->pick(pt);
}
