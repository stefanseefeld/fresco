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

#ifndef _SDL_Drawable_hh
#define _SDL_Drawable_hh

#include <Warsaw/config.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Console.hh>

extern "C"
{
#include <SDL.h>
#include <sys/types.h>
#include <unistd.h>
}





namespace SDL
{

class Console;
class GLContext;

class Drawable : public ::Console::Drawable
{
  friend class Console;
  friend class GLContext;

public:
  typedef Uint32 Pixel;

  Drawable(const char *,
              Warsaw::PixelCoord = 640, Warsaw::PixelCoord = 480,
              Warsaw::PixelCoord = 3);
  virtual ~Drawable();

  virtual Warsaw::Drawable::PixelFormat pixel_format();
  virtual Warsaw::Drawable::BufferFormat buffer_format();
  virtual Warsaw::PixelCoord width() const;
  virtual Warsaw::PixelCoord height() const;
  virtual Warsaw::PixelCoord vwidth() const;
  virtual Warsaw::PixelCoord vheight() const;
  virtual Warsaw::Coord resolution(Warsaw::Axis a) const;
  virtual Warsaw::Coord dpi(Warsaw::Axis a) const;
  virtual Warsaw::PixelCoord row_length() const;
  
  virtual void flush();
  virtual void flush(Warsaw::PixelCoord, Warsaw::PixelCoord,
                     Warsaw::PixelCoord, Warsaw::PixelCoord);
  
  virtual void init() { }
  virtual void finish() { }
  
  // fast blits
  void blit(Warsaw::PixelCoord, Warsaw::PixelCoord,
            Warsaw::PixelCoord, Warsaw::PixelCoord,
            Warsaw::PixelCoord, Warsaw::PixelCoord);

  void blit(const ::Console::Drawable &,
            Warsaw::PixelCoord, Warsaw::PixelCoord,
            Warsaw::PixelCoord, Warsaw::PixelCoord,
            Warsaw::PixelCoord, Warsaw::PixelCoord);
  
  void blit(const SDL::Drawable &,
            Warsaw::PixelCoord, Warsaw::PixelCoord,
            Warsaw::PixelCoord, Warsaw::PixelCoord,
            Warsaw::PixelCoord, Warsaw::PixelCoord);
  void blit(Warsaw::Drawable_ptr,
            Warsaw::PixelCoord, Warsaw::PixelCoord,
            Warsaw::PixelCoord, Warsaw::PixelCoord,
            Warsaw::PixelCoord, Warsaw::PixelCoord);
  
  // SDL specific:
  SDL_Surface *surface() { return _surface; }
  unsigned depth() { return _depth; }
  unsigned width() { return _width; }
  unsigned height() { return _height; }
  bool need_locking() { return _need_locking; }

  Pixel map(const Warsaw::Color &) const;

private:
  SDL_Surface *_surface;
  unsigned     _width;
  unsigned     _height;
  unsigned     _depth;
  bool         _need_locking;
};

}; // namespace SDL

#endif
