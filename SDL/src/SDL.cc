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

#include <Prague/Sys/Memory.hh>
#include <Prague/Sys/FdSet.hh>
#include <Prague/Sys/Tracer.hh>

#include "Console/Renderer.hh"
#include "Console/GLContext.hh"
#include "Console/DirectBuffer.hh"
#include "Console/SDL/SDL.hh"
#include "Console/SDL/pointer.hh"

using namespace Prague;
using namespace Warsaw;

namespace
{
  static void readEvent(SDL_Event &e)
  {
    Trace trace("readEvent()");
    unsigned int t;
    std::cin >> t;
    e.type = static_cast<char>(t);
    switch (e.type)
      {
      case SDL_KEYDOWN:
	{
	  std::cin >> t;
	  e.key.keysym.sym = static_cast<SDLKey>(t);
	  break;
	}
      case SDL_MOUSEMOTION:
	{
	  std::cin >> e.motion.x
		   >> e.motion.y;
	  break;
	}
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
	{
	  break;
      }
      }
  }
  
  static void writeEvent(SDL_Event &e)
  {
    Trace trace("writeEvent()");
    std::cout << static_cast<unsigned int>(e.type) << ' ';
    switch (e.type)
      {
      case SDL_KEYDOWN:
	{
	  std::cout << static_cast<unsigned int>(e.key.keysym.sym);
	  break;
	}
      case SDL_MOUSEMOTION:
	{
	  std::cout << e.motion.x << ' '
		    << e.motion.y;
	  break;
	}
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
	{
	  break;
	}
      }
    std::cout << endl;
  }
};





// ---------------------------------------------------------------
// class SDLExtension
// ---------------------------------------------------------------

class SDLExtension : virtual public Console::Extension
{
public:
  SDLExtension(SDLDrawable * d) : _drawable(d)
  {
    Trace trace("SDLExtension::SDLExtension()");
  }

  SDLDrawable * drawable()
  {
    Trace trace("SDLExtension::drawable()");
    return _drawable;
  }

private:
  SDLDrawable * _drawable;
};





// ---------------------------------------------------------------
// class SDLRenderer
// ---------------------------------------------------------------

class SDLRenderer : public SDLExtension,
		    virtual public Renderer
{
public:
  SDLRenderer(SDLDrawable * drawable) : SDLExtension(drawable)
  {
    Trace trace("SDLRenderer::SDLRenderer()");
    _surface = drawable->surface();
  }

  virtual void set_color(const Color &c)
  {
    Trace trace("SDLRenderer::set_color()");
    _color = drawable()->map(c);
  }

  virtual void draw_pixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y)
  {
    Trace trace("SDLRenderer::draw_pixel()");
    put_pixel(x, y, _color);
  }

  virtual void draw_hline(Warsaw::PixelCoord x, Warsaw::PixelCoord y,
			  Warsaw::PixelCoord w)
  {
    //  draw_line(x,y,w,0);
    Trace trace("SDLRenderer::draw_hline()");
    for (int i = 0; i < w; i++) put_pixel(x + i, y, _color);
  }

  virtual void draw_vline(Warsaw::PixelCoord x, Warsaw::PixelCoord y,
			  Warsaw::PixelCoord h)
  {
    //  draw_line(x,y,0,h);
    Trace trace("SDLRenderer::draw_vline()");
    for (int i = 0; i < h; i++) put_pixel(x, y + h, _color);
  }
  
  virtual void draw_line(Warsaw::PixelCoord x, Warsaw::PixelCoord y,
			 Warsaw::PixelCoord w, Warsaw::PixelCoord h)
  {
    Trace trace("SDLRenderer::draw_line()");
    
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
      put_pixel(x, y, _color); 
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
  
  virtual void draw_box(Warsaw::PixelCoord x, Warsaw::PixelCoord y,
			Warsaw::PixelCoord w, Warsaw::PixelCoord h)
  {
    Trace trace("SDLRenderer::draw_box()");

    SDL_Rect r; r.x = x; r.y = y; r.w = w; r.h = h;

    if (r.x < 0) { r.w += r.x; r.x = 0; }
    if (r.y < 0) { r.h += r.y; r.y = 0; }

    SDL_FillRect(_surface, &r, _color);
  }

private:
  void put_pixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y, SDLDrawable::Pixel c)
  {
    Trace trace("SDLRenderer::put_pixel()");

    if (x >= drawable()->width() || y >= drawable()->height() ||
	x < 0 || y < 0) return;
    if (drawable()->need_locking()) { SDL_LockSurface(_surface); }
    
    Uint8* p = (Uint8 *)_surface->pixels + y * _surface->pitch +
      x * drawable()->depth();
    
    switch( drawable()->depth() )
      {
      case 1: *p = c; break;
      case 2: *(Uint16 *)p = c; break;
      case 3:
	{
	  if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
	    p[0] = (c >> 16) & 0xff;
	    p[1] = (c >> 8) & 0xff;
	    p[2] = c & 0xff;
	  } else {
	    p[0] = c & 0xff;
	    p[1] = (c >> 8) & 0xff;
	    p[2] = (c >> 16) & 0xff;
	  }
	  break;
	}
      case 4: *(Uint32 *)p = c; break; 
      }
    
    if (drawable()->need_locking()) { SDL_UnlockSurface(_surface); }
  }
  
  SDL_Surface        *_surface;
  SDLDrawable::Pixel  _color;
};





