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
#ifndef _GGI_Console_hh
#define _GGI_Console_hh

#include <Prague/Sys/Plugin.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Console.hh>
#include <Console/Renderer.hh>
#include <Console/DirectBuffer.hh>
#include <Console/GLContext.hh>
#include <vector>
extern "C"
{
#include <ggi/ggi-unix.h>
}

class GGIConsole;

class GGIDrawable : public Console::Drawable
{
  friend class GGIConsole;
public:
  GGIDrawable(const char *, Warsaw::PixelCoord = 0, Warsaw::PixelCoord = 0, Warsaw::PixelCoord = 0);
  virtual ~GGIDrawable();
  virtual Warsaw::Drawable::PixelFormat pixel_format();
  virtual Warsaw::Drawable::BufferFormat buffer_format();
  virtual Warsaw::PixelCoord width() const;
  virtual Warsaw::PixelCoord height() const;
  virtual Warsaw::PixelCoord vwidth() const;
  virtual Warsaw::PixelCoord vheight() const;
  virtual Warsaw::Coord resolution(Warsaw::Axis a) const;
  virtual Warsaw::Coord dpi(Warsaw::Axis a) const;
  virtual Warsaw::PixelCoord row_length() const;

  virtual void flush();
  virtual void flush(Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord);
  virtual void init();
  virtual void finish();

  /*
   * fast blit
   */
  void blit(Warsaw::PixelCoord, Warsaw::PixelCoord,
	    Warsaw::PixelCoord, Warsaw::PixelCoord,
	    Warsaw::PixelCoord, Warsaw::PixelCoord);
  void blit(const Drawable &,
	    Warsaw::PixelCoord, Warsaw::PixelCoord,
	    Warsaw::PixelCoord, Warsaw::PixelCoord,
	    Warsaw::PixelCoord, Warsaw::PixelCoord);
  void blit(const GGIDrawable &,
	    Warsaw::PixelCoord, Warsaw::PixelCoord,
	    Warsaw::PixelCoord, Warsaw::PixelCoord,
	    Warsaw::PixelCoord, Warsaw::PixelCoord);
  void blit(Warsaw::Drawable_ptr,
	    Warsaw::PixelCoord, Warsaw::PixelCoord,
	    Warsaw::PixelCoord, Warsaw::PixelCoord,
	    Warsaw::PixelCoord, Warsaw::PixelCoord);

  /*
   * if you really must ask...
   */
  ggi_visual_t visual() const { return _visual;}
  ggi_mode     mode() const { return _mode;}
  const ggi_directbuffer *buffer(unsigned int i) const { return ggiDBGetBuffer (_visual, i);}
  ggi_pixel     map(const Warsaw::Color &) const;
private:
  ggi_visual_t  _visual;
  ggi_mode      _mode;
};

class GGIExtension : virtual public Console::Extension
{
public:
  GGIExtension(GGIDrawable *drawable) : _drawable(drawable) {}
  GGIDrawable *drawable() { return _drawable;}
private:
  GGIDrawable *_drawable;
};

class GGIRenderer : public GGIExtension,
		    virtual public Renderer
{
public:
  GGIRenderer(GGIDrawable *drawable) : GGIExtension(drawable) {}
  virtual void set_color(const Warsaw::Color &c)
  {
    ggiSetGCForeground(drawable()->visual(), drawable()->map(c));
  }
  virtual void draw_pixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y)
  {
    ggiDrawPixel(drawable()->visual(), x, y);
  }
  virtual void draw_hline(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w)
  {
    ggiDrawHLine(drawable()->visual(), x, y, w);
  }
  virtual void draw_vline(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord h)
  {
    ggiDrawVLine(drawable()->visual(), x, y, h);
  }
  virtual void draw_line(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h)
  {
    ggiDrawLine(drawable()->visual(), x, y, x + w, y + h);
  }
  virtual void draw_box(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h)
  {
    ggiDrawBox(drawable()->visual(), x, y, w, h);
  }
};

class GGIDirectBuffer : public GGIExtension,
			virtual public DirectBuffer
{
public:
  GGIDirectBuffer(GGIDrawable *drawable) : GGIExtension(drawable) {}
  virtual Guard read_buffer()
  {
    Guard guard(drawable(), static_cast<Console::Drawable::data_type *>(ggiDBGetBuffer(drawable()->visual(), 0)->read));
    return guard;
  }
  virtual Guard write_buffer()
  {
    Guard guard(drawable(), static_cast<Console::Drawable::data_type *>(ggiDBGetBuffer(drawable()->visual(), 0)->write));
    return guard;
  }
};

class GGIPointer : public Console::Pointer
{
  typedef Console::Drawable::data_type data_type;
  typedef ggi_pixel Pixel;
public:
  GGIPointer(GGIDrawable *, Warsaw::Raster_ptr);
  virtual ~GGIPointer();
  virtual Warsaw::Raster_ptr raster();
  virtual void move(Warsaw::Coord, Warsaw::Coord);
  virtual void draw();
  virtual void save();
  virtual void restore();
  virtual bool intersects(Warsaw::Coord, Warsaw::Coord, Warsaw::Coord, Warsaw::Coord);
private:
  GGIDrawable        *_screen;
  DirectBuffer       *_dbuffer;
  Warsaw::PixelCoord  _origin[2];
  Warsaw::PixelCoord  _position[2];
  Warsaw::PixelCoord  _size[2];
  Warsaw::Coord       _scale[2];
  Warsaw::Raster_ptr  _raster;
  data_type          *_image;
  data_type          *_mask;
  data_type          *_cache;
};

