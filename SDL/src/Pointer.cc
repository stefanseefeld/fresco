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
    return Fresco::Raster::_duplicate(my_raster);
}


bool SDL::Pointer::intersects(Fresco::Coord l, Fresco::Coord r,
                  Fresco::Coord t, Fresco::Coord b)
{
    Prague::Trace trace("SDL::Pointer::intersects(...)");
    
    return
    l/my_scale[0] <= my_position[0] + my_size[0] &&
    r/my_scale[0] >= my_position[0] &&
    t/my_scale[1] <= my_position[1] + my_size[1] &&
    b/my_scale[1] >= my_position[1];
}


void SDL::Pointer::move(Fresco::Coord x, Fresco::Coord y)
{
    Prague::Trace trace("SDL::Pointer::move(...)");
    restore();
    // update position
    my_position[0] =
    static_cast<Fresco::PixelCoord>
    (std::max(static_cast<Fresco::PixelCoord>(x/my_scale[0]),
          my_origin[0]));
    my_position[1] =
      static_cast<Fresco::PixelCoord>
      (std::max(static_cast<Fresco::PixelCoord>(y/my_scale[1]),
        my_origin[1]));
    save();
    draw();
}

// ---------------------------------------------------------------
// class SDL::nonGLPointer (implementation)
// ---------------------------------------------------------------

SDL::nonGLPointer::nonGLPointer(Drawable * drawable,
                Fresco::Raster_ptr raster,
                                void *) :
    my_screen(dynamic_cast<SDL::Drawable *>(drawable))
{
    Prague::Trace trace("SDL::nonGLPointer::nonGLPointer(...)");
    
    // copy over the Raster:
    my_raster = Fresco::Raster::_duplicate(raster);
    
    // Disable SDL default mousecursor
    SDL_ShowCursor(0);
    
    // Copy the raster over into the Drawable:
    Fresco::Raster::Info info = raster->header();
    Fresco::Raster::ColorSeq_var pixels;
    Fresco::Raster::Index lower, upper;
    lower.x = lower.y = 0;
    upper.x = info.width, upper.y = info.height;
    raster->store_pixels(lower, upper, pixels);
    my_origin[0] = my_origin[1] = 0;
    my_size[0] = info.width;
    my_size[1] = info.height;
    my_scale[0] = 1.0/my_screen->resolution(Fresco::xaxis);
    my_scale[1] = 1.0/my_screen->resolution(Fresco::yaxis);
    
    Fresco::Drawable::PixelFormat format = my_screen->pixel_format();
    
    unsigned depth =  format.size >> 3;
    my_cursor = new SDL::Drawable("mouse cursor",
                  my_size[0], my_size[1], 4);
    
    Renderer * renderer = new SDL::Renderer();
    renderer->attach(my_cursor);
    
    for (unsigned short y = 0; y != my_size[1]; ++y)
    for (unsigned short x = 0; x != my_size[0]; ++x)
    {
        renderer->set_color(*(pixels->get_buffer() + y *
                  info.width + x));
        renderer->draw_pixel(x, y);
    }
    
    // set up save_area
    my_saved_area = new SDL::Drawable("save area",
                      my_size[0], my_size[1], depth);
    
    // set position
    my_position[0] = my_position[1] = 8;
    my_old_x = my_position[0] - my_origin[0];
    my_old_y = my_position[1] - my_origin[1];
    my_old_size_x = my_size[0];
    my_old_size_y = my_size[1];
    
    // set SDL_Alpha:
    SDL_SetAlpha(my_cursor->surface(), SDL_SRCALPHA, 128);
}

SDL::nonGLPointer::~nonGLPointer()
{ restore(); }

void SDL::nonGLPointer::save()
{
    Prague::Trace trace("SDL::nonGLPointer::save()");
    
    Fresco::PixelCoord x = my_position[0] - my_origin[0];
    Fresco::PixelCoord y = my_position[1] - my_origin[1];
    Fresco::PixelCoord size_x, size_y;
    size_x = (my_size[0] + x > my_screen->width()) ?
    my_screen->width()-x : my_size[0];
    size_y = (my_size[1] + y > my_screen->height()) ?
    my_screen->height()-y : my_size[1];
    my_saved_area->blit(*my_screen, x, y, size_x, size_y, 0, 0);
}


void SDL::nonGLPointer::restore()
{
    Prague::Trace trace("SDL::nonGLPointer::restore()");
    
    Fresco::PixelCoord x = my_position[0] - my_origin[0];
    Fresco::PixelCoord y = my_position[1] - my_origin[1];
    Fresco::PixelCoord size_x, size_y;
    size_x = (my_size[0] + x > my_screen->width()) ?
    my_screen->width()-x : my_size[0];
    size_y = (my_size[1] + y > my_screen->height()) ?
    my_screen->height()-y : my_size[1];
    my_screen->blit(*my_saved_area, 0, 0, size_x, size_y, x, y);
    my_old_x = x;
    my_old_y = y;
    my_old_size_x = size_x;
    my_old_size_y = size_y;
}


void SDL::nonGLPointer::draw()
{
    Prague::Trace trace("SDL::nonGLPointer::draw()");
    
    Fresco::PixelCoord x = my_position[0] - my_origin[0];
    Fresco::PixelCoord y = my_position[1] - my_origin[1];
    Fresco::PixelCoord size_x, size_y;
    size_x = (my_size[0] + x > my_screen->width()) ?
    my_screen->width()-x : my_size[0];
    size_y = (my_size[1] + y > my_screen->height()) ?
    my_screen->height()-y : my_size[1];
    my_screen->blit(*my_cursor, 0, 0, size_x, size_y, x, y);
    // flush the area we worked on:
    Fresco::PixelCoord x1 = std::min(my_old_x, x);
    Fresco::PixelCoord y1 = std::min(my_old_y, y);
    Fresco::PixelCoord x2 = std::max(my_old_x + my_old_size_x, x + size_x);
    Fresco::PixelCoord y2 = std::max(my_old_y + my_old_size_y, y + size_y);
    my_screen->flush(x1, y1, x2 - x1, y2 - y1);
}

