/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 graydon hoare <graydon@fresco.org>
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

#include "Raster.hh"

using namespace Fresco;
using namespace libArt;

libArt::Raster::Raster(Raster_var r)
  : remote(Fresco::Raster::_duplicate(r)) 
{  
  Fresco::Raster::Info info = remote->header();
  Fresco::Raster::ColorSeq_var colors;
  Fresco::Raster::Index lower, upper;
  lower.x = lower.y = 0;
  upper.x = info.width, upper.y = info.height;
  remote->store_pixels(lower, upper, colors);
  int width = (int)(info.width);
  int height = (int)(info.height);
  pixels = new art_u8[4*width*height];
  for (int y = height - 1; y >= 0; y--) {
    for (int x = 0; x != width; x++) {
      pixels[4*(y*width+x)] = (int)(colors[y * width + x].blue * 0xff);
      pixels[4*(y*width+x)+1] = (int)(colors[y * width + x].green * 0xff);
      pixels[4*(y*width+x)+2] = (int)(colors[y * width + x].red * 0xff);
      pixels[4*(y*width+x)+3] = (int)(colors[y * width + x].alpha * 0xff);
    }
  }
  pixbuf = art_pixbuf_new_const_rgba (pixels, width, height, width * 4);
}

libArt::Raster::~Raster()
{
  art_pixbuf_free (pixbuf);
  delete[] pixels;
}
