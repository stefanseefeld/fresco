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
#include <Fresco/Region.hh>
#include <Fresco/Traversal.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/IO.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/Provider.hh>
#include <Berlin/RegionImpl.hh>
#include "Transformer.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::FigureKit;

Transformer::Transformer() : my_transform(new TransformImpl) { }
Transformer::~Transformer() { }
Transform_ptr Transformer::transformation()
{ return my_transform->_this(); }

void Transformer::request(Fresco::Graphic::Requisition &requisition)
{
  Trace trace("Transformer::request");
  Allocator::request(requisition);
  GraphicImpl::transform_request(requisition,
                 Transform_var(my_transform->_this()));
}

void Transformer::traverse(Traversal_ptr traversal)
{
    Trace trace("Transformer::traverse");
    if (my_transform->identity())
    {
    Allocator::traverse(traversal);
    }
    else
    {
    Fresco::Graphic::Requisition r;
    GraphicImpl::init_requisition(r);
    Allocator::request(r);
    Graphic_var child = body();
    if (CORBA::is_nil(child))    return;
    Lease_var<RegionImpl> rr(Provider<RegionImpl>::provide());
    rr->copy(Region_var(traversal->current_allocation()));
    Vertex delta =
        GraphicImpl::transform_allocate(*rr, r, Transform_var(my_transform->_this()));
    Lease_var<TransformImpl> tx(Provider<TransformImpl>::provide());
    tx->copy(Transform_var(my_transform->_this()));
    try
    {
        traversal->traverse_child (child, 0,
                       Region_var(rr->_this()),
                       Transform_var(tx->_this()));}
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { body(Fresco::Graphic::_nil()); }
    catch (const CORBA::COMM_FAILURE &)
    { body(Fresco::Graphic::_nil()); }
    }
}

void Transformer::allocate(Tag, const Allocation::Info &info)
{
    Trace trace("Transformer::allocate");
    if (!my_transform->identity())
    {
    if (!CORBA::is_nil(info.allocation))
    {
        Lease_var<RegionImpl> rr(Provider<RegionImpl>::provide());
        rr->copy(info.allocation);
        Fresco::Graphic::Requisition r;
        GraphicImpl::init_requisition(r);
        Allocator::request(r);
        Lease_var<TransformImpl>
        tx(Provider<TransformImpl>::provide());
        tx->load_identity();
        Vertex delta =
        GraphicImpl::transform_allocate(*rr, r, Transform_var(my_transform->_this()));
        tx->copy(Transform_var(my_transform->_this()));
        info.transformation->premultiply(Transform_var(tx->_this()));
        info.allocation->copy(Region_var(rr->_this()));
        }
    else
    {
        info.transformation->
        premultiply(Transform_var(my_transform->_this()));
        Allocator::allocate(0, info);
        }
    }
    else Allocator::allocate(0, info);
}
