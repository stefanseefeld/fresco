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

#include <Prague/Sys/Tracer.hh>
#include <Berlin/Logger.hh>
#include <Console/SDL/Drawable.hh>
#include <Console/SDL/Extension.hh>



// ---------------------------------------------------------------
// class SDL::Renderer (implementation)
// ---------------------------------------------------------------

void SDL::DrawableExtension::attach(::Console::Drawable * drawable) {
  _drawable = dynamic_cast<SDL::Drawable *>(drawable);
}





// ---------------------------------------------------------------
// class SDL::Renderer (implementation)
// ---------------------------------------------------------------

SDL::Renderer::Renderer() { }


void SDL::Renderer::set_color(const Warsaw::Color &c)
{
  Prague::Trace trace("SDLRenderer::set_color()");
  _color = drawable()->map(c);
}


void SDL::Renderer::draw_pixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y)
{
  Prague::Trace trace("SDLRenderer::draw_pixel()");
  put_pixel(x, y);
}


void SDL::Renderer::draw_hline(Warsaw::PixelCoord x, Warsaw::PixelCoord y,
				       Warsaw::PixelCoord w)
{
  Prague::Trace trace("SDL::Renderer::draw_hline()");
  for (int i = 0; i < w; i++) put_pixel(x + i, y);
}

void SDL::Renderer::draw_vline(Warsaw::PixelCoord x, Warsaw::PixelCoord y,
				       Warsaw::PixelCoord h)
{
  Prague::Trace trace("SDL::Renderer::draw_vline()");
  for (int i = 0; i < h; i++) put_pixel(x, y + h);
}

void SDL::Renderer::draw_line(Warsaw::PixelCoord x, Warsaw::PixelCoord y,
				      Warsaw::PixelCoord w, Warsaw::PixelCoord h)
{
  Prague::Trace trace("SDLRenderer::draw_line()");
    
  register int distance; 
  int xerr=0, yerr=0;
  int delta_x, delta_y; 
  int incx, incy; 
  
  delta_x = w; 
  delta_y = h; 
  
  if (delta_x>0) incx=1; 
  else if (delta_x==0) incx=0; 
  else incx= -1; 
  
  if (delta_y>0) incy=1; 
  else if (delta_y==0) incy=0; 
  else incy= -1; 
  
  delta_x = abs(delta_x);
  delta_y = abs(delta_y);
  
  distance = delta_x>delta_y ? delta_x : delta_y;
  
  for (int t=0; t<=distance+1; t++) { 
    put_pixel(x, y); 
    xerr+=delta_x; 
    yerr+=delta_y; 
    if (xerr>distance) { 
      xerr-=distance; 
      x+=incx; 
    }
    if (yerr>distance) { 
      yerr-=distance; 
      y+=incy; 
    }
  }
}
  
void SDL::Renderer::draw_box(Warsaw::PixelCoord x, Warsaw::PixelCoord y,
				     Warsaw::PixelCoord w, Warsaw::PixelCoord h)
{
  Prague::Trace trace("SDLRenderer::draw_box()");
  
  SDL_Rect r; r.x = x; r.y = y; r.w = w; r.h = h;
  
  if (r.x < 0) { r.w += r.x; r.x = 0; }
  if (r.y < 0) { r.h += r.y; r.y = 0; }
  
  SDL_FillRect(drawable()->surface(), &r, _color);
}


void SDL::Renderer::put_pixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y)
{
  Prague::Trace trace("SDLRenderer::put_pixel()");
  
  if (x >= drawable()->width() || y >= drawable()->height() ||
      x < 0 || y < 0) return;
  if (drawable()->need_locking()) { SDL_LockSurface(drawable()->surface()); }
  
  Uint8* p = (Uint8 *)drawable()->surface()->pixels + y * drawable()->surface()->pitch +
    x * drawable()->depth();
  
  switch( drawable()->depth() )
    {
    case 1: *p = _color; break;
    case 2: *(Uint16 *)p = _color; break;
    case 3:
      {
	if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
	  p[0] = (_color >> 16) & 0xff;
	  p[1] = (_color >> 8) & 0xff;
	  p[2] = _color & 0xff;
	} else {
	  p[0] = _color & 0xff;
	  p[1] = (_color >> 8) & 0xff;
	  p[2] = (_color >> 16) & 0xff;
	}
	break;
      }
    case 4: *(Uint32 *)p = _color; break; 
    }
  
  if (drawable()->need_locking()) { SDL_UnlockSurface(drawable()->surface()); }
}