// ---------------------------------------------------------------
// class SDLDirectBuffer
// ---------------------------------------------------------------
 
class SDLDirectBuffer : public SDLExtension,
	 		virtual public DirectBuffer
{
public:
  SDLDirectBuffer(SDLDrawable *drawable) : SDLExtension(drawable) {
    Trace trace("SDLDirectBuffer::SDLDirectBuffer()");
    if (drawable->surface()->flags && SDL_OPENGL) { throw; }
  }

  virtual Guard read_buffer()
  {
    Trace trace("SDLDirectBuffer::read_buffer()");
    Guard guard(drawable(),
		static_cast<Console::Drawable::data_type *>
		(drawable()->surface()->pixels));
    return guard;
  }

  virtual Guard write_buffer()
  {
    Trace trace("SDLDirectBuffer::write_buffer()");
    Guard guard(drawable(),
		static_cast<Console::Drawable::data_type *>
		(drawable()->surface()->pixels));
    return guard;
  }
};



// ---------------------------------------------------------------
// class SDLGLContext
// ---------------------------------------------------------------

class SDLGLContext : public GLContext,
		     public SDLExtension
{
  class SDLGLDrawable;
  typedef void (*GL_Enable_Func)(unsigned int type);
  typedef void (*GL_Disable_Func)(unsigned int type);
  typedef void (*GL_CopyPixels_Func)(int x, int y,
				     int width, int height,
				     unsigned int type);
  typedef void (*GL_DrawBuffer_Func)(unsigned int type);
  typedef void (*GL_ReadBuffer_Func)(unsigned int type);
  
public:
  SDLGLContext(SDLDrawable *drawable) : SDLExtension(drawable)
  {
    Trace trace("SDLGLContext::SDLGLContext()");
    Warsaw::PixelCoord w(drawable->width());
    Warsaw::PixelCoord h(drawable->height());

    Logger::log(Logger::loader) << "setting video mode GL " << " w="
				<< w << " h= " << h << endl;

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_Surface * surface = SDL_SetVideoMode(w, h, 0,
					     SDL_HWSURFACE | SDL_HWPALETTE |
					     SDL_OPENGL | SDL_OPENGLBLIT |
					     SDL_DOUBLEBUF | SDL_HWACCEL);
    SDL_WM_SetCaption("Berlin on SDL (OpenGL)", NULL);
    SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &isDoubleBuffered);
    if (!isDoubleBuffered) {
      cout << "SDL_Error: " << SDL_GetError() << endl;
      throw;
    }

    // HACK: Replace the 'real' drawable with its OpenGL-replacement.
    drawable->_surface = surface;
    drawable->_width = w;
    drawable->_height = h;

    int d(4);
    // glGetIntegerv(GL_DEPTH_BITS, &d);
    switch (d) 
      {
      case  0: drawable->_depth = 0; break;
      case  8: drawable->_depth = 1; break;
      case 16: drawable->_depth = 2; break;
      case 24: drawable->_depth = 3; break;
      case 32: drawable->_depth = 4; break;
      default:
	drawable->_depth = 0;
      }

    glEnable_ptr     = (GL_Enable_Func)SDL_GL_GetProcAddress("glEnable");
    glDisable_ptr    = (GL_Disable_Func)SDL_GL_GetProcAddress("glDisable");
    glCopyPixels_ptr = (GL_CopyPixels_Func)SDL_GL_GetProcAddress("glCopyPixels");
    glDrawBuffer_ptr = (GL_DrawBuffer_Func)SDL_GL_GetProcAddress("glDrawBuffer");
    glReadBuffer_ptr = (GL_ReadBuffer_Func)SDL_GL_GetProcAddress("glReadBuffer");

    glReadBuffer_ptr(0x404); // GL_FRONT
    glDrawBuffer_ptr(0x405); // GL_BACK
  }

  virtual ~SDLGLContext()
  {
    Trace trace("SDLGLContext::~SDLGLContext()");
  }

  void flush() {
    Trace trace("SDLGLContext::flush()");

    if (isDoubleBuffered) {
      SDL_GL_SwapBuffers();
      glDisable_ptr(0x0BC0); // GL_ALPHA_TEST
      glDisable_ptr(0x0BE2); // GL_BLEND
      glDisable_ptr(0x0C11); // GL_SCISSOR_TEST
      glCopyPixels_ptr(0, 0, drawable()->width(), drawable()->height(),
		       0x1800); // GL_COLOR
      glEnable_ptr(0x0BC0); // GL_ALPHA_TEST
      glEnable_ptr(0x0BE2); // GL_BLEND
      glEnable_ptr(0x0C11); // GL_SCISSOR_TEST
    } else {
      // TODO
    }
  }

