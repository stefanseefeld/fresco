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
#ifndef _openGL_Raster_hh
#define _openGL_Raster_hh

#include <Fresco/config.hh>
#include <Fresco/Raster.hh>
#include <Fresco/Transform.hh>
#include <Berlin/Console/GLContext.hh>
#include <vector>
#include <GL/gl.h>

namespace Berlin
{
  namespace DrawingKit
  {
    namespace openGL
    {

      class Texture
      {
    public:
      Texture(Fresco::Raster_var);
      ~Texture();
      void activate(Console_Extension::GLContext *);
      Fresco::Raster_var remote;
      Fresco::PixelCoord width;
      Fresco::PixelCoord height;
      Fresco::PixelCoord texgen_w;
      Fresco::PixelCoord texgen_h;
      GLuint texture;
    private:
      class Activate;
      class Bind;
      class Delete;
      bool my_is_bound;
      Console_Extension::GLContext *my_glcontext;
      std::vector<unsigned char> my_data;
      };


      class Image
      {
    public:
      Image(Fresco::Raster_var r);
      ~Image();
      void activate(Console_Extension::GLContext *);
      GLfloat s, t;
      Fresco::Raster_var remote;
      Fresco::PixelCoord width;
      Fresco::PixelCoord height;
      Fresco::PixelCoord texgen_w;
      Fresco::PixelCoord texgen_h;
      GLuint texture;
    private:
      class Activate;
      class Bind;
      class Delete;
      bool my_is_bound;
      Console_Extension::GLContext *my_glcontext;
      std::vector<unsigned char> my_data;
      };
      
    } // namespace
  } // namespace
} // namespace

#endif 
