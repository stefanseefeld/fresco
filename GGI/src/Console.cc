/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#include <Prague/Sys/Path.hh>
#include <Prague/Sys/Tracer.hh>
#include <Berlin/RCManager.hh>
#include "Console.hh"
#include "Drawable.hh"
#include "Extension.hh"
#include "Pointer.hh"

#undef isset

using namespace Prague;
using namespace Fresco;

namespace
{
void read_event(ggi_event &e)
{
  unsigned int t;
  std::cin >> t;
  e.any.type = (char)t;
  switch (e.any.type)
    {
    case evKeyPress:
    case evKeyRepeat:
    case evKeyRelease:
      {
	std::cin >> t;
	e.key.sym = t;
	break;
      }
    case evPtrRelative:
    case evPtrAbsolute:
      {
	std::cin >> e.pmove.x >> e.pmove.y;
	break;
      }
    case evPtrButtonPress:
    case evPtrButtonRelease:
      break;
    }
}

void write_event(ggi_event &e)
{
  std::cout << ((unsigned int)(e.any.type)) << ' ';
  switch (e.any.type)
    {
    case evKeyPress:
    case evKeyRepeat:
    case evKeyRelease:
      {
	std::cout << ((unsigned int)(e.key.sym));
	break;
      }
    case evPtrRelative:
    case evPtrAbsolute:
      {
	std::cout << e.pmove.x << ' ' << e.pmove.y;
	break;
      }
    case evPtrButtonPress:
    case evPtrButtonRelease:
      break;
    }
  std::cout << std::endl;
}
};

GGI::Console::Console(int &argc, char **argv, 
                      Fresco::PixelCoord x, Fresco::PixelCoord y)
  : _autoplay(false)
{
  ggiInit();
  GGI::Drawable *drawable = new GGI::Drawable(0, x, y);
  _visual = drawable->_visual;
#ifdef RMDEBUG
   // make a fullscreen backup visual
   _backup = ggiOpen("display-memory", 0);
   ggi_mode mode;
   mode.visible.x = mode.virt.x = drawable->width();
   mode.visible.y = mode.virt.y = drawable->height();
   mode.size.x = GGI_AUTO;
   mode.size.y = GGI_AUTO;
   mode.dpp.x = mode.dpp.y = 1;
   mode.graphtype = GT_24BIT;
   mode.frames = 1;
   ggiSetMode(_backup, &mode);
#endif
  _size[0] = drawable->_mode.visible.x;
  _size[1] = drawable->_mode.visible.y;
  _position[0] = 0;
  _position[1] = 0;
  _resolution[0] = 0.1 * drawable->_mode.visible.x / drawable->_mode.size.x;
  _resolution[1] = 0.1 * drawable->_mode.visible.y / drawable->_mode.size.y;

  _drawables.push_back(drawable);
  pipe(_wakeupPipe);
}

GGI::Console::~Console()
{
  for (dlist_t::iterator i = _drawables.begin(); i != _drawables.end(); i++) delete *i;
  close(_wakeupPipe[0]);
  close(_wakeupPipe[1]);
  ggiExit();
}

Console::Pointer *GGI::Console::pointer(Raster_ptr raster)
{
  return new GGI::Pointer(dynamic_cast<GGI::Drawable *>(drawable()), raster);
}

Console::Drawable *GGI::Console::drawable()
{
  assert(_drawables.size());
  return _drawables.front();
}

Console::Drawable *GGI::Console::create_drawable(PixelCoord w, PixelCoord h, PixelCoord d)
{
  _drawables.push_back(new GGI::Drawable("display-memory", w, h, d));
  return _drawables.back();
}

Console::Drawable *GGI::Console::reference_to_servant(Drawable_ptr drawable)
{
  Trace trace("GGI::Console::reference_to_servant");
  PortableServer::Servant servant = Console::reference_to_servant(drawable);
  for (dlist_t::iterator i = _drawables.begin(); i != _drawables.end(); ++i)
    if (*i == servant) return *i;
  return 0;
}

