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
#include <Prague/Sys/Memory.hh>
#include <Prague/Sys/Tracer.hh>
#include "Console.hh"
#include "Extension.hh"
#include "Drawable.hh"
#include "Pointer.hh"

using namespace Prague;
using namespace Fresco;

GGI::Pointer::Pointer(GGI::Drawable *drawable, Raster_ptr raster)
  : _screen(drawable), _dbuffer(new GGI::DirectBuffer()), _raster(Raster::_duplicate(raster))
{
  _dbuffer->attach(_screen);
  Raster::Info info = raster->header();
  Raster::ColorSeq_var pixels;
  Raster::Index lower, upper;
  lower.x = lower.y = 0;
  upper.x = info.width, upper.y = info.height;
  raster->store_pixels(lower, upper, pixels);
  _origin[0] = _origin[1] = 0;
  _position[0] = _position[1] = 8;
  _size[0] = info.width;
  _size[1] = info.height;
  _scale[0] = 1/_screen->resolution(xaxis);
  _scale[1] = 1/_screen->resolution(yaxis);
  
  Fresco::Drawable::PixelFormat format = _screen->pixel_format();

  /*
   * create the pointer image
   */
  PixelCoord depth =  format.size >> 3;
  _image = new data_type[_size[0]*_size[1] * depth];
  for (unsigned short y = 0; y != _size[1]; y++)
    for (unsigned short x = 0; x != _size[0]; x++)
      {
	Pixel color = _screen->map(*(pixels->get_buffer() + y * info.width + x));
 	for (unsigned short d = 0; d != depth; d++)
	  _image[y*depth*_size[0] + depth*x + d] = (color >> d) & 0xff;
      }
  /*
   * create the pointer mask
   */
  _mask = new data_type[_size[0]*_size[1]*depth];
  for (unsigned short y = 0; y != _size[1]; y++)
    for (unsigned short x = 0; x != _size[0]; x++)
      {
	char flag = (pixels->get_buffer() + y*_size[0] + x)->alpha <= 0.5 ? 0 : ~0;
	for (unsigned short d = 0; d != depth; d++)
	  _mask[y*depth*_size[0]+depth*x + d] = flag;
      }
  /*
   * create the save and restore cache
   */
  _cache = new Drawable("memory", _size[0], _size[1], depth);

}

GGI::Pointer::~Pointer()
{
  delete _dbuffer;
  delete [] _image;
  delete _cache;
}

Raster_ptr GGI::Pointer::raster()
{
  return Raster::_duplicate(_raster);
}

bool GGI::Pointer::intersects(Coord l, Coord r, Coord t, Coord b)
{
  return
    l/_scale[0] <= _position[0] + _size[0] &&
    r/_scale[0] >= _position[0] &&
    t/_scale[1] <= _position[1] + _size[1] &&
    b/_scale[1] >= _position[1];
}

void GGI::Pointer::move(Coord x, Coord y)
{
  restore();
  _position[0] = static_cast<PixelCoord>(std::max(static_cast<PixelCoord>(x/_scale[0]), _origin[0]));
  _position[1] = static_cast<PixelCoord>(std::max(static_cast<PixelCoord>(y/_scale[1]), _origin[1]));
  save();
  draw();
};

void GGI::Pointer::save()
{
  PixelCoord x = _position[0] - _origin[0];
  PixelCoord y = _position[1] - _origin[1];
  PixelCoord w = _size[0];
  PixelCoord h = _size[1];
  _cache->blit(*_screen, x, y, w, h, 0, 0);
}

void GGI::Pointer::restore()
{
  PixelCoord x = _position[0] - _origin[0];
  PixelCoord y = _position[1] - _origin[1];
  PixelCoord w = _size[0];
  PixelCoord h = _size[1];
  _screen->blit(*_cache, 0, 0, w, h, x, y);
  _screen->flush(x, y, w, h);
}

void GGI::Pointer::draw()
{
  PixelCoord x = _position[0] - _origin[0];
  PixelCoord y = _position[1] - _origin[1];
  PixelCoord w = _size[0];
  PixelCoord h = _size[1];
  PixelCoord r = _screen->row_length();
  PixelCoord s = _screen->vwidth() * _screen->vheight();
  PixelCoord d = _screen->pixel_format().size >> 3;
  data_type *from = _image;
  data_type *bits = _mask;
  const ggi_directbuffer *dbuf = _screen->buffer(0);
  ggiResourceAcquire(dbuf->resource, GGI_ACTYPE_WRITE);
  data_type *to = static_cast<char*>(dbuf->write) + y*r + x*d;
  for (PixelCoord i = 0; i != h && (y+i)*r/d+x+w<s; i++, to += r - w * d)
    for (PixelCoord j = 0; j != w * d ; j++, from++, bits++, to++)
      if (x*d+j < r)
        *to = (*from & *bits) | (*to & ~*bits);
  _screen->flush(x, y, w, h);
  ggiResourceRelease(dbuf->resource);
}

