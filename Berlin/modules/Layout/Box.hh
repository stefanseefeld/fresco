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
#ifndef _Box_hh
#define _Box_hh

#include <Berlin/PolyGraphic.hh>
#include <Layout/LayoutManager.hh>

class Box : public PolyGraphic
{
public:
  Box(LayoutManager *);
  virtual ~Box();

  virtual void request(Warsaw::Graphic::Requisition &);
  virtual void extension(const Warsaw::Allocation::Info &, Warsaw::Region_ptr);

  virtual void traverse(Warsaw::Traversal_ptr);
  virtual void need_resize();
  virtual void need_resize(Warsaw::Tag);
  virtual void allocate(Warsaw::Tag, const Warsaw::Allocation::Info &);

  virtual const char* object_name() { return _obj_name;}

protected:
  LayoutManager::Allocations  children_allocations(Warsaw::Region_ptr);
  void traverse_with_allocation(Warsaw::Traversal_ptr, Warsaw::Region_ptr);
  void traverse_without_allocation(Warsaw::Traversal_ptr);
  
  //. The fixed class name of this object, used for constructing name strings
  const char *_box_name;
  //. The changing object name. Note that this is allocated as a buffer and
  //. strcpy'd into, since it may change over the course of a method but cannot
  //. be deleted in the scope of a Trace guard object
  char *_obj_name;
private:
  LayoutManager               *_layout;
  bool                         _requested;
  Warsaw::Graphic::Requisition _requisition;

  //. The size of the allocation cache
  CORBA::Long                  _cache_size;
  //. A cache of children allocations to speed traversals
  LayoutManager::Allocations   _cache_allocations;
};

class BoxAlignElements : public Box
{
public:
  BoxAlignElements(LayoutManager *, Warsaw::Axis, Warsaw::Alignment);
  virtual ~BoxAlignElements();

  virtual void append_graphic(Warsaw::Graphic_ptr);
  virtual void prepend_graphic(Warsaw::Graphic_ptr);
private:
  Warsaw::Axis axis;
  Warsaw::Alignment alignment;
};

class HBox : public Box
{
public:
  HBox() : Box(new LayoutSuperpose(new LayoutTile(Warsaw::xaxis), new LayoutAlign(Warsaw::yaxis), new LayoutAlign(Warsaw::zaxis))) {}
};

class VBox : public Box
{
public:
  VBox() : Box(new LayoutSuperpose(new LayoutTile(Warsaw::yaxis), new LayoutAlign(Warsaw::xaxis), new LayoutAlign(Warsaw::zaxis))) {}
};

class HBoxFirstAligned : public Box
{
public:
  HBoxFirstAligned() : Box(new LayoutSuperpose(new LayoutTileFirstAligned(Warsaw::xaxis), new LayoutAlign(Warsaw::yaxis))) {}
};

class VBoxFirstAligned : public Box
{
public:
  VBoxFirstAligned() : Box(new LayoutSuperpose(new LayoutTileReversedFirstAligned(Warsaw::yaxis), new LayoutAlign(Warsaw::xaxis))) {}
};

class HBoxAlignElements : public BoxAlignElements
{
public:
  HBoxAlignElements(double align)
    : BoxAlignElements(new LayoutSuperpose(new LayoutTile(Warsaw::xaxis), new LayoutAlign(Warsaw::yaxis)), Warsaw::yaxis, align) {}
};

class VBoxAlignElements : public BoxAlignElements
{
public:
  VBoxAlignElements(double align)
    : BoxAlignElements(new LayoutSuperpose(new LayoutTile(Warsaw::yaxis), new LayoutAlign(Warsaw::xaxis)), Warsaw::xaxis, align) {}
};

class Overlay : public Box
{
public:
  Overlay() : Box(new LayoutSuperpose(new LayoutAlign(Warsaw::xaxis), new LayoutAlign(Warsaw::yaxis))) {}
};

#endif
