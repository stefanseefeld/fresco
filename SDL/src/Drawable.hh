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

#ifndef _SDL_Drawable_hh
#define _SDL_Drawable_hh

#include <Fresco/config.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Console.hh>

extern "C"
{
#include <SDL.h>
#include <sys/types.h>
#include <unistd.h>
}

namespace Berlin
{
  class Console;
}

namespace SDL
{
  class GLContext;

  class Drawable : public Berlin::Console::Drawable
  {
      friend class Berlin::Console;
      friend class SDL::GLContext;

    public:
      typedef Uint32 Pixel;
      
      Drawable(const char *,
           Fresco::PixelCoord = 640, Fresco::PixelCoord = 480,
           int = 3);
      virtual ~Drawable();
      
      virtual Fresco::Drawable::PixelFormat pixel_format();
      virtual Fresco::Drawable::BufferFormat buffer_format();
      virtual Fresco::PixelCoord width() const;
      virtual Fresco::PixelCoord height() const;
      virtual Fresco::PixelCoord vwidth() const;
      virtual Fresco::PixelCoord vheight() const;
      virtual Fresco::Coord resolution(Fresco::Axis a) const;
      virtual Fresco::Coord dpi(Fresco::Axis a) const;
      virtual Fresco::PixelCoord row_length() const;
  
      virtual void flush();
      virtual void flush(Fresco::PixelCoord, Fresco::PixelCoord,
             Fresco::PixelCoord, Fresco::PixelCoord);
  
      virtual void init() { }
      virtual void finish() { }
  
      // fast blits
      void blit(Fresco::PixelCoord, Fresco::PixelCoord,
        Fresco::PixelCoord, Fresco::PixelCoord,
        Fresco::PixelCoord, Fresco::PixelCoord);
      
      void blit(const Berlin::Console::Drawable &,
        Fresco::PixelCoord, Fresco::PixelCoord,
        Fresco::PixelCoord, Fresco::PixelCoord,
        Fresco::PixelCoord, Fresco::PixelCoord);
      
      void blit(const SDL::Drawable &,
        Fresco::PixelCoord, Fresco::PixelCoord,
        Fresco::PixelCoord, Fresco::PixelCoord,
        Fresco::PixelCoord, Fresco::PixelCoord);
      void blit(Fresco::Drawable_ptr,
        Fresco::PixelCoord, Fresco::PixelCoord,
        Fresco::PixelCoord, Fresco::PixelCoord,
        Fresco::PixelCoord, Fresco::PixelCoord);
      
      // SDL specific:
      SDL_Surface *surface() { return my_surface; }
      unsigned depth() { return my_depth; }
      bool need_locking() { return my_need_locking; }
      
      Pixel map(const Fresco::Color &) const;

    private:
      SDL_Surface *my_surface;
      unsigned my_width;
      unsigned my_height;
      unsigned my_depth;
      bool my_need_locking;
  };

} // namespace SDL

#endif
