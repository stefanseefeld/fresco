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

#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Path.hh>
#include "Berlin/RCManager.hh"
#include "Berlin/RasterImpl.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

RasterImpl::RasterImpl(const Fresco::Raster::Info &rinfo) :
    my_rows(0),
    my_png(rinfo)
{
    my_rows = my_png.empty();
}
RasterImpl::RasterImpl(const std::string &file) :
    my_rows(0)
{
    Prague::Path path = RCManager::get_path("rasterpath");
    std::string pngfile = path.lookup_file(file);
    if (pngfile.empty())
    {
    std::cerr << "RasterImpl Warning : can't find '" << file 
          << "' in current rasterpath" << std::endl;
    throw CreationFailureException();
    }
    
    my_rows = my_png.read(pngfile);

    if (my_rows == 0) 
    {
    std::cerr << "RasterImpl Warning : can't read '" << file 
          << "' in current rasterpath" << std::endl;
    throw CreationFailureException();
    }
}
RasterImpl::~RasterImpl() { Trace trace("RasterImpl::~RasterImpl"); }
void RasterImpl::clear()
{
    delete [] my_rows;
    my_rows = 0;
    my_png.clear();
}

Fresco::Raster::Info RasterImpl::header()
{
    Fresco::Raster::Info info;
    my_png.header(info);
    return info;
}

void RasterImpl::load_data(const Fresco::Raster::Data &data)
{
    Trace trace("RasterImpl::load_data");
    clear();
    my_rows = my_png.demarshal(data);
}

void RasterImpl::store_data(Fresco::Raster::Data_out data)
{
    Trace trace("RasterImpl::store_data");
    delete data;
    data = 0;
    data = my_png.marshal(my_rows);
}

void RasterImpl::store_pixel(const Fresco::Raster::Index &index,
                 Color &color)
{
    Trace trace("RasterImpl::store_pixel");
    color = my_png.pixel(index.x, index.y, my_rows);
}

void RasterImpl::load_pixel(const Fresco::Raster::Index &index,
                const Color &color)
{
    Trace trace("RasterImpl::load_pixel");
    my_png.pixel(index.x, index.y, color, my_rows);
}

void RasterImpl::store_pixels(const Fresco::Raster::Index &lower,
                  const Fresco::Raster::Index &upper,
                  Fresco::Raster::ColorSeq_out pixels)
{
    Trace trace("RasterImpl::store_pixels");
    delete pixels;
    pixels = 0;
    pixels = my_png.pixels(lower.x, lower.y, upper.x, upper.y, my_rows);
}

void RasterImpl::load_pixels(const Fresco::Raster::Index &lower,
                 const Fresco::Raster::Index &upper,
                 const Fresco::Raster::ColorSeq &pixels)
{
    Trace trace("RasterImpl::load_pixels");
    my_png.pixels(lower.x, lower.y, upper.x, upper.y, pixels, my_rows);
}

void RasterImpl::write(const char *file)
{
    Trace trace("RasterImpl::write");
    my_png.write(file, my_rows);
}
