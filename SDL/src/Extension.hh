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

#ifndef _SDL_Extension_hh
#define _SDL_Extension_hh

#include <Warsaw/config.hh>
#include <Berlin/Console.hh>
#include <Console/SDL/Console.hh>
#include <Console/SDL/Drawable.hh>
#include <Console/Renderer.hh>
#include <Console/DirectBuffer.hh>
#include <Console/GLContext.hh>

namespace SDL
{

class Drawable;





// ---------------------------------------------------------------
// class Extension
// ---------------------------------------------------------------

class DrawableExtension : virtual public Console::Drawable::Extension
{
public:
  DrawableExtension() : _drawable(0) { }

  virtual void attach(::Console::Drawable *);

  SDL::Drawable * drawable()
  {
    return _drawable;
  }

private:
  SDL::Drawable * _drawable;
};





// ---------------------------------------------------------------
// class Renderer
// ---------------------------------------------------------------

class Renderer : public SDL::DrawableExtension,
		 virtual public ::Renderer
{
public:
  Renderer();

  virtual void set_color(const Warsaw::Color &);

  virtual void draw_pixel(Warsaw::PixelCoord, Warsaw::PixelCoord);

  virtual void draw_hline(Warsaw::PixelCoord, Warsaw::PixelCoord,
                          Warsaw::PixelCoord);

  virtual void draw_vline(Warsaw::PixelCoord, Warsaw::PixelCoord,
                          Warsaw::PixelCoord);

  virtual void draw_line(Warsaw::PixelCoord, Warsaw::PixelCoord,
                         Warsaw::PixelCoord, Warsaw::PixelCoord);

  virtual void draw_box(Warsaw::PixelCoord, Warsaw::PixelCoord,
                        Warsaw::PixelCoord, Warsaw::PixelCoord);

private:
  void put_pixel(Warsaw::PixelCoord, Warsaw::PixelCoord);

  SDL::Drawable::Pixel _color;
};





// ---------------------------------------------------------------
// class DirectBuffer
// ---------------------------------------------------------------
 
class DirectBuffer : public SDL::DrawableExtension,
		     virtual public ::DirectBuffer
{
public:
  DirectBuffer();
  void attach(::Console::Drawable *);

  virtual Guard read_buffer();

  virtual Guard write_buffer();
};





// ---------------------------------------------------------------
// class GLContext
// ---------------------------------------------------------------

class GLContext : public ::GLContext
{
  typedef void (*GL_Enable_Func)(unsigned int type);
  typedef void (*GL_Disable_Func)(unsigned int type);
  typedef void (*GL_CopyPixels_Func)(int x, int y,
                                     int width, int height,
                                     unsigned int type);
  typedef void (*GL_DrawBuffer_Func)(unsigned int type);
  typedef void (*GL_ReadBuffer_Func)(unsigned int type);
  
public:
  GLContext();
  virtual ~GLContext();

  void flush();

private:
  SDL::Drawable     *_drawable;
  int                _isDoubleBuffered;
  GL_Enable_Func     _glEnable_ptr;
  GL_Disable_Func    _glDisable_ptr;
  GL_CopyPixels_Func _glCopyPixels_ptr;
  GL_DrawBuffer_Func _glDrawBuffer_ptr;
  GL_ReadBuffer_Func _glReadBuffer_ptr;
};

}; // namespace SDL

#endif
