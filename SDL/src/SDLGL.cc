/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 2001 Philip Philonenko <philonenko@orgacom.ru> 
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

#include <Prague/Sys/Tracer.hh>
#include <Berlin/Logger.hh>

#include <Console/SDL/SDLGL.hh>





// ---------------------------------------------------------------
// class SDL::GLContext (implementation)
// ---------------------------------------------------------------

SDL::GLContext::GLContext()
{
  Prague::Trace trace("SDL::GLContext::GLContext()");

  _drawable =
    dynamic_cast<SDL::Drawable *>(::Console::instance()->drawable());

  Warsaw::PixelCoord w(_drawable->width());
  Warsaw::PixelCoord h(_drawable->height());
  
  Logger::log(Logger::loader) << "setting video mode GL " << " w="
			      << w << " h= " << h << endl;
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_Surface * surface = SDL_SetVideoMode(w, h, 0,
					   SDL_HWSURFACE | SDL_HWPALETTE |
					   SDL_OPENGL |
					   SDL_DOUBLEBUF |
					   SDL_HWACCEL);
  SDL_WM_SetCaption("Berlin on SDL (OpenGL)", NULL);
  SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &_isDoubleBuffered);
  if (!_isDoubleBuffered) {
    cout << "SDL_Error: " << SDL_GetError() << endl;
    throw;
  }
  
  // HACK: Replace the 'real' drawable with its OpenGL-replacement.
  _drawable->_surface = surface;
  _drawable->_width = w;
  _drawable->_height = h;
  
  int bits;
  glGetIntegerv(GL_DEPTH_BITS, &bits);
  switch (bits) 
    {
    case  0: _drawable->_depth = 0; break;
    case  8: _drawable->_depth = 1; break;
    case 16: _drawable->_depth = 2; break;
    case 24: _drawable->_depth = 3; break;
    case 32: _drawable->_depth = 4; break;
    default:
      _drawable->_depth = 0;
    }

  glReadBuffer(GL_FRONT);
  glDrawBuffer(GL_BACK);

  // setup PointerManager:
  dynamic_cast<SDL::Console *>(::Console::instance())->
    set_PointerManager(new SDL::PointerManagerT<GLPointer>);
}


SDL::GLContext::~GLContext()
{
  Prague::Trace trace("SDL::GLContext::~SDLGLContext()");
}


void SDL::GLContext::flush() {
  Prague::Trace trace("SDL::GLContext::flush()");
  
  if (_isDoubleBuffered) {
    SDL_GL_SwapBuffers();
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);
    glCopyPixels(0, 0, _drawable->width(), _drawable->height(),
		 GL_COLOR);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);
  } else {
    // FIXME: TODO
  }
}





// ---------------------------------------------------------------
// class SDL::GLPointer (implementation)
// ---------------------------------------------------------------

SDL::GLPointer::GLPointer(Drawable * drawable, Warsaw::Raster_ptr raster)
{
  Prague::Trace trace("SDL::GLPointer::GLPointer(...)");

  // copy over the Raster:
  _raster = Warsaw::Raster::_duplicate(raster);

  // get screensizes:
  _max_y_size = drawable->height();

  // copy over the Raster:
  _raster = Warsaw::Raster::_duplicate(raster);

  // Disable SDL default mousecursor
  SDL_ShowCursor(0);

  // Copy the raster over into the Drawable:
  Warsaw::Raster::Info info = raster->header();
  Warsaw::Raster::ColorSeq_var pixels;
  Warsaw::Raster::Index lower, upper;
  lower.x = lower.y = 0;
  upper.x = info.width, upper.y = info.height;
  raster->store_pixels(lower, upper, pixels);
  _origin[0] = _origin[1] = 0;
  _size[0] = info.width;
  _size[1] = info.height;
  _scale[0] = 1.0/drawable->resolution(Warsaw::xaxis);
  _scale[1] = 1.0/drawable->resolution(Warsaw::yaxis);

  _cursor = new Uint8[_size[0] * _size[1] * 4]; // RGBA
  _saved_area = new Uint8[_size[0] * _size[1] * 3]; //RGB

  unsigned pos = 0;
  Warsaw::Color c;

  for (unsigned short y = 0; y != _size[1]; ++y)
    for (unsigned short x = 0; x != _size[0]; ++x)
      {
	c = (*(pixels->get_buffer() + y * info.width + x));

	pos = (((_size[1] - 1 - y) * _size[0] + x) << 2);

	_cursor[pos + 0] = Uint8(c.red   * 0xFF);
	_cursor[pos + 1] = Uint8(c.green * 0xFF);
	_cursor[pos + 2] = Uint8(c.blue  * 0xFF);
	_cursor[pos + 3] = Uint8(c.alpha * 0xFF);
      }

  // set position
  _position[0] = _position[1] = 8;

  save();
  draw();
}


SDL::GLPointer::~GLPointer()
{
  restore();
  delete[] _cursor;
  delete[] _saved_area;
}


void SDL::GLPointer::save()
{
  Prague::Trace trace("SDL::GLPointer::save()");

  Warsaw::PixelCoord x = _position[0] - _origin[0];
  Warsaw::PixelCoord y = _max_y_size - _position[1] - _size[1] + _origin[1];
  glReadBuffer(GL_FRONT);
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA);
  glDisable(GL_SCISSOR_TEST);
  glReadPixels(x, y,
	       _size[0], _size[1],
	       GL_RGB, GL_UNSIGNED_BYTE,
	       _saved_area);
  glEnable(GL_BLEND);
  glEnable(GL_ALPHA);
  glEnable(GL_SCISSOR_TEST);
}


void SDL::GLPointer::restore()
{
  Prague::Trace trace("SDL::GLPointer::restore()");

  Warsaw::PixelCoord x = _position[0] - _origin[0];
  Warsaw::PixelCoord y = _position[1] + _size[1] - _origin[1];
  glDrawBuffer(GL_FRONT);
  glDisable(GL_BLEND);
  glDisable(GL_ALPHA);
  glDisable(GL_SCISSOR_TEST);
  glRasterPos2i(x * 10, y * 10);
  glDrawPixels(_size[0], _size[1], GL_RGB, GL_UNSIGNED_BYTE, _saved_area); 
  glDrawBuffer(GL_BACK);
  glRasterPos2i(0, 0);
  glEnable(GL_BLEND);
  glEnable(GL_ALPHA);
  glEnable(GL_SCISSOR_TEST);
}


void SDL::GLPointer::draw()
{
  Prague::Trace trace("SDL::GLPointer::draw()");

  Warsaw::PixelCoord x = _position[0] - _origin[0];
  Warsaw::PixelCoord y = _position[1] + _size[1] - _origin[1];
  glDrawBuffer(GL_FRONT);
  glDisable(GL_SCISSOR_TEST);
  glRasterPos2i(x * 10, y * 10);
  glDrawPixels(_size[0], _size[1], GL_RGBA, GL_UNSIGNED_BYTE, _cursor); 
  glDrawBuffer(GL_BACK);
  glRasterPos2i(0, 0);
  glEnable(GL_SCISSOR_TEST);
  glFlush();
}





// ---------------------------------------------------------------
// externs
// ---------------------------------------------------------------

extern "C" Console::Extension *load() { return new SDL::GLContext();}
