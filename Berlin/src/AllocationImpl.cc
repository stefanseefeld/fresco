/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
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
#include <Prague/Sys/Tracer.hh>
#include <Fresco/config.hh>
#include <Fresco/Screen.hh>
#include "Berlin/AllocationImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Provider.hh"
#include "Berlin/TransformImpl.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

AllocationImpl::AllocationImpl() { }

AllocationImpl::~AllocationImpl()
{
    for (list_t::iterator i = my_list.begin(); i != my_list.end(); i++)
    {
    Provider<RegionImpl>::adopt((*i).allocation);
    Provider<TransformImpl>::adopt((*i).transformation);
    }
}

void AllocationImpl::add(Region_ptr region, Screen_ptr root)
{
    Trace trace("Allocation::add");
    Lease_var<RegionImpl> reg(Provider<RegionImpl>::provide());
    reg->copy(region);
    
    Lease_var<TransformImpl> trafo(Provider<TransformImpl>::provide());
    trafo->load_identity();
    
    Screen_ptr scrn = Screen::_duplicate(root);
    try
    {
    my_list.push_back (State());
  
    State &state = my_list.back();
    state.allocation = reg._retn();
    state.transformation = trafo._retn();
    state.root = scrn;
    }
    catch (...)
    {
    CORBA::release(scrn);
    throw;
    }
}

CORBA::Long AllocationImpl::size() { return my_list.size(); }

void AllocationImpl::clear()
{ 
    for (list_t::iterator i = my_list.begin(); i != my_list.end(); i++)
    {
    Provider<RegionImpl>::adopt((*i).allocation);
    Provider<TransformImpl>::adopt((*i).transformation);
    }  
    my_list.clear();
}

Allocation::Info *AllocationImpl::get(CORBA::Long l)
{
    Fresco::Allocation::Info_var info = new Fresco::Allocation::Info;
    info->allocation = my_list[l].allocation->_this();
    info->transformation = my_list[l].transformation->_this();
    info->root = my_list[l].root;
    return info._retn();
}
