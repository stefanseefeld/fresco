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

#include <Fresco/config.hh>
#include <Berlin/PNG.hh>
#include <Berlin/Logger.hh>
#include <Prague/Sys/Memory.hh>
#include <Prague/Sys/Tracer.hh>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <png.h>

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

class PNG::ibuf : public std::streambuf
{
  public:
    ibuf(const Raster::Data &data)
    {
    char *begin = (char *)data.get_buffer();
    char *end   = begin + data.length();
    setg(begin, begin, end);
    }
};

class PNG::obuf : public std::streambuf
{
  public:
    unsigned char *data() const
    {
    unsigned char *ret = new unsigned char[my_buf.size()];
    Prague::Memory::copy(&*my_buf.begin(), ret, my_buf.size());
    return ret;
    }
    std::streamsize length() const { return my_buf.size();}
    std::streamsize xsputn(const char *s, std::streamsize n)
    {
    my_buf.insert(my_buf.end(), s, s + n);
    return n;
    }
  private:
    std::vector<unsigned char> my_buf;
};

class PNG::Decoder 
{
    static const size_t my_magic = 8;
  public:
    Decoder(std::streambuf *, png_structp, png_infop, png_infop);
    operator bool () const { return my_valid;}
    unsigned char **decode();
  private:
    static void read(png_structp, png_bytep, png_size_t);
    static void warning(png_structp, png_const_charp);
    static void error(png_structp, png_const_charp);

    std::streambuf *my_input;
    bool my_valid;
    png_structp my_png;
    png_infop my_info;
    png_infop my_end;
};

class PNG::Encoder 
{
  public:
    Encoder(std::streambuf *, png_structp, png_infop, png_infop);
    void encode(unsigned char *const *);
  private:
    static void write(png_structp, png_bytep, png_size_t);
    static void flush(png_structp);
    static void warning(png_structp, png_const_charp);
    static void error(png_structp, png_const_charp);
    std::streambuf *my_output;
    png_structp my_png;
    png_infop my_info; 
    png_infop my_end;
};

inline PNG::Encoder::Encoder(std::streambuf *sb, png_structp p,
                 png_infop i, png_infop e) :
    my_output(sb), my_png(p), my_info(i), my_end(e)
{
    png_set_write_fn (my_png, my_output, &PNG::Encoder::write,
              &PNG::Encoder::flush);
    png_set_error_fn(my_png, my_output, &PNG::Encoder::error,
             &PNG::Encoder::warning);
    png_set_write_status_fn(my_png, 0);
}

inline void PNG::Encoder::encode(unsigned char *const *rows)
{
    Trace trace("Encoder::encode");
    png_write_info(my_png, my_info);
    png_write_image(my_png, const_cast<unsigned char **>(rows));
    png_write_end(my_png, my_end);
}

inline void PNG::Encoder::write(png_structp png_ptr, png_bytep image,
                png_size_t length) 
{
    std::streambuf *sbuf = static_cast<std::streambuf *>(png_get_io_ptr(png_ptr));
    sbuf->sputn((char*)image, (size_t)length);
}

inline void PNG::Encoder::flush(png_structp png_ptr) 
{
    std::streambuf *sbuf = static_cast<std::streambuf *>(png_get_io_ptr(png_ptr));
    sbuf->pubsync();
}

inline void PNG::Encoder::warning(png_structp, png_const_charp msg)
{
    Logger::log(Logger::corba) << "PNG::Encoder::warning : " << msg
                   << std::endl;
}

inline void PNG::Encoder::error(png_structp, png_const_charp msg)
{
    Logger::log(Logger::corba) << "PNG::Encoder::error : " << msg
                   << std::endl;
}

