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

#ifndef _ImageKitImpl_hh
#define _ImageKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/ImageKit.hh>
#include <Fresco/Raster.hh>
#include <Berlin/KitImpl.hh>
#include <vector>

class RasterImpl;

namespace Berlin {
namespace ImageKit {

class ImageKitImpl : public virtual POA_Fresco::ImageKit,
		     public KitImpl
{
public:
  ImageKitImpl(const std::string &, const Fresco::Kit::PropertySeq &);
  virtual ~ImageKitImpl();
  virtual KitImpl *clone(const Fresco::Kit::PropertySeq &p) { return new ImageKitImpl(repo_id(), p);}

  Fresco::Raster_ptr empty();
  Fresco::Raster_ptr create(const char *file);
protected:
};

} // namespace
} // namespace

#endif
