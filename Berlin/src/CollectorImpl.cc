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
#include "Berlin/CollectorImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/TransformImpl.hh"

CollectorImpl::CollectorImpl()
{
}
CollectorImpl::~CollectorImpl()
{
  for (vector<State>::iterator i = allocations.begin(); i != allocations.end(); i++)
    {
      (*i).allocation->_dispose();
      (*i).transformation->_dispose();
      CORBA::release((*i).damage);
    }
}

void CollectorImpl::add(Region_ptr region, Damage_ptr damage)
{
  State state;
  state.allocation = new RegionImpl(region, 0);
  state.allocation->_obj_is_ready(_boa());
  state.transformation = new TransformImpl;
  state.transformation->_obj_is_ready(_boa());
  state.damage = Damage::_duplicate(damage);
  allocations.push_back(state);
}

CORBA::Long CollectorImpl::size() { return allocations.size();}

Graphic::AllocationInfo *CollectorImpl::get(CORBA::Long l)
{
    info.allocation = allocations[l].allocation->_this();
    info.transformation = allocations[l].transformation->_this();
    info.damaged = allocations[l].damage;
//     cout << l << ' ' << allocations[l].allocation->lower.x << ' ' << allocations[l].allocation->lower.y
// 	 << ' ' << allocations[l].allocation->upper.x << ' ' << allocations[l].allocation->upper.y << endl;
    return &info;
}
