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
#ifndef _Pointer_hh
#define _Pointer_hh

#include <Berlin/GGI.hh>

/*
 * a little pointer...
 * should be extended when a first ImageKit is available which knows how to rasterize graphics
 * and how to transform this into ggi's internal format.
 */
class Pointer
{
public:
  Pointer(GGI::Drawable *);
  ~Pointer();
  void move(Coord, Coord);
  void draw();
  void save();
  void restore();
  bool intersects(const Coord &, const Coord &, const Coord &, const Coord &);
private:
  PixelCoord              origin[2];
  PixelCoord              position[2];
  PixelCoord              size[2];
  Coord                   scale[2];
  const ggi_directbuffer *dbuf;
  int                     depth;
  int                     stride;
  int                     maxCoord;
  unsigned char	         *image;
  unsigned char	         *mask;
  unsigned char          *cache;
};

inline bool Pointer::intersects(const Coord &l, const Coord &r, const Coord &t, const Coord &b)
{
  return
    l/size[0] <= position[0] + size[0] &&
    r/size[0] >= position[0] &&
    t/size[1] <= position[1] + size[1] &&
    b/size[1] >= position[1];
}

#endif /* _Pointer_hh */
