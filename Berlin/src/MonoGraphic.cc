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

MonoGraphic::MonoGraphic() {}
MonoGraphic::~MonoGraphic()
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child)) child->removeParent(_this());
}

Graphic_ptr MonoGraphic::body()
{
  MutexGuard guard(childMutex);
  return Graphic::_duplicate(child);
}

void MonoGraphic::body(Graphic_ptr c)
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child)) child->removeParent(_this());
  child = Graphic::_duplicate(c);
  child->addParent(_this());
}

void MonoGraphic::append(Graphic_ptr c)
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child)) child->append(c);
}

void MonoGraphic::prepend(Graphic_ptr c)
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child)) child->prepend(c);
}

Transform_ptr MonoGraphic::transformation()
{
  Graphic_ptr child = body();
  return CORBA::is_nil(child) ? 0 : child->transformation();
}

void MonoGraphic::request(Graphic::Requisition &r)
{
  Graphic_ptr child = body();
  if (!CORBA::is_nil(child)) child->request(r);
}

void MonoGraphic::extension(const Allocation::Info &a, Region_ptr r)
{
  Graphic_ptr child = body();
  if (!CORBA::is_nil(child))
    {
      Allocation::Info i;
      RegionImpl *region = new RegionImpl;
      region->_obj_is_ready(_boa());
      i.allocation = region->_this();
      i.allocation->copy(a.allocation);
      TransformImpl *transform = new TransformImpl;
      transform->_obj_is_ready(_boa());
      i.transformation = transform;
      i.transformation->copy(a.transformation);
      allocateChild(i);
      child->extension(i, r);
      transform->_dispose();
      region->_dispose();
    }
}

void MonoGraphic::shape(Region_ptr r)
{
  Graphic_ptr child = body();
  if (!CORBA::is_nil(child)) child->shape(r);
}

void MonoGraphic::traverse(Traversal_ptr t)
{
  Graphic_ptr child = body();
  if (!CORBA::is_nil(child)) {
      t->traverseChild(child, Region::_nil(), Transform::_nil());
  }
}

void MonoGraphic::allocate(Graphic_ptr g, Allocation_ptr a)
{
  /*
   * tmp isn't really used here, it's just a test that it refers
   * to the child -stefan
   */
  Graphic_var tmp = Graphic::_duplicate(g);
  if (tmp != body()) return;
  GraphicImpl::allocate(tmp, a);
  CORBA::Long size = a->size();
  for (CORBA::Long i = 0; i != size; i++)
    allocateChild(*a->get(i));
}

void MonoGraphic::allocateChild(Allocation::Info &) {}
