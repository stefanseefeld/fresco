/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 2001 Philip Philonenko <philonenko@orgacom.ru> 
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

#include <Prague/Sys/Memory.hh>
#include <Prague/Sys/FdSet.hh>
#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Path.hh>
#include <Berlin/RCManager.hh>
#include <Berlin/Logger.hh>

#include "Console.hh"
#include "Extension.hh"
#include "Drawable.hh"
#include "Pointer.hh"

using namespace Fresco;

namespace
{
  static void readEvent(SDL_Event &e)
  {
    Prague::Trace trace("readEvent()");
    unsigned int t;
    std::cin >> t;
    e.type = static_cast<char>(t);
    switch (e.type)
      {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
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
    Prague::Trace trace("writeEvent()");
    std::cout << static_cast<unsigned int>(e.type) << ' ';
    switch (e.type)
      {
      case SDL_KEYDOWN:
      case SDL_KEYUP:
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
    std::cout << std::endl;
  }
}; // namespace





// ---------------------------------------------------------------
// class SDL::Console (implementation)
// ---------------------------------------------------------------

SDL::Console::Console(int &argc, char **argv,
		      Fresco::PixelCoord x, Fresco::PixelCoord y)
  :

#ifdef RMDEBUG
  _backup(0),
#endif
  _autoplay(false),
  _is_gl(false),
  _pointer_mgr(new PointerManagerT<nonGLPointer>(0)),
  _expose(0)
{
  _size[0] = x;
  _size[1] = y;

  Prague::Trace trace("SDL::Console::Console");
  Logger::log(Logger::loader) << "trying to open SDL console" << std::endl;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_ShowCursor(SDL_DISABLE);
  SDL_EnableUNICODE(SDL_ENABLE);
}

SDL::Console::~Console()
{
  Prague::Trace trace("SDL::Console::~Console");

  for (dlist_t::iterator i = _drawables.begin();
       i != _drawables.end();
       i++) delete *i;
  SDL_Quit();
}

Console::Pointer *SDL::Console::pointer(Raster_ptr raster)
{
  Prague::Trace trace("SDL::Console::pointer");
  return _pointer_mgr->create_pointer(raster);
}

Console::Drawable *SDL::Console::drawable()
{
  Prague::Trace trace("SDL::Console::drawable");

  if (_drawables.empty())
    _drawables.push_back(new SDL::Drawable(0, _size[0], _size[1]));
  
  return _drawables.front();
}

Console::Drawable *
SDL::Console::create_drawable(Fresco::PixelCoord w,
			      Fresco::PixelCoord h, Fresco::PixelCoord d)
{
  Prague::Trace trace("SDL::Console::create_drawable");

  _drawables.push_back(new SDL::Drawable("display-memory", w, h, d));
  return _drawables.back();
}

Console::Drawable *SDL::Console::reference_to_servant(Fresco::Drawable_ptr drawable)
{
  Prague::Trace trace("SDL::Console::reference_to_servant()");
  
  PortableServer::Servant servant = Console::reference_to_servant(drawable);
  for (dlist_t::iterator i = _drawables.begin(); i != _drawables.end(); ++i)
    if (*i == servant) return *i;
  return 0;
}

void SDL::Console::activate_autoplay()
{
  Prague::Trace trace("SDL::Console::activate_autoplay()");

  // FIXME: This should do something.
}

void SDL::Console::device_info(std::ostream &os)
{
  Prague::Trace trace("SDL::Console::device_info()");

  os << "sorry, device info isn't available for SDL at this time" << std::endl;
}

Input::Event *SDL::Console::next_event()
{
  Prague::Trace trace("SDL::Console::next_event()");
  
  SDL_Event event;
  SDL_WaitEvent(&event);
  if (event.type == SDL_USEREVENT)
  {
    return 0;
  }
  return synthesize(event);
}

void SDL::Console::wakeup()
{
  Prague::Trace trace("SDL::Console::wakeup()");

  SDL_Event event;
  event.type = SDL_USEREVENT;
  SDL_PushEvent(&event);
  event.user.code = 0;
  event.user.data1 = 0;
  event.user.data2 = 0;
}

Input::Event *SDL::Console::synthesize(const SDL_Event &e)
{
  Prague::Trace trace("SDL::Console::synthesize()");

  Input::Event_var event = new Input::Event;
  switch (e.type)
    {
    case SDL_VIDEOEXPOSE:
      if (_expose) _expose->refresh_screen();
      break;
    case SDL_KEYDOWN:
      {
	Input::Toggle toggle;
	toggle.actuation = Input::Toggle::press;
	toggle.number = e.key.keysym.unicode;
	event->length(1);
	event[0].dev = 0;
	event[0].attr.selection(toggle); event[0].attr._d(Input::key);
	break;
      }
    case SDL_KEYUP:
      {
        Input::Toggle toggle;
        toggle.actuation = Input::Toggle::release;
        toggle.number = e.key.keysym.unicode;
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
	position.x = _position[0]/drawable()->resolution(Fresco::xaxis);
	position.y = _position[1]/drawable()->resolution(Fresco::yaxis);
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
	position.x = _position[0]/drawable()->resolution(Fresco::xaxis);
	position.y = _position[1]/drawable()->resolution(Fresco::yaxis);
	position.z = 0;
	event->length(2);
	event[0].dev = 1;
	event[0].attr.selection(toggle); event[0].attr._d(Input::button);
	event[1].dev = 1;
	event[1].attr.location(position);
	break;
      }
    case SDL_QUIT:
      {
	// this is a CTRL+C sent to the controlling terminal. Berlin may be
	// already crashed, so terminate forcibly.
	exit(0);
	break;
      }
    }

  return event._retn();
}


void SDL::Console::set_PointerManager(PointerManager * pm) {
  _pointer_mgr = pm;
}


void SDL::Console::set_ExposeHandler(ExposeHandler * eh) {
  _expose = eh;
}


Console::Extension * SDL::Console::create_extension(const std::string & id)
{
  Prague::Trace trace("SDL::Console::create_extension()");

  if (id == "Renderer")
    return new SDL::Renderer();
  if (id == "GLContext") {
    Prague::Path path = RCManager::get_path("modulepath");
    std::string name = path.lookup_file("Console/SDLGL.so");
    Prague::Plugin<Extension> * plugin = 0;
    if (name.empty())
      {
	std::string msg =
	  "GLContext extension for SDL console not found in modulepath.";
	throw std::runtime_error(msg);
      }
    else {
      plugin = new Prague::Plugin<Extension>(name);
      _modules.push_back(plugin);
      _is_gl = 1;
      return plugin->get();
    }
  }
  if (id == "DirectBuffer")
    return new SDL::DirectBuffer();
  return 0;
}



void SDL::Console::highlight_screen(Fresco::Coord lx, Fresco::Coord ly,
				    Fresco::Coord ux, Fresco::Coord uy,
				    double red,
				    double green,
				    double blue)
{
#ifdef RMDEBUG
  // I try to stay 'below' the Drawable whereever possible so that bugs in
  // that code cannot influence the highlighting.

  if (is_gl()) {
    std::cerr << "Region Management Debugging does not work eith OpenGL on SDL."
	      << std::endl;
    return;
  }

   // compute the device space coordinates
  SDL_Rect fill;
  fill.x = static_cast<PixelCoord>(lx * drawable()->resolution(Fresco::xaxis));
  fill.y = static_cast<PixelCoord>(ly * drawable()->resolution(Fresco::yaxis));
  fill.w = static_cast<PixelCoord>(ux * drawable()->resolution(Fresco::xaxis) - fill.x);
  fill.h = static_cast<PixelCoord>(uy * drawable()->resolution(Fresco::yaxis) - fill.y);

  SDL::Drawable * d = static_cast<SDL::Drawable *>(drawable());
  SDL_Surface * screen = d->surface();
  SDL_PixelFormat * pf = screen->format;
  
  if (!_backup)
    _backup = SDL_CreateRGBSurface(SDL_HWSURFACE,
				   d->width(), d->height(), pf->BitsPerPixel,
				   pf->Rmask, pf->Gmask, pf->Bmask, pf->Amask);
  
  // make a backup:
  SDL_BlitSurface(screen, 0, _backup, 0);

   // fill region:
  SDL_FillRect(screen,
	       &fill,
	       SDL_MapRGB(pf,
			  static_cast<Uint8>(0xFF * red),
			  static_cast<Uint8>(0xFF * green),
			  static_cast<Uint8>(0xFF * blue)));
  SDL_UpdateRect(screen, fill.x, fill.y, fill.w, fill.h);

  // wait a bit
  timeval tv = {0, 100000};
  select(0, 0, 0, 0, &tv);

  // restore old content
  SDL_BlitSurface(_backup, NULL, screen, NULL);
  SDL_UpdateRect(screen, 0, 0, 0, 0);
#endif  
}





// ---------------------------------------------------------------
// externs
// ---------------------------------------------------------------

extern "C" ::Console::LoaderT<SDL::Console> *load() { return new Console::LoaderT<SDL::Console>(); }
