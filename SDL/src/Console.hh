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

#ifndef _SDL_Console_hh
#define _SDL_Console_hh

#include <Warsaw/config.hh>
#include <Prague/Sys/Plugin.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
#include <Berlin/Console.hh>

#include <vector>

extern "C"
{
#include <SDL.h>
#include <sys/types.h>
#include <unistd.h>
}





namespace SDL
{

class Drawable;
class Pointer;





// ---------------------------------------------------------------
// class SDLConsole declaration
// ---------------------------------------------------------------

class Console : public ::Console
{
public:
  Console(int &, char **);

  virtual ~Console();
  static Console *instance() { return static_cast<SDL::Console *>(Console::instance());}

  // Create:
  virtual Pointer *pointer(Warsaw::Raster_ptr);
  virtual Drawable *drawable();
  virtual Drawable *create_drawable(Warsaw::PixelCoord, Warsaw::PixelCoord,
				    Warsaw::PixelCoord);

  // CORBA related:
  Drawable *reference_to_servant(Warsaw::Drawable_ptr);

  // Input related:
  virtual void device_info(std::ostream &);
  virtual Warsaw::Input::Event *next_event();
  virtual void activate_autoplay();
  virtual void highlight_screen(Warsaw::Coord, Warsaw::Coord,
				Warsaw::Coord, Warsaw::Coord) {}
  virtual void wakeup();

  void add_drawable(SDL::Drawable *);

  // SDL-specific:
  bool is_gl() const { return _is_gl;}

private:

  typedef std::vector<Drawable *> dlist_t;
  typedef std::vector<Prague::Plugin<Extension> *> elist_t;

  Console::Extension * create_extension(const std::string &);

  Warsaw::Input::Event *synthesize(const SDL_Event &);

  bool                _autoplay;
  dlist_t             _drawables;
  elist_t             _modules;
  Pointer            *_pointer;
  
  bool                _is_gl;

  Warsaw::Coord       _resolution[2];
  Warsaw::PixelCoord  _size[2];
  Warsaw::PixelCoord  _vsize[2];

  int                 _wakeupPipe[2];
  long                _position[2];
};

}; // namespace SDL

#endif
