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
#include <Prague/Sys/Tracer.hh>
#include "Berlin/PolyGraphic.hh"
#include "Berlin/RefCountVar.hh"
#include <iostream>

using namespace Prague;
using namespace Warsaw;

class PolyGraphicIterator : public virtual POA_Warsaw::GraphicIterator,
			    public virtual PortableServer::RefCountServantBase
{
public:
  PolyGraphicIterator(PolyGraphic *g) : graphic(g) { graphic->increment();}
  virtual ~PolyGraphicIterator() { graphic->decrement();}
  virtual Graphic_ptr child() {}
  virtual void next() {}
  virtual void prev() {}
  virtual void dispose() {}// deactivate(this);}
private:
  PolyGraphic *graphic;
  Tag          cursor;
};

Pool<Warsaw::Graphic::Requisition> PolyGraphic::pool;

PolyGraphic::PolyGraphic() {}

PolyGraphic::~PolyGraphic()
{
  Trace trace("PolyGraphic::~PolyGraphic");
  MutexGuard guard(childMutex);
  for (glist_t::iterator i = children.begin(); i != children.end(); i++)
    {
      try
	{
	  (*i).peer->removeParent((*i).peerId);
	  (*i).peer->decrement();
	}
      catch(CORBA::OBJECT_NOT_EXIST &) {}
    }
}

void PolyGraphic::append(Graphic_ptr child)
{
  Trace trace("PolyGraphic::append");
  childMutex.lock();
  Edge edge;
  edge.peer = RefCount_var<Warsaw::Graphic>::increment(child);
  edge.localId = uniqueChildId();
  edge.peerId = child->addParent(Graphic_var(_this()), edge.localId);
  children.push_back(edge);
  childMutex.unlock();
  needResize();
}

void PolyGraphic::prepend(Graphic_ptr child)
{
  Trace trace("PolyGraphic::prepend");
  childMutex.lock();
  Edge edge;
  edge.peer = RefCount_var<Warsaw::Graphic>::increment(child);
  edge.localId = uniqueChildId();
  edge.peerId = child->addParent(Graphic_var(_this()), edge.localId);
  children.insert(children.begin(), edge);
  childMutex.unlock();
  needResize();
}

void PolyGraphic::remove(Tag localId)
{
  Trace trace("PolyGraphic::remove");
  childMutex.lock();
  glist_t::iterator i = childIdToIterator(localId);
  try
    {
      (*i).peer->removeParent((*i).peerId);
      (*i).peer->decrement();
    }
  catch(CORBA::OBJECT_NOT_EXIST &) {}
  children.erase(i);
  childMutex.unlock();
  needResize();
}

void PolyGraphic::removeChild(Tag localId)
{
  Trace trace("PolyGraphic::removeChild");
  childMutex.lock();
  glist_t::iterator i = childIdToIterator(localId);
  children.erase(i);
  childMutex.unlock();
  needResize();
}

Warsaw::Graphic::Iterator_ptr PolyGraphic::firstChild() { return Iterator::_nil();}
Warsaw::Graphic::Iterator_ptr PolyGraphic::lastChild() { return Iterator::_nil();}

void PolyGraphic::needResize() { GraphicImpl::needResize();}
void PolyGraphic::needResize(Tag) { GraphicImpl::needResize();}

long PolyGraphic::numChildren()
{
  MutexGuard guard(childMutex);
  return children.size();
}

Warsaw::Graphic::Requisition *PolyGraphic::childrenRequests()
{
  Trace trace("PolyGraphic::childrenRequests");
  MutexGuard guard(childMutex);
  Warsaw::Graphic::Requisition *requisitions = pool.allocate(children.size());
  Warsaw::Graphic::Requisition *r = requisitions;
  for (glist_t::iterator i = children.begin(); i != children.end(); i++)
    {
      GraphicImpl::initRequisition(*r);
      if (!CORBA::is_nil((*i).peer))
	try { (*i).peer->request(*r);}
	catch (CORBA::OBJECT_NOT_EXIST &) { (*i).peer = Warsaw::Graphic::_nil();}
      ++r;
    }
  return requisitions;
}

void PolyGraphic::deallocateRequisitions(Warsaw::Graphic::Requisition *r)
{
  MutexGuard guard(childMutex);
  pool.deallocate(r);
}

void PolyGraphic::childExtension(size_t i, const Warsaw::Allocation::Info &info, Region_ptr region)
{
  MutexGuard guard(childMutex);
  Graphic_var child = children[i].peer;
  if (!CORBA::is_nil(child))
    try { child->extension(info, region);}
    catch (CORBA::OBJECT_NOT_EXIST &) { children[i].peer = Warsaw::Graphic::_nil();}
}
