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
#include <Prague/Sys/Memory.hh>
#include <Prague/Sys/Tracer.hh>
#include "Console/GGI/Console.hh"

using namespace Prague;
using namespace Warsaw;

GGIPointer::GGIPointer(GGIDrawable *d, Raster_ptr raster)
  : _screen(d), _dbuffer(new GGIDirectBuffer(d)), _raster(Raster::_duplicate(raster))
{
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
  
  Drawable::PixelFormat format = _screen->pixel_format();

  Pixel trans = 0;
  Pixel red = (static_cast<Pixel>(1. * (~0L)) >> format.red_shift) & format.red_mask;
  Pixel green = (static_cast<Pixel>(1. * (~0L)) >> format.green_shift) & format.green_mask;
  Pixel blue = (static_cast<Pixel>(1. * (~0L)) >> format.blue_shift) & format.blue_mask;
  Pixel black =  0;
  Pixel white = red | green | blue;

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
  _cache = new data_type[_size[0]*_size[1]*depth];
  save();
  draw();
}

GGIPointer::~GGIPointer()
{
  delete _dbuffer;
  delete [] _image;
  delete [] _cache;
}

Raster_ptr GGIPointer::raster()
{
  return Raster::_duplicate(_raster);
}

bool GGIPointer::intersects(Coord l, Coord r, Coord t, Coord b)
{
  return
    l/_scale[0] <= _position[0] + _size[0] &&
    r/_scale[0] >= _position[0] &&
    t/_scale[1] <= _position[1] + _size[1] &&
    b/_scale[1] >= _position[1];
}

void GGIPointer::move(Coord x, Coord y)
{
  restore();
  _position[0] = static_cast<PixelCoord>(std::max(static_cast<PixelCoord>(x/_scale[0]), _origin[0]));
  _position[1] = static_cast<PixelCoord>(std::max(static_cast<PixelCoord>(y/_scale[1]), _origin[1]));
  save();
  draw();
};

void GGIPointer::save()
{
  Trace trace("Pointer::save");
  PixelCoord x = _position[0] - _origin[0];
  PixelCoord y = _position[1] - _origin[1];
  PixelCoord w = _size[0];
  PixelCoord h = _size[1];
  PixelCoord r = _screen->row_length();
  PixelCoord s = _screen->vwidth() * _screen->vheight();
  PixelCoord d = _screen->pixel_format().size >> 3;
  DirectBuffer::Guard buffer = _dbuffer->read_buffer();
  data_type *from = buffer.get() + y*r + x*d;
  data_type *to = _cache;
  for (PixelCoord o = 0; o != h && (y + o) * r / d + x + w < s; o++, from += r, to += d * w)
    Memory::copy(from, to, d * w);
}

void GGIPointer::restore()
{
  Trace trace("Pointer::restore");
  PixelCoord x = _position[0] - _origin[0];
  PixelCoord y = _position[1] - _origin[1];
  PixelCoord w = _size[0];
  PixelCoord h = _size[1];
  PixelCoord r = _screen->row_length();
  PixelCoord s = _screen->vwidth() * _screen->vheight();
  PixelCoord d = _screen->pixel_format().size >> 3;
  data_type *from = _cache;
  DirectBuffer::Guard buffer = _dbuffer->write_buffer();
  data_type *to = buffer.get() + y*r + x*d;
  for (PixelCoord o = 0;
       o != h && (y + o) * r / d + x + w < s;
       o++, from += d * w, to += r)
    Memory::copy(from, to, d * w);
  _screen->flush(x, y, w, h);
}

void GGIPointer::draw()
{
  Trace trace("GGIPointer::draw");
  PixelCoord x = _position[0] - _origin[0];
  PixelCoord y = _position[1] - _origin[1];
  PixelCoord w = _size[0];
  PixelCoord h = _size[1];
  PixelCoord r = _screen->row_length();
  PixelCoord s = _screen->vwidth() * _screen->vheight();
  PixelCoord d = _screen->pixel_format().size >> 3;
  data_type *from = _image;
  data_type *bits = _mask;
  DirectBuffer::Guard buffer = _dbuffer->write_buffer();
  data_type *to = buffer.get() + y * r + x * d;
  for (PixelCoord i = 0; i != h && (y + i) * r / d + x + w < s; i++, to += r - w * d)
    for (PixelCoord j = 0; j != w * d; j++, from++, bits++, to++)
      *to = (*from & *bits) | (*to & ~*bits);
  _screen->flush(x, y, w, h);
}

