/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _TraversalImpl_hh
#define _TraversalImpl_hh

class RegionImpl;
class TransformImpl;

#include <Warsaw/config.hh>
#include <Warsaw/Traversal.hh>
#include <Warsaw/Graphic.hh>
#include <Warsaw/Region.hh>
#include <Berlin/ServantBase.hh>
#include <Berlin/TransformImpl.hh>
#include <vector>


class TraversalImpl : public virtual POA_Warsaw::Traversal,
                      public virtual ServantBase
{
protected:
  struct State
  {
    State() : id(0), transformation(0) {}
    State(Warsaw::Graphic_ptr g, Warsaw::Tag i, Warsaw::Region_ptr a, TransformImpl *t)
      : graphic(Warsaw::Graphic::_duplicate(g)),
	id(i),
	allocation(Warsaw::Region::_duplicate(a)),
	transformation(t)
    {}
    State(const State &state)
      : graphic(Warsaw::Graphic::_duplicate(state.graphic)),
	id(state.id),
	allocation(Warsaw::Region::_duplicate(state.allocation)),
	transformation(Provider<TransformImpl>::provide())
    {
      transformation->copy(Warsaw::Transform_var(state.transformation->_this()));
    }
    ~State() { if (transformation) Provider<TransformImpl>::adopt(transformation);}
    State &operator = (const State &state)
    {
      graphic = Warsaw::Graphic::_duplicate(state.graphic);
      id = state.id;
      allocation = Warsaw::Region::_duplicate(state.allocation);
      transformation = Provider<TransformImpl>::provide();
      transformation->copy(Warsaw::Transform_var(state.transformation->_this()));
    }
    Warsaw::Graphic_var      graphic;
    Warsaw::Tag              id;
    Warsaw::Region_var       allocation;
    TransformImpl           *transformation;    
  };
  typedef vector<State> stack_t;
public:
  TraversalImpl(Warsaw::Graphic_ptr, Warsaw::Region_ptr, Warsaw::Transform_ptr);
  ~TraversalImpl();
  virtual Warsaw::Region_ptr current_allocation();
  virtual Warsaw::Transform_ptr current_transformation();
  virtual Warsaw::Graphic_ptr current_graphic();
  virtual CORBA::Boolean bounds(Warsaw::Vertex &, Warsaw::Vertex &, Warsaw::Vertex &);
  virtual CORBA::Boolean intersects_allocation() = 0;
  virtual CORBA::Boolean intersects_region(Warsaw::Region_ptr) = 0;
  virtual void traverse_child(Warsaw::Graphic_ptr, Warsaw::Tag, Warsaw::Region_ptr, Warsaw::Transform_ptr) = 0;
  virtual void visit(Warsaw::Graphic_ptr) = 0;
  virtual Warsaw::Traversal::order direction() = 0;
  virtual CORBA::Boolean ok() = 0;
  virtual void update();
protected:
  void push(Warsaw::Graphic_ptr, Warsaw::Tag, Warsaw::Region_ptr, TransformImpl *);
  void pop();
  size_t size() const { return _stack.size();}  
  const State &get(size_t i) const { return _stack[i];}
private:
  stack_t _stack;
};

#endif

