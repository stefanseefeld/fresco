/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Brent A. Fulgham <bfulgham@debian.org>
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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

#include "Warsaw/config.hh"
#include "Image/ImageKitImpl.hh"
#include "Image/RasterImpl.hh"
#include "Berlin/Plugin.hh"

ImageKitImpl::ImageKitImpl() {}
ImageKitImpl::~ImageKitImpl() {}

Raster_ptr ImageKitImpl::empty()
{
	Raster* r = new RasterImpl();
	r->_obj_is_ready(applyscope(skeletonize(ImageKit), _boa()));
	rasters.push_back(r);
	return r->_this();
}

Raster_ptr ImageKitImpl::create(const char* file)
{
	Raster* r = new RasterImpl(file);
	r->_obj_is_ready(applyscope(skeletonize(ImageKit), _boa()));
	rasters.push_back(r);
	return r->_this();
}

EXPORT_PLUGIN(ImageKitImpl, interface(ImageKit))