// ---------------------------------------------------------------
// class SDL::DirectBuffer (implementation)
// ---------------------------------------------------------------

SDL::DirectBuffer::DirectBuffer() { }

void SDL::DirectBuffer::attach(::Console::Drawable *d) {
  Prague::Trace trace("SDL::DirectBuffer::DirectBuffer(...)");
  DrawableExtension::attach(d);
  if (drawable()->surface()->flags && SDL_OPENGL) { throw; }
}

DirectBuffer::Guard SDL::DirectBuffer::read_buffer()
{
  Prague::Trace trace("SDLDirectBuffer::read_buffer()");
  DirectBuffer::Guard guard(drawable(),
			    static_cast< ::Console::Drawable::data_type *>
			    (drawable()->surface()->pixels));
  return guard;
}

DirectBuffer::Guard SDL::DirectBuffer::write_buffer()
{
  Prague::Trace trace("SDLDirectBuffer::write_buffer()");
  DirectBuffer::Guard guard(drawable(),
			    static_cast< ::Console::Drawable::data_type *>
			    (drawable()->surface()->pixels));
  return guard;
}





// ---------------------------------------------------------------
// class SDL::GLContext (implementation)
// ---------------------------------------------------------------

SDL::GLContext::GLContext()
{
  Prague::Trace trace("SDL::GLContext::attach()");

  _drawable =
    dynamic_cast<SDL::Drawable *>(::Console::instance()->drawable());

  Warsaw::PixelCoord w(_drawable->width());
  Warsaw::PixelCoord h(_drawable->height());
  
  Logger::log(Logger::loader) << "setting video mode GL " << " w="
			      << w << " h= " << h << endl;
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_Surface * surface = SDL_SetVideoMode(w, h, 0,
					   SDL_HWSURFACE | SDL_HWPALETTE |
					   SDL_OPENGL | SDL_OPENGLBLIT |
					   SDL_DOUBLEBUF | SDL_HWACCEL);
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
  
  int bits(0);
  // glGetIntegerv(GL_DEPTH_BITS, &bits); // introduces dependency on libGL!
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
  
  _glEnable_ptr     = (GL_Enable_Func)SDL_GL_GetProcAddress("glEnable");
  _glDisable_ptr    = (GL_Disable_Func)SDL_GL_GetProcAddress("glDisable");
  _glCopyPixels_ptr = (GL_CopyPixels_Func)SDL_GL_GetProcAddress("glCopyPixels");
  _glDrawBuffer_ptr = (GL_DrawBuffer_Func)SDL_GL_GetProcAddress("glDrawBuffer");
  _glReadBuffer_ptr = (GL_ReadBuffer_Func)SDL_GL_GetProcAddress("glReadBuffer");

  _glReadBuffer_ptr(0x404); // GL_FRONT
  _glDrawBuffer_ptr(0x405); // GL_BACK
}


SDL::GLContext::~GLContext()
{
  Prague::Trace trace("SDL::GLContext::~SDLGLContext()");
}


void SDL::GLContext::flush() {
  Prague::Trace trace("SDL::GLContext::flush()");
  
  if (_isDoubleBuffered) {
    SDL_GL_SwapBuffers();
    _glDisable_ptr(0x0BC0); // GL_ALPHA_TEST
    _glDisable_ptr(0x0BE2); // GL_BLEND
    _glDisable_ptr(0x0C11); // GL_SCISSOR_TEST
    _glCopyPixels_ptr(0, 0, _drawable->width(), _drawable->height(),
		      0x1800); // GL_COLOR
    _glEnable_ptr(0x0BC0); // GL_ALPHA_TEST
    _glEnable_ptr(0x0BE2); // GL_BLEND
    _glEnable_ptr(0x0C11); // GL_SCISSOR_TEST
  } else {
    // FIXME: TODO
  }
}
