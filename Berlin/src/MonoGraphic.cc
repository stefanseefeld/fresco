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
#include "Berlin/MonoGraphic.hh"
#include "Berlin/TransformImpl.hh"
#include "Warsaw/Traversal.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Providers.hh"
#include <Prague/Sys/Tracer.hh>

using namespace Prague;

MonoGraphic::MonoGraphic() {}
MonoGraphic::~MonoGraphic()
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child)) child->removeParent(Graphic_var(_this()), 0);
}

Graphic_ptr MonoGraphic::body()
{
  MutexGuard guard(childMutex);
  return Graphic::_duplicate(child);
}

void MonoGraphic::body(Graphic_ptr c)
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child)) child->removeParent(Graphic_var(_this()), 0);
  child = Graphic::_duplicate(c);
  if (!CORBA::is_nil(child)) child->addParent(Graphic_var(_this()), 0);
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

void MonoGraphic::remove(Tag t)
{
  MutexGuard guard(childMutex);
  if (!CORBA::is_nil(child)) child->remove(t);
}

Transform_ptr MonoGraphic::transformation()
{
  Graphic_var child = body();
  return CORBA::is_nil(child) ? Transform::_nil() : child->transformation();
}

void MonoGraphic::request(Graphic::Requisition &r)
{
  //  Trace trace("MonoGraphic::request");
  Graphic_var child = body();
  if (!CORBA::is_nil(child)) child->request(r);
}

void MonoGraphic::extension(const Allocation::Info &info, Region_ptr region)
{
  //  Trace trace("MonoGraphic::extension");
  Graphic_var child = body();
  if (!CORBA::is_nil(child))
    {
      Lease<RegionImpl> tmp;
      Providers::region.provide(tmp);
      tmp->clear();
      Lease<TransformImpl> transform;
      Providers::trafo.provide(transform);
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
