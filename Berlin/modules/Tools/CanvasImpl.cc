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

#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/SHM.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/DrawTraversal.hh>
#include <Warsaw/DrawingKit.hh>
#include <Berlin/Logger.hh>
#include <Berlin/Console.hh>
#include "Tool/CanvasImpl.hh"
#include <sys/ipc.h>

using namespace Prague;
using namespace Warsaw;

SHMDrawableFactory *CanvasImpl::_factory = 0;

CanvasImpl::CanvasImpl(PixelCoord w, PixelCoord h)
  : _width(w), _height(h)
{
  Trace trace("CanvasImpl::CanvasImpl");
  Console *console = Console::instance();
  cout << "I'm still here" << endl;
  if (!_factory) _factory = console->get_extension<SHMDrawableFactory>("SHMDrawableFactory");
  cout << "I'm still here" << endl;
  Warsaw::Drawable::PixelFormat format = console->drawable()->pixel_format();
  size_t size = w * h * format.size;
  _shm = SHM::allocate(size);
  Console::Drawable *drawable = _factory->create_drawable(_shm, w, h, 3);
  _drawable = console->activate_drawable(drawable);
}

CanvasImpl::~CanvasImpl()
{
  Trace trace("CanvasImpl::~CanvasImpl");
  SHM::deallocate(_shm);
}

CORBA::Long CanvasImpl::shm_id()
{
  return _shm;
}

Warsaw::Canvas::PixelFormat CanvasImpl::pixel_format()
{
  return _drawable->pixel_format();
}

Warsaw::Canvas::BufferFormat CanvasImpl::buffer_format()
{
  return _drawable->buffer_format();
}

void CanvasImpl::lock()
{
  _mutex.lock();
}

void CanvasImpl::unlock()
{
  _mutex.unlock();
}

void CanvasImpl::request(Warsaw::Graphic::Requisition &requisition)
{
  Trace trace("CanvasImpl::request");
  requisition.x.defined = true;
  requisition.x.natural = requisition.x.maximum = requisition.x.minimum = _width * 10;// / _drawable->resolution(xaxis);
  requisition.x.align = 0.;
  requisition.y.defined = true;
  requisition.y.natural = requisition.y.maximum = requisition.y.minimum = _height * 10;// / _drawable->resolution(yaxis);
  requisition.y.align = 0.;
  requisition.z.defined = false;
}

void CanvasImpl::draw(DrawTraversal_ptr traversal)
{
  Trace trace("CanvasImpl::draw");
  DrawingKit_var drawing = traversal->drawing();
  drawing->copy_drawable(_drawable, 0, 0, _width, _height);
}