private:
  int                isDoubleBuffered;
  GL_Enable_Func     glEnable_ptr;
  GL_Disable_Func    glDisable_ptr;
  GL_CopyPixels_Func glCopyPixels_ptr;
  GL_DrawBuffer_Func glDrawBuffer_ptr;
  GL_ReadBuffer_Func glReadBuffer_ptr;
};





// ---------------------------------------------------------------
// class SDLConsole
// ---------------------------------------------------------------

SDLConsole::SDLConsole(int &argc, char **argv) // throw (exception)
  : _autoplay(false)
{
  Trace trace("SDLConsole::SDLConsole");
  Logger::log(Logger::loader) << "trying to open console" << endl;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_ShowCursor(SDL_DISABLE);

  _pointer = 0;

  // FIXME: Get some 'real' values!
  _resolution[0] = 0.1;
  _resolution[1] = 0.1;

  _size[0] = 640;
  _size[1] = 480;

  _vsize[0] = 640;
  _vsize[1] = 480;

  pipe(_wakeupPipe);
  // <DEBUG>
  cerr << "SDLConsole::SDLConsole DONE" << endl; 
  // </DEBUG>
}

SDLConsole::~SDLConsole()
{
  Trace trace("SDLConsole::~SDLConsole");

  for (dlist_t::iterator i = _drawables.begin();
       i != _drawables.end();
       i++) delete *i;
  close(_wakeupPipe[0]);
  close(_wakeupPipe[1]);
  SDL_Quit();
}

SDLPointer *SDLConsole::pointer(Raster_ptr raster)
{
  Trace trace("SDLConsole::pointer");
  return new SDLPointer(drawable(), raster);
}

SDLDrawable *SDLConsole::drawable()
{
  Trace trace("SDLConsole::drawable");

  if (_drawables.empty())
    _drawables.push_back(new SDLDrawable(0));

  return _drawables.front();
}

SDLDrawable *SDLConsole::create_drawable(PixelCoord w, PixelCoord h, PixelCoord d)
{
  Trace trace("SDLConsole::create_drawable");

  _drawables.push_back(new SDLDrawable("display-memory", w, h, d));
  return _drawables.back();
}

SDLDrawable *SDLConsole::create_shm_drawable(int id,
					     PixelCoord w, PixelCoord h,
					     PixelCoord d)
{
  Trace trace("SDLConsole::create_shm_drawable");

  throw std::runtime_error("SDL shm drawables not yet supported");
}

SDLDrawable *SDLConsole::reference_to_servant(Warsaw::Drawable_ptr drawable)
{
  Trace trace("SDLConsole::reference_to_servant()");
  
  PortableServer::Servant servant = Console::reference_to_servant(drawable);
  for (dlist_t::iterator i = _drawables.begin(); i != _drawables.end(); ++i)
    if (*i == servant) return *i;
  return 0;
}

void SDLConsole::activate_autoplay()
{
  Trace trace("SDLConsole::activate_autoplay()");

  // FIXME: This should do something.
}

