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

#ifndef _ImageImpl_hh
#define _ImageImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Image.hh>
#include <Fresco/Raster.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/ViewImpl.hh>
#include <Berlin/MonoGraphic.hh>
#include <Berlin/RefCountVar.hh>

namespace Berlin
{
  namespace FigureKit
  {
    class ImageImpl : public virtual POA_Fresco::Image,
                      public virtual ViewImpl,
                      public GraphicImpl
    {
      public:
        ImageImpl(Fresco::Raster_ptr);
        ~ImageImpl();

        virtual Fresco::Raster_ptr data()
        { return Fresco::Raster::_duplicate(raster); }
        virtual void data(Fresco::Raster_ptr r) { raster = r; }

        virtual void request(Fresco::Graphic::Requisition &);
        virtual void draw(Fresco::DrawTraversal_ptr);
        virtual void update(const CORBA::Any &);
      protected:
        virtual void activate_composite();
      private:
        RefCount_var<Fresco::Raster> raster;
        Fresco::Coord width, height;
    };

    class Texture : public MonoGraphic
    {
      public:
        Texture(Fresco::Raster_ptr);
        ~Texture();
        virtual void traverse(Fresco::Traversal_ptr);
        virtual void draw(Fresco::DrawTraversal_ptr);
        virtual void pick(Fresco::PickTraversal_ptr);
      private:
        RefCount_var<Fresco::Raster> raster;
    };

  } // namespace
} // namespace

#endif
