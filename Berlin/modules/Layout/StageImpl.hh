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
#ifndef _StageImpl_hh
#define _StageImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/Stage.hh>
#include <Fresco/Traversal.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Geometry.hh>
#include <list>

class StageHandleImpl;

class StageImpl : public virtual POA_Layout::Stage,
		  public GraphicImpl
{
  class Sequence;
  class QuadTree;
 public:
  StageImpl();
  ~StageImpl();

  virtual void request(Fresco::Graphic::Requisition &);

  virtual void traverse(Fresco::Traversal_ptr);

  virtual void allocate(Fresco::Tag, const Fresco::Allocation::Info &);
  virtual void need_redraw();
  virtual void need_redraw_region(Fresco::Region_ptr);
  //. relayout the children. If the bounding box changes call need_resize on the parent
  virtual void need_resize();
  
  virtual Fresco::Region_ptr bbox();
  virtual CORBA::Long layers();
  virtual Layout::StageHandle_ptr layer(Layout::Stage::Index);
  virtual void lock();
  virtual void unlock();
  virtual Layout::StageHandle_ptr insert(Fresco::Graphic_ptr, const Fresco::Vertex &, const Fresco::Vertex &, Layout::Stage::Index);
  virtual void remove(Layout::StageHandle_ptr);

  void move(StageHandleImpl *, const Fresco::Vertex &);
  void resize(StageHandleImpl *, const Fresco::Vertex &);
  void relayer(StageHandleImpl *, Layout::Stage::Index);

  virtual const char *object_name() { return "Layout/StageImpl";}
private:
  //. Return a new unique tag in the scope of this parent
  Fresco::Tag unique_tag();
  //. Return a handle to the child of the Stage that has the given tag.
  //. It returns 0 if no child has the given tag.
  StageHandleImpl *tag_to_handle(Fresco::Tag);
  //. Mark the region occupied by the given StageHandle as damaged.
  //. This is done by either merging that region with the one allready
  //. damaged or by creating a new onw
  void damage(StageHandleImpl *);

  Sequence            *_children;
  QuadTree            *_tree;
  long                 _nesting;
  Impl_var<RegionImpl> _damage;
  Impl_var<RegionImpl> _bbregion;
  bool                 _need_redraw : 1;
  bool                 _need_resize : 1;
  Prague::Mutex        _mutex;
};

class StageHandleImpl : public virtual POA_Layout::StageHandle
{
 public:
  StageHandleImpl(StageImpl *, Fresco::Graphic_ptr, Fresco::Tag, const Fresco::Vertex &, const Fresco::Vertex &, Layout::Stage::Index);
  virtual Layout::Stage_ptr parent();
  virtual Fresco::Graphic_ptr child();
  virtual void remove();
  virtual Fresco::Vertex position();
  virtual void position(const Fresco::Vertex &);
  virtual Fresco::Vertex size();
  virtual void size(const Fresco::Vertex &);
  virtual Layout::Stage::Index layer();
  virtual void layer(Layout::Stage::Index);

  const Geometry::Rectangle<Fresco::Coord> &bbox();
  void bbox(RegionImpl &);
//  private:
  //. Calculate the bounding box of the graphic in this StageHandle and
  //. stores the result in _bbox.
  void cache_bbox();
  //. The stage this StageHandle belongs into.
  StageImpl                         *_parent;
  //. The graphic forming this StageHandle.
  Fresco::Graphic_var                _child;
  //. This tag is unique for the parent-Stage and identifies this StageHandle.
  Fresco::Tag                        _tag;
  //. The position of the graphic forming this StageHandle.
  Fresco::Vertex                     _position;
  //. The size of the graphic forming this StageHandle
  Fresco::Vertex                     _size;
  //. The layer this StageHandle has.
  Layout::Stage::Index               _layer;
  //. The bounding box of the graphic of this StageHandle as calculated
  //. by cache_bbox().
  Geometry::Rectangle<Fresco::Coord> _bbox;
  //. The alignment along the x-axis.
  Fresco::Alignment                  _xalign;
  //. The alignment along the y-axis.
  Fresco::Alignment                  _yalign;
  //. A mutex for thread safety.
  Prague::Mutex                      _mutex;
};

#endif
