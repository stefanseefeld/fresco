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
#ifndef _GGI_Drawable_hh
#define _GGI_Drawable_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Warsaw/Input.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Console.hh>
#include <Console/GGIDrawableFactory.hh>
#include <vector>
extern "C"
{
#include <ggi/ggi-unix.h>
}

namespace GGI
{

class Console;

  class Drawable : public virtual ::Console::Drawable,
		   public virtual ::GGIDrawable
{
  friend class Console;
public:
  Drawable(const char *, Warsaw::PixelCoord = 0, Warsaw::PixelCoord = 0, Warsaw::PixelCoord = 0);
  virtual ~Drawable();
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
  virtual void blit(Warsaw::PixelCoord, Warsaw::PixelCoord,
		    Warsaw::PixelCoord, Warsaw::PixelCoord,
		    Warsaw::PixelCoord, Warsaw::PixelCoord);
  virtual void blit(const ::Console::Drawable &,
		    Warsaw::PixelCoord, Warsaw::PixelCoord,
		    Warsaw::PixelCoord, Warsaw::PixelCoord,
		    Warsaw::PixelCoord, Warsaw::PixelCoord);
  virtual void blit(const Drawable &,
		    Warsaw::PixelCoord, Warsaw::PixelCoord,
		    Warsaw::PixelCoord, Warsaw::PixelCoord,
		    Warsaw::PixelCoord, Warsaw::PixelCoord);
  virtual void blit(Warsaw::Drawable_ptr,
		    Warsaw::PixelCoord, Warsaw::PixelCoord,
		    Warsaw::PixelCoord, Warsaw::PixelCoord,
		    Warsaw::PixelCoord, Warsaw::PixelCoord);

  virtual const std::string &name() const { return _name;}
  virtual ggi_mode           mode() const { return _mode;}
  virtual ggi_visual_t       visual() const { return _visual;}
  /*
   * if you really must ask...
   */
  const ggi_directbuffer *buffer(unsigned int i) const { return ggiDBGetBuffer (_visual, i);}
  ggi_pixel               map(const Warsaw::Color &) const;
private:
  std::string   _name;
  ggi_visual_t  _visual;
  ggi_mode      _mode;
};

}

#endif
