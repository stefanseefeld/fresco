/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2002 Tobias Hunger <tobias@fresco.org>
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

#ifndef _SDL_Pointer_hh
#define _SDL_Pointer_hh

#include <Fresco/config.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Console.hh>
#include "Drawable.hh"
#include "Console.hh"

extern "C"
{
#include <SDL.h>
#include <sys/types.h>
#include <unistd.h>
}

namespace SDL
{

  // ---------------------------------------------------------------
  // class Pointer
  // ---------------------------------------------------------------

  class GLPointer;

  class Pointer : public Berlin::Console::Pointer
  {
      friend class nonGLPointer;
      friend class GLPointer;
    public:
      Fresco::Raster_ptr raster();
      
      void move(Fresco::Coord, Fresco::Coord);

      bool intersects(Fresco::Coord, Fresco::Coord,
              Fresco::Coord, Fresco::Coord);
      
      virtual void draw() = 0;
      virtual void save() = 0;
      virtual void restore() = 0;

    private:
      Fresco::PixelCoord my_size[2];
      Fresco::Raster_ptr my_raster;
      
      Fresco::PixelCoord my_origin[2];
      Fresco::PixelCoord my_position[2];
      Fresco::PixelCoord my_old_x, my_old_y;
      Fresco::PixelCoord my_old_size_x, my_old_size_y;
      Fresco::PixelCoord my_x, my_y;
      Fresco::Coord      my_scale[2];
  };

  class nonGLPointer : public SDL::Pointer
  {
    public:
      nonGLPointer(Drawable *, Fresco::Raster_ptr, void *);
      ~nonGLPointer();
      
      void draw();
      void save();
      void restore();
    private:
      SDL::Drawable *my_screen;
      SDL::Drawable *my_saved_area;
      SDL::Drawable *my_cursor;
  };


} // namespace SDL

#endif