void SDLConsole::device_info(std::ostream &os)
{
  Trace trace("SDLConsole::device_info()");

  os << "sorry, device info isn't available for SDL at this time" << std::endl;
}

Input::Event *SDLConsole::next_event()
{
  Trace trace("SDLConsole::next_event()");
  
  SDL_Event event;
  SDL_WaitEvent(&event);
  return synthesize(event);
}

void SDLConsole::wakeup()
{
  Trace trace("SDLConsole::wakeup()");

  char c = 'z'; write(_wakeupPipe[1],&c,1);
}

Input::Event *SDLConsole::synthesize(const SDL_Event &e)
{
  Trace trace("SDLConsole::synthesize()");

  Input::Event_var event = new Input::Event;
  switch (e.type)
    {
    case SDL_KEYDOWN:
      {
	Input::Toggle toggle;
	toggle.actuation = Input::Toggle::press;
	toggle.number = e.key.keysym.sym;
	event->length(1);
	event[0].dev = 0;
	event[0].attr.selection(toggle); event[0].attr._d(Input::key);
	break;
      }
    case SDL_MOUSEMOTION:
      {
	// grab waiting mouse events and skip to the last one
	SDL_Event move_events[64];
	SDL_PumpEvents();
	int num = SDL_PeepEvents(move_events, 64, SDL_GETEVENT, SDL_MOUSEMOTIONMASK);
	if (num > 0)
	  {
	    // Use last known position of mouse
	    _position[0] = move_events[num-1].motion.x;
	    _position[1] = move_events[num-1].motion.y;
	  }
	else
	  {
	    // Use position from original event     
	    _position[0] = e.motion.x;
	    _position[1] = e.motion.y;
	  }
	Input::Position position;
	position.x = _position[0]/_resolution[0];
	position.y = _position[1]/_resolution[1];
	position.z = 0;
	event->length(1);
	event[0].dev = 1;
	event[0].attr.location(position);
	break;
      }
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
      {
	Input::Toggle toggle;
	if (e.type == SDL_MOUSEBUTTONDOWN)
	  toggle.actuation = Input::Toggle::press;
	else
	  toggle.actuation = Input::Toggle::release;
	toggle.number = e.button.button;          
	Input::Position position;
	position.x = _position[0]/_resolution[0];
	position.y = _position[1]/_resolution[1];
	position.z = 0;
	event->length(2);
	event[0].dev = 1;
	event[0].attr.selection(toggle); event[0].attr._d(Input::button);
	event[1].dev = 1;
	event[1].attr.location(position);
	break;
      }
    }

  return event._retn();
}

Console::Extension * SDLConsole::create_extension(const std::string & id,
						  Drawable * drawable)
{
  Trace trace("SDLConsole::create_extension()");

  if (id == "Renderer")
    return new SDLRenderer(static_cast<SDLDrawable *>(drawable));
  if (id == "GLContext")
    return new SDLGLContext(static_cast<SDLDrawable *>(drawable));
  if (id == "DirectBuffer")
    return new SDLDirectBuffer(static_cast<SDLDrawable *>(drawable));
  return 0;
}





// ---------------------------------------------------------------
// SDLPointer
// ---------------------------------------------------------------

SDLPointer::SDLPointer(SDLDrawable *d, Raster_ptr raster)
  : _raster(Raster::_duplicate(raster))
{
  Trace trace("SDLPointer::SDLPointer()");

  _size[0] = 16; // width
  _size[1] = 16; // height

  Uint8 image[(_size[0] * _size[1]) / 8];
  Uint8 mask[(_size[0] * _size[1]) / 8];

  int i = -1; 

  for (unsigned short y = 0; y < _size[1]; ++y)
    for (unsigned short x = 0; x < _size[0]; ++x) {
      if (x % 8) {
	image[i] <<= 1;
	mask[i] <<= 1;
      } else {
	++i;
	image[i] = mask[i] = 0;
      }

      image[i] |= ((pointer_image[y * _size[0] + x] & 2) > 0);
      mask [i] |= ((pointer_image[y * _size[0] + x] & 1) > 0);
    }

  _cursor = SDL_CreateCursor(image, mask, _size[0], _size[1], 1, 1);
  SDL_SetCursor(_cursor);
  SDL_ShowCursor(1);
}

