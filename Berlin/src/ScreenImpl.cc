/*$Id$
 *
 * This source file is a part of the Berlin Project.
 *
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 *
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

#include "Berlin/ScreenImpl.hh"
#include "Berlin/ScreenManager.hh"
#include "Berlin/TransformImpl.hh"

ScreenImpl::ScreenImpl(GLDrawingKit *drawing, Coord w, Coord h)
{
  manager = new ScreenManager(this, drawing);
  region = new RegionImpl;
  region->valid = true;
  region->lower.x = region->lower.y = region->lower.z = 0;
  region->upper.x = w, region->upper.y = h, region->upper.z = 0;
  region->_obj_is_ready(CORBA::BOA::getBOA());
  damage = new DamageImpl(manager);
  damage->_obj_is_ready(CORBA::BOA::getBOA());
  // damage->extend(region->_this());
}

void ScreenImpl::allocations(Collector_ptr collector)
{
  collector->add(region->_this(), damage->_this());
}

void ScreenImpl::allocateChild(long i, Graphic::AllocationInfo &a)
{
  long n = children.size();
  Graphic::Requisition *r = childrenRequests();
  Graphic::Requisition &requisition = r[i];
  RegionImpl *region = new RegionImpl;
  region->valid = true;
  region->lower.x = region->lower.y = 0;
  region->upper.x = requisition.x.natural;
  region->xalign = requisition.x.align;
  region->upper.y = requisition.y.natural;
  region->yalign = requisition.y.align;
  region->_obj_is_ready(_boa());
  a.allocation->copy(region->_this());
  region->_dispose();
  pool.deallocate(r);
}

Coord ScreenImpl::width() { return region->upper.x;}
Coord ScreenImpl::height() { return region->upper.y;}

void ScreenImpl::traverse(Traversal_ptr t) {
    GraphicOffset_var edgeToChild = firstOffset();
    while(!CORBA::is_nil(edgeToChild)) {
	edgeToChild->traverse(t);
	edgeToChild = edgeToChild->next();
    }
}
