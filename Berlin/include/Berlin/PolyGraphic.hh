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
#include <Berlin/Thread.hh>
#include <Berlin/Pool.hh>
#include <vector>

class PolyGraphic : virtual public GraphicImpl
{
  typedef vector<Graphic_var> clist_t;
public:
  PolyGraphic();
  virtual ~PolyGraphic();

  virtual void append(Graphic_ptr);
  virtual void prepend(Graphic_ptr);

  virtual void allocate(Graphic_ptr, Allocation_ptr);
  virtual void needResize();
  virtual void needResize(long);
protected:
  long numChildren();
  long findChild(Graphic_ptr);
  Graphic::Requisition *childrenRequests();
  virtual void allocateChild(long, Allocation::Info &);
  static Pool<Requisition> pool;
  clist_t children;
  Mutex childMutex;
};

#endif /* _PolyGraphic_hh */
