/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _Console_hh
#define _Console_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
#include <Warsaw/Drawable.hh>
#include <Berlin/config.hh>
#include <stdexcept>
#include <iosfwd>

class Console
{
  struct Reaper
  {
    ~Reaper();
  };
  friend struct Reaper;
public:
  class Drawable;
  class Pointer;
  class Loader
  {
  public:
    virtual ~Loader(){}
    virtual Console *load(int &, char **) = 0;
  };
  static int open(int argc, char **argv, PortableServer::POA_ptr) throw(std::runtime_error);
  static Console *instance();
  virtual Pointer *pointer() = 0;
  virtual Drawable *drawable() = 0;
  virtual Drawable *create_drawable(Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord) = 0;
  virtual Drawable *create_shm_drawable(int, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord) = 0;

  Warsaw::Drawable_ptr activate_drawable(Drawable *);
  PortableServer::Servant reference_to_servant(Warsaw::Drawable_ptr);

  virtual void device_info(std::ostream &) = 0;
  virtual Warsaw::Input::Event *next_event() = 0;
  virtual void wakeup() = 0;
  virtual void activate_autoplay() = 0;
protected:
  Console() {}
  virtual ~Console() {}
private:
  PortableServer::POA_var _poa;
  static Console         *_console;
  static Reaper           _reaper;
};

class Console::Drawable : public virtual POA_Warsaw::Drawable,
	                  public virtual PortableServer::RefCountServantBase
{
public:
  Drawable() {}
  virtual ~Drawable() {}
  virtual Warsaw::Drawable::PixelFormat pixel_format() = 0;
  virtual Warsaw::Drawable::BufferFormat buffer_format() = 0;
  virtual Warsaw::PixelCoord width() const = 0;
  virtual Warsaw::PixelCoord height() const = 0;
  virtual Warsaw::PixelCoord vwidth() const = 0;
  virtual Warsaw::PixelCoord vheight() const = 0;
  virtual Warsaw::Coord resolution(Warsaw::Axis) const = 0;
  virtual Warsaw::Coord dpi(Warsaw::Axis) const = 0;
  virtual Warsaw::PixelCoord row_length() const = 0;
  virtual void flush() = 0;
  virtual void flush(Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord) = 0;

  /**
   * Init and finish hooks called by the server when the scene is
   * about to be drawn, and when it has been drawn, respectively. This
   * is a suitable place to add calls for building display lists, for
   * example (this is what is done in the GLUT and CAVELib consoles).
   **/
  virtual void init() = 0;
  virtual void finish() = 0;
private:
  Drawable(const Drawable &);
  Drawable &operator = (const Drawable &);
};

class Console::Pointer : public virtual PortableServer::RefCountServantBase
{
public:
  virtual ~Pointer() {}
  virtual void move(Warsaw::Coord, Warsaw::Coord) = 0;
  virtual void draw() = 0;
  virtual void save() = 0;
  virtual void restore() = 0;
  virtual bool intersects(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord) = 0;
};

template <typename T>
class ConsoleLoader : public Console::Loader
{
public:
  virtual T *load(int &argc, char **argv) { return new T(argc, argv);}
};

#endif /* _Console_hh */
