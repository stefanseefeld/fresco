/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _Viewport_hh
#define _Viewport_hh

#include <Warsaw/config.hh>
#include <Warsaw/Viewport.hh>
#include <Warsaw/BoundedRange.hh>
#include <Berlin/MonoGraphic.hh>

class RegionImpl;

class ViewportImpl : public virtual POA_Warsaw::Viewport,
		     public MonoGraphic
{
  class Adjustment;
 public:
  ViewportImpl();
  ~ViewportImpl();
  void attachAdjustments();
  virtual void body(Warsaw::Graphic_ptr);
  virtual Warsaw::Graphic_ptr body() { return MonoGraphic::body();}

  virtual Warsaw::Transform_ptr transformation();
  virtual void request(Warsaw::Graphic::Requisition &);

  virtual void traverse(Warsaw::Traversal_ptr);
  virtual void draw(Warsaw::DrawTraversal_ptr);
  virtual void pick(Warsaw::PickTraversal_ptr);

  virtual void needResize();

  virtual Warsaw::BoundedRange_ptr adjustment(Warsaw::Axis);

  virtual void update(const CORBA::Any &);

protected:
  void allocateChild(Warsaw::Allocation::Info &);
  void cacheRequisition();
  void cacheAllocation(Warsaw::Region_ptr);
  void bodyAllocation(Warsaw::Region_ptr, RegionImpl *);
  void scrollTransform(Warsaw::Transform_ptr);

  Warsaw::BoundedRange::Settings settings[2];
  Adjustment *xadjustment;
  Adjustment *yadjustment;
  bool        requested;
  Warsaw::Graphic::Requisition requisition;
};

#endif
