/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@fresco.org> 
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

#ifndef _Root_hh
#define _Root_hh

#include <Fresco/config.hh>
#include <Fresco/DrawingKit3D.hh>
#include <Berlin/Allocator.hh>

//. Root is supposed to be the root node in a 3D scene graph hierarchy.
//. It therefor switches on all the necessary flags in the DrawingKit
//. that are necessary only when rendering 3D
class Root : public TransformAllocator
{
public:
  Root(Fresco::Alignment, Fresco::Alignment, Fresco::Alignment, Fresco::Alignment, Fresco::Alignment, Fresco::Alignment);
  virtual void traverse(Fresco::Traversal_ptr);
  virtual void draw(Fresco::DrawTraversal_ptr);
  virtual void pick(Fresco::PickTraversal_ptr);
};

#endif
