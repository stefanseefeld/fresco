/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
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
#ifndef _Berlin_PickTraversalImpl_hh
#define _Berlin_PickTraversalImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Input.hh>
#include <Fresco/Controller.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/Transform.hh>
#include <Berlin/TraversalImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Vertex.hh>
#include <Prague/Sys/Tracer.hh>

namespace Berlin
{

  class PositionalFocus;

  //. provide an implementation for the PickTraversal interface.
  //. the traversal keeps a stack of controllers that are on the trail
  //.
  //. some methods are not implemented:
  //. 'intersect_region' has to be implemented if the intersecting object
  //. is known (for example a region for node selections, or a vertex for
  //. positional events
  //. the 'hit()' method needs to be implemented as it adds a specific
  //. strategy for generating a memento. Derived classes may want to
  //. cache the memento to avoid frequent object activation
  class PickTraversalImpl : public virtual POA_Fresco::PickTraversal,
			    public TraversalImpl
  {
      typedef std::vector<Fresco::Controller_var> cstack_t;
      typedef std::vector<size_t> pstack_t;
    public:
      PickTraversalImpl(Fresco::Graphic_ptr, Fresco::Region_ptr,
			Fresco::Transform_ptr, PositionalFocus *);
      PickTraversalImpl(const PickTraversalImpl &);
      ~PickTraversalImpl();
      PickTraversalImpl &operator = (const PickTraversalImpl &);
      virtual Fresco::PickTraversal_ptr _this();
      virtual Fresco::Region_ptr current_allocation();
      virtual Fresco::Transform_ptr current_transformation();
      virtual Fresco::Graphic_ptr current_graphic();
      virtual void traverse_child(Fresco::Graphic_ptr, Fresco::Tag,
				  Fresco::Region_ptr, Fresco::Transform_ptr);
      virtual void visit(Fresco::Graphic_ptr);
      virtual Fresco::Traversal::order direction();
      virtual CORBA::Boolean ok();
      virtual CORBA::Boolean intersects_allocation();
//      virtual CORBA::Boolean intersects_region(Fresco::Region_ptr) = 0;
      virtual void enter_controller(Fresco::Controller_ptr);
      virtual void leave_controller();
      virtual void hit() = 0;
      virtual CORBA::Boolean picked() = 0;
      virtual Fresco::Focus_ptr get_focus();
      virtual CORBA::Boolean forward();
      virtual CORBA::Boolean backward();
      
      void pop_controller();
      Fresco::Controller_ptr top_controller();
      const std::vector<Fresco::Controller_var> &controllers() const
      { return my_controllers; }
      void reinit();
    protected:
      size_t current() const { return my_cursor; }
    private:
      cstack_t                   my_controllers;
      pstack_t                   my_positions;
      PositionalFocus           *my_focus;
      size_t                     my_cursor;
      Fresco::PickTraversal_var  my_this;
  };

  //. remove one controller level from the top, it might have got out of scope
  inline void PickTraversalImpl::pop_controller()
  {
      Prague::Trace trace("PickTraversal::pop_controller");
      if (my_controllers.size())
      {
	  while (size() > my_positions.back()) pop();
	  my_cursor = size() - 1;
	  my_controllers.pop_back();
	  my_positions.pop_back();
      }
  }

  inline void PickTraversalImpl::reinit()
  {
      // DO NOT CALL DURING A TRAVERSAL!
      
      // At the end of the Traversal only the very first element is on the
      // stack (and we won't touch that), or this is a memento of another
      // Traversal. In that case we own Graphic, Transformation and
      // Allocation, so we must explicitly release them before calling pop().
      Prague::Trace trace("PickTraversal::reinit");
      my_controllers.clear();
      my_positions.clear();
      while (size() > 1)
      {
	  CORBA::release(get_graphic(size() - 1));
	  Provider<RegionImpl>::adopt(get_allocation(size() - 1));
	  Provider<TransformImpl>::adopt(get_transformation(size() - 1));
	  pop();
      }
      my_cursor = 0;
  }

  inline Fresco::Controller_ptr PickTraversalImpl::top_controller()
  {
      return my_controllers.size() ?
	  Fresco::Controller::_duplicate(my_controllers.back()) :
	  Fresco::Controller::_nil();
  }

} // namespace

#endif 
