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
#include <iostream>

GLDrawable::GLDrawable(unsigned int w, unsigned int h, unsigned int d)
{
  int gt = GT_8BIT;
  switch (d)
    {
    case 4:  gt = GT_4BIT;  break;
    case 8:  gt = GT_8BIT;  break;
    case 15: gt = GT_15BIT; break;
    case 16: gt = GT_16BIT; break;
    case 24: gt = GT_24BIT; break;
    case 32: gt = GT_32BIT; break;
    }
  context = GGIMesaCreateContext();
  if (!context) cerr << "GGIMesaCreateContext() failed" << endl;
  visual = ggiOpen("display-X", 0);
  if (!visual) cerr << "ggiOpen(0) failed" << endl;
  if (ggiSetGraphMode(visual, w, h, GGI_AUTO, GGI_AUTO, gt))
    cerr << "can't set graphmode (" << w << ',' << h << ") " << d << " bpp" << endl;
  if (GGIMesaSetVisual(context, visual, GL_TRUE, GL_FALSE))
    cerr << "GGIMesaSetVisual() failed" << endl;
  clip = new RegionImpl;
  clip->_obj_is_ready(_boa());
}

GLDrawable::~GLDrawable()
{
  clip->_dispose();
  GGIMesaDestroyContext(context);
}

Coord GLDrawable::dpi(Axis axis)
{
  return 72.;
}

Coord GLDrawable::toCoord(PixelCoord p, Axis axis) { return p/dpi(axis);}
PixelCoord GLDrawable::toPixels(Coord c, Axis axis) { return static_cast<long>(c*dpi(axis));}

void GLDrawable::clipping(Region_ptr r)
{
  clip->copy(r);
  PixelCoord x, y, w, h;
  x = toPixels(clip->lower.x, xaxis);
  y = toPixels(clip->lower.y, yaxis);
  w = toPixels(clip->upper.x - clip->lower.x, xaxis);
  h = toPixels(clip->upper.y - clip->lower.y, yaxis);
//   glViewport(x, y, w, h);
}

Region_ptr GLDrawable::clipping()
{
  return clip->_this();
}
