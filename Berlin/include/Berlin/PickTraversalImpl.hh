/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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
#ifndef _PickTraversalImpl_hh
#define _PickTraversalImpl_hh

#include "Warsaw/config.hh"
#include "Warsaw/Event.hh"
#include "Warsaw/Controller.hh"
#include "Warsaw/PickTraversal.hh"
#include "Warsaw/Transform.hh"
#include "Berlin/TraversalImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/EventManager.hh"
#include "Berlin/Logger.hh"
#include "Berlin/Vertex.hh"

/* this is a traversal which is responsible for distributing events to
   graphics.  as such, speed is somewhat important. We set everything for
   "full throttle" -- everything's inline unfortunately. */

class PickTraversalImpl : implements(PickTraversal), public TraversalImpl
{
 public:
    PickTraversalImpl(Graphic_ptr, Region_ptr, const Event::Pointer &, EventManager *);
    PickTraversalImpl(const PickTraversalImpl &);
    ~PickTraversalImpl();
    
    void visit(Graphic_ptr g) { g->pick(PickTraversal_var(_this()));}
    order direction() { return down;}
    CORBA::Boolean ok() { return !memento;}
    CORBA::Boolean intersectsAllocation()
      {
#if 1 // transform the pointer's location into the local CS
	Vertex local = pointer.location;
	Transform_var transform = transformation();
	transform->inverseTransformVertex(local);
	Region_var alloc = allocation();
	RegionImpl region(alloc, Transform::_nil());
	if (region.contains(local)) return true;
#else // transform the local CS to global coordinates
	Region_var r = allocation();
	Transform_var t = transformation();
	RegionImpl region(r, t);
	if (region.contains(pointer.location)) return true;
#endif
	return false;
      }
    CORBA::Boolean intersectsRegion(Region_ptr allocation)
      {
	if (allocation->contains(pointer.location)) return true;
	else return false;
      }
    void hit(Controller_ptr c)
      {
	Logger::log(Logger::picking) << "hit ?" << endl;
 	Graphic_var current = graphic();
 	if (current->_is_equivalent(c))
	  {
	    Logger::log(Logger::picking) << "hit !" << endl;
	    controller = Controller::_duplicate(c);
	    manager->requestFocus(this, controller);
	    memento = new PickTraversalImpl(*this);
	    memento->_obj_is_ready(_boa());
	  }
      }
    PickTraversal_ptr picked() { return memento ? memento->_this() : PickTraversal::_nil();}
    Controller_ptr receiver() { return Controller::_duplicate(controller);}
 private:
    const Event::Pointer pointer;
    EventManager        *manager;
    PickTraversalImpl   *memento;
    Controller_var       controller;
};

#endif /* _PickTraversalImpl_hh */
