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
#include "Warsaw/Traversal.hh"
#include "Berlin/TransformImpl.hh"
#include "Layout/Box.hh"
#include "Layout/LayoutManager.hh"
#include "Layout/Placement.hh"

const int Box::static_size = 10;

Box::Box(LayoutManager *l)
{
  layout = l;
  requested = false;
}

Box::~Box() { delete layout;}

Graphic_ptr Box::cloneGraphic()
{
  Box *box = new Box(layout->clone());
  box->_obj_is_ready(_boa());
  return box->_this();
//   return new Box(layout->clone());
}

void Box::request(Requisition &r)
{
  if (!requested)
    {
      GraphicImpl::defaultRequisition(requisition);
      GraphicImpl::initRequisition(requisition);
      long n = children.size();
      if (n > 0)
	{
	  Graphic::Requisition req[static_size];
	  Graphic::Requisition *r = childrenRequests(req, static_size);
	  layout->request(n, r, requisition);
	  if (r != req) delete [] r;
	}
      requested = true;
    }
  r = requisition;
}

void Box::extension(const AllocationInfo &a, Region_ptr r)
{
  long n = children.size();
  if (n > 0)
    {
      Graphic::AllocationInfo child;
      Vertex prev_o, o, v;
      prev_o.x = Coord(0); prev_o.y = Coord(0); prev_o.z = Coord(0);
      TransformImpl child_tx, tmp_tx;
      child.transformation._ptr = &child_tx;
      child.transformation->copy(a.transformation);
//       child.damaged = a.damaged;
      RegionImpl **result = childrenAllocations(a.allocation);
      for (long i = 0; i < n; i++)
	{
	  Placement::normalOrigin(result[i], o);
	  v.x = o.x - prev_o.x;
	  v.y = o.y - prev_o.y;
	  v.z = o.z - prev_o.z;
	  tmp_tx.loadIdentity();
	  tmp_tx.translate(v);
	  child.allocation._ptr = result[i];
	  child.transformation->premultiply(&tmp_tx);
	  children[i]->child->extension(child, r);
	  prev_o = o;
	}
      child.transformation._ptr = 0;
      child.allocation._ptr = 0;
//       child.damaged = 0;

//       CORBA::ULong n = CORBA::ULong(children_.count());
      for (long i = 0; i < n; i++) CORBA::release(result[i]);
      delete [] result;
    }
}

//
// The cull test below (allocation_is_visible) is not quite ideal.
// If the box contains something that draws outside the box's allocation,
// then the box might not redraw correctly.  However, the alternative,
// using extensions, can be pretty expensive.  In practice, using
// allocations works in every case we have seen.
//

void Box::traverse(Traversal_ptr t)
{
  if (children.size())
    {
      Region_var given = t->allocation();
      if (!CORBA::is_nil(given))
 	{
  	  if (t->intersects()) traverseWithAllocation(t, given);
 	}
      else traverseWithoutAllocation(t);
    }
}

//
// Both traverse and allocateChild could be made more efficient
// by avoiding memory allocation using a fixed size array of regions
// when the number of children is below a reasonable amount.
//

RegionImpl **Box::childrenAllocations(Region_ptr a)
{
  long n = children.size();
  Graphic::Requisition req[static_size];
  Graphic::Requisition *r = childrenRequests(req, static_size);
  if (!requested)
    {
      GraphicImpl::initRequisition(requisition);
      layout->request(n, r, requisition);
      requested = true;
    }
  RegionImpl **result = new RegionImpl *[n];
  for (long i = 0; i < n; i++)
    {
      RegionImpl *region = new RegionImpl;
      region->valid = true;
      result[i] = region;
    }
  layout->allocate(n, r, a, result);
  if (r != req) delete [] r;
  return result;
}

void Box::traverseWithAllocation(Traversal_ptr t, Region_ptr a)
{
  RegionImpl **result = childrenAllocations(a);
  long begin, end, incr;
  TransformImpl tx;
  tx._obj_is_ready(_boa());
  if (t->direction() == Traversal::up)
    {
      begin = 0;
      end = children.size();
      incr = 1;
    }
  else
    {
      begin = children.size() - 1;
      end = -1;
      incr = -1;
    }
  for (long i = begin; i != end; i += incr)
    {
      Vertex o;
      Placement::normalOrigin(result[i], o);
      result[i]->_obj_is_ready(_boa());
      tx.loadIdentity();
      tx.translate(o);
      t->traverseChild(children[i]->_this(), result[i]->_this(), tx._this());
      if (!t->ok()) break;
    }
  long n = children.size();
  for (long i = 0; i < n; i++) CORBA::release(result[i]);
  delete [] result;
}

void Box::traverseWithoutAllocation(Traversal_ptr t)
{
  if (t->direction() == Traversal::up)
    for (PolyGraphicOffsetList::iterator i = children.begin(); i != children.end(); i++)
      {
	t->traverseChild((*i)->_this(), 0, 0);
	if (!t->ok()) break;
      }
  else
    for (PolyGraphicOffsetList::reverse_iterator i = children.rbegin(); i != children.rend(); i++)
      {
	t->traverseChild((*i)->_this(), 0, 0);
	if (!t->ok()) break;
      }    
}

void Box::allocateChild(long index, Graphic::AllocationInfo &a)
{
  Region_ptr given = a.allocation;
  RegionImpl **result = childrenAllocations(given);
  TransformImpl tx;
  Placement::normalTransform(result[index], &tx);
  if (CORBA::is_nil(a.transformation))
    {
      TransformImpl *transform = new TransformImpl;
      transform->_obj_is_ready(_boa());
      a.transformation = transform->_this();
//       a.transformation = new TransformImpl;
    }
  a.transformation->premultiply(&tx);
  given->copy(result[index]);
  long n = children.size();
  for (long i = 0; i < n; i++) CORBA::release(result[i]);
  delete [] result;
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

void Box::modified() { requested = false;}

// class BoxAlignElements
 
BoxAlignElements::BoxAlignElements(LayoutManager *layout, Axis a, Alignment align)
  : Box(layout), axis(a), alignment(align) {}
BoxAlignElements::~BoxAlignElements() {}

void BoxAlignElements::append(Graphic_ptr g)
{
  Placement *placement = new Placement(g, new LayoutCenter(axis, alignment));
  placement->_obj_is_ready(_boa());
  Box::append(Graphic_var(placement->_this()));
}

void BoxAlignElements::prepend(Graphic_ptr g)
{
  Placement *placement = new Placement(g, new LayoutCenter(axis, alignment));
  placement->_obj_is_ready(_boa());
  Box::prepend(Graphic_var(placement->_this()));
}
