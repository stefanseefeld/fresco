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
#include "Berlin/RegionImpl.hh"
#include "Berlin/Logger.hh"

MonoGraphic::MonoGraphic() {}
MonoGraphic::~MonoGraphic()
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child)) child->removeParent(Graphic_var(_this()));
}

Graphic_ptr MonoGraphic::body()
{
  MutexGuard guard(childMutex);
  return Graphic::_duplicate(child);
}

void MonoGraphic::body(Graphic_ptr c)
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child)) child->removeParent(Graphic_var(_this()));
  child = Graphic::_duplicate(c);
  child->addParent(Graphic_var(_this()));
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
  Graphic_var child = body();
  return CORBA::is_nil(child) ? Transform::_nil() : child->transformation();
}

void MonoGraphic::request(Graphic::Requisition &r)
{
  SectionLog section(Logger::layout, "MonoGraphic::request");
  Graphic_var child = body();
  if (!CORBA::is_nil(child)) child->request(r);
}

void MonoGraphic::extension(const Allocation::Info &info, Region_ptr region)
{
  SectionLog section(Logger::layout, "MonoGraphic::extension");
  Graphic_var child = body();
  if (!CORBA::is_nil(child))
    {
      Allocation::Info i;
      RegionImpl *tmpregion = new RegionImpl;
      tmpregion->_obj_is_ready(_boa());
      i.allocation = tmpregion->_this();
      i.allocation->copy(info.allocation);
      TransformImpl *transform = new TransformImpl;
      transform->_obj_is_ready(_boa());
      i.transformation = transform->_this();
      i.transformation->copy(info.transformation);
      allocateChild(i);
      child->extension(i, region);
      transform->_dispose();
      tmpregion->_dispose();
    }
}

void MonoGraphic::shape(Region_ptr region)
{
  Graphic_var child = body();
  if (!CORBA::is_nil(child)) child->shape(region);
}

void MonoGraphic::traverse(Traversal_ptr traversal)
{
  SectionLog section(Logger::traversal, "MonoGraphic::traverse");
  Graphic_var child = body();
  if (!CORBA::is_nil(child)) traversal->traverseChild(child, Region::_nil(), Transform::_nil());
}

void MonoGraphic::allocate(Graphic_ptr child, Allocation_ptr allocation)
{
  SectionLog section(Logger::layout, "MonoGraphic::allocate");
//   if (!Graphic_var(body())->_is_equivalent(child)) return;
  GraphicImpl::allocate(child, allocation);
  CORBA::Long size = allocation->size();
  for (CORBA::Long i = 0; i != size; i++)
    {
      Allocation::Info_var info = allocation->get(i);
      allocateChild(info);
    }
}

void MonoGraphic::allocateChild(Allocation::Info &) {}
