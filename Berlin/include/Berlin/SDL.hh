/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _SDL_hh
#define _SDL_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
#include <vector>
extern "C"
{
#include "SDL.h"
}

class SDLConsole;

class SDLDrawable
{
  friend class SDLConsole;
  friend class DrawableTie<SDLDrawable>;
public:
  typedef long Pixel;
  DrawableTie<SDLDrawable>::PixelFormat pixelFormat();
  PixelCoord width() const;
  PixelCoord height() const;
  PixelCoord vwidth() const;
  PixelCoord vheight() const;
  Coord resolution(Axis a) const;
  Coord dpi(Axis a) const;
  PixelCoord rowlength() const;
  Pixel map(const Color &);
  void *readBuffer() const;
  void *writeBuffer() const;
  /*
   * read one or more pixels from framebuffer
   */
  void readPixel(PixelCoord, PixelCoord, Pixel &);
  void readPixels(PixelCoord, PixelCoord, PixelCoord, PixelCoord, void *);
  /*
   * draw primitives with the current color (Pixel)
   */
  void setColor(Pixel);
  void drawPixel(PixelCoord, PixelCoord);
  void drawHLine(PixelCoord, PixelCoord, PixelCoord);
  void drawVLine(PixelCoord, PixelCoord, PixelCoord);
  void drawLine(PixelCoord, PixelCoord, PixelCoord, PixelCoord);
  void drawBox(PixelCoord, PixelCoord, PixelCoord, PixelCoord);
  /*
   * draw primitives with the given color (Pixel)
   */
  void putPixel(PixelCoord, PixelCoord, Pixel);
  void putHLine(PixelCoord, PixelCoord, PixelCoord, void *);
  void putVLine(PixelCoord, PixelCoord, PixelCoord, void *);
  void drawPixels(PixelCoord, PixelCoord, PixelCoord, PixelCoord, void *);
  /*
   * fast blits
   */
  void blit(PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord);
  void blit(const GGIDrawable &, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord);

  void flush();
  void flush(PixelCoord, PixelCoord, PixelCoord, PixelCoord);
private:
  SDLDrawable(const char *);
  ~SDLDrawable();
  SDL_Surface surface;
  int         w, h, d;
};

class SDLConsole
{
public:
  typedef SDLDrawable Drawable;
  SDLConsole();
  ~SDLConsole();
  static DrawableTie<Drawable> *drawable();
  static DrawableTie<Drawable> *newDrawable(PixelCoord, PixelCoord, PixelCoord);

  Input::Event *nextEvent();
  void wakeup();
  void activate_autoplay();
private:
};

#endif /* _SDL_hh */
