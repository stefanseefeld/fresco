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
#include "Berlin/Logger.hh"
#include <iostream>
#include <set>

Pool<Graphic::Requisition> PolyGraphic::pool;

PolyGraphic::PolyGraphic() {}

PolyGraphic::~PolyGraphic()
{
  set<Graphic_var> unique;
  {
    MutexGuard guard(childMutex);
    for (clist_t::iterator i = children.begin(); i != children.end(); i++)
      unique.insert(*i);
  }
  for (set<Graphic_var>::iterator i = unique.begin(); i != unique.end(); i++)
    (*i)->removeParent(Graphic_var(_this()));
}

void PolyGraphic::append(Graphic_ptr child)
{
  MutexGuard guard(childMutex);
  children.push_back(Graphic::_duplicate(child));
  child->addParent(Graphic_var(_this()));
  needResize();
}

void PolyGraphic::prepend(Graphic_ptr child)
{
  MutexGuard guard(childMutex);
  children.insert(children.begin(), Graphic::_duplicate(child));
  child->addParent(Graphic_var(_this()));
  needResize();
}

void PolyGraphic::allocate(Graphic_ptr child, Allocation_ptr allocation)
{
  CORBA::Long begin = allocation->size();
  GraphicImpl::allocate(child, allocation);
  CORBA::Long end = allocation->size();
  long l = findChild(child);
  for (long i = begin; i != end; i++)
    {
      Allocation::Info_var info = allocation->get(i);
      allocateChild(l, info);
    }
}

void PolyGraphic::needResize() { GraphicImpl::needResize();}
void PolyGraphic::needResize(long) { GraphicImpl::needResize();}

long PolyGraphic::numChildren()
{
  MutexGuard guard(childMutex);
  return children.size();
}

/*
 * uses a simple linear search since most containers
 * will want to contain only a few (<5) children.
 * You are free to override it in special purpose containers which expect
 * to get large  -stefan
 */
/*
 * FIXME !!! this is plain wrong. findChild() should return a list of indexes
 * since the child may appear more than once  -stefan
 */
long PolyGraphic::findChild(Graphic_ptr child)
{
  MutexGuard guard(childMutex);
  long l = 0;
  for (clist_t::iterator i = children.begin(); i != children.end(); i++, l++)
    if (child->_is_equivalent(*i)) return l;
  return -1;
}

Graphic::Requisition *PolyGraphic::childrenRequests()
{
  SectionLog section(Logger::layout, "PolyGraphic::childrenRequests");
  MutexGuard guard(childMutex);
  Graphic::Requisition *requisitions = pool.allocate(children.size());
  Graphic::Requisition *r = requisitions;
  for (clist_t::iterator i = children.begin(); i != children.end(); i++)
    {
      GraphicImpl::initRequisition(*r);
      if (!CORBA::is_nil(*i)) (*i)->request(*r);
      ++r;
    }
  return requisitions;
}

void PolyGraphic::allocateChild(long, Allocation::Info &) {}
