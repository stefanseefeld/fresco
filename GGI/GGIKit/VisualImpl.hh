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
#ifndef _VisualImpl_hh
#define _VisualImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/GGIKit.hh>
#include <Berlin/ControllerImpl.hh>
#include <Berlin/Console/GGIDrawableFactory.hh>
extern "C"
{
#include <ggi/ggi-unix.h>
}

namespace GGIKit
{

  class VisualImpl : public virtual POA_GGI::Visual,
                     public ControllerImpl
  {
    public:
      VisualImpl(Fresco::PixelCoord, Fresco::PixelCoord);
      virtual ~VisualImpl();
      virtual char *name();
      virtual char *mode();
      virtual void request(Fresco::Graphic::Requisition &);
      virtual void draw(Fresco::DrawTraversal_ptr);
      virtual void extension(const Fresco::Allocation::Info &info, Fresco::Region_ptr region);
      virtual CORBA::Boolean handle_positional(Fresco::PickTraversal_ptr,
                                               const Fresco::Input::Event &);
      virtual CORBA::Boolean handle_non_positional(const Fresco::Input::Event &);
      // this overrides ControllerImpl:
      virtual void move(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    private:
      virtual void handle_pointer_button(const Fresco::Input::Event &);
      void forward_event(const ggi_event &);
      static GGIDrawableFactory *_factory;
      Fresco::PixelCoord         _width;
      Fresco::PixelCoord         _height;
      Fresco::Drawable_var       _drawable;
      int                        _shm;
      GGIDrawable               *_ggi;
      std::string                _mode;
  };

} // namespace

#endif