inline PNG::Decoder::Decoder(std::streambuf *sbuf, png_structp p,
                 png_infop i, png_infop e) : 
    my_input(sbuf), my_valid(false), my_png(p), my_info(i), my_end(e)
{
    png_byte header[my_magic];
    my_input->sgetn((char*)header, my_magic);
    my_valid = !(png_sig_cmp(header, 0, my_magic));
    if (my_valid)
    {
    png_set_sig_bytes(my_png, my_magic);
    png_set_read_fn(my_png, my_input, &PNG::Decoder::read);
    png_set_error_fn(my_png, my_input, &PNG::Decoder::error,
             &PNG::Decoder::warning);
    png_set_read_status_fn(my_png, 0);
    png_read_info(my_png, my_info);
    }
}

inline unsigned char **PNG::Decoder::decode()
{
    Trace trace("PNGDecoder::decode");
    if (!my_valid)
    {
    std::cerr << "PNG::Decoder::decode : invalid raster !"
          << std::endl;
    return 0;
    }
    png_uint_32 height = png_get_image_height(my_png, my_info);
    png_uint_32 rowbytes = png_get_rowbytes(my_png, my_info);
    unsigned char **rows = new unsigned char *[height];
    for (png_uint_32 i = 0; i < height; i++)
    rows[i] = new unsigned char[rowbytes];
    png_read_image(my_png, rows);
    png_read_end(my_png, my_end);
    return rows;
}

inline void PNG::Decoder::read(png_structp png_ptr, png_bytep image,
                   png_size_t length) 
{
    std::streambuf *input = static_cast<std::streambuf *>(png_get_io_ptr(png_ptr));
    input->sgetn((char *)image, (size_t)length);
}

inline void PNG::Decoder::warning(png_structp, png_const_charp msg)
{
    Logger::log(Logger::image) << "PNG::Decoder::warning : " << msg
                   << std::endl;
}

inline void PNG::Decoder::error(png_structp, png_const_charp msg)
{
    Logger::log(Logger::image) << "PNG::Decoder::error : " << msg
                   << std::endl;
}

PNG::PNG()
{
    my_rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    my_rinfo = png_create_info_struct(my_rpng);
    my_rend = png_create_info_struct(my_rpng);
}

PNG::PNG(const Fresco::Raster::Info &info)
{
    my_rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    my_rinfo = png_create_info_struct(my_rpng);
#if 0
    my_rinfo->width = info.width;
    my_rinfo->height = info.height;
    my_rinfo->bit_depth = info.depth;
    my_rinfo->color_type = info.colortype;
    my_rinfo->compression_type = info.compression;
    my_rinfo->filter_type = info.filter;
    my_rinfo->interlace_type = info.interlace;
    switch(my_rinfo->color_type)
    {
    case PNG_COLOR_TYPE_GRAY:
    case PNG_COLOR_TYPE_PALETTE:
    my_rinfo->channels = 1;
    break;
    case PNG_COLOR_TYPE_GA:
    my_rinfo->channels = 2;
    break;
    case PNG_COLOR_TYPE_RGB:
    my_rinfo->channels = 3;
    break;
    case PNG_COLOR_TYPE_RGBA:
    my_rinfo->channels = 4;
    break;
    default:
    std::cerr << "PNG doesn't know number of channels in this "
          << "color type." << std::endl;
    my_rinfo->channels = 1;
    }
    my_rinfo->rowbytes = info.width * info.depth * my_rinfo->channels / 8;
    my_rend = png_create_info_struct(my_rpng);
#endif
}

PNG::~PNG()
{
    clear();
    png_destroy_read_struct(&my_rpng, &my_rinfo, &my_rend);
}

unsigned char **PNG::empty()
{
  png_uint_32 h = png_get_image_height(my_rpng, my_rinfo);
  png_uint_32 w = png_get_rowbytes(my_rpng, my_rinfo);
  unsigned char **rows = new unsigned char *[h];
    for (png_uint_32 i = 0; i < h; i++)
    rows[i] = new unsigned char[w];
    return rows;
}

void PNG::clear()
{
    png_destroy_read_struct(&my_rpng, &my_rinfo, &my_rend);
    my_rpng = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    my_rinfo = png_create_info_struct(my_rpng);
    my_rend = png_create_info_struct(my_rpng);  
}

