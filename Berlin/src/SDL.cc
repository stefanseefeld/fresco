/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include "Berlin/Console.hh"
#include <Prague/Sys/FdSet.hh>
#include <Prague/Sys/Tracer.hh>

vector<DrawableTie<SDLDrawable> *> SDLConsole::drawables;

SDLConsole::SDLConsole()// throw (exception)
  : autoplay(false)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDLDrawable *drawable = new SDLDrawable(0);
  visual = drawable->vis;
  size[0] = drawable->mode.visible.x;
  size[1] = drawable->mode.visible.y;
  pos[0] = 0;
  pos[1] = 0;
  res[0] = 0.1 * drawable->mode.visible.x / drawable->mode.size.x;
  res[1] = 0.1 * drawable->mode.visible.y / drawable->mode.size.y;

  drawables.push_back(new DrawableTie<Drawable>(drawable));
  pipe(wakeupPipe);
}

SDLConsole::~SDLConsole()
{
  for (vector<DrawableTie<SDLDrawable> *>::iterator i = drawables.begin(); i != drawables.end(); i++) delete *i;
  close(wakeupPipe[0]);
  close(wakeupPipe[1]);
  SDL_Quit();
}

DrawableTie<SDLDrawable> *SDLConsole::drawable()
{
//   if (!drawables.size()) drawables.push_back(new DrawableTie<Drawable>(new GGIDrawable(0)));
  return drawables.front();
}

DrawableTie<SDLDrawable> *SDLConsole::newDrawable(PixelCoord w, PixelCoord h, PixelCoord d)
{
  SDLDrawable *drawable = new SDLDrawable("display-memory");
  long depth = GGI_AUTO;
  switch (d)
    {
    case 1: depth = GT_8BIT; break;
    case 2: depth = GT_16BIT; break;
    case 3: depth = GT_24BIT; break;
    case 4: depth = GT_32BIT; break;
    default:
      cerr << "GGIConsole: Warning: " << d << " bytes per pixel not supported" << endl;
      break;
    };
  ggiSetGraphMode(drawable->vis, w, h, w, h, depth);
  return new DrawableTie<SDLDrawable>(drawable);
}

static void readEvent(SDL_Event &e)
{
  unsigned int t;
  cin >> t;
  e.any.type = (char)t;
  switch (e.any.type)
    {
    case evKeyPress:
    case evKeyRepeat:
      {
	cin >> t;
	e.key.sym = t;
	break;
      }
    case evPtrRelative:
    case evPtrAbsolute:
      {
	cin >> e.pmove.x
	    >> e.pmove.y;
	break;
      }
    case evPtrButtonPress:
    case evPtrButtonRelease:
      {
	break;
      }
  }
}

static void writeEvent(SDL_Event &e)
{
  cout << ((unsigned int)(e.any.type)) << ' ';
  switch (e.any.type)
    {
    case evKeyPress:
    case evKeyRepeat:
      {
	cout << ((unsigned int)(e.key.sym));
	break;
      }
    case evPtrRelative:
    case evPtrAbsolute:
      {
	cout << e.pmove.x << ' '
	     << e.pmove.y;
	break;
      }
    case evPtrButtonPress:
    case evPtrButtonRelease:
      {
	break;
      }
    }
  cout << endl;
}

