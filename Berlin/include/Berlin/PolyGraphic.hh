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
#ifndef _PolyGraphic_hh
#define _PolyGraphic_hh

#include <Berlin/GraphicImpl.hh>
#include <Berlin/Pool.hh>
#include <vector>

class PolyGraphicOffset;

typedef vector<PolyGraphicOffset *> PolyGraphicOffsetList;

class PolyGraphic : public GraphicImpl
{
  friend class PolyGraphicOffset;
public:
  PolyGraphic();
  virtual ~PolyGraphic();

//   virtual StyleContext_ptr style();
//   virtual void style(StyleContext_ptr _p);
  virtual void append(Graphic_ptr);
  virtual void prepend(Graphic_ptr);
  virtual GraphicOffset_ptr firstOffset();
  virtual GraphicOffset_ptr lastOffset();
  virtual PolyGraphicOffset *newOffset(long, Graphic_ptr);
  Graphic::Requisition *childrenRequests();
  virtual void allocateChild(long, Graphic::AllocationInfo &);
//   virtual void damages(DamageInfoSeq &);
  virtual void needResize();
  virtual void needResize(long);
//   virtual bool restore_trail(Traversal_ptr);
// protected:
  void updateOffsets(long, long);
  PolyGraphicOffsetList children;
  static Pool<Requisition> pool;
};

class PolyGraphicOffset : implements(GraphicOffset), virtual public CloneableImpl
{
//   friend class PolyGraphic;
public:
  PolyGraphicOffset(PolyGraphic *, long, Graphic_ptr);
  virtual ~PolyGraphicOffset();

  virtual Graphic_ptr Parent();
  virtual Graphic_ptr Child();
  virtual void allocations(Collector_ptr);
  virtual void insert(Graphic_ptr);
  virtual void replace(Graphic_ptr);
  virtual GraphicOffset_ptr next();
  virtual GraphicOffset_ptr previous();
  virtual void remove();
  virtual void needResize();
  virtual void traverse(Traversal_ptr);
//   virtual void visit_trail(Traversal_ptr);
  virtual void allocateChild(Graphic::AllocationInfo &);
// protected:
  GraphicOffset_ptr offset(long);
  PolyGraphic *parent;
  long index;
  Graphic_ptr child;
};

#endif /* _PolyGraphic_hh */
