/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _Allocator_hh
#define _Allocator_hh

#include <Berlin/MonoGraphic.hh>
#include <Berlin/ImplVar.hh>

class Allocator : public MonoGraphic
//. An Allocator is a graphic that always gives its child
//. an allocation that matches the child's requisition.
//. This functionality is useful as a gateway between
//. figure objects, which ignore their allocation, and
//. layout objects.
{
public:
  Allocator();
  virtual ~Allocator();

  virtual void request(Requisition &);

  virtual void traverse(Traversal_ptr);

  virtual void allocate(Tag, const Allocation::Info &);
  virtual void needResize();
// private:
  bool requested : 1;
  bool allocated : 1;
  Graphic::Requisition requisition;
  Impl_var<RegionImpl> natural;
  Impl_var<RegionImpl> extension;
  
  void cacheRequisition();
  void cacheAllocation();
  void needDamage(RegionImpl *, Allocation_ptr);
};

class TransformAllocator : public Allocator
//. A TransformAllocator maps its allocate to a translation
//. during traversal and always gives its child the child's
//. natural allocation.  This functionality is useful
//. as a gateway between layout objects and figure objects
//. (which ignore their allocation).
{
public:
  TransformAllocator(Alignment, Alignment, Alignment, Alignment, Alignment, Alignment);
  ~TransformAllocator();

  virtual void request(Requisition &);
  virtual void traverse(Traversal_ptr);
  virtual void allocate(Tag, const Allocation::Info &);
protected:
  Alignment xparent, yparent, zparent;
  Alignment xchild, ychild, zchild;

  void computeDelta(const Vertex &, const Vertex &, Vertex &);
};

#endif /* _Allocator_hh */
