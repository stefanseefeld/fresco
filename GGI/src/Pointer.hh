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
#ifndef _Pointer_hh
#define _Pointer_hh

#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Fresco/Input.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Console.hh>
#include <vector>
extern "C"
{
#include <ggi/ggi-unix.h>
}

namespace GGI
{

  class DirectBuffer;
  
  class Pointer : public Berlin::Console::Pointer
  {
      typedef Berlin::Console::Drawable::data_type data_type;
      typedef ggi_pixel Pixel;
    public:
      Pointer(Drawable *, Fresco::Raster_ptr);
      virtual ~Pointer();
      virtual Fresco::Raster_ptr raster();
      virtual void move(Fresco::Coord, Fresco::Coord);
      virtual void draw();
      virtual void save();
      virtual void restore();
      virtual bool intersects(Fresco::Coord, Fresco::Coord,
                  Fresco::Coord, Fresco::Coord);
    private:
      Drawable           *my_screen;
      DirectBuffer       *my_dbuffer;
      Fresco::PixelCoord  my_origin[2];
      Fresco::PixelCoord  my_position[2];
      Fresco::PixelCoord  my_size[2];
      Fresco::Coord       my_scale[2];
      Fresco::Raster_ptr  my_raster;
      data_type          *my_image;
      data_type          *my_mask;
      Drawable           *my_cache;
  };

}

#endif
