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
#include "Berlin/Logger.hh"
#include "Berlin/Vertex.hh"

/* this is a traversal which is responsible for distributing events to
   graphics.  as such, speed is somewhat important. We set everything for
   "full throttle" -- everything's inline unfortunately. */

class PickTraversalImpl : implements(PickTraversal), public TraversalImpl
{
  typedef vector<Controller_var> cstack_t;
  typedef vector<size_t> pstack_t;
 public:
  PickTraversalImpl(Graphic_ptr, Region_ptr, Transform_ptr, const Event::Pointer &);
  //. to be used when starting from root level
  ~PickTraversalImpl();
  void reset(const Event::Pointer &);
  void visit(Graphic_ptr g) { g->pick(PickTraversal_var(_this()));}
  order direction() { return down;}
  CORBA::Boolean ok() { return !mem;}
  CORBA::Boolean intersectsAllocation()
    {
#if 1 // transform the pointer's location into the local CS
      Vertex local = pointer.location;
      Transform_var transform = transformation();
      transform->inverseTransformVertex(local);
      Region_var region = allocation();
      if (region->contains(local)) return true;
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
  void enterController(Controller_ptr c)
    {
//       SectionLog log(Logger::picking, "PickTraversal::enterController");
      controllers.push_back(Controller::_duplicate(c));
      positions.push_back(size());
//       debug();
    }
  void leaveController()
    {
//       SectionLog log(Logger::picking, "PickTraversal::leaveController");
      controllers.pop_back();
      positions.pop_back();
//       debug();
    }
  void hit()
    {
//       SectionLog log(Logger::picking, "PickTraversal::hit");
      delete mem;
      mem = new PickTraversalImpl(*this);
    }
  void popController()
    {
//       SectionLog log(Logger::picking, "PickTraversal::popController");
      if (controllers.size())
	{
	  while (size() > positions.back()) pop();
	  controllers.pop_back();
	  positions.pop_back();
	}
//       debug();
    }
  CORBA::Boolean picked() { return mem;}
  Controller_ptr topController()
    {
      return controllers.size() ? Controller::_duplicate(controllers.back()) : Controller::_nil();
    }
  const vector<Controller_var> &controllerStack() const { return controllers;}
  PickTraversalImpl   *memento() { PickTraversalImpl *m = mem; mem = 0; return m;}
//   void debug()
//     {
//       cout << "PickTraversal::debug : stack size = " << size() << '\n';
//       cout << "Controllers at ";
//       for (size_t i = 0; i != positions.size(); i++) cout << positions[i] << ' ';
//       cout << endl;
//     }
 private:
  PickTraversalImpl(const PickTraversalImpl &);
  //. to be used to create the memento
  cstack_t           controllers;
  pstack_t           positions;
  Event::Pointer     pointer;
  PickTraversalImpl *mem;
};

#endif /* _PickTraversalImpl_hh */