void PNG::header(Raster::Info &info)
{
    png_uint_32 w, h;
    int d, c, in, co, f;
    png_get_IHDR(my_rpng, my_rinfo, &w, &h, &d, &c, &in, &co, &f);  

    info.width = w;
    info.height = h;
    info.depth = d;
    info.colortype = c;
    info.compression = co;
    info.filter = f;
    info.interlace = in;
}

Raster::Data *PNG::marshal(unsigned char *const *rows)
{
    png_structp wpng =
    png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop winfo = png_create_info_struct(wpng);
    png_uint_32 width, height;
    int  depth, color, interlace, compression, filter;
    // transfer the IHDR chunk
    png_get_IHDR(my_rpng, my_rinfo, &width, &height, &depth, &color,
         &interlace, &compression, &filter);
    png_set_IHDR(wpng, winfo, width, height, depth, color,
         interlace, compression, filter);
    // set up buffer to hold new data
    obuf buffer;
    Encoder encoder(&buffer, wpng, winfo, my_rend);
    encoder.encode(rows);
    Raster::Data *data =
    new Raster::Data(static_cast<CORBA::ULong>(buffer.length()),
             static_cast<CORBA::ULong>(buffer.length()),
             reinterpret_cast<CORBA::Octet *>(buffer.data()),
             static_cast<CORBA::Boolean>(true));
    png_destroy_write_struct(&wpng, &winfo);
    return data;
}

unsigned char **PNG::demarshal(const Raster::Data &data)
{
    clear();
    ibuf buffer(data);
    Decoder decoder(&buffer, my_rpng, my_rinfo, my_rend);
    unsigned char **rows = decoder.decode();
    return rows;
}

Color PNG::pixel(unsigned long x, unsigned long y,
         unsigned char *const *rows)
{
    Color color;
    color.red = color.green = color.blue = 0.; color.alpha = 1.;
    png_uint_32 h = png_get_image_height(my_rpng, my_rinfo);
    png_uint_32 w = png_get_image_width(my_rpng, my_rinfo);
    if (x >= w || y >= h)
    {
    std::cerr << "PNG::pixel: illegal index !" << std::endl;
    return color;
    }
    else
    {
    unsigned char *pixel = 0;
    unsigned char *buffer = 0;
    png_byte color_type = png_get_color_type(my_rpng, my_rinfo);
    if (color_type != rgbalpha)
        pixel = buffer = new unsigned char[4];

    switch (color_type)
    {
    case palette:
        palette_to_rgbalpha(rows[y] + x, rows[y] + x+1, buffer);
        break;
    case gray:
        gray_to_rgbalpha(rows[y] + x, rows[y] + x+1, buffer);
        break;
    case grayalpha:
        grayalpha_to_rgbalpha(rows[y] + 2*x, rows[y] + 2*(x+1),
                  buffer);
        break;
    case rgb:
        rgb_to_rgbalpha(rows[y] + 3*x, rows[y] + 3*(x+1), buffer);
        break;
    default:
        pixel = rows[y] + 4*x;
    }

    color.red = static_cast<double>(*pixel) / 255;
    color.green = static_cast<double>(*(pixel + 1)) / 255;
    color.blue = static_cast<double>(*(pixel + 2)) / 255;
    color.alpha = static_cast<double>(*(pixel + 3)) / 255;
    delete [] buffer;
    }
    return color;
}

