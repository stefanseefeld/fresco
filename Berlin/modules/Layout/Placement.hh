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
#ifndef _Placement_hh
#define _Placement_hh

#include <Berlin/ImplVar.hh>
#include <Berlin/MonoGraphic.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/TransformImpl.hh>

class LayoutManager;
class RegionImpl;

class Placement : public MonoGraphic
{
public:
  Placement(LayoutManager *);
  virtual ~Placement();

  virtual void request(Fresco::Graphic::Requisition &);

  virtual void traverse(Fresco::Traversal_ptr);

  virtual void allocate(Fresco::Tag, const Fresco::Allocation::Info &);

  virtual const char *object_name() { return _name;}

private:
  LayoutManager       *_layout;
  Impl_var<RegionImpl> _region;
  char                *_name;
};

class LayoutLayer : public MonoGraphic
{
public:
  LayoutLayer(Fresco::Graphic_ptr, Fresco::Graphic_ptr, Fresco::Graphic_ptr);
  virtual ~LayoutLayer();
  virtual void traverse(Fresco::Traversal_ptr);

  virtual const char* object_name() { return "LayoutLayer";}

private:
  Fresco::Graphic_var _under;
  Fresco::Graphic_var _over;
};

#endif
