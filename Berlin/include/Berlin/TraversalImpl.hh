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
#include <vector>
#include "Berlin/TransformImpl.hh"


class TraversalImpl : public virtual POA_Traversal, public virtual PortableServer::RefCountServantBase
{
  struct State
  {
    Graphic_var    graphic;
    Tag            tag;
    Region_var     allocation;
    TransformImpl *transformation;    
  };
  typedef vector<State> stack_t;
 protected:
  typedef Traversal::order order;
 public:
  TraversalImpl(Graphic_ptr, Region_ptr, Transform_ptr);
  TraversalImpl(const TraversalImpl &);
  ~TraversalImpl();
  virtual Region_ptr allocation();
  virtual Transform_ptr transformation();
  virtual CORBA::Boolean bounds(Vertex &, Vertex &, Vertex &);
  virtual CORBA::Boolean intersectsAllocation() = 0;
  virtual CORBA::Boolean intersectsRegion(Region_ptr) = 0;
  virtual void traverseChild(Graphic_ptr, Tag, Region_ptr, Transform_ptr);
  virtual void visit(Graphic_ptr) = 0;
  virtual order direction() = 0;
  virtual CORBA::Boolean ok() = 0;
  virtual void update();
 protected:
  void push(Graphic_ptr, Tag, Region_ptr, TransformImpl *);
  void pop();
  size_t size() { return stack.size();}  
 private:
  stack_t stack;
};

#endif /* _TraversalImpl_h */
