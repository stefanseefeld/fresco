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

//. This is an abstraction of the underlying graphics libraries Berlin uses.
//. The DrawingKits call the methods of this object.
class Console
{
public:
  class Drawable;
  //. Extensions are a means to provide special Drawable APIs
  //. that are not supported on all Consoles
  class Extension
  {
  public:
    virtual ~Extension(){}
  };
private:
  typedef std::vector<Extension *> elist_t;
  //. Deletes this Console in its Destrcutor.
  struct Reaper
  {
    ~Reaper();
  };
  friend struct Reaper;

public:
  class Pointer;

  //. A helperclass to get the Console-module into memory.
  class Loader
  {
  public:
    virtual ~Loader() {}
    // This is what is called by the plugin-loader.
    virtual Console *load(int &, char **) = 0;
  };

  //. Sets up the graphics library. It gets passed the commandline arguments
  //. of the server (argc and argv), checks them for any console-related options and
  //. afterwards passes them on to the graphic's library. Finally you need to pass
  //. the POA to this method.
  static int open(const std::string &, int argc, char **argv, PortableServer::POA_ptr)
    throw(std::runtime_error);

  //. Get the active instance of the Console.
  static Console *instance();

  //. Get a pointerobject to use on this Console.
  virtual Pointer *pointer() = 0;

  //. Get the 'root-drawable' used by this Console. That's the chunk of video
  //. memory covering the whole screen.
  virtual Drawable *drawable() = 0;
  //. Creates a new Drawable of the given size (x, y) and depth.
  virtual Drawable *create_drawable(Warsaw::PixelCoord, //.< Requested x size.
				    Warsaw::PixelCoord, //.< Requested y size.
				    Warsaw::PixelCoord) = 0; //.< Requested color depth.
  //. Creates a new Drawable of the given size (x, y) and depth. It is accessable
  //. under the given shm-id.
  virtual Drawable *create_shm_drawable(int, //.< SHM ID.
					Warsaw::PixelCoord, //.< Requested x size.
					Warsaw::PixelCoord, //.< Requested y size.
					Warsaw::PixelCoord) = 0; //. Requested depth.

  //. Activates a given drawable: After activation it can recieve requests via CORBA.
  Warsaw::Drawable_ptr activate_drawable(Drawable *);
  //. FIXME: Missing documentation!
  PortableServer::Servant reference_to_servant(Warsaw::Drawable_ptr);

  //. FIXME: Missing documentation!
  virtual void device_info(std::ostream &) = 0;
  //. FIXME: Missing documentation!
  virtual Warsaw::Input::Event *next_event() = 0;
  //. FIXME: Missing documentation!
  virtual void wakeup() = 0;
  //. FIXME: Missing documentation!
  virtual void activate_autoplay() = 0;
  template <typename T>
  T *get_extension(const std::string &id, Drawable *drawable)
  {
    Extension *extension = create_extension(id, drawable);
    T *t = dynamic_cast<T *>(extension);
    if (!t)
      {
	delete extension;
	throw (std::runtime_error(id + ": no such extension"));
      }
    _extensions.push_back(extension);
    return t;
  }
protected:
  Console() {}
  virtual ~Console() {}
private:
  virtual Extension      *create_extension(const std::string &, Drawable *) = 0;
  PortableServer::POA_var _poa;
  static Console         *_console;
  static Reaper           _reaper;
  elist_t                 _extensions;
};

