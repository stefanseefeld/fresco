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

#include "Drawing/openGL/GLDrawingKit.hh"
#include "Drawing/openGL/GLDrawable.hh"
#include "Drawing/openGL/GLPencil.hh"

GLDrawingKit::GLDrawingKit()
{
}

Drawable_ptr GLDrawingKit::getdrawable()
{
  GLDrawable *drawable = new GLDrawable;
  drawable->_obj_is_ready(_boa());
  return drawable->_this();
}

Pencil_ptr GLDrawingKit::solidPencil(Drawable_ptr d)
{
  // make sure 'd' is an openGL target
  GLDrawable *drawable = new GLDrawable(d);
  drawable->_obj_is_ready(_boa());
  GLPencil *pencil = new GLPencil(drawable);
  pencil->_obj_is_ready(_boa());
  return pencil->_this();
}
