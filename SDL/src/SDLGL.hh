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

#ifndef _SDL_GL_hh
#define _SDL_GL_hh

#include <Console/SDL/Pointer.hh>
#include <Console/GLContext.hh>

extern "C" {
#include <GL/gl.h>
}

namespace SDL
{



// ---------------------------------------------------------------
// class GLExposeHandler
// ---------------------------------------------------------------

class GLExposeHandler : public SDL::ExposeHandler
{
public:
  GLExposeHandler(GLContext * gl) :
    _glcontext(gl)
  { }
  ~GLExposeHandler() { }

  void refresh_screen();
private:
  GLContext * _glcontext;
};





// ---------------------------------------------------------------
// class GLContext
// ---------------------------------------------------------------

class GLContext : public ::GLContext
{
public:
  GLContext();
  virtual ~GLContext();

  void flush();

private:
  SDL::Drawable     *_drawable;
  int                _isDoubleBuffered;
};





// ---------------------------------------------------------------
// class GLPointer
// ---------------------------------------------------------------

class GLPointer : public SDL::Pointer
{
public:
  GLPointer(Drawable *, Fresco::Raster_ptr);
  ~GLPointer();

  void draw();
  void save();
  void restore();

private:
  Fresco::PixelCoord _max_y_size;

  Uint8  * _cursor;
  Uint8  * _saved_area;
};

}; // namespace SDL

#endif // _SDL_GL_hh
