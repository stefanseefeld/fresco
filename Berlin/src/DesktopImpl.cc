/*$Id$
 *
 * This source file is a part of the Fresco Project.
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

#include <Babylon/Babylon.hh>
#include <Fresco/config.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/Transform.hh>
#include <Fresco/Region.hh>
#include "Berlin/DesktopImpl.hh"
#include "Berlin/Vertex.hh"
#include "Berlin/Logger.hh"

using namespace Prague;
using namespace Fresco;
using namespace Layout;

DesktopImpl::DesktopImpl(CORBA::ORB_ptr orb,
			 Stage_ptr stage,
                         Prague::Semaphore &shutdown_sem) :
  ControllerImpl(false),
  _stage(RefCount_var<Layout::Stage>::increment(stage)),
  _orb(CORBA::ORB::_duplicate(orb)),
  my_shutdown_semaphore(shutdown_sem)
{
  // Attention !!: this invokes _this(), which implicitely activates the desktop.
  ControllerImpl::body(_stage);
}

DesktopImpl::~DesktopImpl() { }

void DesktopImpl::body(Fresco::Graphic_ptr) { }

Fresco::Graphic_ptr DesktopImpl::body()
{
  return CORBA::is_nil(_stage) ?
    Layout::Stage::_nil() : Layout::Stage::_duplicate(_stage);
}

Fresco::Region_ptr DesktopImpl::bbox() { return _stage->bbox();}

CORBA::Long DesktopImpl::layers() { return _stage->layers();}

Layout::StageHandle_ptr DesktopImpl::layer(Layout::Stage::Index l)
{
  return _stage->layer(l);
}

void DesktopImpl::lock() { _stage->lock();}
void DesktopImpl::unlock() { _stage->unlock();}

Layout::StageHandle_ptr DesktopImpl::insert(Fresco::Graphic_ptr g,
					    const Fresco::Vertex &p,
					    const Fresco::Vertex &s,
					    Layout::Stage::Index l)
{
  return _stage->insert(g, p, s, l);
}

/*
 * little hack: stop the server when the <escape> key is hit
 */
void DesktopImpl::key_press(const Input::Event &event)
{
  Trace trace(this, "DesktopImpl::key_press");
  const Input::Toggle &toggle = event[0].attr.selection();
  if (toggle.number == Babylon::UC_ESCAPE) my_shutdown_semaphore.post();
}