class GGIConsole : public Console
{
  typedef std::vector<GGIDrawable *> dlist_t;
  typedef std::vector<Prague::Plugin<Extension::Loader> *> elist_t;
public:
  GGIConsole(int &, char **);
  virtual ~GGIConsole();
  static GGIConsole *instance() { return static_cast<GGIConsole *>(Console::instance());}
  virtual GGIPointer *pointer(Warsaw::Raster_ptr);
  virtual GGIDrawable *drawable();
  virtual GGIDrawable *create_drawable(Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord);
  virtual GGIDrawable *create_shm_drawable(int, Warsaw::PixelCoord, Warsaw::PixelCoord, Warsaw::PixelCoord);
  GGIDrawable *reference_to_servant(Warsaw::Drawable_ptr);

  virtual void device_info(std::ostream &);
  virtual Warsaw::Input::Event *next_event();
  virtual void wakeup();
  virtual void activate_autoplay() { _autoplay = true;}

  void add_drawable(GGIDrawable *);
private:
  virtual Console::Extension *create_extension(const std::string &, Drawable *);
  Warsaw::Input::Event *synthesize(const ggi_event &);
  /*
   * to be used for event notification
   */
  ggi_visual_t  _visual;
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

inline Warsaw::PixelCoord GGIDrawable::width() const { return _mode.visible.x;}
inline Warsaw::PixelCoord GGIDrawable::height() const { return _mode.visible.y;}
inline Warsaw::PixelCoord GGIDrawable::vwidth() const { return _mode.virt.x;}
inline Warsaw::PixelCoord GGIDrawable::vheight() const { return _mode.virt.y;}
inline Warsaw::Coord GGIDrawable::resolution(Warsaw::Axis a) const
{
  /*
   * mode.size is in mm
   * our base unit is 0.1 mm...
   */
  return a == Warsaw::xaxis ?
    0.1 * _mode.visible.x / _mode.size.x :
    0.1 * _mode.visible.y / _mode.size.y;
}
inline Warsaw::Coord GGIDrawable::dpi(Warsaw::Axis a) const { return resolution(a) * 254.0;}
inline Warsaw::PixelCoord GGIDrawable::row_length() const
{ return ggiDBGetBuffer(_visual, 0)->buffer.plb.stride;}

inline void GGIDrawable::flush() { ggiFlush(_visual);}
inline void GGIDrawable::flush(Warsaw::PixelCoord x, Warsaw::PixelCoord y,
			       Warsaw::PixelCoord w, Warsaw::PixelCoord h)
{ ggiFlushRegion(_visual, x, y, w, h);}

inline void GGIDrawable::init() {}
inline void GGIDrawable::finish() {}

inline ggi_pixel GGIDrawable::map(const Warsaw::Color &c) const
{
  ggi_color c2;
  // GGI _appears_ to use 16 bit color + alpha throughout. *sigh*
  static double scale = 0xffff;
  c2.r = static_cast<uint16>(c.red * scale);
  c2.g = static_cast<uint16>(c.green * scale);
  c2.b = static_cast<uint16>(c.blue * scale);
  c2.a = static_cast<uint16>(c.alpha * scale);
  return ggiMapColor(_visual, &c2);
}

inline void GGIDrawable::blit(Warsaw::PixelCoord x1, Warsaw::PixelCoord y1,
			      Warsaw::PixelCoord w, Warsaw::PixelCoord h,
			      Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
{
  ggiCopyBox(_visual, x1, y1, w, h, x2, y2);
}
inline void GGIDrawable::blit(const GGIDrawable &d,
			      Warsaw::PixelCoord x1, Warsaw::PixelCoord y1,
			      Warsaw::PixelCoord w, Warsaw::PixelCoord h,
			      Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
{
  ggiCrossBlit(d._visual, x1, y1, w, h, _visual, x2, y2);
}
inline void GGIDrawable::blit(const Drawable &d,
			      Warsaw::PixelCoord x1, Warsaw::PixelCoord y1,
			      Warsaw::PixelCoord w, Warsaw::PixelCoord h,
			      Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
{
  const GGIDrawable &drawable = static_cast<const GGIDrawable &>(d);
  ggiCrossBlit(drawable._visual, x1, y1, w, h, _visual, x2, y2);
}
inline void GGIDrawable::blit(Warsaw::Drawable_ptr d,
			      Warsaw::PixelCoord x1, Warsaw::PixelCoord y1,
			      Warsaw::PixelCoord w, Warsaw::PixelCoord h,
			      Warsaw::PixelCoord x2, Warsaw::PixelCoord y2)
{
  GGIDrawable *servant = GGIConsole::instance()->reference_to_servant(d);
  if (servant) blit(*servant, x1, y1, w, h, x2, y2);
  else Logger::log(Logger::drawing) << "GGIDrawable::blit: unable to obtain servant from reference" << endl;
}

#endif
