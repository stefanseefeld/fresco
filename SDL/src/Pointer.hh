/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2002 Tobias Hunger <tobias@fresco.org>
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

#ifndef _SDL_Pointer_hh
#define _SDL_Pointer_hh

#include <Warsaw/config.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Console.hh>
#include <Console/SDL/Drawable.hh>

#include <Console/SDL/Console.hh>

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

class Pointer : public ::Console::Pointer
{
  friend class nonGLPointer;
  friend class GLPointer;
public:
  Warsaw::Raster_ptr raster();

  void move(Warsaw::Coord, Warsaw::Coord);

  bool intersects(Warsaw::Coord, Warsaw::Coord,
		  Warsaw::Coord, Warsaw::Coord);

  virtual void draw() = 0;
  virtual void save() = 0;
  virtual void restore() = 0;

private:
  Warsaw::PixelCoord _size[2];
  Warsaw::Raster_ptr _raster;

  Warsaw::PixelCoord _origin[2];
  Warsaw::PixelCoord _position[2];
  Warsaw::PixelCoord _old_x, _old_y;
  Warsaw::PixelCoord _x, _y;
  Warsaw::Coord      _scale[2];
};



class nonGLPointer : public SDL::Pointer
{
public:
  nonGLPointer(Drawable *, Warsaw::Raster_ptr);
  ~nonGLPointer();

  void draw();
  void save();
  void restore();
private:
  SDL::Drawable    * _screen;
  SDL::Drawable    * _saved_area;
  SDL::Drawable    * _cursor;
};


}; // namespace SDL

#endif