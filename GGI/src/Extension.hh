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
#ifndef _GGI_Extension_hh
#define _GGI_Extension_hh

#include <Warsaw/config.hh>
#include <Warsaw/Types.hh>
#include <Berlin/Logger.hh>
#include <Console/Renderer.hh>
#include <Console/DirectBuffer.hh>
#include <Console/SHMDrawableFactory.hh>
#include <Console/GGIDrawableFactory.hh>
#include <Console/GGI/Console.hh>

namespace GGI
{

class Drawable;

class DExtension : virtual public ::Console::Drawable::Extension
{
public:
  DExtension() : _drawable(0) {}
  virtual void attach(::Console::Drawable *drawable);
  Drawable *drawable() { return _drawable;}
private:
  Drawable *_drawable;
};

class Renderer : public DExtension,
		 virtual public ::Renderer
{
public:
  Renderer() {}
  virtual void set_color(const Warsaw::Color &);
  virtual void draw_pixel(Warsaw::PixelCoord x, Warsaw::PixelCoord y);
  virtual void draw_hline(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w);
  virtual void draw_vline(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord h);
  virtual void draw_line(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h);
  virtual void draw_box(Warsaw::PixelCoord x, Warsaw::PixelCoord y, Warsaw::PixelCoord w, Warsaw::PixelCoord h);
};

class DirectBuffer : public DExtension,
		     virtual public ::DirectBuffer
{
public:
  DirectBuffer() {}
  virtual Guard read_buffer();
  virtual Guard write_buffer();
};

class SHMDrawableFactory : virtual public ::SHMDrawableFactory
{
public:
  virtual Console::Drawable *create_drawable(int shmid,
					     Warsaw::PixelCoord,
					     Warsaw::PixelCoord,
					     Warsaw::PixelCoord);
};

class GGIDrawableFactory : virtual public ::GGIDrawableFactory
{
public:
  virtual ::GGIDrawable *create_drawable(int shmid,
					 Warsaw::PixelCoord,
					 Warsaw::PixelCoord,
					 Warsaw::PixelCoord);
};

}

#endif
