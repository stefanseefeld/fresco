/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
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
#include "Fresco/Traversal.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Provider.hh"
#include "Berlin/RefCountVar.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

MonoGraphic::MonoGraphic()
{
  my_child.peer = Fresco::Graphic::_nil();
}

MonoGraphic::~MonoGraphic()
{
  Trace trace(this, "MonoGraphic::~MonoGraphic");
  Prague::Guard<Mutex> guard(my_mutex);
  if (!CORBA::is_nil(my_child.peer))
      try
      {
      my_child.peer->decrement();
      my_child.peer->remove_parent_graphic(my_child.peerId);
      }
      catch(const CORBA::OBJECT_NOT_EXIST &) { }
      catch (const CORBA::COMM_FAILURE &) { }
      catch (const CORBA::TRANSIENT &) { }
}

Graphic_ptr MonoGraphic::body()
{
    Trace trace(this, "MonoGraphic::body");
    Prague::Guard<Mutex> guard(my_mutex);
    return Fresco::Graphic::_duplicate(my_child.peer);
}

void MonoGraphic::body(Graphic_ptr c)
{
    Prague::Guard<Mutex> guard(my_mutex);
    if (!CORBA::is_nil(my_child.peer))
    try
    {
        my_child.peer->remove_parent_graphic(my_child.peerId);
        my_child.peer->decrement();
    }
    catch(const CORBA::OBJECT_NOT_EXIST &) { }
    catch (const CORBA::COMM_FAILURE &) { }
    catch (const CORBA::TRANSIENT &) { }
    my_child.peer = Fresco::Graphic::_duplicate(c);
    if (!CORBA::is_nil(my_child.peer))
    try
    {
        my_child.peerId =
        my_child.peer->add_parent_graphic(Graphic_var(_this()), 0);
        my_child.peer->increment();
    }
    catch(const CORBA::OBJECT_NOT_EXIST &)
    { my_child.peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { my_child.peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::TRANSIENT &)
    { my_child.peer = Fresco::Graphic::_nil(); }
//     needResize();
}

void MonoGraphic::append_graphic(Graphic_ptr c)
{
    Prague::Guard<Mutex> guard(my_mutex);
    if (!CORBA::is_nil(my_child.peer))
    try
    { my_child.peer->append_graphic(c);}
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { my_child.peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { my_child.peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::TRANSIENT &)
    { my_child.peer = Fresco::Graphic::_nil(); }
}

void MonoGraphic::prepend_graphic(Graphic_ptr c)
{
    Prague::Guard<Mutex> guard(my_mutex);
    if (!CORBA::is_nil(my_child.peer))
    try
    { my_child.peer->prepend_graphic(c);}
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { my_child.peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { my_child.peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::TRANSIENT &)
    { my_child.peer = Fresco::Graphic::_nil(); }
}

void MonoGraphic::remove_graphic(Tag localId)
{
    Trace trace(this, "MonoGraphic::remove_graphic");
    Prague::Guard<Mutex> guard(my_mutex);
    if (!CORBA::is_nil(my_child.peer))
    try { my_child.peer->remove_graphic(localId);}
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { my_child.peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::COMM_FAILURE &)
    { my_child.peer = Fresco::Graphic::_nil(); }
    catch (const CORBA::TRANSIENT &)
    { my_child.peer = Fresco::Graphic::_nil(); }
}

void MonoGraphic::remove_child_graphic(Tag localId)
{
    Trace trace(this, "MonoGraphic::remove_child_graphic");
    {
    Prague::Guard<Mutex> guard(my_mutex);
    if (localId == 0) my_child.peer = Fresco::Graphic::_nil();
    }
    need_resize();
}

Fresco::GraphicIterator_ptr MonoGraphic::first_child_graphic()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return (CORBA::is_nil (my_child.peer)
        ? Fresco::GraphicIterator::_nil()
        : my_child.peer->first_child_graphic());
}

Fresco::GraphicIterator_ptr MonoGraphic::last_child_graphic()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return (CORBA::is_nil (my_child.peer)
        ? Fresco::GraphicIterator::_nil()
        : my_child.peer->last_child_graphic());
}

Transform_ptr MonoGraphic::transformation()
{
    Graphic_var child = body();
    return CORBA::is_nil(child) ? Transform::_nil() : child->transformation();
}

void MonoGraphic::request(Fresco::Graphic::Requisition &r)
{
    Trace trace(this, "MonoGraphic::request");
    Graphic_var child = body();
    if (CORBA::is_nil(child)) return;
    try { child->request(r); }
    catch (const CORBA::OBJECT_NOT_EXIST &) { body(Fresco::Graphic::_nil()); }
    catch (const CORBA::COMM_FAILURE &) { body(Fresco::Graphic::_nil()); }
    catch (const CORBA::TRANSIENT &) { body(Fresco::Graphic::_nil()); }
}

void MonoGraphic::extension(const Fresco::Allocation::Info &info,
                Region_ptr region)
{
    Trace trace(this, "MonoGraphic::extension");
    Graphic_var child = body();
    if (!CORBA::is_nil(child))
    {
    Lease_var<RegionImpl> tmp(Provider<RegionImpl>::provide());
    tmp->clear();
    Lease_var<TransformImpl>
        transform(Provider<TransformImpl>::provide());
    transform->load_identity();
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
    Trace trace(this, "MonoGraphic::traverse");
    Graphic_var child = body();
    if (CORBA::is_nil(child)) return;
    try
    {
    traversal->traverse_child(child, 0,
                  Region::_nil(), Transform::_nil());
    }
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { body (Fresco::Graphic::_nil()); }
    catch (const CORBA::COMM_FAILURE &)
    { body(Fresco::Graphic::_nil()); }
    catch (const CORBA::TRANSIENT &)
    { body(Fresco::Graphic::_nil()); }
}

