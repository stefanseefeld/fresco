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
#include <Prague/Sys/FdSet.hh>
#include <Prague/Sys/Tracer.hh>
#include "Berlin/Console.hh"

#include <unistd.h>

using namespace Prague;
using namespace Warsaw;

//vector<DrawableTie<SDLDrawable> *> SDLConsole::_drawables;

SDLConsole::dlist_t SDLConsole::_drawables;
PortableServer::POA_var SDLConsole::_poa;


////////////////////////////////////////////////////////////////////////////////
// SDLDrawable implementation
////////////////////////////////////////////////////////////////////////////////
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
  if (!_surface) throw exception();
  
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
  Logger::log(Logger::loader) << "SDLDrawable::draw_box x=" << x << " y= " << y << " w=" << w << " h=" << h << endl;
  for( int i = y; i < y+h; ++i )
    draw_line( x, i, x+w, i );
}



Warsaw::Drawable::PixelFormat SDLDrawable::pixel_format()
{
  DrawableTie<SDLDrawable>::PixelFormat format;
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


////////////////////////////////////////////////////////////////////////////////
// SDLConsole implementation
////////////////////////////////////////////////////////////////////////////////
SDLConsole::SDLConsole(int &argc, char **argv, PortableServer::POA_ptr poa)// throw (exception)
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
  _resolution[0] = 0.1 * _surface->w / 320;
  _resolution[1] = 0.1 * _surface->h / 240;

  _drawables.push_back(new DrawableTie<Drawable>(drawable));
  _poa = PortableServer::POA::_duplicate(poa);
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

DrawableTie<SDLDrawable> *SDLConsole::drawable()
{
  Trace trace("SDLConsole::drawable");
  assert(_drawables.size());
  return _drawables.front();
}

DrawableTie<SDLDrawable> *SDLConsole::create_drawable(PixelCoord w, PixelCoord h, PixelCoord d)
{
  _drawables.push_back(new DrawableTie<SDLDrawable>(new SDLDrawable("display-memory", w, h, d)));
  return _drawables.back();
}

DrawableTie<SDLDrawable> *SDLConsole::create_drawable(SDLDrawable *drawable)
{
  _drawables.push_back(new DrawableTie<SDLDrawable>(drawable));
  return _drawables.back();
}

Warsaw::Drawable_ptr SDLConsole::activate_drawable(DrawableTie<SDLDrawable> *d)
{
  Trace trace("SDLConsole::activate_drawable");
  PortableServer::ObjectId *oid = _poa->activate_object(d);
  d->_remove_ref();
  delete oid;
  return d->_this();
}

DrawableTie<SDLDrawable> *SDLConsole::reference_to_servant(Warsaw::Drawable_ptr drawable)
{
  Trace trace("SDLConsole::reference_to_servant");
  try
    {
      PortableServer::Servant servant = _poa->reference_to_servant(drawable);
      for (dlist_t::iterator i = _drawables.begin(); i != _drawables.end(); ++i)
	if (*i == servant) return *i;
    }
  catch (const PortableServer::POA::ObjectNotActive &) {}
  catch (const PortableServer::POA::WrongAdapter &) {}
  catch (const CORBA::OBJECT_NOT_EXIST &) {}
  return 0;
}

static void readEvent(SDL_Event &e)
{
//   unsigned int t;
//   cin >> t;
//   e.any.type = (char)t;
//   switch (e.any.type)
//     {
//     case evKeyPress:
//     case evKeyRepeat:
//       {
// 	cin >> t;
// 	e.key.sym = t;
// 	break;
//       }
//     case evPtrRelative:
//     case evPtrAbsolute:
//       {
// 	cin >> e.pmove.x
// 	    >> e.pmove.y;
// 	break;
//       }
//     case evPtrButtonPress:
//     case evPtrButtonRelease:
//       {
// 	break;
//       }
//   }
}

static void writeEvent(SDL_Event &e)
{
//   cout << ((unsigned int)(e.any.type)) << ' ';
//   switch (e.any.type)
//     {
//     case evKeyPress:
//     case evKeyRepeat:
//       {
// 	cout << ((unsigned int)(e.key.sym));
// 	break;
//       }
//     case evPtrRelative:
//     case evPtrAbsolute:
//       {
// 	cout << e.pmove.x << ' '
// 	     << e.pmove.y;
// 	break;
//       }
//     case evPtrButtonPress:
//     case evPtrButtonRelease:
//       {
// 	break;
//       }
//     }
//   cout << endl;
}

Input::Event *SDLConsole::next_event()
{
  Trace trace("SDL::Console::next_event");
//   SDL_Event event;
//   ggi_event_mask mask;
//   ggi_event_mask move_mask = ggi_event_mask (emPtrMove);

//   int input = fileno(stdin);
//   Prague::FdSet rfdset;
//   int nfds;

//   do
//     {
//       rfdset.set (wakeupPipe[0]);
//       if (autoplay)
// 	rfdset.set (input);
//       mask = ggi_event_mask (emKeyboard | emPtrMove | emPtrButtonPress | emPtrButtonRelease);
//       nfds = ggiEventSelect (visual, &mask, rfdset.max() + 1, rfdset, 0, 0, 0);
//     }
//   while (nfds < 0 && errno == EINTR);
 
//   if (nfds == 0)
//     {
//       // no input from the outside world
//       ggiEventRead(visual, &event, mask); 
//       if (event.any.type == evPtrRelative || event.any.type == evPtrAbsolute)
// 	{
// 	  int m = ggiEventsQueued(visual, mask);
// 	  int n = ggiEventsQueued(visual, move_mask);
// 	  if (m == n)  // nothing but a bunch of moves queued up
// 	    {
// 	      int x=event.pmove.x, y=event.pmove.y;
// 	      for (int i = 0; i < n; ++i)
// 		{
// 		  // consume them all
// 		  ggiEventRead(visual, &event, move_mask); 	  
// 		  if (event.any.type == evPtrRelative)
// 		    {
// 		      x += event.pmove.x;
// 		      y += event.pmove.y;
// 		    }
// 		}
// 	      if (event.any.type == evPtrRelative)
// 		{
// 		  event.pmove.x = x;
// 		  event.pmove.y = y;
// 		}
// 	    }
// 	}
//       if (autoplay) writeEvent(event);
//       return synthesize(event);
//     }
//   else 
//     {
//       if (autoplay && rfdset.isset(input))
// 	{
// 	  readEvent(event);
// 	  return synthesize(event);
// 	}
//       else
// 	{
// 	  if (rfdset.isset(wakeupPipe[0]))
// 	    {
// 	      char c; read(wakeupPipe[0], &c, 1);
// 	      return 0;
// 	    }
// 	}
//     }
  return 0;
}

void SDLConsole::wakeup() { char c = 'z'; write(_wakeupPipe[1],&c,1);}

Input::Event *SDLConsole::synthesize(const SDL_Event &e)
{
  Input::Event_var event = new Input::Event;
//   switch (e.any.type)
//     {
//     case evKeyPress:
//       {
// 	Input::Toggle toggle;
// 	toggle.actuation = Input::Toggle::press;
// 	toggle.number = e.key.sym;
// 	event->length(1);
// 	event[0].dev = 0;
// 	event[0].attr.selection(toggle); event[0].attr._d(Input::key);
// 	break;
//       }
//     case evKeyRepeat:
//       {
// 	Input::Toggle toggle;
// 	toggle.actuation = Input::Toggle::hold;
// 	toggle.number = e.key.sym;
// 	event->length(1);
// 	event[0].dev = 0;
// 	event[0].attr.selection(toggle); event[0].attr._d(Input::key);
// 	break;
//       }
//     case evPtrRelative:
//       {
// 	if (pos[0] + e.pmove.x >= 0 && pos[0] + e.pmove.x < size[0]) pos[0] += e.pmove.x;
// 	if (pos[1] + e.pmove.y >= 0 && pos[1] + e.pmove.y < size[1]) pos[1] += e.pmove.y;	  
// 	Input::Position position;
// 	position.x = pos[0]/res[0];
// 	position.y = pos[1]/res[1];
// 	position.z = 0;
// 	event->length(1);
// 	event[0].dev = 1;
// 	event[0].attr.location(position);
// 	break;
//       }
//     case evPtrAbsolute:
//       {
// 	pos[0] = e.pmove.x;
// 	pos[1] = e.pmove.y;
// 	Input::Position position;
// 	position.x = pos[0]/res[0];
// 	position.y = pos[1]/res[1];
// 	position.z = 0;
// 	event->length(1);
// 	event[0].dev = 1;
// 	event[0].attr.location(position);
// 	break;
//       }
//     case evPtrButtonPress:
//     case evPtrButtonRelease:
//       {
// 	Input::Toggle toggle;
// 	if (e.any.type == evPtrButtonPress)
// 	  toggle.actuation = Input::Toggle::press;
// 	else
// 	  toggle.actuation = Input::Toggle::release;
//  	toggle.number = e.pbutton.button;	  
// 	Input::Position position;
// 	position.x = pos[0]/res[0];
// 	position.y = pos[1]/res[1];
// 	position.z = 0;
// 	event->length(2);
// 	event[0].dev = 1;
// 	event[0].attr.selection(toggle); event[0].attr._d(Input::button);
// 	event[1].dev = 1;
// 	event[1].attr.location(position);
// 	break;
//       }
//     }
  return event._retn();
}