//. This is a chunk of (video-) memory that is used to store raster data.
class Console::Drawable : public virtual POA_Warsaw::Drawable,
	                  public virtual PortableServer::RefCountServantBase
{
public:
  typedef char data_type;
  Drawable() {}
  virtual ~Drawable() {}

  //. FIXME: Missing documentation!
  virtual Warsaw::Drawable::PixelFormat pixel_format() = 0;
  //. FIXME: Missing documentation!
  virtual Warsaw::Drawable::BufferFormat buffer_format() = 0;
  //. FIXME: Missing documentation!
  virtual Warsaw::PixelCoord width() const = 0;
  //. FIXME: Missing documentation!
  virtual Warsaw::PixelCoord height() const = 0;
  //. FIXME: Missing documentation!
  virtual Warsaw::PixelCoord vwidth() const = 0;
  //. FIXME: Missing documentation!
  virtual Warsaw::PixelCoord vheight() const = 0;
  //. FIXME: Missing documentation!
  virtual Warsaw::Coord resolution(Warsaw::Axis) const = 0;
  //. FIXME: Missing documentation!
  virtual Warsaw::Coord dpi(Warsaw::Axis) const = 0;
  //. FIXME: Missing documentation!
  virtual Warsaw::PixelCoord row_length() const = 0;

  //. FIXME: Missing documentation!
  virtual void flush() = 0;
  //. FIXME: Missing documentation!
  virtual void flush(Warsaw::PixelCoord, Warsaw::PixelCoord,
		     Warsaw::PixelCoord, Warsaw::PixelCoord) = 0;

  //. Called by the server when the scene is about to be drawn.
  //. This is a suitable place to add calls for building display
  //. lists (for example).
  virtual void init() = 0;
  //. Called by the server as soon as the scene finished drawing.
  virtual void finish() = 0;

  //. Copy part of this Drawable to a new location in the same Drawable.
  //. These locations may overlap.
  virtual void blit(Warsaw::PixelCoord, //.< x position of one corner of the source area
		    Warsaw::PixelCoord, //.< y position of one corner of the source area
		    Warsaw::PixelCoord, //.< width of the source area
		    Warsaw::PixelCoord, //.< height of the source area
		    Warsaw::PixelCoord, //.< x position of correspnding corner of the
		                        //.< destination area
		    Warsaw::PixelCoord) = 0; //.< y position of correspnding corner
		                             //.< of the destination area
  //. Copy parts of the given Drawable to the specified position in this Drawable.
  virtual void blit(const Drawable &,   //.< source Drawable
 		    Warsaw::PixelCoord, //.< x position of one corner of the source area
		    Warsaw::PixelCoord, //.< y position of one corner of the source area
		    Warsaw::PixelCoord, //.< width of the source area
		    Warsaw::PixelCoord, //.< height of the source area
		    Warsaw::PixelCoord, //.< x position of correspnding corner of the
		                        //.< destination area
		    Warsaw::PixelCoord) = 0; //.< y position of correspnding corner
		                             //.< of the destination area
  //. Copy parts of the given Drawable to the specified position in this Drawable
  virtual void blit(Warsaw::Drawable_ptr, //.< source Drawable
		    Warsaw::PixelCoord, //.< x position of one corner of the source area
		    Warsaw::PixelCoord, //.< y position of one corner of the source area
		    Warsaw::PixelCoord, //.< width of the source area
		    Warsaw::PixelCoord, //.< height of the source area
		    Warsaw::PixelCoord, //.< x position of correspnding corner of the
		                        //.< destination area
		    Warsaw::PixelCoord) = 0; //.< y position of correspnding corner
		                             //.< of the destination area
private:
  Drawable(const Drawable &);
  Drawable &operator = (const Drawable &);
};

//. This class is used to render the mousepointer.
class Console::Pointer : public virtual PortableServer::RefCountServantBase
{
public:
  virtual ~Pointer() {}
  //. Move the pointer to the given Pixelcoordinate.
  virtual void move(Warsaw::Coord, Warsaw::Coord) = 0;
  //. FIXME: Missing documentation!
  virtual void draw() = 0;
  //. FIXME: Missing documentation!
  virtual void save() = 0;
  //. FIXME: Missing documentation!
  virtual void restore() = 0;
  //. FIXME: Missing documentation!
  virtual bool intersects(Warsaw::Coord, Warsaw::Coord,
			  Warsaw::Coord, Warsaw::Coord) = 0;
};

template <typename T>
class ConsoleLoader : public Console::Loader
{
public:
  virtual T *load(int &argc, char **argv) { return new T(argc, argv);}
};

#endif
