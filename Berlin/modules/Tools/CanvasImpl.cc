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

#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/SHM.hh>
#include <Fresco/config.hh>
#include <Fresco/Transform.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Console.hh>
#include "CanvasImpl.hh"
#include <sys/ipc.h>

using namespace Prague;
using namespace Fresco;
using namespace Berlin::Console_Extension;

using namespace Berlin::ToolKit;

SHMDrawableFactory *CanvasImpl::my_factory = 0;

CanvasImpl::CanvasImpl(PixelCoord w, PixelCoord h) :
    my_width(w), my_height(h)
{
    Trace trace("CanvasImpl::CanvasImpl");
    Console *console = Console::instance();
    if (!my_factory)
	my_factory = console->get_extension<SHMDrawableFactory>("SHMDrawableFactory");
    Fresco::Drawable::PixelFormat format =
	console->drawable()->pixel_format();
    size_t size = w * h * format.size;
    my_shm = SHM::allocate(size);
    Console::Drawable *drawable =
	my_factory->create_drawable(my_shm, w, h, 3);
    my_drawable = console->activate_drawable(drawable);
}

CanvasImpl::~CanvasImpl()
{
    Trace trace("CanvasImpl::~CanvasImpl");
    SHM::deallocate(my_shm);
}

CORBA::Long CanvasImpl::shm_id() { return my_shm; }

Fresco::Canvas::PixelFormat CanvasImpl::pixel_format()
{ return my_drawable->pixel_format(); }

Fresco::Canvas::BufferFormat CanvasImpl::buffer_format()
{ return my_drawable->buffer_format(); }

void CanvasImpl::lock()
{ my_mutex.lock(); }

void CanvasImpl::unlock()
{ my_mutex.unlock(); }

void CanvasImpl::request(Fresco::Graphic::Requisition &requisition)
{
    Trace trace("CanvasImpl::request");
    requisition.x.defined = true;
    requisition.x.natural = requisition.x.maximum =
	requisition.x.minimum = my_width * 10;
        // FIXME: my_drawable->resolution(xaxis);
    requisition.x.align = 0.;
    requisition.y.defined = true;
    requisition.y.natural = requisition.y.maximum =
	requisition.y.minimum = my_height * 10;
        // FIXME: my_drawable->resolution(yaxis);
    requisition.y.align = 0.;
    requisition.z.defined = false;
}

void CanvasImpl::draw(DrawTraversal_ptr traversal)
{
    Trace trace("CanvasImpl::draw");
    DrawingKit_var drawing = traversal->drawing();
    drawing->copy_drawable(my_drawable, 0, 0, my_width, my_height);
}
