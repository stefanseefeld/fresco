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
#include "Berlin/MonoGraphic.hh"
#include "Berlin/TransformImpl.hh"
#include "Warsaw/Traversal.hh"

MonoGraphic::MonoGraphic() : offset(new MonoGraphicOffset(this)) {}

MonoGraphic::~MonoGraphic()
{
  if (!CORBA::is_nil(offset->child))
    {
      offset->child->removeParent(offset);
      CORBA::release(offset->child);
      offset->child = 0;
    }
  offset->parent = 0;
  CORBA::release(offset);
}

Graphic_ptr MonoGraphic::body() { return Graphic::_duplicate(offset->child);}

void MonoGraphic::body(Graphic_ptr g)
{
  Graphic_ptr child = offset->child;
  if (!CORBA::is_nil(child))
    {
      child->removeParent(offset);
      CORBA::release(child);
    }
  offset->child = Graphic::_duplicate(g);
  g->addParent(offset);
//   offset->remove_tag = !CORBA::is_nil(g) ? g->addParent(offset) : 0;
}

void MonoGraphic::append(Graphic_ptr g)
{
  Graphic_ptr child = offset->child;
  if (!CORBA::is_nil(child)) child->append(g);
}

void MonoGraphic::prepend(Graphic_ptr g)
{
  Graphic_ptr child = offset->child;
  if (!CORBA::is_nil(child)) child->prepend(g);
}

GraphicOffset_ptr MonoGraphic::firstOffset()
{
  Graphic_ptr child = offset->child;
  return CORBA::is_nil(child) ? 0 : child->firstOffset();
}

GraphicOffset_ptr MonoGraphic::lastOffset()
{
  Graphic_ptr child = offset->child;
  return CORBA::is_nil(child) ? 0 : child->lastOffset();
}

Transform_ptr MonoGraphic::transformation()
{
  Graphic_ptr child = offset->child;
  return CORBA::is_nil(child) ? 0 : child->transformation();
}

void MonoGraphic::traverse(Traversal_ptr t)
{
  if (!CORBA::is_nil(offset->child))
    t->traverseChild(offset, t->allocation(), 0);
}

void MonoGraphic::request(Graphic::Requisition &r)
{
  Graphic_ptr child = offset->child;
  if (!CORBA::is_nil(child)) child->request(r);
}

void MonoGraphic::extension(const AllocationInfo &a, Region_ptr r)
{
  Graphic_ptr child = offset->child;
  if (!CORBA::is_nil(child))
    {
      Graphic::AllocationInfo i;
      if (!CORBA::is_nil(a.allocation))
	{
	  i.allocation = new RegionImpl;
	  i.allocation->copy(a.allocation);
	}
      if (!CORBA::is_nil(a.transformation))
	{
	  i.transformation = new TransformImpl;
	  i.transformation->copy(a.transformation);
	}
      allocateChild(i);
      child->extension(i, r);
    }
}

void MonoGraphic::shape(Region_ptr r)
{
  Graphic_ptr child = offset->child;
  if (!CORBA::is_nil(child)) child->shape(r);
}

// void MonoGraphic::visit_trail(Long, GraphicTraversal_ptr) { }
void MonoGraphic::allocateChild(Graphic::AllocationInfo &) { }

// void MonoGraphic::modified() { notify_observers();}

MonoGraphicOffset::MonoGraphicOffset(MonoGraphic *g)
{
  parent = g;
  child  = 0;
}

MonoGraphicOffset::~MonoGraphicOffset()
{
  if (!CORBA::is_nil(child))
    {
      child->removeParent(_this());
      CORBA::release(child);
    }
}

Graphic_ptr MonoGraphicOffset::Parent() { return Graphic::_duplicate(parent);}
Graphic_ptr MonoGraphicOffset::Child() { return Graphic::_duplicate(child);}
GraphicOffset_ptr MonoGraphicOffset::next() { return 0;}
GraphicOffset_ptr MonoGraphicOffset::previous() { return 0;}

void MonoGraphicOffset::allocations(Graphic::AllocationInfoSeq &a)
{
  if (parent)
    {
      ulong start = a.length();
      parent->allocations(a);
      for (ulong i = start; i < a.length(); i++)
	parent->allocateChild(a[i]);
    }
}

void MonoGraphicOffset::insert(Graphic_ptr g) { replace(g);}

void MonoGraphicOffset::replace(Graphic_ptr g)
{
  if (!CORBA::is_nil(child))
    {
      child->removeParent(_this());
      CORBA::release(child);
      child = 0;
    }
  if (!CORBA::is_nil(g))
    {
      child = Graphic::_duplicate(g);
      child->addParent(_this());
    }
}

void MonoGraphicOffset::remove()
{
  if (!CORBA::is_nil(child))
    {
      child->removeParent(_this());
      CORBA::release(child);
      child = 0;
      parent = 0;
    }
}

void MonoGraphicOffset::needResize() { if (parent) parent->needResize();}
void MonoGraphicOffset::traverse(Traversal_ptr t) { if (parent) child->traverse(t);}
// void MonoGraphicOffset::visit_trail(GraphicTraversal_ptr t) { if (parent) parent->visit_trail(t);}
void MonoGraphicOffset::allocateChild(Graphic::AllocationInfo &a) { if (parent) parent->allocateChild(a);}
