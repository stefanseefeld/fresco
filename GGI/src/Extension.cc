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
#include <Console/GGI/Extension.hh>
#include <Console/GGI/Drawable.hh>
#include <strstream.h>
extern "C"
{
#include <ggi/ggi-unix.h>
}

void GGI::DExtension::attach(::Console::Drawable *drawable)
{
  _drawable = dynamic_cast<Drawable *>(drawable);
}

void GGI::Renderer::set_color(const Warsaw::Color &c)
{
  ggiSetGCForeground(drawable()->visual(), drawable()->map(c));
}

void GGI::Renderer::draw_pixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y)
{
  ggiDrawPixel(drawable()->visual(), x, y);
}

void GGI::Renderer::draw_hline(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w)
{
  ggiDrawHLine(drawable()->visual(), x, y, w);
}

void GGI::Renderer::draw_vline(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord h)
{
  ggiDrawVLine(drawable()->visual(), x, y, h);
}

void GGI::Renderer::draw_line(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h)
{
  ggiDrawLine(drawable()->visual(), x, y, x + w, y + h);
}

void GGI::Renderer::draw_box(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h)
{
  ggiDrawBox(drawable()->visual(), x, y, w, h);
}

DirectBuffer::Guard GGI::DirectBuffer::read_buffer()
{
  Guard guard(drawable(), static_cast< ::Console::Drawable::data_type *>(ggiDBGetBuffer(drawable()->visual(), 0)->read));
  return guard;
}

DirectBuffer::Guard GGI::DirectBuffer::write_buffer()
{
  Guard guard(drawable(), static_cast< ::Console::Drawable::data_type *>(ggiDBGetBuffer(drawable()->visual(), 0)->write));
  return guard;
}

::Console::Drawable *SHMDrawableFactory::create_drawable(int shmid,
							 Warsaw::PixelCoord w,
							 Warsaw::PixelCoord h,
							 Warsaw::PixelCoord d)
{
  std::ostrstream oss;
  oss << "display-memory:shmid:" << shmid << std::ends;
  const char *name = oss.str();
  GGI::Drawable *drawable;
  try { drawable = new GGI::Drawable(name, w, h, d);}
  catch (...)
    {
      Logger::log(Logger::console) << "Error : can't open shm GGI::Drawable" << std::endl;
      throw;
    }
  Logger::log(Logger::console) << "open ggi display with name :'" << name << '\'' << std::endl;
  delete [] name;
  
  static_cast<GGI::Console *>(Console::instance())->add_drawable(drawable);
  return drawable;
}

::GGIDrawable *GGIDrawableFactory::create_drawable(int shmid,
						   Warsaw::PixelCoord w,
						   Warsaw::PixelCoord h,
						   Warsaw::PixelCoord d)
{
  std::ostrstream oss;
  oss << "display-memory:-input:shmid:" << shmid << std::ends;
  const char *name = oss.str();
  GGI::Drawable *drawable;
  try { drawable = new GGI::Drawable(name, w, h, d);}
  catch (...)
    {
      Logger::log(Logger::console) << "Error : can't open shm GGI::Drawable" << std::endl;
      throw;
    }
  Logger::log(Logger::console) << "open ggi display with name :'" << name << '\'' << std::endl;
  delete [] name;
  
  static_cast<GGI::Console *>(Console::instance())->add_drawable(drawable);
  return drawable;
}
