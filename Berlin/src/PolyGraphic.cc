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
#include "Berlin/PolyGraphic.hh"

Pool<Graphic::Requisition> PolyGraphic::pool;

PolyGraphic::PolyGraphic() {}

PolyGraphic::~PolyGraphic()
{
  for (PolyGraphicOffsetList::iterator i = children.begin(); i != children.end(); i++)
    {
      if (!CORBA::is_nil((*i)->child))
	{
	  (*i)->child->removeParent(*i);
	  CORBA::release((*i)->child);
	  (*i)->child = 0;
        }
      (*i)->parent = 0;
      CORBA::release(*i);
    }
}

void PolyGraphic::append(Graphic_ptr g)
{
  PolyGraphicOffset *offset = newOffset(children.size(), g);
  children.push_back(offset);
//   modified();
}

void PolyGraphic::prepend(Graphic_ptr g)
{
//   fixup(0, +1);
  PolyGraphicOffset *offset = newOffset(0, g);
  children.insert(children.begin(), offset);
//   modified();
}

GraphicOffset_ptr PolyGraphic::firstOffset()
{
  long n = children.size();
  return n > 0 ? GraphicOffset::_duplicate(children[0]) : 0;
}

GraphicOffset_ptr PolyGraphic::lastOffset()
{
  long n = children.size();
  return n > 0 ? GraphicOffset::_duplicate(children[n-1]) : 0;
}

PolyGraphicOffset *PolyGraphic::newOffset(long index, Graphic_ptr child)
{
  PolyGraphicOffset *offset = new PolyGraphicOffset(this, index, child);
  offset->_obj_is_ready(_boa());
  child->addParent(offset->_this());
  return offset;
}

Graphic::Requisition *PolyGraphic::childrenRequests()
{
  Graphic::Requisition *requisitions = pool.allocate(children.size());
    Graphic::Requisition *r = requisitions;
  for (PolyGraphicOffsetList::iterator i = children.begin(); i != children.end(); i++)
    {
      Graphic_ptr g = (*i)->child;
//       fresco_assert(this != g);
      GraphicImpl::initRequisition(*r);
      if (!CORBA::is_nil(g)) g->request(*r);
      ++r;
    }
  return requisitions;
}

// void PolyGraphic::visit_trail(long, GraphicTraversal_ptr) { }

void PolyGraphic::allocateChild(long, Graphic::AllocationInfo &) { }

void PolyGraphic::needResize() { GraphicImpl::needResize();}
void PolyGraphic::needResize(long) { GraphicImpl::needResize();}

// void PolyGraphic::fixup(long start, long delta)
// {
//   long n = children.size();
//   for (long i = start; i < n; i++)
//     {
//       PolyGraphicOffset *p = children[i];
//       p->index += delta;
//     }
// }

// void PolyGraphic::change(long) { modified(); }

//
// Default behavior when modified is to notify any observers
// of this parent.
//

// void PolyGraphic::modified() { notify_observers();}

PolyGraphicOffset::PolyGraphicOffset(PolyGraphic *p, long index, Graphic_ptr c)
{
  parent = p;
  index  = index;
  child  = Graphic::_duplicate(c);
}

PolyGraphicOffset::~PolyGraphicOffset()
{
  if (!CORBA::is_nil(child))
    {
      child->removeParent(_this());
      CORBA::release(child);
    }
}

Graphic_ptr PolyGraphicOffset::Parent() { return Graphic::_duplicate(parent);}
Graphic_ptr PolyGraphicOffset::Child() { return Graphic::_duplicate(child);}

GraphicOffset_ptr PolyGraphicOffset::offset(long index)
{
  GraphicOffset_ptr g = 0;
  if (index >= 0 && index < static_cast<long>(parent->children.size()))
    g = GraphicOffset::_duplicate(parent->children[index]);
  return g;
}

GraphicOffset_ptr PolyGraphicOffset::next() { return offset(index + 1);}
GraphicOffset_ptr PolyGraphicOffset::previous() { return offset(index - 1);}

void PolyGraphicOffset::allocations(Graphic::AllocationInfoSeq &a)
{
  ulong start = a.length();
  parent->allocations(a);
  for (ulong i = start; i < a.length(); i++)
    parent->allocateChild(index, a[i]);
}

void PolyGraphicOffset::insert(Graphic_ptr g)
{
  PolyGraphicOffset *p = parent->newOffset(index, g);
  parent->children.insert(parent->children.begin() + index, p);
//   parent->fixup(index + 1, +1);
//   parent->modified();
  parent->needResize(index);
}

void PolyGraphicOffset::replace(Graphic_ptr g)
{
  if (index < static_cast<long>(parent->children.size()))
    {
      child->removeParent(_this());
      CORBA::release(child);
      child = Graphic::_duplicate(g);
      child->addParent(_this());
      needResize();
    }
}

void PolyGraphicOffset::remove()
{
  PolyGraphicOffsetList &list = parent->children;
  if (index < static_cast<long>(list.size()))
    {
//       list.remove(index);
//       parent->fixup(index, -1);
//       parent->modified();
      child->removeParent(_this());
      CORBA::release(child);
      child = 0;
      CORBA::release(this);
    }
}

void PolyGraphicOffset::needResize() { parent->needResize(index);}

void PolyGraphicOffset::traverse(Traversal_ptr t) { Child()->traverse(t);}
// void PolyGraphicOffset::visit_trail(Traversal_ptr t) { parent->visit_trail(index, t);}
void PolyGraphicOffset::allocateChild(Graphic::AllocationInfo &a) { parent->allocateChild(index, a);}
