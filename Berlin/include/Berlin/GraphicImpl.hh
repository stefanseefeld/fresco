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
#ifndef _GraphicImpl_hh
#define _GraphicImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Graphic.hh>
#include <Berlin/CloneableImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <vector>

struct OffsetTag
{
  OffsetTag(GraphicOffset_ptr);
  GraphicOffset_ptr offset;
  Tag tag;
};

typedef vector<GraphicOffset *> GraphicOffsetList;
typedef vector<OffsetTag *> OffsetTagList;

class GraphicImpl : implements(Graphic), public virtual CloneableImpl
{
public:
  static const Coord infinity = 10e6;
  GraphicImpl();
  virtual ~GraphicImpl();

  virtual Graphic_ptr cloneGraphic();
//   virtual StyleContext_ptr style();
//   virtual void style(StyleContext_ptr _p);
  virtual Transform_ptr transformation();
  virtual void request(Requisition &);
  virtual void extension(const AllocationInfo &, Region_ptr);
  virtual void shape(Region_ptr);
  virtual void traverse(Traversal_ptr);
  virtual void draw(DrawTraversal_ptr);
  virtual void pick(PickTraversal_ptr);
  virtual Graphic_ptr body();
  virtual void body(Graphic_ptr);
  virtual void append(Graphic_ptr);
  virtual void prepend(Graphic_ptr);
  virtual void addParent(GraphicOffset_ptr);
  virtual void removeParent(GraphicOffset_ptr);
  virtual GraphicOffset_ptr firstOffset();
  virtual GraphicOffset_ptr lastOffset();
  virtual void parentOffsets(OffsetSeq &);
  virtual void allocations(Collector_ptr);
//   virtual void damages(DamageInfoSeq &);
  virtual void needRedraw();
  virtual void needRedrawRegion(Region_ptr);
  virtual void needResize();
//   virtual bool restore_trail(Traversal_ptr);
  static void initRequisition(Graphic::Requisition &);
  static void defaultRequisition(Graphic::Requisition &);
  static void require(Graphic::Requirement &, Coord, Coord, Coord, Coord);
  static void requireLeadTrail(Graphic::Requirement &, Coord, Coord, Coord, Coord, Coord, Coord);
  static Graphic::Requirement *requirement(Graphic::Requisition &, Axis);
  static void defaultExtension(const Graphic::AllocationInfo &, Region_ptr);
  static void getParentOffsets(Graphic::OffsetSeq &, const GraphicOffsetList &);
  static Region_ptr naturalAllocation(Graphic_ptr);
  static void transformRequest(Graphic::Requisition &, Transform_ptr);
  static Vertex transformAllocate(RegionImpl &, const Graphic::Requisition &, Transform_ptr);
protected:
//   OffsetTagList parents;
  GraphicOffsetList parents;
};

#endif /* _GraphicImpl_hh */
