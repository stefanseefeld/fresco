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
#include "Berlin/MonoGraphic.hh"
#include "Berlin/TransformImpl.hh"
#include "Warsaw/Traversal.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Provider.hh"
#include "Berlin/RefCountVar.hh"

using namespace Prague;
using namespace Warsaw;

MonoGraphic::MonoGraphic() {}
MonoGraphic::~MonoGraphic()
{
  Trace trace("MonoGraphic::~MonoGraphic");
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child.peer))
    {
      try
	{
	  child.peer->decrement();
	  child.peer->removeParent(child.peerId);
	}
      catch(CORBA::OBJECT_NOT_EXIST &) {}
    }
}

Graphic_ptr MonoGraphic::body()
{
  Trace trace("MonoGraphic::body");
  MutexGuard guard(childMutex);
  return RefCount_var<Warsaw::Graphic>::increment(child.peer);
}

void MonoGraphic::body(Graphic_ptr c)
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child.peer))
    {
      try
	{
	  child.peer->removeParent(child.peerId);
	  child.peer->decrement();
	}
      catch(CORBA::OBJECT_NOT_EXIST &) {}
    }
  child.peer = Warsaw::Graphic::_duplicate(c);
  if (!CORBA::is_nil(child.peer))
    {
      try
	{
	  child.peerId = child.peer->addParent(Graphic_var(_this()), 0);
	  child.peer->increment();
	}
      catch(CORBA::OBJECT_NOT_EXIST &) { child.peer = Warsaw::Graphic::_nil();}
    }
//   needResize();
}

void MonoGraphic::append(Graphic_ptr c)
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child.peer))
    try { child.peer->append(c);}
    catch (CORBA::OBJECT_NOT_EXIST &) { child.peer = Warsaw::Graphic::_nil();}
}

void MonoGraphic::prepend(Graphic_ptr c)
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child.peer))
    try { child.peer->prepend(c);}
    catch (CORBA::OBJECT_NOT_EXIST &) { child.peer = Warsaw::Graphic::_nil();}
}

void MonoGraphic::remove(Tag localId)
{
  Trace trace("MonoGraphic::remove");
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child.peer))
    try { child.peer->remove(localId);}
    catch (CORBA::OBJECT_NOT_EXIST &) { child.peer = Warsaw::Graphic::_nil();}
}

void MonoGraphic::removeChild(Tag localId)
{
  Trace trace("MonoGraphic::removeChild");
  {
    MutexGuard guard(childMutex);
    if (localId == 0) child.peer = Warsaw::Graphic::_nil();
  }
  needResize();
}

Warsaw::Graphic::Iterator_ptr MonoGraphic::firstChild()
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child.peer)) return child.peer->firstChild();
}

Warsaw::Graphic::Iterator_ptr MonoGraphic::lastChild()
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child.peer)) return child.peer->lastChild();
}

Transform_ptr MonoGraphic::transformation()
{
  Graphic_var child = body();
  return CORBA::is_nil(child) ? Transform::_nil() : child->transformation();
}

void MonoGraphic::request(Warsaw::Graphic::Requisition &r)
{
  Trace trace("MonoGraphic::request");
  Graphic_var child = body();
  if (!CORBA::is_nil(child)) child->request(r);
}

void MonoGraphic::extension(const Warsaw::Allocation::Info &info, Region_ptr region)
{
  Trace trace("MonoGraphic::extension");
  Graphic_var child = body();
  if (!CORBA::is_nil(child))
    {
      Lease_var<RegionImpl> tmp(Provider<RegionImpl>::provide());
      tmp->clear();
      Lease_var<TransformImpl> transform(Provider<TransformImpl>::provide());
      transform->loadIdentity();
      Allocation::Info i;
      i.allocation = tmp->_this();
      i.allocation->copy(info.allocation);
      i.transformation = transform->_this();
      i.transformation->copy(info.transformation);
      allocate(0, i);
      child->extension(i, region);
    }
}

void MonoGraphic::shape(Region_ptr region)
{
  Graphic_var child = body();
  if (!CORBA::is_nil(child)) child->shape(region);
}

void MonoGraphic::traverse(Traversal_ptr traversal)
{
  Trace trace("MonoGraphic::traverse");
  Graphic_var child = body();
  if (!CORBA::is_nil(child))
    traversal->traverseChild(child, 0, Region_var(Region::_nil()), Transform_var(Transform::_nil()));
}
