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


// ---------------------------------------------------------------
// class SDL::Drawable (implementation)
// ---------------------------------------------------------------

SDL::Drawable::Drawable(const char *display,
            Fresco::PixelCoord w, Fresco::PixelCoord h, int d)
{
    Prague::Trace trace("SDL::Drawable::Drawable()");

    if (d < 0 || d > 4) throw std::exception();

    int bpp(d * 8);
    
    my_width = w;
    my_height = h;

    std::string displaystring;
    if (display == 0) displaystring = "(NULL)";
    else displaystring = display;
  
    Berlin::Logger::log(Berlin::Logger::loader)
    << "setting video mode d=" << displaystring << " w=" << w << " h="
    << h << " bpp=" << bpp << std::endl;
    if (display == NULL)
    {
    my_surface = SDL_SetVideoMode(w, h, bpp,
                      SDL_HWSURFACE | SDL_HWPALETTE);
    SDL_WM_SetCaption("Berlin on SDL", NULL);
    }
    else
    {
    Pixel red_mask, green_mask, blue_mask, alpha_mask;

    switch(bpp) {
    case 8:
        std::cerr
        << "SDL::Drawable: indexed palette mode not supported."
        << std::endl;
        throw std::exception();
    case 16:
        red_mask   = 0x0000F800;
        green_mask = 0x000007E0;
        blue_mask  = 0x0000001F;
        alpha_mask = 0x00000000;
        break;
    case 24:
        red_mask   = 0x00FF0000;
        green_mask = 0x0000FF00;
        blue_mask  = 0x000000FF;
        alpha_mask = 0x00000000;
        break;
    case 32:
        red_mask   = 0x00FF0000;
        green_mask = 0x0000FF00;
        blue_mask  = 0x000000FF;
        alpha_mask = 0xFF000000;
        break;
    }
    my_surface = SDL_CreateRGBSurface( SDL_SRCCOLORKEY | SDL_SRCALPHA,
                       w, h, bpp,
                       red_mask, green_mask, blue_mask,
                       alpha_mask);
    }
  
    if (!my_surface) throw std::exception();
  
    my_depth = bpp ? d : my_surface->format->BytesPerPixel;
    my_need_locking = SDL_MUSTLOCK(my_surface);
}



SDL::Drawable::~Drawable()
{
    Prague::Trace trace("SDL::Drawable::~SDLDrawable()");
    SDL_FreeSurface(my_surface);
}



Fresco::Drawable::PixelFormat SDL::Drawable::pixel_format()
{
    Prague::Trace trace("SDL::Drawable::pixel_format()");

    Fresco::Drawable::PixelFormat format;
    const SDL_PixelFormat *pf = my_surface->format;

    format.depth       = pf->BitsPerPixel;
    format.size        = pf->BitsPerPixel;
    format.red_mask    = pf->Rmask;
    format.red_shift   = pf->Rshift;
    format.green_mask  = pf->Gmask;
    format.green_shift = pf->Gshift;
    format.blue_mask   = pf->Bmask;
    format.blue_shift  = pf->Bshift;
    format.alpha_mask  = pf->Amask;
    format.alpha_shift = pf->Ashift;

    return format;
}



Fresco::Drawable::BufferFormat SDL::Drawable::buffer_format()
{
    Prague::Trace trace("SDL::Drawable::buffer_format()");

    Fresco::Drawable::BufferFormat format;
    format.skip_width = 0;
    format.width = width();
    format.skip_height = 0;
    format.height = height();
    format.row_length = row_length();
    return format;
}



Fresco::PixelCoord SDL::Drawable::width() const { return my_width; }


Fresco::PixelCoord SDL::Drawable::height() const { return my_height; }


Fresco::PixelCoord SDL::Drawable::vwidth() const { return my_width; }


Fresco::PixelCoord SDL::Drawable::vheight() const { return my_height; }


Fresco::Coord SDL::Drawable::resolution(Fresco::Axis a) const
{
    return 0.1; // FIXME: hack, see below
    //  return a == Fresco::xaxis ?
    //    0.1 * 1.0:
    //    0.1 * 1.0; // FIXME: get some physical size in there.
}


Fresco::Coord SDL::Drawable::dpi(Fresco::Axis a) const
{ return resolution(a) * 254.0; }


