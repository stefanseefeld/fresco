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
#include "Berlin/PolyGraphic.hh"
#include "Berlin/RefCountVar.hh"
#include <iostream>

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

namespace Berlin
{

  class PolyGraphic::Iterator : public virtual POA_Fresco::GraphicIterator,
		     public virtual GraphicIteratorImpl
  {
    public:
      Iterator(PolyGraphic *p, Tag c) :
	  my_parent(p),
	  my_cursor(c)
      {
	  Trace trace("PolyGraphic::Iterator::Iterator");
	  my_parent->_add_ref();
      }
      virtual ~Iterator()
      {
	  Trace trace("PolyGraphic::Iterator::~Iterator");
	  my_parent->_remove_ref();
      }
      virtual Fresco::Graphic_ptr child()
      {
	  Trace trace("PolyGraphic::Iterator::child");
	  Prague::Guard<Mutex> guard(my_parent->my_mutex);
	  if (my_cursor >= my_parent->my_children.size())
	      return Fresco::Graphic::_nil();
	  return RefCount_var<Fresco::Graphic>::increment(my_parent->my_children[my_cursor].peer);
      }
      virtual void next() { my_cursor++; }
      virtual void prev() { my_cursor--; }
      virtual void insert(Graphic_ptr child)
      {
	  Trace trace("PolyGraphic::Iterator::insert");
	  {
	      Prague::Guard<Mutex> guard(my_parent->my_mutex);
	      Edge edge;
	      edge.peer = RefCount_var<Fresco::Graphic>::increment(child);
	      edge.localId = my_parent->unique_child_id();
	      edge.peerId =
		  child->add_parent_graphic(Graphic_var(my_parent->_this()),
					    edge.localId);
	      if (my_cursor >= my_parent->my_children.size())
		  my_parent->my_children.insert(my_parent->my_children.end(),
						edge);
	      else
		  my_parent->my_children.insert(my_parent->my_children.begin() +
						my_cursor, edge);
	  }
	  my_parent->need_resize();
      }
      virtual void replace(Graphic_ptr child)
      {
	  Trace trace("PolyGraphic::Iterator::replace");
	  {
	      Prague::Guard<Mutex> guard(my_parent->my_mutex);
	      if (my_cursor >= my_parent->my_children.size()) return;
	      Edge &edge = my_parent->my_children[my_cursor];
	      if (!CORBA::is_nil(edge.peer))
		  try
		  {
		      edge.peer->remove_parent_graphic(edge.peerId);
		      edge.peer->decrement();
		  }
		  catch(const CORBA::OBJECT_NOT_EXIST &) { }
		  catch (const CORBA::COMM_FAILURE &) { }
		  catch (const CORBA::TRANSIENT &) { }
	      edge.peer = RefCount_var<Fresco::Graphic>::increment(child);
	      edge.peerId =
		  child->add_parent_graphic(Graphic_var(my_parent->_this()),
					    edge.localId);
	  }
	  my_parent->need_resize();
      }
    
      virtual void remove()
      {
	  Trace trace("PolyGraphic::Iterator::remove");
	  {
	      Prague::Guard<Mutex> guard(my_parent->my_mutex);
	      if (my_cursor >= my_parent->my_children.size()) return;
	      
	      GraphicImpl::glist_t::iterator i =
		  my_parent->my_children.begin() + my_cursor;
	      try
	      {
		  (*i).peer->remove_parent_graphic((*i).peerId);
		  (*i).peer->decrement();
	      }
	      catch(const CORBA::OBJECT_NOT_EXIST &) { }
	      catch (const CORBA::COMM_FAILURE &) { }
	      catch (const CORBA::TRANSIENT &) { }
	      my_parent->my_children.erase(i);
	  }
	  my_parent->need_resize();
      }
    private:
      PolyGraphic *my_parent;
      CORBA::ULong my_cursor;
  };

} // namespace

Pool<Fresco::Graphic::Requisition> PolyGraphic::my_pool;

PolyGraphic::PolyGraphic() { }
PolyGraphic::~PolyGraphic()
{
    Trace trace(this, "PolyGraphic::~PolyGraphic");
    Prague::Guard<Mutex> guard(my_mutex);
    for (glist_t::iterator i = my_children.begin();
	 i != my_children.end();
	 ++i)
    {
	if (!CORBA::is_nil((*i).peer))
	    try
	    {
		(*i).peer->remove_parent_graphic((*i).peerId);
		(*i).peer->decrement();
	    }
	    catch(const CORBA::OBJECT_NOT_EXIST &) { }
	    catch (const CORBA::COMM_FAILURE &) { }
	    catch (const CORBA::TRANSIENT &) { }
    }
}

