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
#ifndef _GridImpl_hh
#define _GridImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Grid.hh>
#include <Berlin/GraphicImpl.hh>
#include <vector>

namespace Berlin {
namespace LayoutKit {

class GridImpl : public virtual POA_Layout::Grid,
		 public GraphicImpl
{
  struct Dimension
  {
    void init(long count, long n)
    {
      children.resize(count);
      for (std::vector<std::vector<Fresco::Graphic_var> >::iterator i = children.begin(); i != children.end(); ++i)
	(*i).resize(n);
      requirements.resize(count);
    }
    CORBA::Long size() { return children.size();}
    std::vector<std::vector<Fresco::Graphic_var> > children;
    std::vector<Fresco::Graphic::Requirement> requirements;
  };
public:
  struct Span
  {
    Fresco::Coord lower;
    Fresco::Coord upper;
    Fresco::Alignment align;
  };
  GridImpl(const Layout::Grid::Index &upper);
  ~GridImpl();

  virtual void append_graphic(Fresco::Graphic_ptr);
  virtual void prepend_graphic(Fresco::Graphic_ptr);

  virtual void request(Fresco::Graphic::Requisition &);
  virtual void traverse(Fresco::Traversal_ptr);
  virtual void need_resize();
  virtual void allocate(Fresco::Tag, const Fresco::Allocation::Info &);

  virtual void replace(Fresco::Graphic_ptr, const Layout::Grid::Index &);
  virtual Layout::Grid::Index find(Fresco::Traversal_ptr);
  virtual void allocate_cell(Fresco::Region_ptr, const Layout::Grid::Index &, Fresco::Region_ptr);
  virtual void request_range(Fresco::Graphic::Requisition &, const Layout::Grid::Range &);
  virtual void traverse_range(Fresco::Traversal_ptr, const Layout::Grid::Range &);
  virtual Layout::Grid::Index find_range(Fresco::Traversal_ptr, const Layout::Grid::Range &);
  virtual void range_position(Fresco::Region_ptr, const Layout::Grid::Range &, Fresco::Vertex &);
  virtual Layout::Grid::Index upper();

 private:
  Fresco::Tag index_to_tag(const Layout::Grid::Index &index) { return (index.col << 16) + index.row;}
  Layout::Grid::Index tag_to_index(Fresco::Tag tag)
    {
      Layout::Grid::Index index;
      index.col = tag >> 16;
      index.row = tag & 0xffff;
      return index;
    }
  void cache_request();
  void partial_request(Fresco::Axis axis, long lower, long, Fresco::Graphic::Requirement &);
  void full_request(Fresco::Axis, Fresco::Axis);
  Span *full_allocate(Fresco::Axis, Fresco::Region_ptr);
  void traverse_with_allocation(Fresco::Traversal_ptr, Fresco::Region_ptr, const Layout::Grid::Range &);
  void traverse_without_allocation(Fresco::Traversal_ptr, const Layout::Grid::Range &);

  Dimension _dimensions[2];
  Layout::Grid::Index _cursor;

  bool _requested;
  Fresco::Graphic::Requisition _requisition;
};

class SubGridImpl : public GraphicImpl
{
public:
  SubGridImpl(Layout::Grid_ptr, const Layout::Grid::Range &);
  ~SubGridImpl();

  virtual void request(Fresco::Graphic::Requisition &);
  virtual void traverse(Fresco::Traversal_ptr);
private:
  Layout::Grid_var _child;
  Layout::Grid::Range _range;
};

} // namespace
} // namespace

#endif
