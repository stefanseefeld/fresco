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
#ifndef _Console_hh
#define _Console_hh

#include <Prague/Sys/Plugin.hh>
#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Fresco/Input.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Console.hh>
#include <vector>
extern "C"
{
#include <ggi/ggi-unix.h>
}

namespace GGI
{

class Drawable;
class Pointer;

class Console : public ::Console
{
  typedef std::vector<Drawable *> dlist_t;
  typedef std::vector<Prague::Plugin<Extension> *> elist_t;
public:
  Console(int &, char **, Fresco::PixelCoord, Fresco::PixelCoord);
  virtual ~Console();

  virtual Pointer *pointer(Fresco::Raster_ptr);
  virtual Drawable *drawable();
  virtual Drawable *create_drawable(Fresco::PixelCoord, Fresco::PixelCoord,
				    Fresco::PixelCoord);
  Drawable *reference_to_servant(Fresco::Drawable_ptr);

  virtual void device_info(std::ostream &);
  virtual Fresco::Input::Event *next_event();
  virtual void wakeup();
  virtual void activate_autoplay() { _autoplay = true;}
  virtual void highlight_screen(Fresco::Coord, Fresco::Coord,
				Fresco::Coord, Fresco::Coord,
				double red = 1.0,
				double green = 0.0,
				double blue = 0.0);
  void add_drawable(Drawable *);
private:
  virtual Console::Extension *create_extension(const std::string &);
  Fresco::Input::Event *synthesize(const ggi_event &);
  /*
   * to be used for event notification
   */
  ggi_visual_t  _visual;
#ifdef RMDEBUG
  ggi_visual_t  _backup;
#endif
  /*
   * to be used for pointing devices
   */
  long          _size[2];
  long          _position[2];
  double        _resolution[2];
  bool          _autoplay;
  int           _wakeupPipe[2];
  dlist_t       _drawables;

  elist_t       _modules;
};

}

#endif