inline Fresco::PixelCoord SDL::Drawable::row_length() const
{ return my_width * my_depth; /* return bytes-per-row */ }

void SDL::Drawable::flush() { SDL_UpdateRect(my_surface, 0, 0, 0, 0); }


void SDL::Drawable::flush(Fresco::PixelCoord x, Fresco::PixelCoord y,
            Fresco::PixelCoord w, Fresco::PixelCoord h)
{
    if (x < 0) { w += x; x = 0; }
    if (y < 0) { h += y; y = 0; }
    if (w > my_width) { w = my_width; }
    if (h > my_height) { h = my_height; }
    SDL_UpdateRect(my_surface, x, y, w, h);
}


SDL::Drawable::Pixel SDL::Drawable::map(const Fresco::Color &c) const
{
    double scale = 0xff;
    return SDL_MapRGBA(my_surface->format, 
               static_cast<Uint8>(c.red * scale), 
               static_cast<Uint8>(c.green * scale),
               static_cast<Uint8>(c.blue * scale),
               static_cast<Uint8>(c.alpha * scale));
}


void SDL::Drawable::blit(Fresco::PixelCoord x1, Fresco::PixelCoord y1, 
             Fresco::PixelCoord w, Fresco::PixelCoord h, 
             Fresco::PixelCoord x2, Fresco::PixelCoord y2)
{
    Prague::Trace("SDL::Drawable::blit: surface-surface");
    SDL_Rect r1,r2;
    r1.x = x1; r1.y = y1;
    r1.w = w; r1.h = h;
    r2.x = x2; r2.y = y2;
    r2.w = w; r2.h = h;
    if (r1.x < 0) { r1.w += r1.x; r1.x = 0; }
    if (r2.x < 0) { r2.w += r2.x; r2.x = 0; }
    if (r1.y < 0) { r1.h += r1.y; r1.y = 0; }
    if (r2.y < 0) { r2.h += r2.y; r2.y = 0; }
    SDL_BlitSurface(my_surface, &r1, my_surface, &r2);
}


void SDL::Drawable::blit(const SDL::Drawable &src,
             Fresco::PixelCoord x1, Fresco::PixelCoord y1, 
             Fresco::PixelCoord w, Fresco::PixelCoord h,
             Fresco::PixelCoord x2, Fresco::PixelCoord y2)
{
    Prague::Trace("SDL::Drawable::blit: other-surface");
    SDL_Rect r1,r2;
    r1.x = x1; r1.y = y1;
    r1.w = w; r1.h = h;
    r2.x = x2; r2.y = y2;
    r2.w = w; r2.h = h;
    if (r1.x < 0) { r1.w += r1.x; r1.x = 0; }
    if (r2.x < 0) { r2.w += r2.x; r2.x = 0; }
    if (r1.y < 0) { r1.h += r1.y; r1.y = 0; }
    if (r2.y < 0) { r2.h += r2.y; r2.y = 0; }
    SDL_BlitSurface(src.my_surface, &r1, my_surface, &r2);
}


void SDL::Drawable::blit(const Berlin::Console::Drawable & d,
             Fresco::PixelCoord x1, Fresco::PixelCoord y1,
             Fresco::PixelCoord w, Fresco::PixelCoord h,
             Fresco::PixelCoord x2, Fresco::PixelCoord y2)
{ blit(static_cast<const SDL::Drawable &>(d), x1, y1, w, h, x2, y2); }

void SDL::Drawable::blit(Fresco::Drawable_ptr d, 
             Fresco::PixelCoord x1, Fresco::PixelCoord y1, 
             Fresco::PixelCoord w, Fresco::PixelCoord h, 
             Fresco::PixelCoord x2, Fresco::PixelCoord y2)
{
    Prague::Trace("SDL::Drawable::blit 3");
    SDL::Drawable *servant =
    dynamic_cast<SDL::Drawable *>(Berlin::Console::instance()->
                      reference_to_servant(d));
    if (servant) blit(*servant, x1, y1, w, h, x2, y2);
    else Berlin::Logger::log(Berlin::Logger::drawing)
    << "SDL::Drawable::blit: unable to obtain servant from reference,"
    << std::endl;
}
