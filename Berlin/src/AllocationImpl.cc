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
#include "Berlin/Providers.hh"
#include "Berlin/TransformImpl.hh"
#include "Warsaw/Screen.hh"

AllocationImpl::AllocationImpl()
{
}

AllocationImpl::~AllocationImpl()
{
  for (list_t::iterator i = list.begin(); i != list.end(); i++)
    {
      Providers::region.adopt((*i).allocation);
      Providers::trafo.adopt((*i).transformation);
    }
}

void AllocationImpl::add(Region_ptr region, Screen_ptr root)
{
  State state;
  Lease<RegionImpl> reg;
  Providers::region.provide(reg);
  reg->copy(region);
  state.allocation = reg.release();
  Lease<TransformImpl> trafo;
  Providers::trafo.provide(trafo);
  trafo->loadIdentity();
  state.transformation = trafo.release();
  state.root = Screen::_duplicate(root);
  list.push_back(state);
}

CORBA::Long AllocationImpl::size() { return list.size();}

void AllocationImpl::clear() { 
  for (list_t::iterator i = list.begin(); i != list.end(); i++)
    {
      Providers::region.adopt((*i).allocation);
      Providers::trafo.adopt((*i).transformation);
    }  
  list.clear();
}

Allocation::Info *AllocationImpl::get(CORBA::Long l)
{
  Allocation::Info *info = new Allocation::Info;
  info->allocation = list[l].allocation->_this();
  info->transformation = list[l].transformation->_this();
  info->root = list[l].root;
  return info;
}