void PNG::pixel(unsigned long x, unsigned long y, const Color &color,
        unsigned char **rows)
{
    png_uint_32 h = png_get_image_height(my_rpng, my_rinfo);
    png_uint_32 w = png_get_image_width(my_rpng, my_rinfo);
    if (x >= w || y >= h)
    {
    std::cerr << "RasterImpl::loadPixel: illegal index !" << std::endl;
    return;
    }
    else
    {
    png_byte color_type = png_get_color_type(my_rpng, my_rinfo);
    if (color_type != rgbalpha)
        std::cerr << "wrong color type : "
              << static_cast<int>(color_type)
              << std::endl;
    png_byte bit_depth = png_get_bit_depth(my_rpng, my_rinfo);
    if (bit_depth != 8)
        std::cerr << "wrong depth : "
              << static_cast<int>(bit_depth)
              << std::endl;
    unsigned char *pixel = rows[y] + 4*x;
    *pixel++ = static_cast<png_byte>(color.red * 255);
    *pixel++ = static_cast<png_byte>(color.green * 255);
    *pixel++ = static_cast<png_byte>(color.blue * 255);
    *pixel = static_cast<png_byte>(color.alpha * 255);
    }
}

Raster::ColorSeq *PNG::pixels(unsigned long xlower, unsigned long ylower,
                  unsigned long xupper, unsigned long yupper,
                  unsigned char *const *rows)
{
    png_uint_32 h = png_get_image_height(my_rpng, my_rinfo);
    png_uint_32 w = png_get_image_width(my_rpng, my_rinfo);
    png_uint_32 rowbytes = png_get_rowbytes(my_rpng, my_rinfo);
    if (xupper < xlower || yupper < ylower ||
    xupper > w || yupper > h ||
    xlower > w || ylower > h)
    {
    std::cerr << "PNG::pixels: illegal indexes !\n";
    std::cerr << xlower << ' ' << ylower << ' ' << xupper << ' '
          << yupper << " not contained in " << ' '
          << w << 'x' << h
          << std::endl;
    return 0;
    }
    png_uint_32 width = xupper - xlower;
    png_uint_32 height = yupper - ylower;
    
    Raster::ColorSeq *colors = new Raster::ColorSeq;
    colors->length(width*height);
  
    const unsigned char *row = 0;
    unsigned char *buffer = 0;
    png_byte color_type = png_get_color_type(my_rpng, my_rinfo);
    if (color_type != rgbalpha)
    row = buffer = new unsigned char[w *
                     h * 4];
    for (png_uint_32 y = ylower, i = 0; y != yupper; y++, i++)
    {
    switch (color_type)
    {
    case palette:
        palette_to_rgbalpha(rows[y], rows[y] + rowbytes,
                buffer);
        break;
    case gray:
        gray_to_rgbalpha(rows[y], rows[y] + rowbytes,
                 buffer);
        break;
    case grayalpha:
        grayalpha_to_rgbalpha(rows[y], rows[y] + rowbytes,
                  buffer);
        break;
    case rgb:
        rgb_to_rgbalpha(rows[y], rows[y] + rowbytes, buffer);
        break;
    default:
        row = rows[y];
    }
    for (png_uint_32 x = xlower, j = 0; x != xupper; x++, j++)
    {
        const unsigned char *pixel = row + 4*x;
        Color &color = (*colors)[i*width + j];
        color.red = static_cast<double>(*pixel) / 255;
        color.green = static_cast<double>(*(pixel + 1)) / 255;
        color.blue = static_cast<double>(*(pixel + 2)) / 255;
        color.alpha = static_cast<double>(*(pixel + 3)) / 255;
    }
    }
    delete [] buffer;
    return colors;
}

