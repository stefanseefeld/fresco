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
#ifndef _Berlin_Allocator_hh
#define _Berlin_Allocator_hh

#include <Berlin/ImplVar.hh>
#include <Berlin/MonoGraphic.hh>

namespace Berlin
{

  //. An Allocator is a graphic that always gives its child
  //. an allocation that matches the child's requisition.
  //. This functionality is useful as a gateway between
  //. figure objects, which ignore their allocation, and
  //. layout objects.
  class Allocator : public MonoGraphic
  {
    public:
      Allocator();
      virtual ~Allocator();
      
      virtual void request(Fresco::Graphic::Requisition &);
      
      virtual void traverse(Fresco::Traversal_ptr);
      
      virtual void allocate(Fresco::Tag, const Fresco::Allocation::Info &);
      virtual void need_resize();
//   private:
      bool my_requested : 1;
      bool my_allocated : 1;
      Fresco::Graphic::Requisition my_requisition;
      Impl_var<RegionImpl> my_natural;
      Impl_var<RegionImpl> my_extension;
  
      void cache_requisition();
      void cache_allocation();
      void need_damage(RegionImpl *, Fresco::Allocation_ptr);
      static void natural_allocation(const Fresco::Graphic::Requisition &,
                     RegionImpl &);
  };

  //. A TransformAllocator maps its allocate to a translation
  //. during traversal and always gives its child the child's
  //. natural allocation.  This functionality is useful
  //. as a gateway between layout objects and figure objects
  //. (which ignore their allocation).
  class TransformAllocator : public Allocator
  {
    public:
      TransformAllocator(Fresco::Alignment, Fresco::Alignment,
             Fresco::Alignment, Fresco::Alignment,
             Fresco::Alignment, Fresco::Alignment);
      ~TransformAllocator();

      virtual void request(Fresco::Graphic::Requisition &);
      virtual void traverse(Fresco::Traversal_ptr);
      virtual void allocate(Fresco::Tag, const Fresco::Allocation::Info &);
    protected:
      Fresco::Alignment my_xparent, my_yparent, my_zparent;
      Fresco::Alignment my_xchild, my_ychild, my_zchild;
      
      void compute_delta(const Fresco::Vertex &, const Fresco::Vertex &,
             Fresco::Vertex &);
  };

} // namespace

#endif 
