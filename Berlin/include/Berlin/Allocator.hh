/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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

class Allocator : public MonoGraphic
{
public:
  Allocator();
  virtual ~Allocator();

  virtual void request(Requisition &);
  virtual void allocations(Collector_ptr);
  void allocateChild(Graphic::AllocationInfo &);
  virtual void traverse(Traversal_ptr);
  virtual void needResize();

protected:
  bool requested;
  Graphic::Requisition req;
  RegionImpl *nat;
  RegionImpl *ext;
  
  void updateRequisition();
  void needDamage(RegionImpl *, Collector_ptr);
};

class TransformAllocator : public Allocator
{
public:
  TransformAllocator(Alignment x_parent, Alignment y_parent, Alignment z_parent,
		     Alignment x_child, Alignment y_child, Alignment z_child);
  ~TransformAllocator();

  virtual void request(Requisition &);
  virtual void traverse(Traversal_ptr);

  void allocateChild(Graphic::AllocationInfo &);
protected:
  Alignment x_parent, y_parent, z_parent;
  Alignment x_child, y_child, z_child;

  void computeDelta(const Vertex &lower, const Vertex &upper, Vertex &delta);
};

#endif /* _Allocator_hh */
