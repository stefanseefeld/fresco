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

#ifndef _Berlin_Console_hh
#define _Berlin_Console_hh

#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <Fresco/Input.hh>
#include <Fresco/Drawable.hh>
#include <Fresco/Raster.hh>
#include <Berlin/config.hh>
#include <stdexcept>
#include <iosfwd>
#include <vector>
#include <map>

namespace Berlin
{

  //. This is an abstraction of the underlying graphics libraries
  //. Berlin uses. The DrawingKits call the methods of this object.
  class Console
  {
    public:
      class Drawable;
      //. Extensions are a means to provide special APIs
      //. that are not supported on all Consoles
      class Extension
      {
    public:
      virtual ~Extension() { }
      };
    private:
      typedef std::vector<Extension *> elist_t;
      //. Deletes this Console in its Destrcuctor.
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
      virtual Console *load(int &, char **, 
                Fresco::PixelCoord,
                Fresco::PixelCoord) = 0;
      
      };
      template <typename T>
      class LoaderT : public Loader
      {
    public:
      virtual T *load(int &argc, char **argv, 
              Fresco::PixelCoord x, Fresco::PixelCoord y)
      { return new T(argc, argv, x, y); }

      };

      //. List available consoles (modules)
      static void list_available(std::ostream &);

      //. Check whether a particular console (module) is avilable
      static bool is_available(std::string const &console);

      //. Sets up the graphics library. It gets passed the commandline
      //. arguments of the server (argc and argv), checks them for any
      //. console-related options and afterwards passes them on to the
      //. graphic's library. Finally you need to pass the POA to this
      //. method.
      // FIXME: argc/argv are unused? are we still aiming for cascading
      //        GetOpt?
      static int open(const std::string &, int argc, char **argv, 
              PortableServer::POA_ptr, 
              Fresco::PixelCoord x, Fresco::PixelCoord y)
      throw(std::runtime_error);

      //. Get the active instance of the Console.
      static Console *instance();
      
      //. Get a pointerobject to use on this Console.
      virtual Pointer *pointer(Fresco::Raster_ptr) = 0;
      
      //. Get the 'root-drawable' used by this Console. That's the chunk
      //. of video memory covering the whole screen.
      virtual Drawable *drawable() = 0;
      //. Creates a new Drawable of the given size (x, y) and depth.
      virtual Drawable *
      create_drawable(Fresco::PixelCoord, //.< Requested x size.
              Fresco::PixelCoord, //.< Requested y size.
              Fresco::PixelCoord) = 0; //.< Requested color depth.

      //. Activates a given drawable: After activation it can recieve
      //. requests via CORBA.
      Fresco::Drawable_ptr activate_drawable(Drawable *);
      //. FIXME: Missing documentation!
      PortableServer::Servant reference_to_servant(Fresco::Drawable_ptr);

      //. FIXME: Missing documentation!
      virtual void device_info(std::ostream &) = 0;
      //. FIXME: Missing documentation!
      virtual Fresco::Input::Event *next_event() = 0;
      //. FIXME: Missing documentation!
      virtual void wakeup() = 0;
      //. FIXME: Missing documentation!
      virtual void activate_autoplay() = 0;
      //. Highlight the specified region to aid debugging.
      //. You can set the color of the highlight by passing a
      //. red, green and blue betwenn 0.0 and 1.0. If
      //. you do not pass a color it defaults to red.
      virtual void highlight_screen(Fresco::Coord, Fresco::Coord,
                    Fresco::Coord, Fresco::Coord,
                    double red = 1.0,
                    double green = 0.0,
                    double blue = 0.0) = 0;
      
      template <typename T>
      T *get_extension(const std::string &id)
      {
      Extension *extension = create_extension(id);
      T *t = dynamic_cast<T *>(extension);
      if (!t)
      {
          delete extension;
          throw (std::runtime_error(id + ": no such extension"));
      }
      my_extensions.push_back(extension);
      return t;
      }
    protected:
      Console() { }
      virtual ~Console() { }
    private:
      virtual Extension      *create_extension(const std::string &) = 0;
      PortableServer::POA_var my_poa;
      static Console         *my_console;
      static Reaper           my_reaper;
      elist_t                 my_extensions;

      typedef std::map<std::string, std::string> console_list_t;
      static console_list_t my_available_consoles;
      //. Attempt to load all consoles, and cache their name/location
      static void cache_available_consoles();
  };

