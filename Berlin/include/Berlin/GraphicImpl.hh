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
#ifndef _GraphicImpl_hh
#define _GraphicImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Graphic.hh>
#include <Prague/Sys/Thread.hh>
#include <vector>
#include <algorithm>
#include <functional>
#include "Berlin/RefCountBaseImpl.hh"
#include "Berlin/IdentifiableImpl.hh"

class RegionImpl;
class AllocationImpl;

class GraphicImpl : public virtual POA_Warsaw::Graphic,
                    public virtual RefCountBaseImpl,
                    public virtual IdentifiableImpl
{
 protected:
  struct Edge
  {
    Warsaw::Graphic_var peer;
    Warsaw::Tag         peerId;
    Warsaw::Tag         localId;
  };
  typedef Warsaw::Graphic::Iterator Iterator;
  typedef Warsaw::Graphic::Iterator_ptr Iterator_ptr;
  typedef Warsaw::Graphic::Requirement Requirement;
  typedef Warsaw::Graphic::Requisition Requisition;
  typedef vector<Edge> glist_t;
  struct localId_eq : public unary_function<Warsaw::Graphic::Edge, bool>
    {
      localId_eq(Warsaw::Tag t) : id(t) {}
      bool operator()(const Edge &e) const { return e.localId == id; }
      Warsaw::Tag id;
    };
 public:
  static const Warsaw::Coord infinity = 10e6;
  GraphicImpl();
  virtual ~GraphicImpl();

  virtual Warsaw::Graphic_ptr body();
  virtual void body(Warsaw::Graphic_ptr);
  virtual void append(Warsaw::Graphic_ptr);
  virtual void prepend(Warsaw::Graphic_ptr);
  virtual void remove(Warsaw::Tag);
  virtual void removeChild(Warsaw::Tag);
  virtual Warsaw::Tag addParent(Warsaw::Graphic_ptr, Warsaw::Tag);
  virtual void removeParent(Warsaw::Tag);
  virtual Iterator_ptr firstChild();
  virtual Iterator_ptr lastChild();
  virtual Iterator_ptr firstParent();
  virtual Iterator_ptr lastParent();

  virtual Warsaw::Transform_ptr transformation();
  virtual void request(Requisition &);
  virtual void extension(const Warsaw::Allocation::Info &, Warsaw::Region_ptr);
  virtual void shape(Warsaw::Region_ptr);

  virtual void traverse(Warsaw::Traversal_ptr);
  virtual void draw(Warsaw::DrawTraversal_ptr);
  virtual void pick(Warsaw::PickTraversal_ptr);

  virtual void allocate(Warsaw::Tag, const Warsaw::Allocation::Info &);
  virtual void allocations(Warsaw::Allocation_ptr);
  virtual void needRedraw();
  virtual void needRedrawRegion(Warsaw::Region_ptr);
  virtual void needResize();

  static void initRequisition(Warsaw::Graphic::Requisition &);
  static void defaultRequisition(Warsaw::Graphic::Requisition &);
  static void require(Warsaw::Graphic::Requirement &, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  static void requireLeadTrail(Warsaw::Graphic::Requirement &, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
  static Warsaw::Graphic::Requirement *requirement(Warsaw::Graphic::Requisition &, Warsaw::Axis);
  static void defaultExtension(const Warsaw::Allocation::Info &, Warsaw::Region_ptr);
  static void naturalAllocation(Warsaw::Graphic_ptr, RegionImpl &);
  static void transformRequest(Warsaw::Graphic::Requisition &, Warsaw::Transform_ptr);
  static Warsaw::Vertex transformAllocate(RegionImpl &, const Warsaw::Graphic::Requisition &, Warsaw::Transform_ptr);
private:
  Warsaw::Tag uniqueParentId();
  glist_t parents;
  Prague::Mutex parentMutex;
};

class GraphicIteratorImpl : public virtual POA_Warsaw::GraphicIterator,
			    public virtual ServantBase
{
public:
  virtual void destroy() { deactivate();}
};

#endif