Input::Event *SDLConsole::nextEvent()
{
  Prague::Trace trace("SDL::Console::nextEvent");
  SDL_Event event;
  ggi_event_mask mask = ggi_event_mask (emKeyboard | emPtrMove | emPtrButtonPress | emPtrButtonRelease);
  ggi_event_mask move_mask = ggi_event_mask (emPtrMove);

  int input = fileno(stdin);
  Prague::FdSet rfdset;
  rfdset.set(wakeupPipe[0]);
  if (autoplay) rfdset.set(input);
  int nfds = ggiEventSelect(visual, &mask, rfdset.max() + 1, rfdset, 0, 0, 0);
 
  if (nfds == 0)
    {
      // no input from the outside world
      ggiEventRead(visual, &event, mask); 
      if (event.any.type == evPtrRelative || event.any.type == evPtrAbsolute)
	{
	  int m = ggiEventsQueued(visual, mask);
	  int n = ggiEventsQueued(visual, move_mask);
	  if (m == n)  // nothing but a bunch of moves queued up
	    {
	      int x=event.pmove.x, y=event.pmove.y;
	      for (int i = 0; i < n; ++i)
		{
		  // consume them all
		  ggiEventRead(visual, &event, move_mask); 	  
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
      if (autoplay) writeEvent(event);
      return synthesize(event);
    }
  else 
    {
      if (autoplay && rfdset.isset(input))
	{
	  readEvent(event);
	  return synthesize(event);
	}
      else
	{
	  if (rfdset.isset(wakeupPipe[0]))
	    {
	      char c; read(wakeupPipe[0], &c, 1);
	      return 0;
	    }
	}
    }
  return 0;
}

void SDLConsole::wakeup() { char c = 'z'; write(wakeupPipe[1],&c,1);}

Input::Event *SDLConsole::synthesize(const SDL_Event &e)
{
  Input::Event_var event = new Input::Event;
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
    case evPtrRelative:
      {
	if (pos[0] + e.pmove.x >= 0 && pos[0] + e.pmove.x < size[0]) pos[0] += e.pmove.x;
	if (pos[1] + e.pmove.y >= 0 && pos[1] + e.pmove.y < size[1]) pos[1] += e.pmove.y;	  
	Input::Position position;
	position.x = pos[0]/res[0];
	position.y = pos[1]/res[1];
	position.z = 0;
	event->length(1);
	event[0].dev = 1;
	event[0].attr.location(position);
	break;
      }
    case evPtrAbsolute:
      {
	pos[0] = e.pmove.x;
	pos[1] = e.pmove.y;
	Input::Position position;
	position.x = pos[0]/res[0];
	position.y = pos[1]/res[1];
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
	position.x = pos[0]/res[0];
	position.y = pos[1]/res[1];
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

SDLDrawable::SDLDrawable(const char *display) // throw (exception)
{
  if (display) vis = ggiOpen(display, 0);
  else vis = ggiOpen(0);
  if (!vis) throw exception();
  mode.visible.x = mode.visible.y = GGI_AUTO;
  mode.virt.x = mode.virt.y = GGI_AUTO;
  mode.size.x = GGI_AUTO;
  mode.size.y = GGI_AUTO;
  mode.dpp.x = mode.dpp.y = 1;
  mode.graphtype = GT_AUTO;
  mode.frames = 1;
  if (ggiCheckMode(vis, &mode) == 0)
    {
      // Cannot set visual, even though GGI says it's ok???
      if (ggiSetMode(vis, &mode) != 0) throw exception();
    }
  else
    {
      // Hmm. internal GGI problem. The mode GGI gave us still won't work.
      if (ggiCheckMode(vis, &mode) != 0 || ggiSetMode(vis, &mode) != 0) throw exception();
    }
  mode.size = mode.visible; // awful hack around a ggi bug...
  ggiAddFlags(vis, GGIFLAG_ASYNC);
}

GGIDrawable::~GGIDrawable()
{
  ggiClose(vis);
}

DrawableTie<GGIDrawable>::PixelFormat GGIDrawable::pixelFormat()
{
  DrawableTie<GGIDrawable>::PixelFormat format;
  const ggi_pixelformat *pf = ggiGetPixelFormat(vis);
  format.depth       = pf->depth;
  format.size        = pf->size;
  format.red_mask    = pf->red_mask;
  format.red_shift   = pf->red_shift;
  format.green_mask  = pf->green_mask;
  format.green_shift = pf->green_shift;
  format.blue_mask   = pf->blue_mask;
  format.blue_shift  = pf->blue_shift;
  format.alpha_mask  = pf->alpha_mask;
  format.alpha_shift = pf->alpha_shift;
  return format;
}
