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
#include <Berlin/Logger.hh>
#include "Drawable.hh"
#include "Extension.hh"

// ---------------------------------------------------------------
// class SDL::Renderer (implementation)
// ---------------------------------------------------------------

void SDL::Extension::attach(Berlin::Console::Drawable * drawable)
{ my_drawable = dynamic_cast<SDL::Drawable *>(drawable); }

// ---------------------------------------------------------------
// class SDL::Renderer (implementation)
// ---------------------------------------------------------------

SDL::Renderer::Renderer() { }


void SDL::Renderer::set_color(const Fresco::Color &c)
{
    Prague::Trace trace("SDLRenderer::set_color()");
    my_color = drawable()->map(c);
}


void SDL::Renderer::draw_pixel(Fresco::PixelCoord x, Fresco::PixelCoord y)
{
    Prague::Trace trace("SDLRenderer::draw_pixel()");
    put_pixel(x, y);
}


void SDL::Renderer::draw_hline(Fresco::PixelCoord x, Fresco::PixelCoord y,
                       Fresco::PixelCoord w)
{
    Prague::Trace trace("SDL::Renderer::draw_hline()");
    for (int i = 0; i < w; ++i) put_pixel(x + i, y);
}

void SDL::Renderer::draw_vline(Fresco::PixelCoord x, Fresco::PixelCoord y,
                       Fresco::PixelCoord h)
{
    Prague::Trace trace("SDL::Renderer::draw_vline()");
    for (int i = 0; i < h; ++i) put_pixel(x, y + h);
}

void SDL::Renderer::draw_line(Fresco::PixelCoord x, Fresco::PixelCoord y,
                      Fresco::PixelCoord w, Fresco::PixelCoord h)
{
    Prague::Trace trace("SDLRenderer::draw_line()");
    
    register int distance; 
    int xerr=0, yerr=0;
    int delta_x, delta_y; 
    int incx, incy; 
    
    delta_x = w; 
    delta_y = h; 
    
    if (delta_x>0) incx=1; 
    else if (delta_x==0) incx=0; 
    else incx= -1; 
  
    if (delta_y>0) incy=1; 
    else if (delta_y==0) incy=0; 
    else incy= -1; 
  
    delta_x = abs(delta_x);
    delta_y = abs(delta_y);
  
    distance = delta_x>delta_y ? delta_x : delta_y;
  
    for (int t=0; t<=distance+1; ++t) { 
    put_pixel(x, y); 
    xerr+=delta_x; 
    yerr+=delta_y; 
    if (xerr>distance)
    { 
        xerr-=distance; 
        x+=incx; 
    }
    if (yerr>distance)
    { 
        yerr-=distance; 
        y+=incy; 
    }
    }
}
  
void SDL::Renderer::draw_box(Fresco::PixelCoord x, Fresco::PixelCoord y,
                 Fresco::PixelCoord w, Fresco::PixelCoord h)
{
    Prague::Trace trace("SDLRenderer::draw_box()");
  
    SDL_Rect r; r.x = x; r.y = y; r.w = w; r.h = h;
    
    if (r.x < 0) { r.w += r.x; r.x = 0; }
    if (r.y < 0) { r.h += r.y; r.y = 0; }
  
    SDL_FillRect(drawable()->surface(), &r, my_color);
}


void SDL::Renderer::put_pixel(Fresco::PixelCoord x, Fresco::PixelCoord y)
{
    Prague::Trace trace("SDLRenderer::put_pixel()");
  
    if (x >= drawable()->width() || y >= drawable()->height() ||
    x < 0 || y < 0) return;
    if (drawable()->need_locking())
    SDL_LockSurface(drawable()->surface());
  
    Uint8* p = (Uint8 *)drawable()->surface()->pixels +
    y * drawable()->surface()->pitch +
    x * drawable()->depth();
  
    switch( drawable()->depth() )
    {
    case 1:
    *p = my_color;
    break;
    case 2:
    *(Uint16 *)p = my_color;
    break;
    case 3:
    {
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
    {
        p[0] = (my_color >> 16) & 0xff;
        p[1] = (my_color >> 8) & 0xff;
        p[2] = my_color & 0xff;
    }
    else
    {
        p[0] = my_color & 0xff;
        p[1] = (my_color >> 8) & 0xff;
        p[2] = (my_color >> 16) & 0xff;
    }
    break;
    }
    case 4: *(Uint32 *)p = my_color; break; 
    }
    
    if (drawable()->need_locking())
    SDL_UnlockSurface(drawable()->surface());
}


// ---------------------------------------------------------------
// class SDL::DirectBuffer (implementation)
// ---------------------------------------------------------------

SDL::DirectBuffer::DirectBuffer() { }

void SDL::DirectBuffer::attach(Berlin::Console::Drawable *d)
{
    Prague::Trace trace("SDL::DirectBuffer::DirectBuffer(...)");
    Extension::attach(d);
    if (drawable()->surface()->flags && SDL_OPENGL) { throw; }
}

SDL::DirectBuffer::Guard SDL::DirectBuffer::read_buffer()
{
    Prague::Trace trace("SDLDirectBuffer::read_buffer()");
    DirectBuffer::Guard
    guard(drawable(), static_cast<Berlin::Console::Drawable::data_type *>
          (drawable()->surface()->pixels));
    return guard;
}

SDL::DirectBuffer::Guard SDL::DirectBuffer::write_buffer()
{
    Prague::Trace trace("SDLDirectBuffer::write_buffer()");
    DirectBuffer::Guard
    guard(drawable(), static_cast<Berlin::Console::Drawable::data_type *>
          (drawable()->surface()->pixels));
    return guard;
}
