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
#include "Berlin/PolyGraphic.hh"
#include <Prague/Sys/Tracer.hh>
#include <iostream>

using namespace Prague;

Pool<Graphic::Requisition> PolyGraphic::pool;

PolyGraphic::PolyGraphic() {}

PolyGraphic::~PolyGraphic()
{
  for (clist_t::iterator i = children.begin(); i != children.end(); i++)
    (*i).parent->removeParent(Graphic_var(_this()), (*i).id);
}

void PolyGraphic::append(Graphic_ptr child)
{
  childMutex.lock();
  Edge edge;
  edge.parent = Graphic::_duplicate(child);
  edge.id = tag();
  children.push_back(edge);
  if (!CORBA::is_nil(child)) child->addParent(Graphic_var(_this()), edge.id);
  childMutex.unlock();
  needResize();
}

void PolyGraphic::prepend(Graphic_ptr child)
{
  childMutex.lock();
  Edge edge;
  edge.parent = Graphic::_duplicate(child);
  edge.id = tag();
  children.insert(children.begin(), edge);
  if (!CORBA::is_nil(child)) child->addParent(Graphic_var(_this()), edge.id);
  childMutex.unlock();
  needResize();
}

void PolyGraphic::remove(Tag t)
{
  childMutex.lock();
  size_t i = index(t);
  if (i < children.size()) children.erase(children.begin() + i);
  childMutex.unlock();
  needResize();
}

void PolyGraphic::needResize() { GraphicImpl::needResize();}
void PolyGraphic::needResize(Tag) { GraphicImpl::needResize();}

long PolyGraphic::numChildren()
{
  MutexGuard guard(childMutex);
  return children.size();
}

Tag PolyGraphic::tag()
{
  Tag t = 0;
  do
    {
      clist_t::iterator i;
      for (i = children.begin(); i != children.end(); i++)
	if ((*i).id == t) break;
      if (i == children.end()) return t;
    }
  while (++t);
  return 0;
}

CORBA::Long PolyGraphic::index(Tag tag)
{
  size_t i = 0;
  for (; i != children.size(); i++)
    if (children[i].id == tag) break;
  return i;
}

Graphic::Requisition *PolyGraphic::childrenRequests()
{
  Trace trace("PolyGraphic::childrenRequests");
  MutexGuard guard(childMutex);
  Graphic::Requisition *requisitions = pool.allocate(children.size());
  Graphic::Requisition *r = requisitions;
  for (clist_t::iterator i = children.begin(); i != children.end(); i++)
    {
      GraphicImpl::initRequisition(*r);
      if (!CORBA::is_nil((*i).parent)) (*i).parent->request(*r);
      ++r;
    }
  return requisitions;
}

void PolyGraphic::deallocateRequisitions(Graphic::Requisition *r)
{
  MutexGuard guard(childMutex);
  pool.deallocate(r);
}

void PolyGraphic::childExtension(size_t i, const Allocation::Info &info, Region_ptr region)
{
  MutexGuard guard(childMutex);
  Graphic_var child = children[i].parent;
  if (!CORBA::is_nil(child)) child->extension(info, region);
}