void PNG::pixels(unsigned long xlower, unsigned long ylower,
                 unsigned long xupper, unsigned long yupper,
                 const Raster::ColorSeq &pixels, unsigned char **rows)
{
    png_uint_32 h = png_get_image_height(my_rpng, my_rinfo);
    png_uint_32 w = png_get_image_width(my_rpng, my_rinfo);
    if (xupper < xlower || yupper < ylower ||
    xupper > w || yupper > h ||
    xlower > w || ylower > h)
    {
    std::cerr << "PNG::pixels: illegal indexes !\n";
    std::cerr << xlower << ' ' << ylower << ' ' << xupper << ' '
          << yupper << " not contained in " << ' '
          << w << 'x' << h
          << std::endl;
    return;
    }

    png_byte color_type = png_get_color_type(my_rpng, my_rinfo);
    if (color_type != rgbalpha)
    {
    std::cerr << "wrong color type : "
          << static_cast<int>(color_type) << std::endl;
    return;
    }
    png_byte bit_depth = png_get_bit_depth(my_rpng, my_rinfo);
    if (bit_depth != 8)
    {
    std::cerr << "wrong depth : " 
          << static_cast<int>(bit_depth)
          << std::endl;
    return;
    }

    png_uint_32 width = xupper - xlower;
    
    for (png_uint_32 y = ylower, i = 0; y != yupper; y++, i++)
    {
    for (png_uint_32 x = xlower, j = 0; x != xupper; x++, j++)
    {
        Color color = pixels[i*width + j];
        unsigned char *pixel = rows[y] + 4*x;
        *pixel++ = static_cast<png_byte>(color.red * 255);
        *pixel++ = static_cast<png_byte>(color.green * 255);
        *pixel++ = static_cast<png_byte>(color.blue * 255);
        *pixel = static_cast<png_byte>(color.alpha * 255);
    }
    }
}

unsigned char **PNG::read(const std::string &file)
{
    unsigned char **rows = 0;
    std::ifstream ifs(file.c_str());
    if (!ifs.is_open()) 
    {
    std::cerr << "PNG : file " << file << " unreadable" << std::endl;
    }
    else
    {
    Decoder decoder(ifs.rdbuf(), my_rpng, my_rinfo, my_rend);
    rows = decoder.decode();
    }
    return rows;
}

void PNG::write(const std::string &file, unsigned char *const *rows)
{
    png_structp wpng =
    png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_infop winfo = png_create_info_struct(wpng);
    png_uint_32 width, height;
    int depth, color, interlace, compression, filter;

    // transfer the IHDR chunk
    png_get_IHDR(my_rpng, my_rinfo, &width, &height, &depth, &color,
         &interlace, &compression, &filter);
    png_set_IHDR(wpng, winfo, width, height, depth, color,
         interlace, compression, filter);

    std::ofstream ofs(file.c_str());
    Encoder encoder(ofs.rdbuf(), wpng, winfo, my_rend);
    encoder.encode(rows);
    png_destroy_write_struct(&wpng, &winfo);
}

void PNG::palette_to_rgbalpha(const unsigned char *begin,
                  const unsigned char *end, unsigned char *to)
//. expands palette png into rgba
{
    png_byte color_type = png_get_color_type(my_rpng, my_rinfo);
    if (color_type != PNG_COLOR_TYPE_PALETTE) return;
    size_t length = end - begin;
    png_byte bit_depth = png_get_bit_depth(my_rpng, my_rinfo);
    switch (bit_depth)
    {
    case 1:
    {
    const unsigned char *sp = begin + ((length - 1) >> 3);
    unsigned char *dp = to + length - 1;
    int shift = 7 - (int)((length + 7) & 7);
    for (size_t i = 0; i < length; i++)
    {
        if ((*sp >> shift) & 0x1) *dp = 1;
        else *dp = 0;
        if (shift == 7)
        {
        shift = 0;
        sp--;
        }
        else shift++;
        dp--;
    }
    break;
    }
    case 2:
    {
    const unsigned char *sp = begin + ((length - 1) >> 2);
    unsigned char *dp = to + length - 1;
    int shift = (3 - ((length + 3) & 3)) << 1;
    for (size_t i = 0; i < length; i++)
    {
        unsigned char value = (*sp >> shift) & 0x3;
        *dp = value;
        if (shift == 6)
        {
        shift = 0;
        sp--;
        }
        else shift += 2;
        dp--;
    }
    break;
    }
    case 4:
    {
    const unsigned char *sp = begin + ((length - 1) >> 1);
    unsigned char *dp = to + length - 1;
    int shift = (length & 1) << 2;
    for (size_t i = 0; i < length; i++)
    {
        char value = (*sp >> shift) & 0xf;
        *dp = value;
        if (shift == 4)
        {
        shift = 0;
        sp--;
        }
        else shift += 4;
        dp--;
    }
    break;
    }
    case 8:
    {
    Memory::copy(begin, to, length);
    break;
    }
    }
    const unsigned char *sp = to + length - 1;
    unsigned char *dp = to + (length << 2) - 1;
    png_bytep trans;
    int num_trans;
    png_get_tRNS(my_rpng, my_rinfo, &trans, &num_trans, NULL);
    png_colorp palette;
    int num_palette;
    png_get_PLTE(my_rpng, my_rinfo, &palette, &num_palette);
    for (unsigned long i = 0; i < length; i++)
    {
    if ((int)(*sp) >= num_trans) *dp-- = 0xff;
    else *dp-- = trans[*sp];
    *dp-- = palette[*sp].blue;
    *dp-- = palette[*sp].green;
    *dp-- = palette[*sp].red;
    sp--;
    }
}

