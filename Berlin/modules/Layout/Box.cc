/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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
#include "Layout/Box.hh"
#include "Layout/LayoutManager.hh"
#include "Layout/Placement.hh"
#include "Berlin/TransformImpl.hh"
#include "Warsaw/Traversal.hh"
#include <iostream>

Box::Box(LayoutManager *l)
{
  layout = l;
  requested = false;
}

Box::~Box() { delete layout;}

void Box::request(Requisition &r)
{
  if (!requested)
    {
      GraphicImpl::defaultRequisition(requisition);
      GraphicImpl::initRequisition(requisition);
      long n = numChildren();
      if (n > 0)
	{
	  Graphic::Requisition *r = childrenRequests();
	  layout->request(n, r, requisition);
	  pool.deallocate(r);
	}
      requested = true;
    }
  r = requisition;
}

void Box::extension(const Allocation::Info &info, Region_ptr r)
{
  Region_var region = r;
  long n = numChildren();
  if (n > 0)
    {
      Allocation::Info child;
      Vertex prev_o, o, v;
      prev_o.x = prev_o.y = prev_o.z = 0;

      TransformImpl *child_tx = new TransformImpl;
      child_tx->_obj_is_ready(_boa());

      TransformImpl *tmp_tx = new TransformImpl;
      tmp_tx->_obj_is_ready(_boa());
      
      child.transformation = child_tx->_this();
      child.transformation->copy(Transform::_duplicate(info.transformation));
      RegionImpl **result = childrenAllocations(info.allocation);

      for (long i = 0; i < n; i++)
	{
	  Placement::normalOrigin(result[i], o);
	  v.x = o.x - prev_o.x;
	  v.y = o.y - prev_o.y;
	  v.z = o.z - prev_o.z;
	  tmp_tx->loadIdentity();
	  tmp_tx->translate(v);
	  child.allocation = result[i]->_this();
	  child.transformation->premultiply(tmp_tx->_this());
	  children[i]->extension(child, region);
	  prev_o = o;
	}
      child_tx->_dispose();
      tmp_tx->_dispose();
      for (long i = 0; i < n; i++) result[i]->_dispose();
      delete [] result;
    }
}

void Box::traverse(Traversal_ptr t)
{
  Traversal_var traversal = t;
  if (numChildren())
    {
      Region_var given = traversal->allocation();
      if (!CORBA::is_nil(given))
 	{
	  if (traversal->intersects())
	    traverseWithAllocation(traversal, given);
	}
      else traverseWithoutAllocation(traversal);
    }
}

void Box::needResize()
{
  requested = false;
  PolyGraphic::needResize();
}

void Box::needResize(long)
{
  needResize();
}


/** this is a method called (but left empty in the superclass) in
    PolyGraphic::allocate. it is called after a particular child has been
    located in the child list. It is supposed to "finish off" providing the
    allocation info for the given child */

void Box::allocateChild(long childNum, Allocation::Info &a)
{
  // fetch requested (presumably allocated) child regions
  RegionImpl **childRegions = childrenAllocations(a.allocation);

  // make new transformation
  TransformImpl *txForThisChild = new TransformImpl;
  txForThisChild->_obj_is_ready(_boa());

  // copy transformation and region into allocation
  Placement::normalTransform(childRegions[childNum], txForThisChild);
  a.transformation->premultiply(txForThisChild->_this());
  a.allocation->copy(childRegions[childNum]);

  // clean up
  for (size_t i = 0; i < children.size(); i++) childRegions[i]->_dispose();
  delete [] childRegions;
}


/** this is called from Box::allocateChild to resolve the layout of the box's
   children by (a) asking the children how big they want to be, then (b)
   delegating the actual allocation to the current layoutManager. It also caches
   the children's requests so that the real layout (at draw time) will happen
   faster. */

RegionImpl **Box::childrenAllocations(Region_ptr a) {
    long numChildren = children.size();
    Graphic::Requisition *whatChildrenWant = childrenRequests(); // first defined  in PolyGraphic.cc
    
    // cache integrated form of children requisitions
    if (!requested) {
	GraphicImpl::initRequisition(requisition);
	layout->request(numChildren, whatChildrenWant, requisition);
	requested = true;
    }
    
    // build region array for children
    RegionImpl **regionsForChildren = new RegionImpl *[numChildren];
    for (long i = 0; i < numChildren; i++) {	
	regionsForChildren[i] = new RegionImpl;
	regionsForChildren[i]->_obj_is_ready(_boa());
	regionsForChildren[i]->valid = true;
    }
    
    // fill in numChildren regions which are reasonable matches for the given requesitions
    layout->allocate(numChildren, whatChildrenWant, a, regionsForChildren);
    pool.deallocate(whatChildrenWant);
    return regionsForChildren;
}



void Box::traverseWithAllocation(Traversal_ptr t, Region_ptr r)
{
  RegionImpl **result = childrenAllocations(r);
  long size = numChildren();
  long begin, end, incr;
  TransformImpl *tx = new TransformImpl;
  tx->_obj_is_ready(_boa());
  if (t->direction() == Traversal::up)
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
  for (long i = begin; i != end; i += incr)
    {
      Vertex o;
      Placement::normalOrigin(result[i], o);
      tx->loadIdentity();
      /*
       * ok, so we stipulate that Boxes lay out their children 
       * only translating them -stefan */
      tx->translate(o);
      t->traverseChild(Graphic::_duplicate(children[i]), result[i]->_this(), tx->_this());
      if (!t->ok()) break;
    }
  for (long i = 0; i < size; i++) result[i]->_dispose();
  delete [] result;
  tx->_dispose();
}

void Box::traverseWithoutAllocation(Traversal_ptr t)
{
  if (t->direction() == Traversal::up)
    for (clist_t::iterator i = children.begin(); i != children.end(); i++)
      {
	t->traverseChild(Graphic::_duplicate(*i), Region::_nil(), Transform::_nil());
	if (!t->ok()) break;
      }
  else
    for (clist_t::reverse_iterator i = children.rbegin(); i != children.rend(); i++)
      {
	t->traverseChild(Graphic::_duplicate(*i), Region::_nil(), Transform::_nil());
	if (!t->ok()) break;
      }    
}

BoxAlignElements::BoxAlignElements(LayoutManager *layout, Axis a, Alignment align)
  : Box(layout), axis(a), alignment(align) {}
BoxAlignElements::~BoxAlignElements() {}

void BoxAlignElements::append(Graphic_ptr g)
{
  Placement *placement = new Placement(new LayoutCenter(axis, alignment));
  placement->_obj_is_ready(_boa());
  placement->body(g);
  Box::append(placement->_this());
}

void BoxAlignElements::prepend(Graphic_ptr g)
{
  Placement *placement = new Placement(new LayoutCenter(axis, alignment));
  placement->_obj_is_ready(_boa());
  placement->body(g);
  Box::prepend(placement->_this());
}
