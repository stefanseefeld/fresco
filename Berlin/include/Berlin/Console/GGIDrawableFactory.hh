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

#ifndef _Console_GGIDrawableFactory_hh
#define _Console_GGIDrawableFactory_hh

#include <Berlin/config.hh>
#include <Berlin/Console.hh>
#include <string>
extern "C"
{
#include <ggi/ggi-unix.h>
}

class GGIDrawable : public virtual ::Console::Drawable
{
public:
  virtual const std::string &name() const = 0;
  virtual ggi_mode           mode() const = 0;
  virtual ggi_visual_t       visual() const = 0;
};

class GGIDrawableFactory : virtual public Console::Extension
{
public:
  //. Creates a new Drawable of the given size (x, y) and depth. It is accessable
  //. under the given shm-id.
  virtual GGIDrawable *create_drawable(int shmid,
				       Warsaw::PixelCoord,
				       Warsaw::PixelCoord,
				       Warsaw::PixelCoord) = 0;
};

#endif
