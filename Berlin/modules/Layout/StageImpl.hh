/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#ifndef _StageImpl_hh
#define _StageImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Stage.hh>
#include <Warsaw/Traversal.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/QuadTree.hh>
#include <list>

struct StageInfoImpl : Stage::Info
{
  StageInfoImpl(Graphic_ptr g, const Vertex &p, const Vertex &s, Stage::Index l)
    : child(Graphic::_duplicate(g))
    {
      position = p;
      size = s;
      layer = l;
      cacheBBox();
    }
  const Geometry::Rectangle<Coord> &bbox()
    { return boundingbox;}
  void bbox(RegionImpl &region)
    {
      region.valid   = true;
      region.lower.x = boundingbox.l;
      region.upper.x = boundingbox.r;
      region.xalign  = xalign;
      region.lower.y = boundingbox.t;
      region.upper.y = boundingbox.b;
      region.yalign  = yalign;
    }
  Graphic_var child;
  Geometry::Rectangle<Coord> boundingbox;
  Alignment xalign;
  Alignment yalign;
  void cacheBBox();
};

class StageSequence : public list<StageInfoImpl *>
{
  typedef list<StageInfoImpl *> parent_t;
  iterator lookup(Stage::Index layer);
public:
  StageSequence() : cursor(begin()) {}
  ~StageSequence() {}
  
  void insert(StageInfoImpl *);
  void remove(StageInfoImpl *);
  
  StageInfoImpl *find(Stage::Index layer) { return *lookup(layer);}
  StageInfoImpl *front() { return parent_t::front();}
  StageInfoImpl *back() { return parent_t::back();}
private:
  iterator cursor;
};
 
class StageFinder
{
public:
  virtual ~StageFinder() {}
  virtual void found(StageInfoImpl *) = 0;
};

class StageQuad : public QTNode<Coord, StageInfoImpl>
{
  typedef QTNode<Coord, StageInfoImpl> parent_t;
public:
  StageQuad(const Geometry::Rectangle<Coord> &);
  StageQuad(const Geometry::Rectangle<Coord> &, StageQuad *);
  StageQuad *node(int i) { return static_cast<StageQuad *>(parent_t::node(static_cast<index>(i)));}
  void within(const Geometry::Rectangle<Coord> &, StageFinder &);
  void contains(const Geometry::Point<Coord> &, StageFinder &);
  void intersects(const Geometry::Rectangle<Coord> &, StageFinder &);
  void intersects(const Geometry::Rectangle<Coord> &, const Geometry::Polygon<Coord> &, StageFinder &);
};

class StageQuadTree : public QuadTree<Coord, StageInfoImpl>
{
  typedef QuadTree<Coord, StageInfoImpl> parent_t;
public:
  StageQuadTree() : transaction(0), operations(0) {}
  StageQuad *node() { return static_cast<StageQuad *>(parent_t::node());}

  void begin(){ transaction++;}
  void insert(StageInfoImpl *);
  void remove(StageInfoImpl *);
  void end();
  StageInfoImpl *contains(const Geometry::Point<Coord> &);
  void within(const Geometry::Rectangle<Coord> &r, StageFinder &f) { if (node()) node()->within(r, f);}
  void intersects(const Geometry::Rectangle<Coord> &r, StageFinder &f) { if (node()) node()->intersects(r, f);}
  void intersects(const Geometry::Polygon<Coord> &, StageFinder &);
private:
  unsigned transaction;
  unsigned operations;
};

class StageImpl : implements(Stage), public GraphicImpl
{
 public:
  StageImpl();
  ~StageImpl();

  virtual void request(Requisition &);

  virtual void traverse(Traversal_ptr);

  virtual void allocate(Graphic_ptr, Allocation_ptr);
  virtual void needRedraw();
  virtual void needRedrawRegion(Region_ptr);
  
  virtual Region_ptr bbox();
  virtual CORBA::Long layers() { return tree.size();}
  virtual Stage::Info layer(Stage::Index i) { return *list.find(i);}
  /*
   * begin() and end() 'lock' the stage
   * in that only after the last end() conditions for needRedraw() & needResize() are done
   */
  virtual void begin();
  virtual void end();
  virtual Stage::Info insert(Graphic_ptr, const Vertex &, const Vertex &, Index);

  void remove(const Stage::Info &);
  void reposition(const Stage::Info &, const Vertex &);
  void relayer(const Stage::Info &, Stage::Index);

private:
  void allocateChild(StageInfoImpl *, Allocation::Info &);
  void damage(StageInfoImpl *);

  StageSequence list;
  StageQuadTree tree;
  long nesting;
  RegionImpl *damage_;
  RegionImpl *bbregion;
  bool need_redraw : 1;
  bool need_resize : 1;
  typedef omni_mutex_lock Guard;
  omni_mutex myMutex;
};

#endif
