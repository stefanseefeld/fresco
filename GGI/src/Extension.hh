/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _GGI_Extension_hh
#define _GGI_Extension_hh

#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Berlin/Console/Renderer.hh>
#include <Berlin/Console/DirectBuffer.hh>
#include <Berlin/Console/SHMDrawableFactory.hh>
#include <Berlin/Console/GGIDrawableFactory.hh>
#include "Console.hh"

namespace GGI
{

  class Extension : virtual public Berlin::Console::Drawable::Extension
  {
    public:
      Extension() : my_drawable(0) { }
      virtual void attach(Berlin::Console::Drawable *drawable);
      Drawable *drawable() { return my_drawable;}
    private:
      Drawable *my_drawable;
  };

  class Renderer : public Extension,
           virtual public Berlin::Console_Extension::Renderer
  {
    public:
      Renderer() { }
      virtual void set_color(const Fresco::Color &);
      virtual void draw_pixel(Fresco::PixelCoord x, Fresco::PixelCoord y);
      virtual void draw_hline(Fresco::PixelCoord x, Fresco::PixelCoord y,
                  Fresco::PixelCoord w);
      virtual void draw_vline(Fresco::PixelCoord x, Fresco::PixelCoord y,
                  Fresco::PixelCoord h);
      virtual void draw_line(Fresco::PixelCoord x, Fresco::PixelCoord y,
                 Fresco::PixelCoord w, Fresco::PixelCoord h);
      virtual void draw_box(Fresco::PixelCoord x, Fresco::PixelCoord y,
                Fresco::PixelCoord w, Fresco::PixelCoord h);
  };

  class DirectBuffer : public Extension,
               virtual public Berlin::Console_Extension::DirectBuffer
  {
    public:
      DirectBuffer() { }
      virtual Guard read_buffer();
      virtual Guard write_buffer();
  };

  class SHMDrawableFactory :
    virtual public Berlin::Console_Extension::SHMDrawableFactory
  {
    public:
      virtual Console::Drawable *create_drawable(int shmid,
                         Fresco::PixelCoord,
                         Fresco::PixelCoord,
                         Fresco::PixelCoord);
  };

  class GGIDrawableFactory :
    virtual public Berlin::Console_Extension::GGIDrawableFactory
  {
    public:
      virtual Berlin::Console_Extension::GGIDrawable *
      create_drawable(int shmid, Fresco::PixelCoord, Fresco::PixelCoord,
              Fresco::PixelCoord);
  };
  
}

#endif
