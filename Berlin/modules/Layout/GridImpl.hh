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
#ifndef _GridImpl_hh
#define _GridImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Grid.hh>
#include <Berlin/GraphicImpl.hh>
#include <vector>

class GridImpl;

struct GridDimension
{
  void init(long count, long n)
    {
      children.resize(count);
      for (vector<vector<Warsaw::Graphic_var> >::iterator i = children.begin(); i != children.end(); i++)
	(*i).resize(n);
      requirements.resize(count);
    }
  CORBA::Long size() { return children.size();}
  vector<vector<Warsaw::Graphic_var> > children;
  vector<Warsaw::Graphic::Requirement> requirements;
};

class GridImpl : public virtual POA_Warsaw::Grid,
		 public GraphicImpl
{
  struct Span
  {
    Warsaw::Coord lower;
    Warsaw::Coord upper;
    Warsaw::Alignment align;
  };
public:
  GridImpl(const Warsaw::Grid::Index &upper);
  ~GridImpl();

  virtual void append(Warsaw::Graphic_ptr);
  virtual void prepend(Warsaw::Graphic_ptr);

  virtual void request(Warsaw::Graphic::Requisition &);
  virtual void traverse(Warsaw::Traversal_ptr);
  virtual void needResize();
  virtual void allocate(Warsaw::Tag, const Warsaw::Allocation::Info &);

  virtual void replace(Warsaw::Graphic_ptr, const Warsaw::Grid::Index &);
  virtual Warsaw::Grid::Index find(Warsaw::Traversal_ptr);
  virtual void allocateCell(Warsaw::Region_ptr, const Warsaw::Grid::Index &, Warsaw::Region_ptr);
  virtual void requestRange(Warsaw::Graphic::Requisition &, const Warsaw::Grid::Range &);
  virtual void traverseRange(Warsaw::Traversal_ptr, const Warsaw::Grid::Range &);
  virtual Warsaw::Grid::Index findRange(Warsaw::Traversal_ptr, const Warsaw::Grid::Range &);
  virtual void rangePosition(Warsaw::Region_ptr, const Warsaw::Grid::Range &, Warsaw::Vertex &);
  virtual Warsaw::Grid::Index upper();

 private:
  Warsaw::Tag index2tag(const Warsaw::Grid::Index &index) { return (index.col << 16) + index.row;}
  Warsaw::Grid::Index tag2index(Warsaw::Tag tag)
    {
      Warsaw::Grid::Index index;
      index.col = tag >> 16;
      index.row = tag & 0xffff;
      return index;
    }
  void cacheRequest();
  void partialRequest(Warsaw::Axis axis, long lower, long, Warsaw::Graphic::Requirement &);
  void fullRequest(Warsaw::Axis, Warsaw::Axis);
  Span *fullAllocate(Warsaw::Axis, Warsaw::Region_ptr);
  void traverseWithAllocation(Warsaw::Traversal_ptr, Warsaw::Region_ptr, const Warsaw::Grid::Range &);
  void traverseWithoutAllocation(Warsaw::Traversal_ptr, const Warsaw::Grid::Range &);

  GridDimension dimensions[2];

  Warsaw::Grid::Index cursor;

  bool requested;
  Warsaw::Graphic::Requisition requisition;
};

class SubGridImpl : public GraphicImpl
{
public:
  SubGridImpl(Warsaw::Grid_ptr, const Warsaw::Grid::Range &);
  ~SubGridImpl();

  virtual void request(Warsaw::Graphic::Requisition &);
  virtual void traverse(Warsaw::Traversal_ptr);
private:
  Warsaw::Grid_var child;
  Warsaw::Grid::Range range;
};

#endif
