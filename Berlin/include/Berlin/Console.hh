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
    CORBA::Long depth;          /* Number of significant bits */
    CORBA::Long size;           /* Physical size in bits */
    CORBA::Long red_mask;       /* Bitmask of red bits */
    CORBA::Long red_shift;      /* Shift  for red bits */
    CORBA::Long green_mask;     /* Bitmask of green bits */
    CORBA::Long green_shift;    /* Shift  for green bits */
    CORBA::Long blue_mask;      /* Bitmask of blue bits */
    CORBA::Long blue_shift;     /* Shift  for blue bits */
    CORBA::Long alpha_mask;     /* Bitmask of alphachannel bits */
    CORBA::Long alpha_shift;    /* Shift  for alpha bits */
  };
  DrawableTie(T *tt) : t(tt) {}
  ~DrawableTie() { delete t;}
  PixelFormat pixelFormat() { return t->pixelFormat();}
  Warsaw::PixelCoord width() const { return t->width();}
  Warsaw::PixelCoord height() const { return t->height();}
  Warsaw::PixelCoord vwidth() const { return t->vwidth();}
  Warsaw::PixelCoord vheight() const { return t->vheight();}
  Warsaw::Coord resolution(Warsaw::Axis a) const { return t->resolution(a);}
  Warsaw::Coord dpi(Warsaw::Axis a) const { return t->dpi(a);}
  Warsaw::PixelCoord rowlength() { return t->rowlength();}
  Pixel map(const Warsaw::Color &c) { return t->map(c);}
  void *readBuffer() { return t->readBuffer();}
  void *writeBuffer() { return t->writeBuffer();}
  /*
   * read one or more pixels from framebuffer
   */
  void readPixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Pixel &p) { t->readPixel(x, y, p);}
  void readPixels(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h, void *p) { t->readPixels(x, y, w, h, p);}
  /*
   * draw primitives with the current color (Pixel)
   */
  void setColor(Pixel p) { t->setColor(p);}
  void drawPixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y) { t->drawPixel(x, y);}
  void drawHLine(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w) { t->drawHLine(x, y, w);}
  void drawVLine(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord h) { t->drawVLine(x, y, h);}
  void drawLine(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h) { t->drawLine(x, y, w, h);}
  void drawBox(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h) { t->drawBox(x, y, w, h);}
  /*
   * draw primitives with the given color (Pixel)
   */
  void putPixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Pixel p) { t->putPixel(x, y, p);}
  void putHLine(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, void *p) { t->putHLine(x, y, w, p);}
  void putVLine(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord h, void *p) { t->putVLine(x, y, h, p);}
  void drawPixels(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h, void *p) { t->drawPixels(x, y, w, h, p);}
  /*
   * fast blits
   */
  void blit(Warsaw::PixelCoord x1, Warsaw::PixelCoord y1, Warsaw::PixelCoord w, Warsaw::PixelCoord h, Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
  { t->blit(x1, y1, w, h, x2, y2);}
  void blit(const DrawableTie &d, Warsaw::PixelCoord x1, Warsaw::PixelCoord y1, Warsaw::PixelCoord w, Warsaw::PixelCoord h, Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
  { t->blit(*d.t, x1, y1, w, h, x2, y2);}

  void flush() { t->flush();}
  void flush(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h) { t->flush(x, y, w, h);}

  /**
   * Init and finish hooks called by the server when the scene is
   * about to be drawn, and when it has been drawn, respectively. This
   * is a suitable place to add calls for building display lists, for
   * example (this is what is done in the GLUT and CAVELib consoles).
   **/
  void init() { t->init(); }
  void finish() { t->finish(); }
    
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
  static void open(int &argc, char **argv) { if (!t) t = new T(argc, argv);}
  static DrawableTie<typename T::Drawable> *drawable() { return T::drawable();}
  static DrawableTie<typename T::Drawable> *newDrawable(Warsaw::PixelCoord w, Warsaw::PixelCoord h, Warsaw::PixelCoord d) { return T::newDrawable(w, h, d);}

  static Warsaw::Input::Event *next_event() { return t->next_event();}
  static void wakeup() { t->wakeup();}
  static void activate_autoplay() { t->activate_autoplay();}
private:
  static T *t;
  static Reaper reaper;
};

#if defined(CONSOLE_GGI)
#  include <Berlin/GGI.hh>

typedef ConsoleTie<GGIConsole> Console;

#elif defined(CONSOLE_SDL)
#  include <Berlin/SDL.hh>

typedef ConsoleTie<SDLConsole> Console;

#elif defined(CONSOLE_CAVELIB)
#  include <Berlin/CAVE.hh>

typedef ConsoleTie<CAVEConsole> Console;

#elif defined(CONSOLE_GLUT)
#  include <Berlin/GLUT.hh>

typedef ConsoleTie<GLUTConsole> Console;

#else
#  warning "no console type defined"
#endif

#endif /* _Console_hh */
