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

#include <Prague/Sys/Tracer.hh>
#include <Console/SDL/Drawable.hh>
#include <Console/SDL/Extension.hh>
#include <Console/SDL/Pointer.hh>




// ---------------------------------------------------------------
// class SDL::Pointer (implementation)
// ---------------------------------------------------------------

Warsaw::Raster_ptr SDL::Pointer::raster()
{
  Prague::Trace trace("SDL::Pointer::raster()");

  return Warsaw::Raster::_duplicate(_raster);
}


bool SDL::Pointer::intersects(Warsaw::Coord l, Warsaw::Coord r,
			      Warsaw::Coord t, Warsaw::Coord b)
{
  Prague::Trace trace("SDL::Pointer::intersects(...)");

  return
    l/_scale[0] <= _position[0] + _size[0] &&
    r/_scale[0] >= _position[0] &&
    t/_scale[1] <= _position[1] + _size[1] &&
    b/_scale[1] >= _position[1];
}


void SDL::Pointer::move(Warsaw::Coord x, Warsaw::Coord y)
{
  Prague::Trace trace("SDL::Pointer::move(...)");

  restore();

  // update position
  _position[0] =
    static_cast<Warsaw::PixelCoord>
    (std::max(static_cast<Warsaw::PixelCoord>(x/_scale[0]),
	      _origin[0]));
  _position[1] =
    static_cast<Warsaw::PixelCoord>
    (std::max(static_cast<Warsaw::PixelCoord>(y/_scale[1]),
	      _origin[1]));

  save();
  draw();
}





// ---------------------------------------------------------------
// class SDL::nonGLPointer (implementation)
// ---------------------------------------------------------------

SDL::nonGLPointer::nonGLPointer(Drawable * drawable, Warsaw::Raster_ptr raster) :
  _screen(dynamic_cast<SDL::Drawable *>(drawable))
{
  Prague::Trace trace("SDL::nonGLPointer::nonGLPointer(...)");

  // copy over the Raster:
  _raster = Warsaw::Raster::_duplicate(raster);

  // Disable SDL default mousecursor
  SDL_ShowCursor(0);

  // Copy the raster over into the Drawable:
  Warsaw::Raster::Info info = raster->header();
  Warsaw::Raster::ColorSeq_var pixels;
  Warsaw::Raster::Index lower, upper;
  lower.x = lower.y = 0;
  upper.x = info.width, upper.y = info.height;
  raster->store_pixels(lower, upper, pixels);
  _origin[0] = _origin[1] = 0;
  _size[0] = info.width;
  _size[1] = info.height;
  _scale[0] = 1.0/_screen->resolution(Warsaw::xaxis);
  _scale[1] = 1.0/_screen->resolution(Warsaw::yaxis);

  Warsaw::Drawable::PixelFormat format = _screen->pixel_format();

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

  Warsaw::PixelCoord x = _position[0] - _origin[0];
  Warsaw::PixelCoord y = _position[1] - _origin[1];
  _saved_area->blit(*_screen, x, y, _size[0], _size[1], 0, 0);
}


void SDL::nonGLPointer::restore()
{
  Prague::Trace trace("SDL::nonGLPointer::restore()");

  Warsaw::PixelCoord x = _position[0] - _origin[0];
  Warsaw::PixelCoord y = _position[1] - _origin[1];
  _screen->blit(*_saved_area, 0, 0, _size[0], _size[1], x, y);
  _old_x = x;
  _old_y = y;
}


void SDL::nonGLPointer::draw()
{
  Prague::Trace trace("SDL::nonGLPointer::draw()");

  Warsaw::PixelCoord x = _position[0] - _origin[0];
  Warsaw::PixelCoord y = _position[1] - _origin[1];
  _screen->blit(*_cursor, 0, 0, _size[0], _size[1], x, y);
  
  // flush the area we worked on:
  Warsaw::PixelCoord x1 = std::min(_old_x, x);
  Warsaw::PixelCoord y1 = std::min(_old_y, y);
  Warsaw::PixelCoord x2 = std::max(_old_x + _size[0], x + _size[0]);
  Warsaw::PixelCoord y2 = std::max(_old_y + _size[1], y + _size[1]);
  _screen->flush(x1, y1, x2 - x1, y2 - y1);
}