void PolyGraphic::append_graphic(Graphic_ptr child)
{
    Trace trace(this, "PolyGraphic::append_graphic");
    {
	Prague::Guard<Mutex> guard(my_mutex);
	Edge edge;
	edge.peer = RefCount_var<Fresco::Graphic>::increment(child);
	edge.localId = unique_child_id();
	edge.peerId = child->add_parent_graphic(Graphic_var(_this()),
						edge.localId);
	my_children.push_back(edge);
    }
    need_resize();
}

void PolyGraphic::prepend_graphic(Graphic_ptr child)
{
    Trace trace(this, "PolyGraphic::prepend_graphic");
    {
	Prague::Guard<Mutex> guard(my_mutex);
	Edge edge;
	edge.peer = RefCount_var<Fresco::Graphic>::increment(child);
	edge.localId = unique_child_id();
	edge.peerId = child->add_parent_graphic(Graphic_var(_this()),
						edge.localId);
	my_children.insert(my_children.begin(), edge);
    }
    need_resize();
}

void PolyGraphic::remove_graphic(Tag localId)
{
    Trace trace(this, "PolyGraphic::remove_graphic");
    {
	Prague::Guard<Mutex> guard(my_mutex);
	glist_t::iterator i = child_id_to_iterator(localId);
	try
	{
	    (*i).peer->remove_parent_graphic((*i).peerId);
	    (*i).peer->decrement();
	}
	catch(const CORBA::OBJECT_NOT_EXIST &) { }
	catch (const CORBA::COMM_FAILURE &) { }
	catch (const CORBA::TRANSIENT &) { }
	my_children.erase(i);
    }
    need_resize();
}

void PolyGraphic::remove_child_graphic(Tag localId)
{
    Trace trace(this, "PolyGraphic::remove_child_graphic");
    {
	Prague::Guard<Mutex> guard(my_mutex);
	glist_t::iterator i = child_id_to_iterator(localId);
	my_children.erase(i);
    }
    need_resize();
}

Fresco::GraphicIterator_ptr PolyGraphic::first_child_graphic()
{
    Trace trace(this, "PolyGraphic::first_child_graphic");
    Iterator *iterator = new Iterator(this, 0);
    activate(iterator);
    return iterator->_this();
}

Fresco::GraphicIterator_ptr PolyGraphic::last_child_graphic()
{
    Trace trace(this, "PolyGraphic::last_child_graphic");
    
    Iterator *iterator = new Iterator(this, num_children() ?
				      num_children() - 1 : 0);
    activate(iterator);
    return iterator->_this();
}

void PolyGraphic::need_resize() { GraphicImpl::need_resize(); }
void PolyGraphic::need_resize(Tag) { GraphicImpl::need_resize(); }

CORBA::ULong PolyGraphic::num_children()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_children.size();
}

Fresco::Graphic::Requisition *PolyGraphic::children_requests()
{
    Trace trace(this, "PolyGraphic::children_requests");
    Prague::Guard<Mutex> guard(my_mutex);
    Fresco::Graphic::Requisition *requisitions =
	my_pool.allocate(my_children.size());
    Fresco::Graphic::Requisition *r = requisitions;
    for (glist_t::iterator i = my_children.begin();
	 i != my_children.end();
	 ++i)
    {
	GraphicImpl::init_requisition(*r);
	if (!CORBA::is_nil((*i).peer))
	    try
	    { (*i).peer->request(*r); }
	    catch (const CORBA::OBJECT_NOT_EXIST &)
	    { (*i).peer = Fresco::Graphic::_nil(); }
	    catch (const CORBA::COMM_FAILURE &)
	    { (*i).peer = Fresco::Graphic::_nil(); }
	    catch (const CORBA::TRANSIENT &)
	    { (*i).peer = Fresco::Graphic::_nil(); }
	++r;
    }
    return requisitions;
}

void PolyGraphic::deallocate_requisitions(Fresco::Graphic::Requisition *r)
{
    Prague::Guard<Mutex> guard(my_mutex);
    my_pool.deallocate(r);
}

void PolyGraphic::child_extension(size_t i,
				  const Fresco::Allocation::Info &info,
				  Region_ptr region)
{
    Prague::Guard<Mutex> guard(my_mutex);
    Graphic_var child = my_children[i].peer;
    if (!CORBA::is_nil(child))
	try
	{ child->extension(info, region); }
	catch (const CORBA::OBJECT_NOT_EXIST &)
	{ my_children[i].peer = Fresco::Graphic::_nil(); }
	catch (const CORBA::COMM_FAILURE &)
	{ my_children[i].peer = Fresco::Graphic::_nil(); }
	catch (const CORBA::TRANSIENT &)
	{ my_children[i].peer = Fresco::Graphic::_nil(); }
}
