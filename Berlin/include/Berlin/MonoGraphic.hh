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
#ifndef _MonoGraphic_hh
#define _MonoGraphic_hh

#include <Berlin/GraphicImpl.hh>
#include <vector>

class MonoGraphicOffset;

typedef vector<MonoGraphicOffset *> MonoGraphicOffsetList;

class MonoGraphic : public GraphicImpl
{
public:
  MonoGraphic();
  virtual ~MonoGraphic();

//   virtual StyleContext_ptr style();
//   virtual void style(StyleContext_ptr _p);
  virtual Transform_ptr transformation();
  virtual void request(Requisition &);
  virtual void extension(const AllocationInfo &, Region_ptr);
  virtual void shape(Region_ptr);
  virtual void traverse(Traversal_ptr);
  virtual Graphic_ptr body();
  virtual void body(Graphic_ptr);
  virtual void append(Graphic_ptr);
  virtual void prepend(Graphic_ptr);
  virtual GraphicOffset_ptr firstOffset();
  virtual GraphicOffset_ptr lastOffset();
  virtual void allocateChild(Graphic::AllocationInfo& a);
//   virtual void damages(DamageInfoSeq &);
//   virtual bool restore_trail(Traversal_ptr);
protected:
  MonoGraphicOffset *offset;
};

class MonoGraphicOffset : public virtual _sk_GraphicOffset
{
  friend class MonoGraphic;
public:
  MonoGraphicOffset(MonoGraphic * = 0);
  virtual ~MonoGraphicOffset();

  virtual Graphic_ptr Parent();
  virtual Graphic_ptr Child();
  virtual void allocations(Graphic::AllocationInfoSeq &);
  virtual void insert(Graphic_ptr);
  virtual void replace(Graphic_ptr);
  virtual GraphicOffset_ptr next();
  virtual GraphicOffset_ptr previous();
  virtual void remove();
  virtual void needResize();
  virtual void traverse(Traversal_ptr);
//   virtual void visit_trail(Traversal_ptr);
  virtual void allocateChild(Graphic::AllocationInfo &);
protected:
  MonoGraphic *parent;
  Graphic_ptr child;
//   Tag remove_tag;
};

#endif /* _MonoGraphic_hh */