SDLPointer::~SDLPointer()
{
  Trace trace("SDLPointer::~SDLPointer()");

  SDL_FreeCursor(_cursor);
  SDL_ShowCursor(0);
}

Raster_ptr SDLPointer::raster()
{
  return Raster::_duplicate(_raster);
}

bool SDLPointer::intersects(Warsaw::Coord l, Warsaw::Coord r,
			    Warsaw::Coord t, Warsaw::Coord b)
{
  Trace trace("SDLPointer::intersects()");
  return
    l*0.1 <= _x - 10 &&
    r*0.1 >= _x &&
    t*0.1 <= _y - 10 &&
    b*0.1 >= _y;
}

void SDLPointer::move(Coord x, Coord y)
{
  Trace trace("SDLPointer::move()");

  _x = Warsaw::PixelCoord(x);
  _y = Warsaw::PixelCoord(y); 
}

void SDLPointer::save()
{
  Trace trace("SDLPointer::save()");
}
void SDLPointer::restore()
{
  Trace trace("SDLPointer::restore()");
}
void SDLPointer::draw()
{
  Trace trace("SDLPointer::draw()");
}





// ---------------------------------------------------------------
// SDLDrawable
// ---------------------------------------------------------------

SDLDrawable::SDLDrawable(const char *display,
			 PixelCoord w, PixelCoord h, PixelCoord d)
  // throw (exception)
{
  Trace trace("SDLDrawable::SDLDrawable()");

  static unsigned int _redMask;
  static unsigned int _greenMask;
  static unsigned int _blueMask;
  static unsigned int _alphaMask;

  int bpp;

  switch( d ) {
  case 0: bpp = 0; break;
  case 1: bpp = 8; break;
  case 2: bpp = 16; break;
  case 3: bpp = 24; break;
  case 4: bpp = 32; break;
  default:
    std::cerr << "SDLDrawable: Warning: " << d
	      << " bytes per pixel not supported" << std::endl;
  }

  _width = w;
  _height = h;
  Logger::log(Logger::loader) << "setting video mode d = " << display
			      << " w=" << w << " h= " << h << " bpp=" << bpp
			      << std::endl;
  if (display == NULL) {
    _surface = SDL_SetVideoMode( w, h, bpp, SDL_HWSURFACE | SDL_HWPALETTE );
    SDL_WM_SetCaption("Berlin on SDL", NULL);
    _redMask = _surface->format->Rmask;
    _greenMask = _surface->format->Gmask;
    _blueMask = _surface->format->Bmask;
    _alphaMask = _surface->format->Amask;
  } else {
    _surface = SDL_CreateRGBSurface( SDL_SRCCOLORKEY | SDL_SRCALPHA,
				     w, h, bpp,
				     _redMask, _greenMask, _blueMask, _alphaMask);
  }

  if (!_surface) throw std::exception();
  
  _depth = bpp ? d : _surface->format->BytesPerPixel;
  _need_locking = SDL_MUSTLOCK(_surface);
}

SDLDrawable::~SDLDrawable()
{
  Trace trace("SDLDrawable::~SDLDrawable()");

  SDL_FreeSurface(_surface);
}

Warsaw::Drawable::PixelFormat SDLDrawable::pixel_format()
{
  Trace trace("SDLDrawable::pixel_format()");

  Warsaw::Drawable::PixelFormat format;
  const SDL_PixelFormat *pf = _surface->format;

  format.depth       = pf->BitsPerPixel;
  format.size        = pf->BitsPerPixel;
  format.red_mask    = pf->Rmask;
  format.red_shift   = pf->Rshift;
  format.green_mask  = pf->Gmask;
  format.green_shift = pf->Gshift;
  format.blue_mask   = pf->Bmask;
  format.blue_shift  = pf->Bshift;
  format.alpha_mask  = pf->Amask;
  format.alpha_shift = pf->Ashift;

  return format;
}


Warsaw::Drawable::BufferFormat SDLDrawable::buffer_format()
{
  Trace trace("SDLDrawable::buffer_format()");

  Warsaw::Drawable::BufferFormat format;
  format.skip_width = 0;
  format.width = width();
  format.skip_height = 0;
  format.height = height();
  format.row_length = row_length();
  return format;
}





// ---------------------------------------------------------------
// externs
// ---------------------------------------------------------------

extern "C" Console::LoaderT<SDLConsole> *load() { return new Console::LoaderT<SDLConsole>(); }
