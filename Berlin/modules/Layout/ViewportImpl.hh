/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _ViewportImpl_hh
#define _ViewportImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Viewport.hh>
#include <Fresco/BoundedRange.hh>
#include <Berlin/ViewImpl.hh>
#include <Berlin/MonoGraphic.hh>
#include <Berlin/RefCountVar.hh>

class RegionImpl;

class ViewportImpl : public virtual POA_Layout::Viewport,
		     public virtual ViewImpl,
		     public MonoGraphic
{
  class Adjustment;
 public:
  ViewportImpl();
  ~ViewportImpl();
  virtual void body(Fresco::Graphic_ptr);
  virtual Fresco::Graphic_ptr body() { return MonoGraphic::body();}

  virtual Fresco::Transform_ptr transformation();
  virtual void request(Fresco::Graphic::Requisition &);

  virtual void traverse(Fresco::Traversal_ptr);
  virtual void draw(Fresco::DrawTraversal_ptr);
  virtual void pick(Fresco::PickTraversal_ptr);

  virtual void need_resize();

  virtual Fresco::BoundedRange_ptr adjustment(Fresco::Axis);

  virtual void update(const CORBA::Any &);

  virtual const char *object_name() { return "Layout/ViewportImpl";}

private:
  virtual void activate_composite();
  void allocate_child(Fresco::Allocation::Info &);
  void cache_requisition();
  void cache_allocation(Fresco::Region_ptr);
  void body_allocation(Fresco::Region_ptr, RegionImpl *);
  void scroll_transform(Fresco::Transform_ptr);

  Fresco::BoundedRange::Settings     _settings[2];
  RefCount_var<Fresco::BoundedRange> _xadjustment;
  RefCount_var<Fresco::BoundedRange> _yadjustment;
  bool                               _requested;
  Fresco::Graphic::Requisition       _requisition;
};

#endif
