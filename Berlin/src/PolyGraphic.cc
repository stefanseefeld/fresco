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
#include <iostream>

Pool<Graphic::Requisition> PolyGraphic::pool;

PolyGraphic::PolyGraphic() {}

PolyGraphic::~PolyGraphic()
{
  Guard guard(childMutex);
  for (clist_t::iterator i = children.begin(); i != children.end(); i++)
    (*i)->removeParent(_this());
}

void PolyGraphic::append(Graphic_ptr child)
{
  Guard guard(childMutex);
  children.push_back(Graphic::_duplicate(child));
  needResize();
}

void PolyGraphic::prepend(Graphic_ptr child)
{
  Guard guard(childMutex);
  children.insert(children.begin(), Graphic::_duplicate(child));
  needResize();
}

void PolyGraphic::allocate(Graphic_ptr g, Allocation_ptr allocation)
{
  long start = allocation->size();
  GraphicImpl::allocate(g, allocation);
  long l = findChild(g);
  for (long i = start; i != allocation->size(); i++)
    allocateChild(l, *allocation->get(i));
}

void PolyGraphic::needResize() { GraphicImpl::needResize();}
void PolyGraphic::needResize(long) { GraphicImpl::needResize();}

long PolyGraphic::numChildren()
{
  Guard guard(childMutex);
  return children.size();
}

/*
 * uses a simple linear search since most containers
 * will want to contain only a few (<5) children.
 * You are free to override it in special purpose containers which expect
 * to get large  -stefan
 */
long PolyGraphic::findChild(Graphic_ptr g)
{
  Guard guard(childMutex);
  Graphic_var tmp = Graphic::_duplicate(g);
  long l = 0;
  for (clist_t::iterator i = children.begin(); i != children.end(); i++, l++)
    if (tmp == *i) break;
  return l;
}

Graphic::Requisition *PolyGraphic::childrenRequests()
{
  Guard guard(childMutex);
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
