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

#ifndef _SDL_Extension_hh
#define _SDL_Extension_hh

#include <Fresco/config.hh>
#include <Berlin/Console.hh>
#include <Berlin/Console/Renderer.hh>
#include <Berlin/Console/DirectBuffer.hh>
#include <Berlin/Console/GLContext.hh>
#include "Console.hh"
#include "Drawable.hh"

namespace SDL
{

  class Drawable;

  // ---------------------------------------------------------------
  // class Extension
  // ---------------------------------------------------------------

  class Extension : virtual public Console::Drawable::Extension
  {
    public:
      Extension() : my_drawable(0) { }
      
      virtual void attach(Berlin::Console::Drawable *);
      
      SDL::Drawable * drawable()
      { return my_drawable; }
    private:
      SDL::Drawable * my_drawable;
  };

  // ---------------------------------------------------------------
  // class Renderer
  // ---------------------------------------------------------------

  class Renderer : public Extension,
           virtual public Berlin::Console_Extension::Renderer
  {
    public:
      Renderer();
      
      virtual void set_color(const Fresco::Color &);
      virtual void draw_pixel(Fresco::PixelCoord, Fresco::PixelCoord);
      virtual void draw_hline(Fresco::PixelCoord, Fresco::PixelCoord,
                  Fresco::PixelCoord);
      virtual void draw_vline(Fresco::PixelCoord, Fresco::PixelCoord,
                  Fresco::PixelCoord);
      virtual void draw_line(Fresco::PixelCoord, Fresco::PixelCoord,
                 Fresco::PixelCoord, Fresco::PixelCoord);
      virtual void draw_box(Fresco::PixelCoord, Fresco::PixelCoord,
                Fresco::PixelCoord, Fresco::PixelCoord);
    private:
      void put_pixel(Fresco::PixelCoord, Fresco::PixelCoord);
      
      SDL::Drawable::Pixel my_color;
  };

  // ---------------------------------------------------------------
  // class DirectBuffer
  // ---------------------------------------------------------------
 
  class DirectBuffer : public Extension,
               virtual public Berlin::Console_Extension::DirectBuffer
  {
    public:
      DirectBuffer();
      void attach(Berlin::Console::Drawable *);
      virtual Guard read_buffer();
      virtual Guard write_buffer();
  };

} // namespace SDL

#endif
