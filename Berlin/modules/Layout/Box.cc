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

void Box::extension(const Allocation::Info &a, Region_ptr r)
{
  long n = children.size();
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
      child.transformation->copy(a.transformation);
      RegionImpl **result = childrenAllocations(a.allocation);

      for (long i = 0; i < n; i++)
	{
	  Placement::normalOrigin(result[i], o);
	  v.x = o.x - prev_o.x;
	  v.y = o.y - prev_o.y;
	  v.z = o.z - prev_o.z;
	  tmp_tx->loadIdentity();
	  tmp_tx->translate(v);
	  child.allocation = Region::_duplicate(result[i]->_this());
	  child.transformation->premultiply(tmp_tx->_this());
	  cerr << "extending Box by Child" << endl;
	  children[i]->extension(child, r);
	  cerr << "extended Box by Child" << endl;
	  prev_o = o;
	  CORBA::release(child.allocation);
	}
      child_tx->_dispose();
      tmp_tx->_dispose();
      for (long i = 0; i < n; i++) result[i]->_dispose();
      delete [] result;
    }
}

void Box::traverse(Traversal_ptr t)
{
  if (children.size())
    {
      Region_var given = t->allocation();
      if (!CORBA::is_nil(given))
 	{ if (t->intersects()) traverseWithAllocation(t, given);}
      else traverseWithoutAllocation(t);
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

void Box::allocateChild(long index, Allocation::Info &a)
{
  RegionImpl **result = childrenAllocations(a.allocation);
  TransformImpl *tx = new TransformImpl;
  tx->_obj_is_ready(_boa());
  Placement::normalTransform(result[index], tx);
  a.transformation->premultiply(tx->_this());
  a.allocation->copy(result[index]);
  for (size_t i = 0; i < children.size(); i++) result[i]->_dispose();
  delete [] result;
}

RegionImpl **Box::childrenAllocations(Region_ptr a)
{
  long n = children.size();
  Graphic::Requisition *r = childrenRequests();
  if (!requested)
    {
      GraphicImpl::initRequisition(requisition);
      layout->request(n, r, requisition);
      requested = true;
    }
  RegionImpl **result = new RegionImpl *[n];
  for (long i = 0; i < n; i++)
    {
      result[i] = new RegionImpl;
      result[i]->_obj_is_ready(_boa());
      result[i]->valid = true;
    }
  layout->allocate(n, r, a, result);
  pool.deallocate(r);
  return result;
}

void Box::traverseWithAllocation(Traversal_ptr t, Region_ptr a)
{
  RegionImpl **result = childrenAllocations(a);
  long begin, end, incr;
  TransformImpl *tx = new TransformImpl;
  tx->_obj_is_ready(_boa());
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
      tx->loadIdentity();
      /*
       * ok, so we stipulate that Boxes lay out their children 
       * only translating them  -stefan
       */
      tx->translate(o);
      t->traverseChild(children[i], result[i]->_this(), tx->_this());
      if (!t->ok()) break;
    }
  long n = children.size();
  for (long i = 0; i < n; i++) result[i]->_dispose();
  delete [] result;
  tx->_dispose();
}

void Box::traverseWithoutAllocation(Traversal_ptr t)
{
  if (t->direction() == Traversal::up)
    for (clist_t::iterator i = children.begin(); i != children.end(); i++)
      {
	t->traverseChild(*i, Region::_nil(), Transform::_nil());
	if (!t->ok()) break;
      }
  else
    for (clist_t::reverse_iterator i = children.rbegin(); i != children.rend(); i++)
      {
	t->traverseChild(*i, Region::_nil(), Transform::_nil());
	if (!t->ok()) break;
      }    
}

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
