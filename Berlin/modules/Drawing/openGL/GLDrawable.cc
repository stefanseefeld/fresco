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
#include "Drawing/openGL/GLDrawable.hh"
#include "Berlin/RegionImpl.hh"

GLDrawable::GLDrawable()
{
  context = GGIMesaCreateContext();
}

GLDrawable::GLDrawable(Drawable_ptr)
{
  context = GGIMesaCreateContext();
}

GLDrawable::~GLDrawable()
{
  GGIMesaDestroyContext(context);
}

Coord GLDrawable::toCoord(PixelCoord, Axis) { return 1./72.;}
PixelCoord GLDrawable::toPixels(Coord, Axis) { return 72;}

void GLDrawable::clipping(Region_ptr r)
{
  Vertex v1, v2;
  r->bounds(v1, v2);
  clip.x = toPixels(v1.x, xaxis);
  clip.y = toPixels(v1.y, yaxis);
  clip.w = toPixels(v2.x - v1.x, xaxis);
  clip.h = toPixels(v2.y - v1.y, yaxis);
//   glViewport(clip.x, clip.y, clip.w, clip.h);
}

Region_ptr GLDrawable::clipping()
{
  RegionImpl *r = new RegionImpl;
  r->lower.x = toCoord(clip.x, xaxis);
  r->lower.y = toCoord(clip.y, yaxis);
  r->upper.x = toCoord(clip.x + clip.w, xaxis);
  r->upper.y = toCoord(clip.y + clip.h, yaxis);
  return r;
}
