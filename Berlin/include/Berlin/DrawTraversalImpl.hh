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
#ifndef _DrawTraversal_hh
#define _DrawTraversal_hh

#include <Warsaw/config.hh>
#include <Warsaw/Traversal.hh>
#include <Warsaw/DrawingKit.hh>
#include <Berlin/TraversalImpl.hh>
#include <vector>

class DrawTraversalImpl : implements(DrawTraversal), virtual public TraversalImpl
{
public:
  DrawTraversalImpl(DrawingKit_ptr, Region_ptr);
  DrawTraversalImpl(const DrawTraversalImpl &);
  ~DrawTraversalImpl();
  CORBA::Boolean intersects();
  void visit(Graphic_ptr);
  order direction() { return up;}
  CORBA::Boolean ok() { return true;}
  DrawingKit_ptr kit();
protected: // private: ??
  DrawingKit_var drawingkit;
  Drawable_var drawable;
  Region_var clipping;
};

#endif /* _DrawTraversalImpl_hh */