//. This is a chunk of (video-) memory that is used to store raster data.
  class Console::Drawable : public virtual POA_Fresco::Drawable,
                    public virtual PortableServer::RefCountServantBase
  {
    public:
      class Extension : public virtual Console::Extension
      {
    public:
      virtual void attach(Drawable *) = 0;
      };
      typedef char data_type;
      Drawable() {}
      virtual ~Drawable() {}

      //. FIXME: Missing documentation!
      virtual Fresco::Drawable::PixelFormat pixel_format() = 0;
      //. FIXME: Missing documentation!
      virtual Fresco::Drawable::BufferFormat buffer_format() = 0;
      //. FIXME: Missing documentation!
      virtual Fresco::PixelCoord width() const = 0;
      //. FIXME: Missing documentation!
      virtual Fresco::PixelCoord height() const = 0;
      //. FIXME: Missing documentation!
      virtual Fresco::PixelCoord vwidth() const = 0;
      //. FIXME: Missing documentation!
      virtual Fresco::PixelCoord vheight() const = 0;
      //. FIXME: Missing documentation!
      virtual Fresco::Coord resolution(Fresco::Axis) const = 0;
      //. FIXME: Missing documentation!
      virtual Fresco::Coord dpi(Fresco::Axis) const = 0;
      //. FIXME: Missing documentation!
      virtual Fresco::PixelCoord row_length() const = 0;

      //. FIXME: Missing documentation!
      virtual void flush() = 0;
      //. FIXME: Missing documentation!
      virtual void flush(Fresco::PixelCoord, Fresco::PixelCoord,
             Fresco::PixelCoord, Fresco::PixelCoord) = 0;

      //. Called by the server when the scene is about to be drawn.
      //. This is a suitable place to add calls for building display
      //. lists (for example).
      virtual void init() = 0;
      //. Called by the server as soon as the scene finished drawing.
      virtual void finish() = 0;
      
      //. Copy part of this Drawable to a new location in the same
      //. Drawable. These locations may overlap.
      virtual void blit(Fresco::PixelCoord, //.< x position of one corner of the source area
            Fresco::PixelCoord, //.< y position of one corner of the source area
            Fresco::PixelCoord, //.< width of the source area
            Fresco::PixelCoord, //.< height of the source area
            Fresco::PixelCoord, //.< x position of correspnding corner of the
                                //.< destination area
            Fresco::PixelCoord) = 0; //.< y position of correspnding corner
                                     //.< of the destination area
      //. Copy parts of the given Drawable to the specified position in this Drawable.
      virtual void blit(const Drawable &,   //.< source Drawable
            Fresco::PixelCoord, //.< x position of one corner of the source area
            Fresco::PixelCoord, //.< y position of one corner of the source area
            Fresco::PixelCoord, //.< width of the source area
            Fresco::PixelCoord, //.< height of the source area
            Fresco::PixelCoord, //.< x position of correspnding corner of the
                                //.< destination area
            Fresco::PixelCoord) = 0; //.< y position of correspnding corner
                                                 //.< of the destination area
      //. Copy parts of the given Drawable to the specified position in this Drawable
      virtual void blit(Fresco::Drawable_ptr, //.< source Drawable
            Fresco::PixelCoord, //.< x position of one corner of the source area
            Fresco::PixelCoord, //.< y position of one corner of the source area
            Fresco::PixelCoord, //.< width of the source area
            Fresco::PixelCoord, //.< height of the source area
            Fresco::PixelCoord, //.< x position of correspnding corner of the
                                //.< destination area
            Fresco::PixelCoord) = 0; //.< y position of correspnding corner
                                         //.< of the destination area
    private:
      Drawable(const Drawable &);
      Drawable &operator = (const Drawable &);
  };

  //. This class is used to render the mousepointer.
  class Console::Pointer :
    public virtual PortableServer::RefCountServantBase
  {
    public:
      virtual ~Pointer() { }
      
      //. return the raster associated with this pointer
      virtual Fresco::Raster_ptr raster() = 0;
      //. Move the pointer to the given Pixelcoordinate.
      virtual void move(Fresco::Coord, Fresco::Coord) = 0;
      //. FIXME: Missing documentation!
      virtual void draw() = 0;
      //. FIXME: Missing documentation!
      virtual void save() = 0;
      //. FIXME: Missing documentation!
      virtual void restore() = 0;
      //. FIXME: Missing documentation!
      virtual bool intersects(Fresco::Coord, Fresco::Coord,
                  Fresco::Coord, Fresco::Coord) = 0;
  };

} // namespace

#endif
