/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Brent A. Fulgham <bfulgham@debian.org>
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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

#include <Berlin/ImplVar.hh>
#include <Berlin/RasterImpl.hh>
#include "ImageKitImpl.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::ImageKit;

ImageKitImpl::ImageKitImpl(const std::string &id,
			   const Fresco::Kit::PropertySeq &p)
    : KitImpl(id, p) { }
ImageKitImpl::~ImageKitImpl() { }

Raster_ptr ImageKitImpl::create_empty_raster()
{
  return create<Fresco::Raster>(new RasterImpl());
}

Raster_ptr ImageKitImpl::create_raster(const char *file)
{
  return create<Raster>(new RasterImpl(file));
}



extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "ImageKitImpl"};
  return create_kit<ImageKitImpl> ("IDL:fresco.org/Fresco/ImageKit:1.0", properties, 2);
}
