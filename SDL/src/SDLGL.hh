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

#ifndef _SDLGL_hh
#define _SDLGL_hh

#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/ThreadQueue.hh>
#include <Berlin/Console/GLContext.hh>
#include "Pointer.hh"

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
  class Callback;
  GLContext * _glcontext;
};





// ---------------------------------------------------------------
// class GLContext
// ---------------------------------------------------------------

class GLContext : public virtual ::GLContext
{
public:
  GLContext();
  virtual ~GLContext();

  void add_to_queue(::GLContext::Callback *);
  void flush();

private:
  Prague::Thread *gl_thread;
  Prague::Thread::Queue<GLContext::Callback *> *queue;

  class Initialize;
  class Flush;

  SDL::Drawable     *_drawable;
  int                _isDoubleBuffered;
};





// ---------------------------------------------------------------
// class GLPointer
// ---------------------------------------------------------------

class GLPointer : public SDL::Pointer
{
public:
  GLPointer(Drawable *, Fresco::Raster_ptr, GLContext *glcontext);
  ~GLPointer();

  void draw();
  void save();
  void restore();

private:
  GLContext *my_glcontext;
  Fresco::PixelCoord _max_y_size;
  Fresco::Raster_ptr my_raster;

  class Save;
  class Restore;
  class Draw;

  std::vector<unsigned char> my_cursor;
  std::vector<unsigned char> my_saved_area;
};

}; // namespace SDL

#endif // _SDL_GL_hh
