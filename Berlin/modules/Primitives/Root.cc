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

#include <Fresco/config.hh>
#include <Fresco/Traversal.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/DrawingKit3D.hh>
#include "Root.hh"

using namespace Fresco;

Root::Root(Alignment xp, Alignment yp, Alignment zp,
	   Alignment xc, Alignment yc, Alignment zc)
  : TransformAllocator(xp, yp, zp, xc, yc, zc) {}

void Root::traverse(Traversal_ptr traversal) { traversal->visit(Graphic_var(_this()));}
void Root::draw(DrawTraversal_ptr traversal)
{
  DrawingKit_var drawing = traversal->drawing();
  DrawingKit3D_var d3d = DrawingKit3D::_narrow(drawing);
  if (!CORBA::is_nil(d3d))
    {
      // initialize the 3D substate of the DrawingKit here...
    }
  TransformAllocator::traverse(traversal);
}

void Root::pick(Fresco::PickTraversal_ptr traversal)
{
  TransformAllocator::traverse(traversal);
}
