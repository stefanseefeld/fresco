/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Raster_hh
#define _Raster_hh

#include <Fresco/config.hh>
#include <Fresco/Raster.hh>
#include <Fresco/Transform.hh>
#include <vector>
#include <GL/gl.h>

namespace openGL
{

struct Raster
{
  Raster(Fresco::Raster_var r) : remote(Fresco::Raster::_duplicate(r)) {}
  Fresco::Raster_var remote;
  Fresco::PixelCoord width;
  Fresco::PixelCoord height;
  GLuint texture;
};

struct Texture : Raster
{
  Texture(Fresco::Raster_var);
  ~Texture();
private:
  GLuint bind(GLint components, GLenum format, unsigned char *data);
};

struct Image : Raster
{
  Image(Fresco::Raster_var);
  ~Image();
  GLfloat s, t;
private:
  GLuint bind(GLint components, GLenum format, unsigned char *data);
};

}

#endif 
