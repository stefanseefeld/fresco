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
#ifndef _GGI_Drawable_hh
#define _GGI_Drawable_hh

#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Fresco/Input.hh>
#include <Berlin/Console.hh>
#include <Berlin/Console/GGIDrawableFactory.hh>
#include <vector>
extern "C"
{
#include <ggi/ggi-unix.h>
}

namespace GGI
{
  class Console;

  class Drawable : public virtual Berlin::Console::Drawable,
           public virtual Berlin::Console_Extension::GGIDrawable
  {
      friend class GGI::Console;
    public:
      Drawable(const char *, Fresco::PixelCoord = 0,
           Fresco::PixelCoord = 0, Fresco::PixelCoord = 0);
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
      virtual void init();
      virtual void finish();
      
      // fast blit
      virtual void blit(Fresco::PixelCoord, Fresco::PixelCoord,
            Fresco::PixelCoord, Fresco::PixelCoord,
            Fresco::PixelCoord, Fresco::PixelCoord);
      virtual void blit(const Berlin::Console::Drawable &,
            Fresco::PixelCoord, Fresco::PixelCoord,
            Fresco::PixelCoord, Fresco::PixelCoord,
            Fresco::PixelCoord, Fresco::PixelCoord);
      virtual void blit(const Drawable &,
            Fresco::PixelCoord, Fresco::PixelCoord,
            Fresco::PixelCoord, Fresco::PixelCoord,
            Fresco::PixelCoord, Fresco::PixelCoord);
      virtual void blit(Fresco::Drawable_ptr,
            Fresco::PixelCoord, Fresco::PixelCoord,
            Fresco::PixelCoord, Fresco::PixelCoord,
            Fresco::PixelCoord, Fresco::PixelCoord);
      
      virtual const std::string &name() const { return my_name; }
      virtual ggi_mode mode() const { return my_mode; }
      virtual ggi_visual_t visual() const { return my_visual; }
     
      // if you really must ask...
      const ggi_directbuffer *buffer(unsigned int i) const
      { return ggiDBGetBuffer(my_visual, i); }
      ggi_pixel map(const Fresco::Color &) const;
    private:
      std::string my_name;
      ggi_visual_t my_visual;
      ggi_mode my_mode;
  };
  
}

#endif
