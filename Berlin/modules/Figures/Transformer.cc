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

#include <Warsaw/config.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/Traversal.hh>
#include <Warsaw/DrawTraversal.hh>
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/IO.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/Providers.hh>
#include <Berlin/RegionImpl.hh>
#include "Figure/Transformer.hh"
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

Transformer::Transformer()
{
  transform = new TransformImpl;
  transform->_obj_is_ready(_boa());
}

Transformer::~Transformer()
{
  transform->_dispose();
}

Transform_ptr Transformer::transformation()
{
  return transform->_this();
}

void Transformer::request(Requisition &requisition)
{
  Trace trace("Transformer::request");
  Allocator::request(requisition);
//   cout << "request before trafo " << requisition << endl;
  GraphicImpl::transformRequest(requisition, Transform_var(transform->_this()));
//   cout << "request after trafo " << requisition << endl;
}

void Transformer::traverse(Traversal_ptr traversal)
{
  Trace trace("Transformer::traverse");
  Graphic_var child = body();
  if (CORBA::is_nil(child)) return;
  if (!transform->Identity())
    {
      Lease<RegionImpl> rr;
      Providers::region.provide(rr);
      rr->copy(traversal->allocation());
	  
      Requisition r;
      GraphicImpl::initRequisition(r);
	  
      Allocator::request(r);

      Lease<TransformImpl> tx;
      Providers::trafo.provide(tx);
      tx->loadIdentity();
//       cout << "parent region " << rr << endl;
      Vertex delta = GraphicImpl::transformAllocate(*rr, r, Transform_var(transform->_this()));
//       Vertex origin;
//       rr->normalize(origin);
//       tx->translate(origin);
//       cout << "origin " << origin << endl;
//       rr->normalize(Transform_var(tx->_this()));
      tx->copy(Transform_var(transform->_this()));
//       cout << tx->matrix();
//       tx->postmultiply(Transform_var(transform->_this()));
//       cout << "child region " << rr << endl;
//       cout << "delta " << delta << endl;
//       tx->translate(delta);
//       rr->normalize(delta);
//      cout << "transformer matrix\n" << tx->matrix();
//       Impl_var<TransformImpl> cumulative(new TransformImpl(Transform_var(traversal->transformation())));
//      cout << "old accumulated matrix\n" << cumulative->matrix();
//       cumulative->premultiply(Transform_var(tx->_this()));
//      cout << "accumulated matrix\n" << cumulative->matrix();
//      rr->normalize(Transform_var(tx->_this()));
      traversal->traverseChild(child, 0, Region_var(rr->_this()), Transform_var(tx->_this()));
    }
  else Allocator::traverse(traversal);
}

void Transformer::allocate(Tag, const Allocation::Info &info)
{
  Trace trace("Transformer::allocate");
  if (!transform->Identity())
    {
      if (!CORBA::is_nil(info.allocation))
	{
	  Lease<RegionImpl> rr;
	  Providers::region.provide(rr);
	  rr->copy(info.allocation);
	  Requisition r;
	  GraphicImpl::initRequisition(r);
	  Allocator::request(r);
	  Lease<TransformImpl> tx;
	  Providers::trafo.provide(tx);
	  tx->loadIdentity();
	  Vertex delta = GraphicImpl::transformAllocate(*rr, r, Transform_var(transform->_this()));
// 	  rr->normalize(Transform_var(tx->_this()));
 	  tx->copy(Transform_var(transform->_this()));
// 	  tx->postmultiply(Transform_var(transform->_this()));
//   	  tx->translate(delta);
//  	  rr->normalize(delta);
// 	  rr->normalize(Transform_var(tx->_this()));
	  info.transformation->premultiply(tx);
	  info.allocation->copy(rr);
        }
      else
	{
	  info.transformation->premultiply(Transform_var(transform->_this()));
	  Allocator::allocate(0, info);
        }
    }
  else Allocator::allocate(0, info);
}
