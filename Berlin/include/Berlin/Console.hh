/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _Console_hh
#define _Console_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
#include <Berlin/config.hh>
// #include <exception>

template <typename T>
class DrawableTie
{
public:
  typedef typename T::Pixel Pixel;
  struct PixelFormat
  {
    long depth;          /* Number of significant bits */
    long size;           /* Physical size in bits */
    long red_mask;       /* Bitmask of red bits */
    long red_shift;      /* Shift  for red bits */
    long green_mask;     /* Bitmask of green bits */
    long green_shift;    /* Shift  for green bits */
    long blue_mask;      /* Bitmask of blue bits */
    long blue_shift;     /* Shift  for blue bits */
    long alpha_mask;     /* Bitmask of alphachannel bits */
    long alpha_shift;    /* Shift  for alpha bits */
  };
  DrawableTie(T *tt) : t(tt) {}
  ~DrawableTie() { delete t;}
  PixelFormat pixelFormat() { return t->pixelFormat();}
  PixelCoord width() const { return t->width();}
  PixelCoord height() const { return t->height();}
  PixelCoord vwidth() const { return t->vwidth();}
  PixelCoord vheight() const { return t->vheight();}
  Coord resolution(Axis a) const { return t->resolution(a);}
  Coord dpi(Axis a) const { return t->dpi(a);}
  PixelCoord rowlength() { return t->rowlength();}
  Pixel map(const Color &c) { return t->map(c);}
  void *readBuffer() { return t->readBuffer();}
  void *writeBuffer() { return t->writeBuffer();}
  /*
   * read one or more pixels from framebuffer
   */
  void readPixel(PixelCoord x, PixelCoord y, Pixel &p) { t->readPixel(x, y, p);}
  void readPixels(PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h, void *p) { t->readPixels(x, y, w, h, p);}
  /*
   * draw primitives with the current color (Pixel)
   */
  void setColor(Pixel p) { t->setColor(p);}
  void drawPixel(PixelCoord x, PixelCoord y) { t->drawPixel(x, y);}
  void drawHLine(PixelCoord x, PixelCoord y, PixelCoord w) { t->drawHLine(x, y, w);}
  void drawVLine(PixelCoord x, PixelCoord y, PixelCoord h) { t->drawVLine(x, y, h);}
  void drawLine(PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) { t->drawLine(x, y, w, h);}
  void drawBox(PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) { t->drawBox(x, y, w, h);}
  /*
   * draw primitives with the given color (Pixel)
   */
  void putPixel(PixelCoord x, PixelCoord y, Pixel p) { t->putPixel(x, y, p);}
  void putHLine(PixelCoord x, PixelCoord y, PixelCoord w, void *p) { t->putHLine(x, y, w, p);}
  void putVLine(PixelCoord x, PixelCoord y, PixelCoord h, void *p) { t->putVLine(x, y, h, p);}
  void drawPixels(PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h, void *p) { t->drawPixels(x, y, w, h, p);}
  /*
   * fast blits
   */
  void blit(PixelCoord x1, PixelCoord y1, PixelCoord w, PixelCoord h, PixelCoord x2, PixelCoord y2)
  { t->blit(x1, y1, w, h, x2, y2);}
  void blit(const DrawableTie &d, PixelCoord x1, PixelCoord y1, PixelCoord w, PixelCoord h, PixelCoord x2, PixelCoord y2)
  { t->blit(*d.t, x1, y1, w, h, x2, y2);}

  void flush() { t->flush();}
  void flush(PixelCoord x, PixelCoord y, PixelCoord w, PixelCoord h) { t->flush(x, y, w, h);}

  T &impl() { return *t;}
private:
  DrawableTie(const DrawableTie &);
  DrawableTie &operator = (const DrawableTie &);
  T *t;
};

template <typename T>
class ConsoleTie
{
  struct Reaper { ~Reaper() { delete ConsoleTie::t;}};
  friend struct Reaper;
public:
  typedef DrawableTie<typename T::Drawable> Drawable;
  ConsoleTie() {}
  ~ConsoleTie() {}
  static void open() { if (!t) t = new T();}
  static DrawableTie<typename T::Drawable> *drawable() { return T::drawable();}
  static DrawableTie<typename T::Drawable> *newDrawable(PixelCoord w, PixelCoord h, PixelCoord d) { return T::newDrawable(w, h, d);}

  static Input::Event *nextEvent() { return t->nextEvent();}
  static void wakeup() { t->wakeup();}
  static void activate_autoplay() { t->activate_autoplay();}
private:
  static T *t;
  static Reaper reaper;
};

#ifdef CONSOLE_IMPL
#  if CONSOLE_IMPL == GGI
#  include <Berlin/GGI.hh>

typedef ConsoleTie<GGIConsole> Console;

#  elif CONSOLE_IMPL == SDL
#  include <Berlin/SDL.hh>

typedef ConsoleTie<SDLConsole> Console;

#  else
#  warning "unknown console type defined"
#  endif
#else
#  warning "no console type defined"
#endif

#endif /* _Console_hh */