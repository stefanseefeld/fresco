/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include <Warsaw/config.hh>
#include <Warsaw/Input.hh>
#include <Warsaw/Controller.hh>
#include <Warsaw/PickTraversal.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/Focus.hh>
#include <Berlin/TraversalImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Vertex.hh>
#include <Prague/Sys/Tracer.hh>

class PickTraversalImpl : public virtual POA_Warsaw::PickTraversal,
                          public TraversalImpl
{
  typedef vector<Warsaw::Controller_var> cstack_t;
  typedef vector<size_t> pstack_t;
 public:
  PickTraversalImpl(Warsaw::Graphic_ptr, Warsaw::Region_ptr, Warsaw::Transform_ptr, const Warsaw::Input::Position &, Warsaw::Focus_ptr);
  //. to be used when starting from root level
  ~PickTraversalImpl();
  void visit(Warsaw::Graphic_ptr g) { g->pick(Warsaw::PickTraversal_var(_this()));}
  Warsaw::Traversal::order direction() { return Warsaw::Traversal::down;}
  CORBA::Boolean ok() { return !mem;}
  CORBA::Boolean intersects_allocation();
  CORBA::Boolean intersects_region(Warsaw::Region_ptr);
  Warsaw::Input::Device device() { return focus->device();}
  void enter_controller(Warsaw::Controller_ptr);
  void leave_controller();
  void hit();
  void pop_controller();
  CORBA::Boolean picked() { return mem;}
  void grab() { focus->grab();}
  void ungrab() { focus->ungrab();}

  Warsaw::Controller_ptr top_controller();
  const vector<Warsaw::Controller_var> &controllerStack() const { return controllers;}
  PickTraversalImpl   *memento() { PickTraversalImpl *m = mem; mem = 0; return m;}
  void reset(const Warsaw::Input::Position &);
  void debug();
 private:
  PickTraversalImpl(const PickTraversalImpl &);
  //. to be used to create the memento
  cstack_t                controllers;
  pstack_t                positions;
  Warsaw::Input::Position pointer;
  Warsaw::Focus_var       focus;
  PickTraversalImpl      *mem;
};

//. remove one controller level from the top, it might have got out of scope
inline void PickTraversalImpl::pop_controller()
{
  Prague::Trace trace("PickTraversal::pop_controller");
  if (controllers.size())
    {
      while (size() > positions.back()) pop();
      controllers.pop_back();
      positions.pop_back();
    }
}

inline Warsaw::Controller_ptr PickTraversalImpl::top_controller()
{
  return controllers.size() ? Warsaw::Controller::_duplicate(controllers.back()) : Warsaw::Controller::_nil();
}

inline void PickTraversalImpl::reset(const Warsaw::Input::Position &p)
//. pop all graphics up to the top most controller and set the pointer
//. so the traversal can be used to start over directly at the top
{
  Prague::Trace trace("PickTraversal::reset");
  pop_controller();
  pointer = p;
}

#endif 