void GGI::Console::device_info(std::ostream &os)
{
  unsigned int number = 0;
  unsigned int origin;
  gii_cmddata_getdevinfo device;
  int status = 0;
  while ((status = giiQueryDeviceInfoByNumber(ggiJoinInputs(_visual, 0), number++, &origin, &device)) == 0)
    {
      os << "device name: '" << device.longname << "\', axes: " << device.num_axes << ", buttons: " << device.num_buttons << "\n";
      for (int i = 0; i != device.num_axes; ++i)
	{
	  gii_cmddata_getvalinfo valuator;
	  int s = giiQueryValInfo(ggiJoinInputs(_visual, 0), origin, i, &valuator);
	  if (s == 0)
	    os << "\t axis: '" << valuator.longname << "\', range: min="
	       << valuator.range.min << ", max=" << valuator.range.max << ", origin=" << valuator.range.center << std::endl;
	}
    }
}

Input::Event *GGI::Console::next_event()
{
  Prague::Trace trace("GGI::Console::next_event");
  ggi_event event;
  ggi_event_mask mask;
  ggi_event_mask move_mask = ggi_event_mask(emPtrMove | emValuator);

  int input = fileno(stdin);
  Prague::FdSet rfdset;

  int nfds = -1;
  do
    {
      mask = ggi_event_mask(emKeyboard | emPtrMove | emPtrButton | emValuator);
      rfdset.set (_wakeupPipe[0]);
      if (_autoplay)
	rfdset.set (input);
      nfds = ggiEventSelect(_visual, &mask, rfdset.max() + 1, rfdset, 0, 0, 0);
    }
  while (nfds == -1 && errno == EINTR);

  if (nfds == 0)
    {
      // no input from the outside world
      ggiEventRead(_visual, &event, mask); 
      if (event.any.type == evPtrRelative || event.any.type == evPtrAbsolute)// ||
	//	  event.any.type == evValAbsolute)
	{
	  int m = ggiEventsQueued(_visual, mask);
	  int n = ggiEventsQueued(_visual, move_mask);
	  // std::cout << "events " << m << ' ' << n << std::endl;
	  if (m == n)  // nothing but a bunch of moves queued up
	    {
	      int x = event.pmove.x, y = event.pmove.y;
	      for (int i = 0; i < n; ++i)
		{
		  // consume them all
		  ggiEventRead(_visual, &event, move_mask); 	  
		  if (event.any.type == evPtrRelative)
		    {
		      x += event.pmove.x;
		      y += event.pmove.y;
		    }
		}
	      if (event.any.type == evPtrRelative)
		{
		  event.pmove.x = x;
		  event.pmove.y = y;
		}
	    }
	}
      if (_autoplay) write_event(event);
      return synthesize(event);
    }
  else if (nfds > 0)
    {
      if (_autoplay && rfdset.isset(input))
	{
	  read_event(event);
	  return synthesize(event);
	}
      else
	{
	  if (rfdset.isset(_wakeupPipe[0]))
	    {
	      char c; read(_wakeupPipe[0], &c, 1);
	      return 0;
	    }
	}
    }
  return 0;
}

void GGI::Console::wakeup() { char c = 'z'; write(_wakeupPipe[1],&c,1);}

void GGI::Console::add_drawable(Console::Drawable *drawable)
{
  _drawables.push_back(drawable);
}

