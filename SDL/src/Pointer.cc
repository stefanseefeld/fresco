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

#include <Prague/Sys/Tracer.hh>
#include "Drawable.hh"
#include "Extension.hh"
#include "Pointer.hh"

// ---------------------------------------------------------------
// class SDL::Pointer (implementation)
// ---------------------------------------------------------------

Fresco::Raster_ptr SDL::Pointer::raster()
{
  Prague::Trace trace("SDL::Pointer::raster()");

  return Fresco::Raster::_duplicate(_raster);
}


bool SDL::Pointer::intersects(Fresco::Coord l, Fresco::Coord r,
			      Fresco::Coord t, Fresco::Coord b)
{
  Prague::Trace trace("SDL::Pointer::intersects(...)");

  return
    l/_scale[0] <= _position[0] + _size[0] &&
    r/_scale[0] >= _position[0] &&
    t/_scale[1] <= _position[1] + _size[1] &&
    b/_scale[1] >= _position[1];
}


void SDL::Pointer::move(Fresco::Coord x, Fresco::Coord y)
{
  Prague::Trace trace("SDL::Pointer::move(...)");

  restore();

  // update position
  _position[0] =
    static_cast<Fresco::PixelCoord>
    (std::max(static_cast<Fresco::PixelCoord>(x/_scale[0]),
	      _origin[0]));
  _position[1] =
    static_cast<Fresco::PixelCoord>
    (std::max(static_cast<Fresco::PixelCoord>(y/_scale[1]),
	      _origin[1]));

  save();
  draw();
}





// ---------------------------------------------------------------
// class SDL::nonGLPointer (implementation)
// ---------------------------------------------------------------

SDL::nonGLPointer::nonGLPointer(Drawable * drawable, Fresco::Raster_ptr raster,
                                void *)
  : _screen(dynamic_cast<SDL::Drawable *>(drawable))
{
  Prague::Trace trace("SDL::nonGLPointer::nonGLPointer(...)");

  // copy over the Raster:
  _raster = Fresco::Raster::_duplicate(raster);

  // Disable SDL default mousecursor
  SDL_ShowCursor(0);

  // Copy the raster over into the Drawable:
  Fresco::Raster::Info info = raster->header();
  Fresco::Raster::ColorSeq_var pixels;
  Fresco::Raster::Index lower, upper;
  lower.x = lower.y = 0;
  upper.x = info.width, upper.y = info.height;
  raster->store_pixels(lower, upper, pixels);
  _origin[0] = _origin[1] = 0;
  _size[0] = info.width;
  _size[1] = info.height;
  _scale[0] = 1.0/_screen->resolution(Fresco::xaxis);
  _scale[1] = 1.0/_screen->resolution(Fresco::yaxis);

  Fresco::Drawable::PixelFormat format = _screen->pixel_format();

  unsigned depth =  format.size >> 3;
  _cursor = new SDL::Drawable("mouse cursor", _size[0], _size[1], 4);

  Renderer * renderer = new SDL::Renderer();
  renderer->attach(_cursor);

  for (unsigned short y = 0; y != _size[1]; y++)
    for (unsigned short x = 0; x != _size[0]; x++)
      {
        renderer->set_color(*(pixels->get_buffer() + y * info.width + x));
	renderer->draw_pixel(x, y);
      }

  // set up save_area
  _saved_area = new SDL::Drawable("save area", _size[0], _size[1], depth);

  // set position
  _position[0] = _position[1] = 8;
  _old_x = _position[0] - _origin[0];
  _old_y = _position[1] - _origin[1];
  _old_size_x = _size[0];
  _old_size_y = _size[1];

  // set SDL_Alpha:
  SDL_SetAlpha(_cursor->surface(), SDL_SRCALPHA, 128);
}


SDL::nonGLPointer::~nonGLPointer()
{
  restore();
}


void SDL::nonGLPointer::save()
{
  Prague::Trace trace("SDL::nonGLPointer::save()");

  Fresco::PixelCoord x = _position[0] - _origin[0];
  Fresco::PixelCoord y = _position[1] - _origin[1];
  Fresco::PixelCoord size_x, size_y;
  size_x = (_size[0] + x > _screen->width()) ? _screen->width()-x : _size[0];
  size_y = (_size[1] + y > _screen->height()) ? _screen->height()-y : _size[1];
  _saved_area->blit(*_screen, x, y, size_x, size_y, 0, 0);
}


void SDL::nonGLPointer::restore()
{
  Prague::Trace trace("SDL::nonGLPointer::restore()");

  Fresco::PixelCoord x = _position[0] - _origin[0];
  Fresco::PixelCoord y = _position[1] - _origin[1];
  Fresco::PixelCoord size_x, size_y;
  size_x = (_size[0] + x > _screen->width()) ? _screen->width()-x : _size[0];
  size_y = (_size[1] + y > _screen->height()) ? _screen->height()-y : _size[1];
  _screen->blit(*_saved_area, 0, 0, size_x, size_y, x, y);
  _old_x = x;
  _old_y = y;
  _old_size_x = size_x;
  _old_size_y = size_y;
}


void SDL::nonGLPointer::draw()
{
  Prague::Trace trace("SDL::nonGLPointer::draw()");

  Fresco::PixelCoord x = _position[0] - _origin[0];
  Fresco::PixelCoord y = _position[1] - _origin[1];
  Fresco::PixelCoord size_x, size_y;
  size_x = (_size[0] + x > _screen->width()) ? _screen->width()-x : _size[0];
  size_y = (_size[1] + y > _screen->height()) ? _screen->height()-y : _size[1];
  _screen->blit(*_cursor, 0, 0, size_x, size_y, x, y);
  // flush the area we worked on:
  Fresco::PixelCoord x1 = std::min(_old_x, x);
  Fresco::PixelCoord y1 = std::min(_old_y, y);
  Fresco::PixelCoord x2 = std::max(_old_x + _old_size_x, x + size_x);
  Fresco::PixelCoord y2 = std::max(_old_y + _old_size_y, y + size_y);
  _screen->flush(x1, y1, x2 - x1, y2 - y1);
}

