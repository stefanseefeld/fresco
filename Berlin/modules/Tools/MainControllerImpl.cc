/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include <Warsaw/config.hh>
#include <Warsaw/Focus.hh>
#include "Tool/MainControllerImpl.hh"

using namespace Prague;
using namespace Warsaw;

MainControllerImpl::MainControllerImpl(bool transparent) : ControllerImpl(transparent) {}
MainControllerImpl::~MainControllerImpl() {}
void MainControllerImpl::cursor(Raster_ptr r)
{
  Trace trace("MainControllerImpl::cursor");
  Prague::Guard<Mutex> guard(_mutex);
  _cursor = Raster::_duplicate(r);
}

Raster_ptr MainControllerImpl::cursor()
{
  Prague::Guard<Mutex> guard(_mutex);
  return Raster::_duplicate(_cursor);
}

CORBA::Boolean MainControllerImpl::receive_focus(Focus_ptr focus)
{
  Trace trace(this, "MainControllerImpl::receive_focus");
  Input::Device d = focus->device();
  bool ret = ControllerImpl::receive_focus(focus);
  if (ret && d == 1 && !CORBA::is_nil(_cursor))
    focus->set_cursor(_cursor);
  return ret;
}

