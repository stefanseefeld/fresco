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
  DrawableTie<SDLDrawable>::PixelFormat pixel_format();
  PixelCoord width() const;
  PixelCoord height() const;
  PixelCoord vwidth() const;
  PixelCoord vheight() const;
  Coord resolution(Axis a) const;
  Coord dpi(Axis a) const;
  PixelCoord row_length() const;
  Pixel map(const Color &);
  void *read_buffer() const;
  void *write_buffer() const;
  /*
   * read one or more pixels from framebuffer
   */
  void read_pixel(PixelCoord, PixelCoord, Pixel &);
  void read_pixels(PixelCoord, PixelCoord, PixelCoord, PixelCoord, void *);
  /*
   * draw primitives with the current color (Pixel)
   */
  void set_color(Pixel);
  void draw_pixel(PixelCoord, PixelCoord);
  void draw_hline(PixelCoord, PixelCoord, PixelCoord);
  void draw_vline(PixelCoord, PixelCoord, PixelCoord);
  void draw_line(PixelCoord, PixelCoord, PixelCoord, PixelCoord);
  void draw_box(PixelCoord, PixelCoord, PixelCoord, PixelCoord);
  /*
   * draw primitives with the given color (Pixel)
   */
  void put_pixel(PixelCoord, PixelCoord, Pixel);
  void put_hline(PixelCoord, PixelCoord, PixelCoord, void *);
  void put_vline(PixelCoord, PixelCoord, PixelCoord, void *);
  void draw_pixels(PixelCoord, PixelCoord, PixelCoord, PixelCoord, void *);
  /*
   * fast blits
   */
  void blit(PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord);
  void blit(const GGIDrawable &, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord, PixelCoord);

  void flush();
  void flush(PixelCoord, PixelCoord, PixelCoord, PixelCoord);
  void init() { }
  void finish() { }
private:
  SDLDrawable(const char *);
  ~SDLDrawable();
  SDL_Surface _surface;
  int         _width;
  int         _height;
  int         _depth;
};

class SDLConsole
{
public:
  typedef SDLDrawable Drawable;
  SDLConsole(int &argc, char **argv);
  ~SDLConsole();
  static DrawableTie<Drawable> *drawable();
  static DrawableTie<Drawable> *create_drawable(PixelCoord, PixelCoord, PixelCoord);
  static DrawableTie<Drawable> *create_drawable(Drawable *);

  Input::Event *next_event();
  void wakeup();
  void activate_autoplay();
private:
};

#endif
