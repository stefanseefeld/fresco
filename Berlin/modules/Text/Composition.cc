/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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
#include "Text/Composition.hh"
#include "Text/Compositor.hh"
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/Traversal.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/ImplVar.hh>
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/Tracer.hh>
#include <algorithm>

using namespace Prague;

Composition::Composition(DrawingKit_ptr dk, Compositor *c)
  : canonicalDK(DrawingKit::_duplicate(dk)),
    compositor(c),
    requested(false)
{
  Trace trace("Composition::Composition");
}

Composition::~Composition() {}

void Composition::request(Requisition &r)
{
  Trace trace("Composition::request");
  if (!requested)
    {
      GraphicImpl::defaultRequisition(requisition);
      GraphicImpl::initRequisition(requisition);
      long n = numChildren();
      if (n > 0)
	{
	  Graphic::Requisition *r = childrenRequests();
	  compositor->request(n, r, canonicalDK, requisition);
	  deallocateRequisitions(r);
	}
      requested = true;
    }
  r = requisition;
}

void Composition::extension(const Allocation::Info &info, Region_ptr region)
{
  Trace trace("Composition::extension");  
  long n = numChildren();
  if (n > 0)
    {
      Allocation::Info child;
      Vertex origin, previous, delta;
      previous.x = previous.y = previous.z = 0;
      
      Impl_var<TransformImpl> child_tx(new TransformImpl);
      Impl_var<TransformImpl> tmp_tx(new TransformImpl);
      
      child.transformation = child_tx->_this();
      child.transformation->copy(info.transformation);
      RegionImpl **result = childrenAllocations(info.allocation);

      for (long i = 0; i < n; i++)
	{
	  result[i]->normalize(origin);
	  delta = origin - previous;
	  // 	  tmp_tx->loadIdentity();
	  tmp_tx->translate(delta);
	  child.allocation = result[i]->_this();
	  child.transformation->premultiply(Transform_var(tmp_tx->_this()));
	  childExtension(i, child, region);
	  previous = origin;
	}
      for (long i = 0; i < n; i++) result[i]->_dispose();
      delete [] result;
    }
}

void Composition::traverse(Traversal_ptr traversal)
{
  Trace trace("Composition::traverse");
  if (numChildren())
    {
      Region_var given = traversal->allocation();
      /*
       * this cull test is not accurate, it assumes that the children
       * don't draw outside the box' allocation.
       * the alternative - using extension - is expensive...
       *              -stefan
       */
      if (!traversal->intersectsAllocation()) return;
      RegionImpl **result = childrenAllocations(given);
      CORBA::Long size = numChildren();
      CORBA::Long begin, end, incr;
      Impl_var<TransformImpl> tx(new TransformImpl);
      if (traversal->direction() == Traversal::up)
	{
	  begin = 0;
	  end = size;
	  incr = 1;
	}
      else
	{
	  begin = size - 1;
	  end = -1;
	  incr = -1;
	}
      for (CORBA::Long i = begin; i != end; i += incr)
	{
	  if (CORBA::is_nil(children[i].first)) continue;
	  Vertex origin;
	  result[i]->normalize(origin);
	  tx->loadIdentity();
	  /*
	   * ok, so we stipulate that Boxes lay out their children 
	   * only translating them -stefan
	   */
	  tx->translate(origin);
	  traversal->traverseChild(children[i].first, children[i].second, Region_var(result[i]->_this()), Transform_var(tx->_this()));
	  if (!traversal->ok()) break;
	}
      for (long i = 0; i < size; i++) result[i]->_dispose();
      delete [] result;
    }
}

void Composition::needResize()
{
  requested = false;
  PolyGraphic::needResize();
}

void Composition::needResize(Tag)
{
  needResize();
}

void Composition::allocate(Tag tag, const Allocation::Info &info)
{
  Trace trace("Composition::allocate");
  RegionImpl **result = childrenAllocations(info.allocation);
  Impl_var<TransformImpl> tx(new TransformImpl);
  CORBA::Long idx = index(tag);
  result[idx]->normalize(Transform_var(tx->_this()));
  info.transformation->premultiply(Transform_var(tx->_this()));
  info.allocation->copy(Region_var(result[idx]->_this()));
  CORBA::Long children = numChildren();
  for (CORBA::Long i = 0; i < children; i++) result[i]->_dispose();
  delete [] result;
}

RegionImpl **Composition::childrenAllocations(Region_ptr allocation)
{
  Trace trace("Composition::childrenAllocations");
  CORBA::Long children = numChildren();
  Graphic::Requisition *childrenRequisitions = childrenRequests(); // first defined  in PolyGraphic.cc
    
  // cache integrated form of children requisitions
  if (!requested)
    {
      GraphicImpl::initRequisition(requisition);
      compositor->request(children, childrenRequisitions, canonicalDK, requisition);
      requested = true;
    }
  // build region array for children
  RegionImpl **childrenRegions = new RegionImpl *[children];
  for (CORBA::Long i = 0; i < children; i++)
    {
      childrenRegions[i] = new RegionImpl;
      childrenRegions[i]->_obj_is_ready(_boa());
      childrenRegions[i]->valid = true;
    }
  // fill in children regions which are reasonable matches for the given requesitions
  compositor->allocate(children, childrenRequisitions, canonicalDK, allocation, childrenRegions);
  deallocateRequisitions(childrenRequisitions);
  return childrenRegions;
}
