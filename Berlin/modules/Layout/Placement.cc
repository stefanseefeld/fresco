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
#include <Berlin/TraversalImpl.hh>
#include <Berlin/Provider.hh>
#include <Berlin/ImplVar.hh>
#include "Placement.hh"
#include "LayoutManager.hh"
#include <sstream>

using namespace Fresco;
using namespace Prague;

using namespace Berlin::LayoutKit;

Placement::Placement(LayoutManager *l) :
    my_layout(l), my_region(new RegionImpl())
{
    std::ostringstream buf;
    buf << "Placement" << my_layout->name() << std::ends;
    my_name = strdup(buf.str().c_str());
}

Placement::~Placement() { delete my_layout; }

void Placement::request(Fresco::Graphic::Requisition &r)
{
    MonoGraphic::request(r);
    my_layout->request(0, 0, r);
}

void Placement::traverse(Traversal_ptr traversal)
{
    Trace trace(this, "Placement::traverse");
    Region_var allocation = traversal->current_allocation();
    if (!CORBA::is_nil(allocation))
    {
    Fresco::Graphic::Requisition r;
    GraphicImpl::init_requisition(r);
    MonoGraphic::request(r);
    Graphic_var child = body();
    if (CORBA::is_nil(child)) return;
    Lease_var<RegionImpl> result(Provider<RegionImpl>::provide());
    result->copy(allocation);
    RegionImpl *tmp = static_cast<RegionImpl *>(result);
    my_layout->allocate(1, &r, allocation, &tmp);
    Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
    tx->load_identity();
    result->normalize(Transform_var(tx->_this()));
    try
    {
        traversal->traverse_child(child, 0,
                      Region_var(result->_this()),
                      Transform_var(tx->_this()));
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { body(Fresco::Graphic::_nil()); }
    catch (const CORBA::COMM_FAILURE &)
    { body(Fresco::Graphic::_nil()); }
    catch (const CORBA::TRANSIENT &)
    { body(Fresco::Graphic::_nil()); }
    }
    else MonoGraphic::traverse(traversal);
}

void Placement::allocate(Tag, const Allocation::Info &a)
{
    Trace trace(this, "Placement::allocate");
    my_region->copy(a.allocation);
    Fresco::Graphic::Requisition r;
    GraphicImpl::init_requisition(r);
    MonoGraphic::request(r);
    RegionImpl *cast = my_region;
    my_layout->allocate(1, &r, a.allocation, &cast);
    Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
    tx->load_identity();
    my_region->normalize(Transform_var(tx->_this()));
    a.transformation->premultiply(Transform_var(tx->_this()));
    a.allocation->copy(Region_var(my_region->_this()));
}

LayoutLayer::LayoutLayer(Graphic_ptr between, Graphic_ptr under,
             Graphic_ptr over) :
    my_under(Fresco::Graphic::_duplicate(under)),
    my_over(Fresco::Graphic::_duplicate(over))
{ body(between); }

LayoutLayer::~LayoutLayer() { }

void LayoutLayer::traverse(Traversal_ptr t)
{
    if (!CORBA::is_nil(my_under))
    try { my_under->traverse(t); }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { my_under = Fresco::Graphic::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { my_under = Fresco::Graphic::_nil(); }
    catch (const CORBA::TRANSIENT &)
    { my_under = Fresco::Graphic::_nil(); }
    MonoGraphic::traverse(t);
    if (!CORBA::is_nil(my_over))
    try { my_over->traverse(t); }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { my_over = Fresco::Graphic::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { my_over = Fresco::Graphic::_nil(); }
    catch (const CORBA::TRANSIENT &)
    { my_over = Fresco::Graphic::_nil(); } 
}
