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
#ifndef _ToolKit_CanvasImpl_hh
#define _ToolKit_CanvasImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/Canvas.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/Console.hh>
#include <Berlin/Console/SHMDrawableFactory.hh>

namespace Berlin 
{
  namespace ToolKit
  {

    class CanvasImpl : public virtual POA_Fresco::Canvas,
		       public GraphicImpl
    {
      public:
	CanvasImpl(Fresco::PixelCoord, Fresco::PixelCoord);
	virtual ~CanvasImpl();
	virtual CORBA::Long shm_id();
	virtual Fresco::Canvas::PixelFormat pixel_format();
	virtual Fresco::Canvas::BufferFormat buffer_format();
	virtual void lock();
	virtual void unlock();
	
	virtual void request(Fresco::Graphic::Requisition &);
	virtual void draw(Fresco::DrawTraversal_ptr);
      private:
	static Console_Extension::SHMDrawableFactory *my_factory;
	Fresco::PixelCoord my_width;
	Fresco::PixelCoord my_height;
	Fresco::Drawable_var my_drawable;
	Prague::Mutex my_mutex;
	CORBA::Long my_shm;
    };

  } // namespace
} // namespace

#endif
