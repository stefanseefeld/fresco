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
#include "Image/PNGDecoder.hh"
#include "Image/PNGEncoder.hh"
#include "Prague/Sys/Memory.hh"
#include <fstream>

class RasterImpl::ibuf : public streambuf
{
public:
  ibuf(const Raster::Data &data)
    {
      char *begin = (char *)data.NP_data(); // soon to be replaced with get_buffer()  -stefan
      char *end   = begin + data.length();
      setg (begin, begin, end);
    }
};

class RasterImpl::obuf : public streambuf
{
public:
  unsigned char *data() const
    {
      unsigned char *ret = new unsigned char[buf.size()];
      Prague::Memory::copy(buf.begin(), ret, buf.size());
      return ret;
    }
  streamsize  length() const { return buf.size();}
  streamsize  xsputn(const char *s, streamsize n)
    {
      buf.insert(buf.end(), s, s + n);
      return n;
    }
private:
  vector<unsigned char> buf;
};

RasterImpl::RasterImpl()
  : rows(0)
{
  rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  rinfo = png_create_info_struct(rpng);
  rend = png_create_info_struct(rpng);
}

RasterImpl::RasterImpl(const char *file)
  : rows(0)
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

void RasterImpl::loadData(const Raster::Data& data)
{
  SectionLog section(Logger::image, "RasterImpl::load");
  clear();
  ibuf buffer(data);
  PNGDecoder decoder(&buffer, rpng, rinfo, rend);
  rows = decoder.decode();
}

void RasterImpl::storeData(Raster::Data *&data)
{
  SectionLog section(Logger::image, "RasterImpl::export");
  /*
   * create temporary write structures here...
   */
  png_structp wpng = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  png_infop winfo = png_create_info_struct(wpng);
  png_uint_32 width, height;
  int  depth, color, interlace, compression, filter;
  /*
   * transfer the IHDR chunk
   */
  png_get_IHDR(rpng, rinfo, &width, &height, &depth, &color, &interlace, &compression, &filter);
  png_set_IHDR(wpng, winfo, width, height, depth, color, interlace, compression, filter);
  /*
   * set up buffer to hold new data
   */
    obuf buffer;
    PNGEncoder encoder(&buffer, wpng, winfo, rend);
    encoder.encode(rows);
    delete data;
    data = 0;
    data = new Data(static_cast<CORBA::ULong>(buffer.length()), static_cast<CORBA::ULong>(buffer.length()),
		    reinterpret_cast<CORBA::Octet *>(buffer.data()), static_cast<CORBA::Boolean>(true));
    png_destroy_write_struct(&wpng, &winfo);
}

void RasterImpl::storePixel(const Index &index, Color &color)
{
  png_uint_32 width = png_get_image_width(rpng, rinfo);
  png_uint_32 height = png_get_image_height(rpng, rinfo);
  if (index.x >= width || index.y >= height)
    {
      cerr << "RasterImpl::storePixel: illegal index !" << endl;
      return;
    }
  else
    {
      png_bytep pixel = rows[index.y] + 4*index.x;
      color.red = static_cast<double>(*pixel) / 256;
      color.green = static_cast<double>(*(pixel + 1)) / 256;
      color.blue = static_cast<double>(*(pixel + 2)) / 256;
      color.alpha = static_cast<double>(*(pixel + 3)) / 256;
    }
}

void RasterImpl::loadPixel(const Index &index, const Color &color)
{
  png_uint_32 width = png_get_image_width(rpng, rinfo);
  png_uint_32 height = png_get_image_height(rpng, rinfo);
  if (index.x >= width || index.y >= height)
    {
      cerr << "RasterImpl::loadPixel: illegal index !" << endl;
      return;
    }
  else
    {
      png_bytep pixel = rows[index.y] + 4*index.x;
      *pixel++ = static_cast<png_byte>(color.red * 256);
      *pixel++ = static_cast<png_byte>(color.green * 256);
      *pixel++ = static_cast<png_byte>(color.blue * 256);
      *pixel = static_cast<png_byte>(color.alpha * 256);
    }
}

void RasterImpl::loadPixels(const Index &lower, const Index &upper, const Raster::ColorSeq &pixels)
{
  cerr << "sorry, RasterImpl::loadPixels not yet implemented" << endl;
//   clear();
//   Raster::Info info;
//   info.width = width;
//   info.height = height;
//   info.depth = 8;
//   info.colortype = PNG_COLOR_TYPE_RGB_ALPHA;
//   info.compression = PNG_COMPRESSION_TYPE_BASE;
//   info.filter = PNG_FILTER_TYPE_BASE;
//   info.interlace = PNG_INTERLACE_NONE;
//   png_set_IHDR(rpng, rinfo, info.width, info.height, info.depth, info.colortype, info.interlace, info.compression, info.filter);
//   rows = new png_bytep[height];
//   png_uint_32 rowbytes = (info.width * 32 + 7) >> 3;
//   for (png_uint_32 i = 0; i != info.height; i++)
//     {
//       rows[i] = new png_byte[rowbytes];
//       Prague::Memory::copy(data.NP_data() + i * rowbytes, rows[i], rowbytes);
//     }
}

void RasterImpl::storePixels(const Index &lower, const Index &upper, Raster::ColorSeq *&pixels)
{
  /*
   * test index ranges
   */
  png_uint_32 width = png_get_image_width(rpng, rinfo);
  png_uint_32 height = png_get_image_height(rpng, rinfo);
  if (upper.x < lower.x || upper.y < lower.y ||
      upper.x > width || upper.y > height ||
      lower.x > width || lower.y > height)
    {
      cerr << "RasterImpl::storePixels: illegal indexes !" << endl;
      cerr << lower.x << ' ' << lower.y << ' ' << upper.x << ' ' << upper.y << ' ' << width << ' ' << height << endl;
      return;
    }
  
  width = upper.x - lower.x;
  height = upper.y - lower.y;
  
  pixels = new ColorSeq;
  pixels->length(width*height);
  
  /*
   * FIXME !!!: the following code makes strong assumptions about the
   * internal format of the raster (4 channels, 1 byte each).
   * Generalize this to make sure it works for every possible format
   * (using the information from rpng and rinfo)
   *             -stefan
   */
  for (png_uint_32 y = lower.y, i = 0; y != upper.y; y++, i++)
    for (png_uint_32 x = lower.x, j = 0; x != upper.x; x++, j++)
      {
	png_bytep pixel = rows[y] + 4*x;
	Color &color = (*pixels)[i*width + j];
	color.red = static_cast<double>(*pixel) / 256;
	color.green = static_cast<double>(*(pixel + 1)) / 256;
	color.blue = static_cast<double>(*(pixel + 2)) / 256;
	color.alpha = static_cast<double>(*(pixel + 3)) / 256;
      }
}

void RasterImpl::write(const char *file)
{
  SectionLog section(Logger::image, "RasterImpl::write");
  /*
   * create temporary write structures here...
   */
  png_structp wpng = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
  png_infop winfo = png_create_info_struct(wpng);
  png_uint_32 width, height;
  int depth, color, interlace, compression, filter;

  /*
   * transfer the IHDR chunk
   */
  png_get_IHDR(rpng, rinfo, &width, &height, &depth, &color, &interlace, &compression, &filter);
  png_set_IHDR(wpng, winfo, width, height, depth, color, interlace, compression, filter);

  ofstream ofs(file);
  PNGEncoder encoder(ofs.rdbuf(), wpng, winfo, rend);
  encoder.encode(rows);
  png_destroy_write_struct(&wpng, &winfo);
}
