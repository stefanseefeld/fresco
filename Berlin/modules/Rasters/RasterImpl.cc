/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Brent Fulgham <bfulgham@debian.org>
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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

#include "Berlin/Logger.hh"
#include "Image/RasterImpl.hh"
#include <fstream>

RasterImpl::RasterImpl()
  : rows(0)
{
  rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  rinfo = png_create_info_struct(rpng);
}

RasterImpl::RasterImpl(const char *file)
{
  rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  rinfo = png_create_info_struct(rpng);
  ifstream ifs(file);
  if (!ifs) cerr << "RasterImpl : file " << file << " unreadable" << endl;
  else
    {
      PNGDecoder decoder(ifs.rdbuf(), rpng, rinfo);
      rows = decoder.decode();
    }
}

RasterImpl::~RasterImpl()
{
  clear();
  png_destroy_read_struct(&rpng, &rinfo, 0);
}

void RasterImpl::load(const Raster::Data &data)
{
  clear();
  ibuf buffer(data);
  PNGDecoder decoder(&buffer, rpng, rinfo);
  rows = decoder.decode();
}

void RasterImpl::export(Raster::Data *&data)
{
  /*
   * set up buffer to hold new data
   */
  obuf buffer;
  /*
   * create temporary write structures here...
   */
  PNGEncoder encoder(&buffer, rpng, rinfo);
  encoder.encode(rows);
  delete data;
  data = new Data(static_cast<CORBA::ULong>(buffer.length()), static_cast<CORBA::ULong>(buffer.length()),
		  reinterpret_cast<CORBA::Octet *>(buffer.data()), static_cast<CORBA::Boolean>(true));
}

void RasterImpl::getData(Raster::Data &buffer)
{
  /*
   * Note:  This differs from 'export' in that it returns
   * the actual manipulated block of memory that represents
   * the image.
   *
   * In addition, because of OpenGL's sematics, we need to
   * reverse the order of the pixel bytes to get the image
   * to come out right-side-up.
   */
  // Make buffer correct size
//   png_uint_32 width = png_get_image_width(rpng, rinfo);
//   png_uint_32 height = png_get_image_height(rpng, rinfo);

//   buffer.length(width*height);
  
//   for (int i=0; i < totBytes; i++)
//     buffer[i] = *(data+((totBytes-1)-i));
}

void RasterImpl::write(const char *file)
{
  ofstream ofs(file);
  PNGEncoder encoder(ofs.rdbuf(), rpng, rinfo);
  encoder.encode(rows);
}

void RasterImpl::clear()
{
  if (!rpng || !rinfo) return;
  png_uint_32 height = png_get_image_height(rpng, rinfo);
  for (png_uint_32 i = 0; i < height; i++) delete [] rows;
  delete [] rows;
  rows = 0;
}

