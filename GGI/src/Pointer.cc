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

GGI::Pointer::Pointer(GGI::Drawable *drawable, Raster_ptr raster) : 
    my_screen(drawable),
    my_dbuffer(new GGI::DirectBuffer()),
    my_raster(Raster::_duplicate(raster))
{
    my_dbuffer->attach(my_screen);
    Raster::Info info = raster->header();
    Raster::ColorSeq_var pixels;
    Raster::Index lower, upper;
    lower.x = lower.y = 0;
    upper.x = info.width, upper.y = info.height;
    raster->store_pixels(lower, upper, pixels);
    my_origin[0] = my_origin[1] = 0;
    my_position[0] = my_position[1] = 8;
    my_size[0] = info.width;
    my_size[1] = info.height;
    my_scale[0] = 1/my_screen->resolution(xaxis);
    my_scale[1] = 1/my_screen->resolution(yaxis);
  
    Fresco::Drawable::PixelFormat format = my_screen->pixel_format();

    // create the pointer image
    PixelCoord depth =  format.size >> 3;
    my_image = new data_type[my_size[0]*my_size[1] * depth];
    for (unsigned short y = 0; y != my_size[1]; ++y)
    for (unsigned short x = 0; x != my_size[0]; ++x)
    {
        Pixel color =
        my_screen->map(*(pixels->get_buffer() +
                 y * info.width + x));
        for (unsigned short d = 0; d != depth; d++)
        my_image[y*depth*my_size[0] + depth*x + d] =
            (color >> d) & 0xff;
    }

    // create the pointer mask
    my_mask = new data_type[my_size[0]*my_size[1]*depth];
    for (unsigned short y = 0; y != my_size[1]; y++)
    for (unsigned short x = 0; x != my_size[0]; x++)
    {
        char flag =
        (pixels->get_buffer() + y*my_size[0] + x)->alpha <= 0.5 ?
        0 : ~0;
        for (unsigned short d = 0; d != depth; d++)
        my_mask[y*depth*my_size[0]+depth*x + d] = flag;
    }

    // create the save and restore cache
    my_cache = new Drawable("memory", my_size[0], my_size[1], depth);
}

GGI::Pointer::~Pointer()
{
    delete my_dbuffer;
    delete [] my_image;
    delete my_cache;
}

Raster_ptr GGI::Pointer::raster()
{ return Raster::_duplicate(my_raster); }

bool GGI::Pointer::intersects(Coord l, Coord r, Coord t, Coord b)
{
    return
    l/my_scale[0] <= my_position[0] + my_size[0] &&
    r/my_scale[0] >= my_position[0] &&
    t/my_scale[1] <= my_position[1] + my_size[1] &&
    b/my_scale[1] >= my_position[1];
}

void GGI::Pointer::move(Coord x, Coord y)
{
    restore();
    my_position[0] = static_cast<PixelCoord>
    (std::max(static_cast<PixelCoord>(x/my_scale[0]), my_origin[0]));
    my_position[1] = static_cast<PixelCoord>
    (std::max(static_cast<PixelCoord>(y/my_scale[1]), my_origin[1]));
    save();
    draw();
}

void GGI::Pointer::save()
{
    PixelCoord x = my_position[0] - my_origin[0];
    PixelCoord y = my_position[1] - my_origin[1];
    PixelCoord w = my_size[0];
    PixelCoord h = my_size[1];
    my_cache->blit(*my_screen, x, y, w, h, 0, 0);
}

void GGI::Pointer::restore()
{
    PixelCoord x = my_position[0] - my_origin[0];
    PixelCoord y = my_position[1] - my_origin[1];
    PixelCoord w = my_size[0];
    PixelCoord h = my_size[1];
    my_screen->blit(*my_cache, 0, 0, w, h, x, y);
    my_screen->flush(x, y, w, h);
}

void GGI::Pointer::draw()
{
    PixelCoord x = my_position[0] - my_origin[0];
    PixelCoord y = my_position[1] - my_origin[1];
    PixelCoord w = my_size[0];
    PixelCoord h = my_size[1];
    PixelCoord r = my_screen->row_length();
    PixelCoord s = my_screen->vwidth() * my_screen->vheight();
    PixelCoord d = my_screen->pixel_format().size >> 3;
    data_type *from = my_image;
    data_type *bits = my_mask;
    const ggi_directbuffer *dbuf = my_screen->buffer(0);
    ggiResourceAcquire(dbuf->resource, GGI_ACTYPE_WRITE);
    data_type *to = static_cast<char*>(dbuf->write) + y*r + x*d;
    for (PixelCoord i = 0; i != h && (y+i)*r/d+x+w<s; i++, to += r - w * d)
    for (PixelCoord j = 0; j != w * d ; ++j, ++from, ++bits, ++to)
        if (x*d+j < r)
        *to = (*from & *bits) | (*to & ~*bits);
    my_screen->flush(x, y, w, h);
    ggiResourceRelease(dbuf->resource);
}

