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
#ifndef _StageImpl_hh
#define _StageImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Stage.hh>
#include <Warsaw/Traversal.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Geometry.hh>
#include <Prague/Sys/Thread.hh>
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

  virtual void request(Warsaw::Graphic::Requisition &);

  virtual void traverse(Warsaw::Traversal_ptr);

  virtual void allocate(Warsaw::Tag, const Warsaw::Allocation::Info &);
  virtual void need_redraw();
  virtual void need_redraw_region(Warsaw::Region_ptr);
  //. relayout the children. If the bounding box changes call need_resize on the parent
  virtual void need_resize();
  
  virtual Warsaw::Region_ptr bbox();
  virtual CORBA::Long layers();
  virtual Layout::StageHandle_ptr layer(Layout::Stage::Index);
  virtual void begin();
  virtual void end();
  virtual Layout::StageHandle_ptr insert(Warsaw::Graphic_ptr, const Warsaw::Vertex &, const Warsaw::Vertex &, Layout::Stage::Index);
  virtual void remove(Layout::StageHandle_ptr);

  void move(StageHandleImpl *, const Warsaw::Vertex &);
  void resize(StageHandleImpl *, const Warsaw::Vertex &);
  void relayer(StageHandleImpl *, Layout::Stage::Index);
private:
  //. Return a new unique tag in the scope of this parent
  Warsaw::Tag unique_tag();
  //. Return a handle to the child of the Stage that has the given tag.
  //. It returns 0 if no child has the given tag.
  StageHandleImpl *tag_to_handle(Warsaw::Tag);
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
  StageHandleImpl(StageImpl *, Warsaw::Graphic_ptr, Warsaw::Tag, const Warsaw::Vertex &, const Warsaw::Vertex &, Layout::Stage::Index);
  virtual Layout::Stage_ptr parent();
  virtual Warsaw::Graphic_ptr child();
  virtual void remove();
  virtual Warsaw::Vertex position();
  virtual void position(const Warsaw::Vertex &);
  virtual Warsaw::Vertex size();
  virtual void size(const Warsaw::Vertex &);
  virtual Layout::Stage::Index layer();
  virtual void layer(Layout::Stage::Index);

  const Geometry::Rectangle<Warsaw::Coord> &bbox();
  void bbox(RegionImpl &);
 private:
  //. Calculate the bounding box of the graphic in this StageHandle and
  //. stores the result in _bbox.
  void cache_bbox();
  //. The stage this StageHandle belongs into.
  StageImpl                         *_parent;
  //. The graphic forming this StageHandle.
  Warsaw::Graphic_var                _child;
  //. This tag is unique for the parent-Stage and identifies this StageHandle.
  Warsaw::Tag                        _tag;
  //. The position of the graphic forming this StageHandle.
  Warsaw::Vertex                     _position;
  //. The size of the graphic forming this StageHandle
  Warsaw::Vertex                     _size;
  //. The layer this StageHandle has.
  Layout::Stage::Index               _layer;
  //. The bounding box of the graphic of this StageHandle as calculated
  //. by cache_bbox().
  Geometry::Rectangle<Warsaw::Coord> _bbox;
  //. The alignment along the x-axis.
  Warsaw::Alignment                  _xalign;
  //. The alignment along the y-axis.
  Warsaw::Alignment                  _yalign;
  //. A mutex for thread safety.
  Prague::Mutex                      _mutex;
};

#endif
