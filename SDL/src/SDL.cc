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
#include "Console/SDL/SDL.hh"

#include <unistd.h>

using namespace Prague;
using namespace Warsaw;

namespace
{
static void readEvent(SDL_Event &e)
{
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

SDLConsole::dlist_t SDLConsole::_drawables;

SDLConsole::SDLConsole(int &argc, char **argv)// throw (exception)
  : _autoplay(false)
{
  Logger::log(Logger::loader) << "trying to open console" << endl;
  Trace trace("SDLConsole::SDLConsole");
  SDL_Init(SDL_INIT_VIDEO);
  SDLDrawable *drawable = new SDLDrawable(0);
  _surface = drawable->surface();
  _size[0] = _surface->w;
  _size[1] = _surface->h;
  _position[0] = 0;
  _position[1] = 0;
  _resolution[0] = drawable->resolution(Warsaw::xaxis);
  _resolution[1] = drawable->resolution(Warsaw::yaxis);

  _drawables.push_back(drawable);
  pipe(_wakeupPipe);
}

SDLConsole::~SDLConsole()
{
  Trace trace("SDLConsole::~SDLConsole");
  for (dlist_t::iterator i = _drawables.begin(); i != _drawables.end(); i++) delete *i;
  close(_wakeupPipe[0]);
  close(_wakeupPipe[1]);
  SDL_Quit();
}

SDLPointer *SDLConsole::pointer()
{
  Trace trace("SDLConsole::pointer");
  return new SDLPointer(drawable());
}

SDLDrawable *SDLConsole::drawable()
{
  Trace trace("SDLConsole::drawable");
  assert(_drawables.size());
  return _drawables.front();
}

SDLDrawable *SDLConsole::create_drawable(PixelCoord w, PixelCoord h, PixelCoord d)
{
  _drawables.push_back(new SDLDrawable("display-memory", w, h, d));
  return _drawables.back();
}

SDLDrawable *SDLConsole::create_shm_drawable(int id, PixelCoord w, PixelCoord h, PixelCoord d)
{
  throw std::runtime_error("SDL shm drawables not yet supported");
}

SDLDrawable *SDLConsole::reference_to_servant(Warsaw::Drawable_ptr drawable)
{
  Trace trace("SDLConsole::reference_to_servant");
  PortableServer::Servant servant = Console::reference_to_servant(drawable);
  for (dlist_t::iterator i = _drawables.begin(); i != _drawables.end(); ++i)
    if (*i == servant) return *i;
  return 0;
}

void SDLConsole::device_info(std::ostream &os)
{
  os << "sorry, device info isn't available for SDL at this time" << std::endl;
}

Input::Event *SDLConsole::next_event()
{
  Trace trace("SDL::Console::next_event");
  SDL_Event event;
  SDL_WaitEvent(&event);
  return synthesize(event);
}

void SDLConsole::wakeup() { char c = 'z'; write(_wakeupPipe[1],&c,1);}

Input::Event *SDLConsole::synthesize(const SDL_Event &e)
{
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
	_position[0] = e.motion.x;
 	_position[1] = e.motion.y;
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

namespace
{
unsigned char pointerImg[256] = 
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
  1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
  1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,
  1,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,
  1,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,
  1,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,
  1,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,
  1,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,
  1,2,2,1,2,2,1,0,0,0,0,0,0,0,0,0,
  1,1,0,1,2,2,2,1,0,0,0,0,0,0,0,0,
  1,0,0,0,1,2,2,1,0,0,0,0,0,0,0,0,
  0,0,0,0,1,2,2,2,1,0,0,0,0,0,0,0,
  0,0,0,0,0,1,2,2,1,0,0,0,0,0,0,0,
  0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0 };
}

SDLPointer::SDLPointer(SDLDrawable *d)
  : _screen(d)
{
  _origin[0] = _origin[1] = 0;
  _position[0] = _position[1] = 8;
  _size[0] = _size[1] = 16;
  _scale[0] = 1/_screen->resolution(xaxis);
  _scale[1] = 1/_screen->resolution(yaxis);
  
  Drawable::PixelFormat format = _screen->pixel_format();

  Pixel trans = 0;
  Pixel red = (static_cast<Pixel>(1. * (~0L)) >> format.red_shift) & format.red_mask;
  Pixel green = (static_cast<Pixel>(1. * (~0L)) >> format.green_shift) & format.green_mask;
  Pixel blue = (static_cast<Pixel>(1. * (~0L)) >> format.blue_shift) & format.blue_mask;
  Pixel black =  0;
  Pixel white = red | green | blue;

  /*
   * create the pointer image
   */
  PixelCoord depth =  format.size >> 3;
  _image = new data_type[_size[0]*_size[1] * depth];
  for (unsigned short y = 0; y != _size[1]; y++)
    for (unsigned short x = 0; x != _size[0]; x++)
      {
	Pixel color = pointerImg[y*_size[0] + x] == 1 ? white : black;
 	for (unsigned short d = 0; d != depth; d++)
	  _image[y*depth*_size[0] + depth*x + d] = (color >> d) & 0xff;
      }
  /*
   * create the pointer mask
   */
  _mask = new data_type[_size[0]*_size[1]*depth];
  for (unsigned short y = 0; y != _size[1]; y++)
    for (unsigned short x = 0; x != _size[0]; x++)
      {
	char flag = pointerImg[y*_size[0] + x] == 0 ? 0 : ~0;
	for (unsigned short d = 0; d != depth; d++)
	  _mask[y*depth*_size[0]+depth*x + d] = flag;
      }
  _cache = new data_type[_size[0]*_size[1]*depth];
  save();
  draw();
}

SDLPointer::~SDLPointer()
{
  delete [] _image;
  delete [] _cache;
}

bool SDLPointer::intersects(Warsaw::Coord l, Warsaw::Coord r, Warsaw::Coord t, Warsaw::Coord b)
{
  return
    l/_scale[0] <= _position[0] + _size[0] &&
    r/_scale[0] >= _position[0] &&
    t/_scale[1] <= _position[1] + _size[1] &&
    b/_scale[1] >= _position[1];
}

void SDLPointer::move(Coord x, Coord y)
{
  restore();
  _position[0] = static_cast<PixelCoord>(std::max(static_cast<PixelCoord>(x/_scale[0]), _origin[0]));
  _position[1] = static_cast<PixelCoord>(std::max(static_cast<PixelCoord>(y/_scale[1]), _origin[1]));
  save();
  draw();
};

void SDLPointer::save()
{
  Trace trace("Pointer::save");
  PixelCoord x = _position[0] - _origin[0];
  PixelCoord y = _position[1] - _origin[1];
  PixelCoord w = _size[0];
  PixelCoord h = _size[1];
  PixelCoord r = _screen->row_length();
  PixelCoord s = _screen->vwidth() * _screen->vheight();
  PixelCoord d = _screen->pixel_format().size >> 3;
  SDLDrawable::Buffer buffer = _screen->read_buffer();
  data_type *from = buffer.get() + y*r + x*d;
  data_type *to = _cache;
  for (PixelCoord o = 0; o != h && (y + o) * r / d + x + w < s; o++, from += r, to += d * w)
    Memory::copy(from, to, d * w);
}

void SDLPointer::restore()
{
  Trace trace("Pointer::restore");
  PixelCoord x = _position[0] - _origin[0];
  PixelCoord y = _position[1] - _origin[1];
  PixelCoord w = _size[0];
  PixelCoord h = _size[1];
  PixelCoord r = _screen->row_length();
  PixelCoord s = _screen->vwidth() * _screen->vheight();
  PixelCoord d = _screen->pixel_format().size >> 3;
  data_type *from = _cache;
  SDLDrawable::Buffer buffer = _screen->write_buffer();
  data_type *to = buffer.get() + y*r + x*d;
  for (PixelCoord o = 0;
       o != h && (y + o) * r / d + x + w < s;
       o++, from += d * w, to += r)
    Memory::copy(from, to, d * w);
}

void SDLPointer::draw()
{
  Trace trace("SDLPointer::draw");
  PixelCoord x = _position[0] - _origin[0];
  PixelCoord y = _position[1] - _origin[1];
  PixelCoord w = _size[0];
  PixelCoord h = _size[1];
  PixelCoord r = _screen->row_length();
  PixelCoord s = _screen->vwidth() * _screen->vheight();
  PixelCoord d = _screen->pixel_format().size >> 3;
  data_type *from = _image;
  data_type *bits = _mask;
  SDLDrawable::Buffer buffer = _screen->write_buffer();
  data_type *to = buffer.get() + y * r + x * d;
  for (PixelCoord i = 0; i != h && (y + i) * r / d + x + w < s; i++, to += r - w * d)
    for (PixelCoord j = 0; j != w * d; j++, from++, bits++, to++)
      *to = (*from & *bits) | (*to & ~*bits);
  _screen->flush();
}

SDLDrawable::SDLDrawable(const char *display, PixelCoord w, PixelCoord h, PixelCoord d) // throw (exception)
{
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
    cerr << "SDLDrawable: Warning: " << d << " bytes per pixel not supported" << endl;
  }

  _width = w;
  _height = h;
  Logger::log(Logger::loader) << "setting video mode d = " << display << " w=" << w << " h= " << h << " bpp=" << bpp << endl;
  if (display == NULL) {
    _surface = SDL_SetVideoMode( w, h, bpp, SDL_HWSURFACE|SDL_HWPALETTE|SDL_ASYNCBLIT );
    _redMask = _surface->format->Rmask;
    _greenMask = _surface->format->Gmask;
    _blueMask = _surface->format->Bmask;
    _alphaMask = _surface->format->Amask;
  } else {
    _surface = SDL_CreateRGBSurface( SDL_SRCCOLORKEY | SDL_SRCALPHA, w, h, bpp, _redMask, _greenMask, _blueMask, _alphaMask );
  }
  if (!_surface) throw std::exception();
  
  _depth = bpp ? d : _surface->format->BytesPerPixel;
  _need_locking = SDL_MUSTLOCK(_surface);

}

SDLDrawable::~SDLDrawable()
{
  SDL_FreeSurface(_surface);
}

void SDLDrawable::draw_line(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h)
{
  //  Logger::log(Logger::loader) << "SDLDrawable::draw_line x=" << x << " y= " << y << " w=" << w << " h=" << h << endl;

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
    put_pixel( x, y, _color); 
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

void SDLDrawable::draw_box(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h)
{
  //Logger::log(Logger::loader) << "SDLDrawable::draw_box x=" << x << " y= " << y << " w=" << w << " h=" << h << endl;

  SDL_Rect r; r.x = x; r.y = y; r.w = w; r.h = h;

  if (r.x < 0) { r.w += r.x; r.x = 0; }
  if (r.y < 0) { r.h += r.y; r.y = 0; }
  
  SDL_FillRect(_surface, &r, _color);
}



Warsaw::Drawable::PixelFormat SDLDrawable::pixel_format()
{
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
  Warsaw::Drawable::BufferFormat format;
  format.skip_width = 0;
  format.width = width();
  format.skip_height = 0;
  format.height = height();
  format.row_length = row_length();
  return format;
}

extern "C" ConsoleLoader<SDLConsole> *load() { return new ConsoleLoader<SDLConsole>();}
