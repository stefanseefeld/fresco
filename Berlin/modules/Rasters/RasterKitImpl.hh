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

#ifndef _RasterKit_RasterKitImpl_hh
#define _RasterKit_RasterKitImpl_hh

#include <Fresco/config.hh>
#include <Fresco/RasterKit.hh>
#include <Fresco/Raster.hh>
#include <Berlin/KitImpl.hh>

class RasterImpl;

namespace Berlin 
{
  namespace RasterKit 
  {

    class RasterKitImpl : public virtual POA_Fresco::RasterKit,
              public KitImpl
    {
      public:
    RasterKitImpl(const std::string &,
              const Fresco::Kit::PropertySeq &,
              ServerContextImpl *);
    virtual ~RasterKitImpl();
    virtual Berlin::KitImpl *clone(const Fresco::Kit::PropertySeq &p,
                       ServerContextImpl *c)
    { return new RasterKitImpl(repo_id(), p, c); }

    Fresco::Raster_ptr
    create_empty_raster(const Fresco::Raster::Info &);
    Fresco::Raster_ptr create_raster(const char *file);
    };

  } // namespace
} // namespace

#endif
