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

#include "Warsaw/config.hh"
#include "Warsaw/Stage.hh"
#include "Warsaw/Traversal.hh"
#include "Berlin/GraphicImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/QuadTree.hh"
#include "Berlin/Thread.hh"
#include <list>

class StageImpl;

class StageHandleImpl : implements(StageHandle)
{
 public:
  StageHandleImpl(StageImpl *, Graphic_ptr, const Vertex &, const Vertex &, Stage::Index);
  virtual Vertex position() { MutexGuard guard(mutex); return p;}
  virtual void position(const Vertex &);
  virtual Vertex size() { MutexGuard guard(mutex); return s;}
  virtual void size(const Vertex &);
  virtual Stage::Index layer() { MutexGuard guard(mutex); return l;}
  virtual void layer(Stage::Index);

  const Geometry::Rectangle<Coord> &bbox() { return boundingbox;}
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
//  private:
  void cacheBBox();
  StageImpl *parent;
  Graphic_var child;
  Vertex p;
  Vertex s;
  Stage::Index l;
  Geometry::Rectangle<Coord> boundingbox;
  Alignment xalign;
  Alignment yalign;
  Mutex mutex;
};

class StageSequence : public list<StageHandleImpl *>
{
  typedef list<StageHandleImpl *> parent_t;
  iterator lookup(Stage::Index layer);
public:
  StageSequence() : cursor(begin()) {}
  ~StageSequence() {}
  
  void insert(StageHandleImpl *);
  void remove(StageHandleImpl *);
  
  StageHandleImpl *find(Stage::Index layer) { return *lookup(layer);}
  StageHandleImpl *front() { return parent_t::front();}
  StageHandleImpl *back() { return parent_t::back();}
private:
  iterator cursor;
};
 
class StageFinder
{
public:
  virtual ~StageFinder() {}
  virtual void found(StageHandleImpl *) = 0;
};

class StageQuad : public QTNode<Coord, StageHandleImpl *>
{
  typedef QTNode<Coord, StageHandleImpl *> parent_t;
public:
  StageQuad(const Geometry::Rectangle<Coord> &);
  StageQuad(const Geometry::Rectangle<Coord> &, StageQuad *);
  StageQuad *node(int i) { return static_cast<StageQuad *>(parent_t::node(static_cast<index>(i)));}
  void within(const Geometry::Rectangle<Coord> &, StageFinder &);
  void contains(const Geometry::Point<Coord> &, StageFinder &);
  void intersects(const Geometry::Rectangle<Coord> &, StageFinder &);
  void intersects(const Geometry::Rectangle<Coord> &, const Geometry::Polygon<Coord> &, StageFinder &);
};

class StageQuadTree : public QuadTree<Coord, StageHandleImpl *>
{
  typedef QuadTree<Coord, StageHandleImpl *> parent_t;
public:
  StageQuadTree() : transaction(0), operations(0) {}
  StageQuad *node() { return static_cast<StageQuad *>(parent_t::node());}

  void begin(){ transaction++;}
  void insert(StageHandleImpl *);
  void remove(StageHandleImpl *);
  void end();
  StageHandleImpl *contains(const Geometry::Point<Coord> &);
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
  virtual void needResize();
  //. relayout the children. If the bounding box changes call needResize on the parent
  
  virtual Region_ptr bbox();
  virtual CORBA::Long layers() { return tree.size();}
  virtual StageHandle_ptr layer(Stage::Index);
  /*
   * begin() and end() 'lock' the stage
   * in that only after the last end() conditions for needRedraw() & needResize() are done
   */
  virtual void begin();
  virtual void end();
  virtual StageHandle_ptr insert(Graphic_ptr, const Vertex &, const Vertex &, Index);
  virtual void remove(StageHandle_ptr);

  void reposition(StageHandleImpl *, const Vertex &);
  void resize(StageHandleImpl *, const Vertex &);
  void relayer(StageHandleImpl *, Stage::Index);
private:
  void allocateChild(StageHandleImpl *, Allocation::Info &);
  void damage(StageHandleImpl *);

  StageSequence list;
  StageQuadTree tree;
  long nesting;
  RegionImpl *damage_;
  RegionImpl *bbregion;
  bool need_redraw : 1;
  bool need_resize : 1;
  Mutex childMutex;
};

#endif
