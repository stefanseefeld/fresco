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
#ifndef _DrawTraversal_hh
#define _DrawTraversal_hh

#include <Warsaw/config.hh>
#include <Warsaw/DrawTraversal.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/TraversalImpl.hh>
#include <vector>

//. The DrawTraversal walks the SceneGraph and 'makes it visible' by
//. asking the DrawingKit to render the nodes as the Traversal
//. passes through it.
class DrawTraversalImpl : public virtual POA_Warsaw::DrawTraversal,
                          public TraversalImpl
{
public:
  DrawTraversalImpl(Warsaw::Graphic_ptr, Warsaw::Region_ptr, Warsaw::Transform_ptr, Warsaw::DrawingKit_ptr);
  DrawTraversalImpl(const DrawTraversalImpl &);
  virtual ~DrawTraversalImpl();
  virtual CORBA::Boolean intersects_allocation();
  virtual CORBA::Boolean intersects_region(Warsaw::Region_ptr);
  virtual void traverse_child(Warsaw::Graphic_ptr, Warsaw::Tag, Warsaw::Region_ptr, Warsaw::Transform_ptr);
  virtual void visit(Warsaw::Graphic_ptr);
  virtual Warsaw::Traversal::order direction();
  virtual CORBA::Boolean ok();
  virtual Warsaw::DrawingKit_ptr drawing();
  //. Saves the DrawingKit's state and sets it to sane values for
  //. the DrawTraversal.
  //  FIXME: Why is the state changed _before_ it is saved?
  void init();
  //. Restores the DrawingKit's state prior to the DrawTraversal.
  void finish();
private:
  Warsaw::DrawingKit_var     _drawing;
  Warsaw::Region_var         _clipping;
  Impl_var<TransformImpl>    _id;
  Warsaw::DrawTraversal_var __this;
};

#endif 
