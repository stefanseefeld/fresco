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
#ifndef _Berlin_GraphicImpl_hh
#define _Berlin_GraphicImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Graphic.hh>
#include <Prague/Sys/Thread.hh>
#include <vector>
#include <algorithm>
#include <functional>
#include "Berlin/RefCountBaseImpl.hh"
#include "Berlin/IdentifiableImpl.hh"

class RegionImpl;
class AllocationImpl;

class GraphicImpl : public virtual POA_Fresco::Graphic,
                    public virtual RefCountBaseImpl,
                    public virtual IdentifiableImpl
{
 protected:
  //. An edge is a reference to a graphic within a composite.
  //. Because a graphic might appear twice within the same composite,
  //. a graphic itself is insufficient to identify its position within
  //. its parent.
  struct Edge
  {
    Fresco::Graphic_var peer;
    Fresco::Tag         peerId;
    Fresco::Tag         localId;
  };
  typedef std::vector<Edge> glist_t;
  struct localId_eq : public std::unary_function<Edge, bool>
    {
      localId_eq(Fresco::Tag t) : id(t) {}
      bool operator()(const Edge &e) const { return e.localId == id; }
      Fresco::Tag id;
    };
 public:
  static const Fresco::Coord infinity = 10e6;
  GraphicImpl();
  virtual ~GraphicImpl();
  virtual void deactivate();

  virtual Fresco::Graphic_ptr body();
  virtual void body(Fresco::Graphic_ptr);
  virtual void append_graphic(Fresco::Graphic_ptr);
  virtual void prepend_graphic(Fresco::Graphic_ptr);
  virtual void remove_graphic(Fresco::Tag);
  virtual void remove_child_graphic(Fresco::Tag);
  virtual Fresco::Tag add_parent_graphic(Fresco::Graphic_ptr, Fresco::Tag);
  virtual void remove_parent_graphic(Fresco::Tag);
  virtual Fresco::GraphicIterator_ptr first_child_graphic();
  virtual Fresco::GraphicIterator_ptr last_child_graphic();

  virtual Fresco::Transform_ptr transformation();
  virtual void request(Fresco::Graphic::Requisition &);
  virtual void extension(const Fresco::Allocation::Info &, Fresco::Region_ptr);
  virtual void shape(Fresco::Region_ptr);

  virtual void traverse(Fresco::Traversal_ptr);
  virtual void draw(Fresco::DrawTraversal_ptr);
  virtual void pick(Fresco::PickTraversal_ptr);

  virtual void allocate(Fresco::Tag, const Fresco::Allocation::Info &);
  virtual void allocations(Fresco::Allocation_ptr);
  virtual void need_redraw();
  virtual void need_redraw_region(Fresco::Region_ptr);
  virtual void need_resize();

  static void init_requisition(Fresco::Graphic::Requisition &);
  static void default_requisition(Fresco::Graphic::Requisition &);
  static void require(Fresco::Graphic::Requirement &, Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Coord);
  static void require_lead_trail(Fresco::Graphic::Requirement &,
				 Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Coord);
  static Fresco::Graphic::Requirement *requirement(Fresco::Graphic::Requisition &, Fresco::Axis);
  static void default_extension(const Fresco::Allocation::Info &, Fresco::Region_ptr);
  static void natural_allocation(Fresco::Graphic_ptr, RegionImpl &);
  static void transform_request(Fresco::Graphic::Requisition &, Fresco::Transform_ptr);
  static Fresco::Vertex transform_allocate(RegionImpl &, const Fresco::Graphic::Requisition &, Fresco::Transform_ptr);
private:
  Fresco::Tag unique_parent_id();
  glist_t              my_parents;
  Prague::Mutex        my_mutex;
};

class GraphicIteratorImpl : public virtual POA_Fresco::GraphicIterator,
		            public virtual ServantBase
{
public:
  virtual void destroy() { deactivate();}
};

#endif
