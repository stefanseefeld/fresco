/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
// #include <exception>
#include <vector>
extern "C"
{
#include <ggi/ggi-unix.h>
}

class GGI
{
public:
  class Drawable;
  GGI();
  ~GGI();
  static Drawable *drawable();//be prepared for multiple drawables (multi head, offscreen memory etc.)
private:
  static vector<Drawable *> drawables;
};

class GGI::Drawable
{
  friend class GGI;
public:
  bool nextEvent(ggi_event &event); // to be encapsulated further...
  void wakeup();
  void flush() { ggiFlush(vis);}
  PixelCoord width() const { return mode.visible.x;}
  PixelCoord height() const { return mode.visible.y;}
  PixelCoord vwidth() const { return mode.virt.x;}
  PixelCoord vheight() const { return mode.virt.y;}
  Coord resolution(Axis a) const
    {
      /*
       * mode.size is in mm
       * our base unit is 0.1 mm...
       */
      return a == xaxis ?
	0.1 * mode.visible.x / mode.size.x :
	0.1 * mode.visible.y / mode.size.y;
    }
  Coord dpi(Axis a) const { return resolution(a) * 254.0;}
  ggi_visual_t visual() { return vis;}
  const ggi_directbuffer *buffer(unsigned int i) const { return ggiDBGetBuffer (vis, i);}
private:
  Drawable();
  ~Drawable();
  ggi_visual_t vis;
  ggi_mode     mode;
  int          wakeupPipe[2];
};

#endif /* _GGI_hh */
