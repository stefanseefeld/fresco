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
#include "Berlin/AllocationImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Provider.hh"
#include "Berlin/TransformImpl.hh"
#include "Berlin/Provider.hh"
#include <Warsaw/Screen.hh>

using namespace Warsaw;

AllocationImpl::AllocationImpl()
{
}

AllocationImpl::~AllocationImpl()
{
  for (list_t::iterator i = list.begin(); i != list.end(); i++)
    {
      Provider<RegionImpl>::adopt((*i).allocation);
      Provider<TransformImpl>::adopt((*i).transformation);
    }
}

void AllocationImpl::add(Region_ptr region, Screen_ptr root)
{
  State state;
  Lease_var<RegionImpl> reg(Provider<RegionImpl>::provide());
  reg->copy(region);
  state.allocation = reg._retn();
  Lease_var<TransformImpl> trafo(Provider<TransformImpl>::provide());
  trafo->loadIdentity();
  state.transformation = trafo._retn();
  state.root = Screen::_duplicate(root);
  list.push_back(state);
}

CORBA::Long AllocationImpl::size() { return list.size();}

void AllocationImpl::clear()
{ 
  for (list_t::iterator i = list.begin(); i != list.end(); i++)
    {
      Provider<RegionImpl>::adopt((*i).allocation);
      Provider<TransformImpl>::adopt((*i).transformation);
    }  
  list.clear();
}

Allocation::Info *AllocationImpl::get(CORBA::Long l)
{
  Warsaw::Allocation::Info_var info = new Warsaw::Allocation::Info;
  info->allocation = list[l].allocation->_this();
  info->transformation = list[l].transformation->_this();
  info->root = list[l].root;
  return info._retn();
}
