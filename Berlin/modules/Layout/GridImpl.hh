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
#ifndef _GridImpl_hh
#define _GridImpl_hh

#include <Warsaw/Grid.hh>
#include <Berlin/GraphicImpl.hh>

class GridImpl;

class GridOffset : virtual public _sk_GraphicOffset
{
public:
  GridOffset(GridImpl *parent, Graphic_ptr child, Grid::Index index);
  ~GridOffset();

  Graphic::Requirement requirement(Axis axis);
  GridOffset *&next(Axis axis) { return next_[static_cast<int>(axis)]; }

  virtual Graphic_ptr Parent();
  virtual Graphic_ptr Child();
  virtual GraphicOffset_ptr next();
  virtual GraphicOffset_ptr previous();
  virtual void allocations(Graphic::AllocationInfoSeq &a);
  virtual void insert(Graphic_ptr);
  virtual void replace(Graphic_ptr);
  virtual void remove();
  virtual void needResize();
  virtual void traverse(Traversal_ptr);
  virtual void visit_trail(Traversal_ptr);
  virtual void allocateChild(Graphic::AllocationInfo &);
  
  Grid::Index index;
  
private:
  GridImpl *parent;
  Graphic_var child;
  GridOffset *next_[2];
};

class GridDimension
{
public:
  GridDimension();
  ~GridDimension();
  
  void initialize(long count);

  long count;
  GridOffset **offsets;
  Graphic::Requirement *requirements;
};

class GridImpl : virtual public _sk_Grid, public GraphicImpl
{
  struct Span
  {
    Coord lower;
    Coord upper;
    Alignment align;
  };
public:
  GridImpl(const Index &upper);
  ~GridImpl();

  virtual void request(Requisition &);
  virtual void traverse(Traversal_ptr);
  virtual void append(Graphic_ptr);
  virtual void prepend(Graphic_ptr);
  virtual void needResize();

  virtual void replace(Graphic_ptr, const Grid::Index &i);
  virtual Grid::Index find(Traversal_ptr);
  virtual void allocateCell(Region_ptr, const Grid::Index &, Region_ptr);
  virtual void requestRange(Graphic::Requisition &, const Grid::Range &);
  virtual void traverseRange(Traversal_ptr, const Grid::Range &);
  virtual Grid::Index findRange(Traversal_ptr, const Grid::Range &);
  virtual void rangePosition(Region_ptr, const Grid::Range &, Vertex &);
  virtual Grid::Index upper();

  void allocateChild(Graphic::AllocationInfo &, Grid::Index);
    
private:
  void cacheRequest();
  void partialRequest(Axis axis, long lower, long, Graphic::Requirement &);
  void fullRequest(Axis, Axis);
  Span *fullAllocate(Axis, Region_ptr);
  void traverseWithAllocation(Traversal_ptr, Region_ptr, const Grid::Range &);
  void traverseWithoutAllocation(Traversal_ptr, const Grid::Range &);

  GridDimension dimensions[2];

  Grid::Index cursor;

  bool requested;
  Requisition requisition;
};

class SubGridImpl;

class SubGridOffset : virtual public _sk_GraphicOffset
{
public:
  SubGridOffset(SubGridImpl *, Grid_ptr, const Grid::Range &);
  ~SubGridOffset();

  virtual Graphic_ptr Parent();
  virtual Graphic_ptr Child();
  virtual GraphicOffset_ptr next();
  virtual GraphicOffset_ptr previous();
  virtual void allocations(Graphic::AllocationInfoSeq &);
  virtual void insert(Graphic_ptr);
  virtual void replace(Graphic_ptr);
  virtual void remove();
  virtual void needResize();
  virtual void traverse(Traversal_ptr);
  virtual void visit_trail(Traversal_ptr);
  virtual void allocateChild(Graphic::AllocationInfo &);

  void request(Graphic::Requisition &);

protected:
  SubGridImpl *parent;
  Grid_var child;
  Tag remove_tag;
  Grid::Range range;
};

class SubGridImpl : public GraphicImpl
{
public:
  SubGridImpl(Grid_ptr, const Grid::Range &);
  ~SubGridImpl();

  virtual void request(Requisition &);
  virtual void traverse(Traversal_ptr);
private:
  SubGridOffset *offset;
};

#endif /* _GridImpl_hh */
