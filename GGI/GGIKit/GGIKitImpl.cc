/*$Id$
 *
 * This source file is a part of the Fresco Project.
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
#include "GGIKitImpl.hh"
#include "VisualImpl.hh"

using namespace Fresco;

GGIKitImpl::GGIKitImpl(const std::string &id,
		       const Fresco::Kit::PropertySeq &p,
		       ServerContextImpl *c)
  : KitImpl(id, p, c) {}
GGIKitImpl::~GGIKitImpl() {}

GGI::Visual_ptr GGIKitImpl::create_visual(Fresco::PixelCoord w, Fresco::PixelCoord h)
{
    return create<GGI::Visual>(new VisualImpl(w, h));
}



extern "C" KitImpl *load()
{
  static std::string properties[] = {"implementation", "GGIKitImpl"};
  return create_prototype<GGIKitImpl>("IDL:GGI/GGIKit:1.0", properties, 2);
} 