void PNG::gray_to_rgbalpha(const unsigned char *begin,
               const unsigned char *end, unsigned char *to)
{
    png_byte color_type = png_get_color_type(my_rpng, my_rinfo);
    if (color_type != gray) return;
    png_byte bit_depth = png_get_bit_depth(my_rpng, my_rinfo);
    if (bit_depth == 8)
    for (; begin < end; begin++)
    {
        *(to++) = *begin;//red
        *(to++) = *begin;//green
        *(to++) = *begin;//blue
        *(to++) =  0xff; //alpha
    }
    else
      for (; begin < end; begin += 2)// 16 bit
      {
      *(to++) = *begin;
      *(to++) = *(begin + 1);
      *(to++) = *begin;
      *(to++) = *(begin + 1);
      *(to++) = *(begin++);
      *(to++) = *(begin++);
      *(to++) =  0xff;
      *(to++) =  0xff;
      }
}

void PNG::grayalpha_to_rgbalpha(const unsigned char *begin,
                const unsigned char *end,
                unsigned char *to)
//. expands gray alpha png into rgba
{
    png_byte color_type = png_get_color_type(my_rpng, my_rinfo);
    if (color_type != grayalpha) return;
    png_byte bit_depth = png_get_bit_depth(my_rpng, my_rinfo);
    if (bit_depth == 8)
    for (; begin != end; begin++)
    {
        *(to++) = *begin;  // red
        *(to++) = *begin;  // green
        *(to++) = *begin++;// blue
        *(to++) = *begin;  // alpha
    }
    else
    for (; begin < end; begin++)
    {
        *(to++) = *begin;       // red
        *(to++) = *(begin + 1); // red
        *(to++) = *begin;       // green
        *(to++) = *(begin + 1); // green
        *(to++) = *(begin++);   // blue
        *(to++) = *(begin++);   // blue
        *(to++) = *(begin++);   // alpha
        *(to++) = *begin;       // alpha
    }
}

void PNG::rgb_to_rgbalpha(const unsigned char *begin,
              const unsigned char *end, unsigned char *to)
{
    png_byte color_type = png_get_color_type(my_rpng, my_rinfo);
    if (color_type != rgb) return;
    png_byte bit_depth = png_get_bit_depth(my_rpng, my_rinfo);
    if (bit_depth == 8)
    for (; begin < end; begin++)
    {
        *(to++) = *(begin++); //red
        *(to++) = *(begin++); //green
        *(to++) = *begin; //blue
        *(to++) =  0xff; //alpha
    }
    else
    for (; begin < end; begin++)// 16 bit
    {
        *(to++) = *(begin++);
        *(to++) = *(begin++);
        *(to++) = *(begin++);
        *(to++) = *(begin++);
        *(to++) = *(begin++);
        *(to++) = *begin;
        *(to++) =  0xff;
        *(to++) =  0xff;
    }
}

