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
#ifndef _GGI_hh
#define _GGI_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
#include <vector>
extern "C"
{
#include <ggi/ggi-unix.h>
}

class GGIConsole;

class GGIDrawable
{
  friend class GGIConsole;
  friend class DrawableTie<GGIDrawable>;
public:
  typedef ggi_pixel Pixel;
  DrawableTie<GGIDrawable>::PixelFormat pixelFormat();
  Warsaw::PixelCoord width() const { return mode.visible.x;}
  Warsaw::PixelCoord height() const { return mode.visible.y;}
  Warsaw::PixelCoord vwidth() const { return mode.virt.x;}
  Warsaw::PixelCoord vheight() const { return mode.virt.y;}
  Warsaw::Coord resolution(Warsaw::Axis a) const;
  Warsaw::Coord dpi(Warsaw::Axis a) const { return resolution(a) * 254.0;}
  Warsaw::PixelCoord rowlength() { return ggiDBGetBuffer(vis, 0)->buffer.plb.stride;}
  Pixel map(const Warsaw::Color &);
  void *readBuffer() { return ggiDBGetBuffer (vis, 0)->read;}
  void *writeBuffer() { return ggiDBGetBuffer (vis, 0)->write;}
  /*
   * read one or more pixels from framebuffer
   */
  void readPixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Pixel &p) { ggiGetPixel(vis, x, y, &p);}
  void readPixels(Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, void *);
  /*
   * draw primitives with the current color (Pixel)
   */
  void setColor(Pixel p) { ggiSetGCForeground(vis, p);}
  void drawPixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y) { ggiDrawPixel(vis, x, y);}
  void drawHLine(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w) { ggiDrawHLine(vis, x, y, w);}
  void drawVLine(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord h) { ggiDrawVLine(vis, x, y, h);}
  void drawLine(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h) { ggiDrawLine(vis, x, y, x + w, y + h);}
  void drawBox(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h) { ggiDrawBox(vis, x, y, w, h);}
  /*
   * draw primitives with the given color (Pixel)
   */
  void putPixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Pixel p) { ggiPutPixel(vis, x, y, p);}
  void putHLine(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, void *p) { ggiPutHLine(vis, x, y, w, p);}
  void putVLine(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord h, void *p) { ggiPutVLine(vis, x, y, h, p);}
  void drawPixels(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h, void *p) { ggiPutBox(vis, x, y, w, h, p);}
  /*
   * fast blits
   */
  void blit(Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord);
  void blit(const GGIDrawable &, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord);

  void flush() { ggiFlush(vis);}
  void flush(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h) { ggiFlushRegion(vis, x, y, w, h);}
  /*
   * if you really must ask...
   */
  ggi_visual_t visual() { return vis;}
  const ggi_directbuffer *buffer(unsigned int i) const { return ggiDBGetBuffer (vis, i);}
  void init() { }
  void finish() { }
private:
  GGIDrawable(const char *);
  ~GGIDrawable();
  ggi_visual_t  vis;
  ggi_mode      mode;
};

class GGIConsole
{
public:
  typedef GGIDrawable Drawable;
  GGIConsole(int &, char **);
  ~GGIConsole();
  static DrawableTie<Drawable> *drawable();
  static DrawableTie<Drawable> *newDrawable(Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord);

  Warsaw::Input::Event *next_event();
  void wakeup();
  void activate_autoplay() {autoplay = true;}
private:
  Warsaw::Input::Event *synthesize(const ggi_event &);
  /*
   * to be used for event notification
   */
  ggi_visual_t  visual;
  /*
   * to be used for pointing devices
   */
  long          size[2];
  long          pos[2];
  double        res[2];
  bool          autoplay;
  int           wakeupPipe[2];
  static vector<DrawableTie<Drawable> *> drawables;
};

inline GGIDrawable::Pixel GGIDrawable::map(const Warsaw::Color &c)
{
  ggi_color c2;
  // GGI _appears_ to use 16 bit color + alpha throughout. *sigh*
  static double scale = 0xffff;
  c2.r = static_cast<uint16>(c.red * scale);
  c2.g = static_cast<uint16>(c.green * scale);
  c2.b = static_cast<uint16>(c.blue * scale);
  c2.a = static_cast<uint16>(c.alpha * scale);
  return ggiMapColor(vis, &c2);
}

inline Warsaw::Coord GGIDrawable::resolution(Warsaw::Axis a) const
{
  /*
   * mode.size is in mm
   * our base unit is 0.1 mm...
   */
  return a == Warsaw::xaxis ?
    0.1 * mode.visible.x / mode.size.x :
    0.1 * mode.visible.y / mode.size.y;
}

inline void GGIDrawable::readPixels(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h, void *p)
{
  ggiGetBox(vis, x, y, w, h, p);
}

inline void GGIDrawable::blit(Warsaw::PixelCoord x1, Warsaw::PixelCoord y1, Warsaw::PixelCoord w, Warsaw::PixelCoord h, Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
{
  ggiCopyBox(vis, x1, y1, w, h, x2, y2);
}

inline void GGIDrawable::blit(const GGIDrawable &d, Warsaw::PixelCoord x1, Warsaw::PixelCoord y1, Warsaw::PixelCoord w, Warsaw::PixelCoord h, Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
{
  ggiCrossBlit(d.vis, x1, y1, w, h, vis, x2, y2);
}

#endif /* _GGI_hh */
