/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Brent Fulgham <bfulgham@debian.org>
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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

#ifndef _Berlin_RasterImpl_hh
#define _Berlin_RasterImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Raster.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/PNG.hh>
#include <string>

class RasterImpl : public virtual POA_Fresco::Raster,
		   public SubjectImpl
						  
{  	
public:
  RasterImpl(const Fresco::Raster::Info &);
  RasterImpl(const std::string &file);
  virtual ~RasterImpl();
  virtual Fresco::Raster::Info header();
  virtual void clear();
  virtual void load_data(const Fresco::Raster::Data &);
  virtual void store_data(Fresco::Raster::Data_out);
  virtual void load_pixel(const Fresco::Raster::Index &, const Fresco::Color &);
  virtual void store_pixel(const Fresco::Raster::Index &, Fresco::Color &);
  virtual void load_pixels(const Fresco::Raster::Index &, const Fresco::Raster::Index &, const Fresco::Raster::ColorSeq &);
  virtual void store_pixels(const Fresco::Raster::Index &, const Fresco::Raster::Index &, Fresco::Raster::ColorSeq_out);
  void write(const char *);
 private:
  PNG _png;
  unsigned char **_rows;
};

#endif
