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
#include "Berlin/Logger.hh"
#include <fstream>

RasterImpl::RasterImpl()
  : rows(0)
{
  rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  rinfo = png_create_info_struct(rpng);
  rend = png_create_info_struct(rpng);
}

RasterImpl::RasterImpl(const char *file)
{
  rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  rinfo = png_create_info_struct(rpng);
  rend = png_create_info_struct(rpng);
  ifstream ifs(file);
  if (!ifs) cerr << "RasterImpl : file " << file << " unreadable" << endl;
  else
    {
      PNGDecoder decoder(ifs.rdbuf(), rpng, rinfo, rend);
      rows = decoder.decode();
    }
}

RasterImpl::~RasterImpl()
{
  clear();
  png_destroy_read_struct(&rpng, &rinfo, &rend);
}

Raster::Info RasterImpl::header()
{
  png_uint_32 w, h;
  int d, c, i, z, f;
  png_get_IHDR(rpng, rinfo, &w, &h, &d, &c, &i, &z, &f);
  Info info;
  info.width = w;
  info.height = h;
  info.depth = d;
  info.colortype = c;
  info.compression = z;
  info.filter = f;
  info.interlace = i;
  return info;
}

void RasterImpl::load(const Raster::Data& data)
{
	clear();
	ibuf buffer(data);
	PNGDecoder decoder(&buffer, rpng, rinfo, rend);
	Logger::log(Logger::corba) << "About to Decode..." << endl;
	rows = decoder.decode();
    Logger::log(Logger::corba) << "Done decoding..." << endl;
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
  png_structp wpng = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  png_infop winfo = png_create_info_struct(wpng);

  // Get the data on the image
  Raster::Info info = header();
  png_set_IHDR(wpng, winfo, info.width, info.height, info.depth,
			   info.colortype, info.interlace,
			   info.compression, info.filter);

  png_infop wend = png_create_info_struct(wpng);
  // Set the "end" data  -- these are comments and similar
  // text for the file.
  //*wend = *rend;
    
  PNGEncoder encoder(&buffer, wpng, winfo, wend);
  encoder.encode(rows);
  if (data != NULL)
  {
	  delete data;
	  data = NULL;
  }
  
  data = new Data(static_cast<CORBA::ULong>(buffer.length()), static_cast<CORBA::ULong>(buffer.length()),
		  reinterpret_cast<CORBA::Octet *>(buffer.data()), static_cast<CORBA::Boolean>(true));

  png_destroy_write_struct(&wpng, &winfo);
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
  png_structp wpng = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  png_infop winfo = png_create_info_struct(rpng);
  png_infop wend = png_create_info_struct(rpng);
  ofstream ofs(file);
  PNGEncoder encoder(ofs.rdbuf(), wpng, winfo, wend);
  encoder.encode(rows);
  png_destroy_write_struct(&wpng, &winfo);
}

void RasterImpl::clear()
{
  if (!rpng || !rinfo) return;
  png_uint_32 height = png_get_image_height(rpng, rinfo);
  for (png_uint_32 i = 0; i < height; i++) delete [] rows;
  delete [] rows;
  rows = 0;

  png_destroy_read_struct(&rpng, &rinfo, &rend);
  rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  rinfo = png_create_info_struct(rpng);
  rend = png_create_info_struct(rpng);  
}

