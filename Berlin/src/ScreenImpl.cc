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

#include "Berlin/ScreenImpl.hh"
#include "Berlin/ScreenManager.hh"
#include "Berlin/TransformImpl.hh"

ScreenImpl::ScreenImpl(Coord ww, Coord hh)
  : w(ww), h(hh)
{
  manager = new ScreenManager(this);
  damage = new DamageImpl(manager);
  RegionImpl *region = new RegionImpl;
  region->valid = true;
  region->lower.x = region->lower.y = 0;
  region->upper.x = width();
  region->upper.y = height();
  region->_obj_is_ready(_boa());
  damage->extend(region->_this());
  region->_dispose();
}

void ScreenImpl::allocations(AllocationInfoSeq &allocations)
{
  unsigned long i = allocations.length();
  /*
   * insert new AllocationInfo and initialize it appropriately
   */
  AllocationInfo &info = allocations[i];
  info.allocation = new RegionImpl;
  info.transformation = new TransformImpl;
  info.damaged    = Damage::_duplicate(damage);
}

Coord ScreenImpl::width() { return w;}
Coord ScreenImpl::height() { return h;}
