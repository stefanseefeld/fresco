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
#ifndef _Berlin_TraversalImpl_hh
#define _Berlin_TraversalImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Traversal.hh>
#include <Fresco/Graphic.hh>
#include <Berlin/ServantBase.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/TransformImpl.hh>
#include <vector>

//. TraversalImpl keeps a stack of context information for
//. the Graphic nodes it visits. Use push and pop to add/remove
//. new nodes to the stack. Items added via push are assumed to
//. be managed by the caller, i.e. they are not deleted in the pop
//. operation. In contrast, if you create a TraversalImpl via the
//. copy constructor, it creates a deep copy of raw pointer types,
//. and increments the ref count for ref counted objects.
//. The number of push and pop operations called on a single TraversalImpl
//. object therefor need to be balanced.
class TraversalImpl : public virtual POA_Fresco::Traversal,
                      public virtual ServantBase
{
    struct State
    {
	State() : id(0), transformation(0) { }
	State(Fresco::Graphic_ptr g, Fresco::Tag i,
	      RegionImpl *a, TransformImpl *t) :
	    graphic(g), id(i), allocation(a), transformation(t)
	{ }
	Fresco::Graphic_ptr      graphic;
	Fresco::Tag              id;
	RegionImpl              *allocation;
	TransformImpl           *transformation;    
    };
    typedef std::vector<State> stack_t;
  public:
    TraversalImpl(Fresco::Graphic_ptr, Fresco::Region_ptr,
		  Fresco::Transform_ptr);
    TraversalImpl(const TraversalImpl &);
    ~TraversalImpl();
    TraversalImpl &operator = (const TraversalImpl &);
    virtual Fresco::Region_ptr current_allocation();
    virtual Fresco::Transform_ptr current_transformation();
    virtual Fresco::Graphic_ptr current_graphic();
    virtual CORBA::Boolean bounds(Fresco::Vertex &, Fresco::Vertex &,
				  Fresco::Vertex &);
    virtual CORBA::Boolean intersects_allocation() = 0;
    virtual CORBA::Boolean intersects_region(Fresco::Region_ptr) = 0;
    virtual void traverse_child(Fresco::Graphic_ptr, Fresco::Tag,
				Fresco::Region_ptr,
				Fresco::Transform_ptr) = 0;
    virtual void visit(Fresco::Graphic_ptr) = 0;
    virtual Fresco::Traversal::order direction() = 0;
    virtual CORBA::Boolean ok() = 0;
    virtual void update();
  protected:
    //. push puts the actual trail values on a stack. They are *not*
    //. reference counted, it is assumed that pop is called in the same
    //. scope. Alternatively, values not removed from the stack are
    //. deallocated in the destructor.
    void push(Fresco::Graphic_ptr, Fresco::Tag,
	      RegionImpl *, TransformImpl *);
    void pop();
    size_t size() const { return my_stack.size(); }
    RegionImpl    *get_allocation(size_t i) { return my_stack[i].allocation; }
    TransformImpl *get_transformation(size_t i)
    { return my_stack[i].transformation; }
    Fresco::Graphic_ptr get_graphic(size_t i) { return my_stack[i].graphic; }
  private:
    void clear();
    stack_t my_stack;
};

#endif