Input::Event *GGI::Console::synthesize(const ggi_event &e)
{
  Input::Event_var event = new Input::Event;
//   std::cerr << "input from event " << e.any.origin << std::endl;
  switch (e.any.type)
    {
    case evKeyPress:
      {
	Input::Toggle toggle;
	toggle.actuation = Input::Toggle::press;
	toggle.number = e.key.sym;
	event->length(1);
	event[0].dev = 0;
	event[0].attr.selection(toggle); event[0].attr._d(Input::key);
	break;
      }
    case evKeyRepeat:
      {
	Input::Toggle toggle;
	toggle.actuation = Input::Toggle::hold;
	toggle.number = e.key.sym;
	event->length(1);
	event[0].dev = 0;
	event[0].attr.selection(toggle); event[0].attr._d(Input::key);
	break;
      }
    case evKeyRelease:
      {
        Input::Toggle toggle;
        toggle.actuation = Input::Toggle::release;
        toggle.number = e.key.sym;
        event->length(1);
        event[0].dev = 0;
        event[0].attr.selection(toggle); event[0].attr._d(Input::key);
        break;
      }
    case evPtrRelative:
      {
	if (_position[0] + e.pmove.x >= 0 && _position[0] + e.pmove.x < _size[0]) _position[0] += e.pmove.x;
	if (_position[1] + e.pmove.y >= 0 && _position[1] + e.pmove.y < _size[1]) _position[1] += e.pmove.y;	  
	Input::Position position;
	position.x = _position[0]/_resolution[0];
	position.y = _position[1]/_resolution[1];
	position.z = 0;
	event->length(1);
	event[0].dev = 1;
	event[0].attr.location(position);
	break;
      }
    case evPtrAbsolute:
      {
	_position[0] = e.pmove.x;
	_position[1] = e.pmove.y;
	Input::Position position;
	position.x = _position[0]/_resolution[0];
	position.y = _position[1]/_resolution[1];
	position.z = 0;
	event->length(1);
	event[0].dev = 1;
	event[0].attr.location(position);
	break;
      }
    case evPtrButtonPress:
    case evPtrButtonRelease:
      {
	Input::Toggle toggle;
	if (e.any.type == evPtrButtonPress)
	  toggle.actuation = Input::Toggle::press;
	else
	  toggle.actuation = Input::Toggle::release;
 	toggle.number = e.pbutton.button;	  
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
    case evValAbsolute:
      {
	// wacom intuo (quick hack):
	// stylus uses val numbers 0 and 1 for x/y
	for (int i = 0; i != e.val.count; ++i)
	  {
	    int number = e.val.first + i;
	    if (number == 0) _position[0] = (e.val.value[i]*800)/20320;
	    else if (number == 1) _position[1] = (e.val.value[i]*600)/15040;;
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
    }
  return event._retn();
}

void GGI::Console::highlight_screen(Coord lx, Coord ly,
				    Coord ux, Coord uy,
				    double red,
				    double green,
				    double blue)
{
#ifdef RMDEBUG
   // compute the device space coordinates
   PixelCoord x = static_cast<PixelCoord>(lx * _resolution[0]);
   PixelCoord y = static_cast<PixelCoord>(ly * _resolution[1]);
   PixelCoord w = static_cast<PixelCoord>(ux * _resolution[0] - x);
   PixelCoord h = static_cast<PixelCoord>(uy * _resolution[1] - y);

   // make a backup
   ggiCrossBlit(_visual, x, y, w, h, _backup, x, y);

   // fill region with red
   ggi_pixel back;
   ggiGetGCForeground(_visual, &back);
   ggi_color hi = {static_cast<unsigned>(0xffff * red),
		   static_cast<unsigned>(0xffff * green),
		   static_cast<unsigned>(0xffff * blue),
		   0xffff};
   ggiSetGCForeground(_visual, ggiMapColor(_visual, &hi));
   ggiDrawBox(_visual, x, y, w, h);
   ggiFlushRegion(_visual, x, y, w, h);
   ggiSetGCForeground(_visual, back);
   
   // wait a bit
   timeval tv = {0, 100000};
   select(0, 0, 0, 0, &tv);

   // restore old content
   ggiCrossBlit(_backup, x, y, w, h, _visual, x, y);
   ggiFlush(_visual);
#endif  
}


Console::Extension *GGI::Console::create_extension(const std::string &id)
{
  if (id == "DirectBuffer") return new DirectBuffer();
  if (id == "Renderer") return new Renderer();
  if (id == "SHMDrawableFactory") return new SHMDrawableFactory();
  if (id == "GGIDrawableFactory") return new GGIDrawableFactory();
  if (id == "GLContext")
    {
      Prague::Path path = RCManager::get_path("modulepath");
      std::string name = path.lookup_file("Console/GGIGL.so");
      Plugin<Extension> *plugin = 0;
      if (name.empty())
        {
          std::string msg = "GLContext extension for GGI console not found in modulepath.";
          throw std::runtime_error(msg);
        }
      else plugin = new Plugin<Extension>(name);
      _modules.push_back(plugin);
      return plugin->get();
    }
  return 0;
}

extern "C" ::Console::LoaderT<GGI::Console> *load() { return new Console::LoaderT<GGI::Console>();}
