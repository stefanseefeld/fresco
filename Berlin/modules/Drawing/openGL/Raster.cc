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

#include "Drawing/openGL/GLRaster.hh"
#include <GL/glu.h>

GLRaster::GLRaster(Raster_var r)
  : remote(r)
{
  Raster::Info info = remote->header();
  Raster::ColorSeq_var pixels;
  Raster::Index lower, upper;
  lower.x = lower.y = 0;
  upper.x = info.width, upper.y = info.height;
  remote->storePixels(lower, upper, pixels);
  width = info.width;
  height = info.height;
  data.resize(4*width*height);
  vector<char>::iterator pixel = data.begin();
  for (int y = height - 1; y >= 0; y--)
    for (int x = 0; x != width; x++)
      {
	Color &color = pixels[y * info.width + x];
	*pixel++ = static_cast<char>(color.red * 256);
	*pixel++ = static_cast<char>(color.green * 256);
	*pixel++ = static_cast<char>(color.blue * 256);
	*pixel++ = static_cast<char>(color.alpha * 256);
      }
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data.begin());
//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.begin());
}

GLRaster::~GLRaster()
{
  glDeleteTextures(1, &texture);
}
