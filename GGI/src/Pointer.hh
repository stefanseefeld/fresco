/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _GGI_Pointer_hh
#define _GGI_Pointer_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
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

class Pointer : public ::Console::Pointer
{
  typedef ::Console::Drawable::data_type data_type;
  typedef ggi_pixel Pixel;
public:
  Pointer(Drawable *, Warsaw::Raster_ptr);
  virtual ~Pointer();
  virtual Warsaw::Raster_ptr raster();
  virtual void move(Warsaw::Coord, Warsaw::Coord);
  virtual void draw();
  virtual void save();
  virtual void restore();
  virtual bool intersects(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
private:
  Drawable           *_screen;
  DirectBuffer       *_dbuffer;
  Warsaw::PixelCoord  _origin[2];
  Warsaw::PixelCoord  _position[2];
  Warsaw::PixelCoord  _size[2];
  Warsaw::Coord       _scale[2];
  Warsaw::Raster_ptr  _raster;
  data_type          *_image;
  data_type          *_mask;
  data_type          *_cache;
};

}

#endif
