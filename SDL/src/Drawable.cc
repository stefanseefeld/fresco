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
#include <Berlin/Logger.hh>
#include <Console/SDL/Drawable.hh>


// ---------------------------------------------------------------
// class SDL::Drawable (implementation)
// ---------------------------------------------------------------

SDL::Drawable::Drawable(const char *display,
			Warsaw::PixelCoord w, Warsaw::PixelCoord h,
			Warsaw::PixelCoord d)
{
  Prague::Trace trace("SDL::Drawable::Drawable()");

  static unsigned int _redMask;
  static unsigned int _greenMask;
  static unsigned int _blueMask;
  static unsigned int _alphaMask;

  int bpp;

  switch( d ) {
  case 0: bpp = 0; break;
  case 1: bpp = 8; break;
  case 2: bpp = 16; break;
  case 3: bpp = 24; break;
  case 4: bpp = 32; break;
  default:
    std::cerr << "SDL::Drawable: Warning: " << d
              << " bytes per pixel not supported" << std::endl;
  }
  
  _width = w;
  _height = h;
  Logger::log(Logger::loader) << "setting video mode d = " << display
                              << " w=" << w << " h= " << h << " bpp=" << bpp
                              << std::endl;
  if (display == NULL) {
    _surface = SDL_SetVideoMode( w, h, bpp, SDL_HWSURFACE | SDL_HWPALETTE );
    SDL_WM_SetCaption("Berlin on SDL", NULL);
    _redMask = _surface->format->Rmask;
    _greenMask = _surface->format->Gmask;
    _blueMask = _surface->format->Bmask;
    _alphaMask = _surface->format->Amask;
  } else {
    _surface = SDL_CreateRGBSurface( SDL_SRCCOLORKEY | SDL_SRCALPHA,
                                     w, h, bpp,
                                     _redMask, _greenMask, _blueMask, _alphaMask);
  }
  
  if (!_surface) throw std::exception();
  
  _depth = bpp ? d : _surface->format->BytesPerPixel;
  _need_locking = SDL_MUSTLOCK(_surface);
}



SDL::Drawable::~Drawable()
{
  Prague::Trace trace("SDL::Drawable::~SDLDrawable()");

  SDL_FreeSurface(_surface);
}



Warsaw::Drawable::PixelFormat SDL::Drawable::pixel_format()
{
  Prague::Trace trace("SDL::Drawable::pixel_format()");

  Warsaw::Drawable::PixelFormat format;
  const SDL_PixelFormat *pf = _surface->format;

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



Warsaw::Drawable::BufferFormat SDL::Drawable::buffer_format()
{
  Prague::Trace trace("SDL::Drawable::buffer_format()");

  Warsaw::Drawable::BufferFormat format;
  format.skip_width = 0;
  format.width = width();
  format.skip_height = 0;
  format.height = height();
  format.row_length = row_length();
  return format;
}



Warsaw::PixelCoord SDL::Drawable::width() const { return _width;}


Warsaw::PixelCoord SDL::Drawable::height() const { return _height;}


Warsaw::PixelCoord SDL::Drawable::vwidth() const { return _width;}


Warsaw::PixelCoord SDL::Drawable::vheight() const { return _height;}


Warsaw::Coord SDL::Drawable::resolution(Warsaw::Axis a) const
{
  return 0.1; // FIXME: hack, see below
  //  return a == Warsaw::xaxis ?
  //    0.1 * 1.0:
  //    0.1 * 1.0; // FIXME: get some physical size in there.
}


Warsaw::Coord SDL::Drawable::dpi(Warsaw::Axis a) const {
  return resolution(a) * 254.0;
}


inline Warsaw::PixelCoord SDL::Drawable::row_length() const {
  return _width * _depth; // return bytes-per-row
}

void SDL::Drawable::flush() { SDL_UpdateRect( _surface, 0, 0, _width, _height);}


void SDL::Drawable::flush(Warsaw::PixelCoord x, Warsaw::PixelCoord y,
			Warsaw::PixelCoord w, Warsaw::PixelCoord h)
{
  if (x < 0) { w += x; x = 0;}
  if (y < 0) { h += y; y = 0;}
  SDL_UpdateRect(_surface, x, y, w, h);
}


SDL::Drawable::Pixel SDL::Drawable::map(const Warsaw::Color &c) const
{
  double scale = 0xff;
  return SDL_MapRGBA(_surface->format, 
                     static_cast<Uint8>(c.red * scale), 
                     static_cast<Uint8>(c.green * scale),
                     static_cast<Uint8>(c.blue * scale),
                     static_cast<Uint8>(c.alpha * scale));
}


void SDL::Drawable::blit(Warsaw::PixelCoord x1, Warsaw::PixelCoord y1, 
			 Warsaw::PixelCoord w, Warsaw::PixelCoord h, 
			 Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
{
  Prague::Trace("SDL::Drawable::blit: surface-surface");
  SDL_Rect r1,r2;
  r1.x = x1; r1.y = y1;
  r1.w = w; r1.h = h;
  r2.x = x2; r2.y = y2;
  r2.w = w; r2.h = h;
  if (r1.x < 0) { r1.w += r1.x; r1.x = 0; } if (r2.x < 0) { r2.w += r2.x; r2.x =
 0; }
  if (r1.y < 0) { r1.h += r1.y; r1.y = 0; } if (r2.y < 0) { r2.h += r2.y; r2.y =
 0; }
  SDL_BlitSurface(_surface, &r1, _surface, &r2);
  flush(x2, y2, w, h);
}


void SDL::Drawable::blit(const SDL::Drawable &src,
			 Warsaw::PixelCoord x1, Warsaw::PixelCoord y1, 
			 Warsaw::PixelCoord w, Warsaw::PixelCoord h,
			 Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
{
  Prague::Trace("SDL::Drawable::blit: other-surface");
  SDL_Rect r1,r2;
  r1.x = x1; r1.y = y1;
  r1.w = w; r1.h = h;
  r2.x = x2; r2.y = y2;
  r2.w = w; r2.h = h;
  if (r1.x < 0) { r1.w += r1.x; r1.x = 0; } if (r2.x < 0) { r2.w += r2.x; r2.x = 0; }
  if (r1.y < 0) { r1.h += r1.y; r1.y = 0; } if (r2.y < 0) { r2.h += r2.y; r2.y = 0; }
  SDL_BlitSurface(src._surface, &r1, _surface, &r2);
  flush(x2, y2, w, h);
}


void SDL::Drawable::blit(const ::Console::Drawable & d,
			 Warsaw::PixelCoord x1, Warsaw::PixelCoord y1,
			 Warsaw::PixelCoord w, Warsaw::PixelCoord h,
			 Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
{
  blit(static_cast<const SDL::Drawable &>(d), x1, y1, w, h, x2, y2);
}

void SDL::Drawable::blit(Warsaw::Drawable_ptr d, 
			 Warsaw::PixelCoord x1, Warsaw::PixelCoord y1, 
			 Warsaw::PixelCoord w, Warsaw::PixelCoord h, 
			 Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
{
  Prague::Trace("SDL::Drawable::blit 3");
  SDL::Drawable *servant = dynamic_cast<SDL::Drawable *>(::Console::instance()->
							 reference_to_servant(d));
  if (servant) blit(*servant, x1, y1, w, h, x2, y2);
  else Logger::log(Logger::drawing) << "SDL::Drawable::blit: unable to obtain servant "
                                    << "from reference" << endl;
}
