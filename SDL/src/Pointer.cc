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

#if 0

// This works with stefan's new focus code, but it breaks on GL.
// It has a semitransparent cursor. Something is still broken with
// this (alpha is globally set, not from the image data).

SDL::Pointer::Pointer(Drawable * drawable, Warsaw::Raster_ptr raster) :
  _screen(dynamic_cast<SDL::Drawable *>(drawable)),
  _raster(Warsaw::Raster::_duplicate(raster))
{
  Prague::Trace trace("SDL::Pointer::Pointer(...)");

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

  // set SDL_Alpha:
  SDL_SetAlpha(_cursor->surface(), SDL_SRCALPHA, 128);

  save();
  draw();
}


SDL::Pointer::~Pointer() { }


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


void SDL::Pointer::save()
{
  Prague::Trace trace("SDL::Pointer::save()");

  Warsaw::PixelCoord x = _position[0] - _origin[0];
  Warsaw::PixelCoord y = _position[1] - _origin[1];
  _saved_area->blit(*_screen, x, y, _size[0], _size[1], 0, 0);
}


void SDL::Pointer::restore()
{
  Prague::Trace trace("SDL::Pointer::restore()");

  Warsaw::PixelCoord x = _position[0] - _origin[0];
  Warsaw::PixelCoord y = _position[1] - _origin[1];
  _screen->blit(*_saved_area, 0, 0, _size[0], _size[1], x, y);
}


void SDL::Pointer::draw()
{
  Prague::Trace trace("SDL::Pointer::draw()");

  Warsaw::PixelCoord x = _position[0] - _origin[0];
  Warsaw::PixelCoord y = _position[1] - _origin[1];
  _screen->blit(*_cursor, 0, 0, _size[0], _size[1], x, y);
}

#else

// This does not work with stefan's new Focus code, but it works with GL

static unsigned char pointer_image[] = {
  1,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  1,3,1,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  1,3,3,1, 0,0,0,0, 0,0,0,0, 0,0,0,0,
  1,3,3,3, 1,0,0,0, 0,0,0,0, 0,0,0,0,

  1,3,3,3, 3,1,0,0, 0,0,0,0, 0,0,0,0,
  1,3,3,3, 3,3,1,0, 0,0,0,0, 0,0,0,0,
  1,3,3,3, 3,3,3,1, 0,0,0,0, 0,0,0,0,
  1,3,3,3, 3,3,3,3, 1,0,0,0, 0,0,0,0,

  1,3,3,3, 3,3,1,1, 1,1,0,0, 0,0,0,0,
  1,3,3,1, 3,3,1,0, 0,0,0,0, 0,0,0,0,
  1,1,0,1, 3,3,3,1, 0,0,0,0, 0,0,0,0,
  1,0,0,0, 1,3,3,1, 0,0,0,0, 0,0,0,0,

  0,0,0,0, 1,3,3,3, 1,0,0,0, 0,0,0,0,
  0,0,0,0, 0,1,3,3, 1,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,1,1, 0,0,0,0, 0,0,0,0,
  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0
};

SDL::Pointer::Pointer(Drawable * drawable, Warsaw::Raster_ptr raster) :
  _raster(Warsaw::Raster::_duplicate(raster))
{
  Prague::Trace trace("SDL::Pointer::Pointer(...)");
  
  _size[0] = 16; // width
  _size[1] = 16; // height
  
  Uint8 image[(_size[0] * _size[1]) / 8];
  Uint8 mask[(_size[0] * _size[1]) / 8];

  int i = -1; 

  for (unsigned short y = 0; y < _size[1]; ++y)
    for (unsigned short x = 0; x < _size[0]; ++x) {
      if (x % 8) {
        image[i] <<= 1;
        mask[i] <<= 1;
      } else {
        ++i;
        image[i] = mask[i] = 0;
      }

      image[i] |= ((pointer_image[y * _size[0] + x] & 2) > 0);
      mask [i] |= ((pointer_image[y * _size[0] + x] & 1) > 0);
    }

  _cursor = SDL_CreateCursor(image, mask, _size[0], _size[1], 1, 1);
  SDL_SetCursor(_cursor);
  SDL_ShowCursor(1);
}

SDL::Pointer::~Pointer()
{
  Prague::Trace trace("SDL::Pointer::~SDLPointer()");
  
  SDL_FreeCursor(_cursor);
  SDL_ShowCursor(0);
}

Warsaw::Raster_ptr SDL::Pointer::raster()
{
  Prague::Trace trace("SDL::Pointer::raster()");

  return Warsaw::Raster::_duplicate(_raster);
}

bool SDL::Pointer::intersects(Warsaw::Coord l, Warsaw::Coord r,
			      Warsaw::Coord t, Warsaw::Coord b)
{
  Prague::Trace trace("SDLPointer::intersects()");
  return
    l*0.1 <= _x - 10 &&
    r*0.1 >= _x &&
    t*0.1 <= _y - 10 &&
    b*0.1 >= _y;
}

void SDL::Pointer::move(Warsaw::Coord x, Warsaw::Coord y)
{
  Prague::Trace trace("SDLPointer::move()");

  _x = Warsaw::PixelCoord(x);
  _y = Warsaw::PixelCoord(y); 
}

void SDL::Pointer::save()
{
  Prague::Trace trace("SDLPointer::save()");
}
void SDL::Pointer::restore()
{
  Prague::Trace trace("SDLPointer::restore()");
}
void SDL::Pointer::draw()
{
  Prague::Trace trace("SDLPointer::draw()");
}

#endif
