/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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
#include <Fresco/config.hh>
#include <Fresco/Focus.hh>
#include "MainControllerImpl.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::ToolKit;

MainControllerImpl::MainControllerImpl(bool transparent) :
    ControllerImpl(transparent)
{ }
MainControllerImpl::~MainControllerImpl() { }
void MainControllerImpl::cursor(Raster_ptr r)
{
    Trace trace("MainControllerImpl::cursor");
    Prague::Guard<Mutex> guard(my_mutex);
    my_cursor = Raster::_duplicate(r);
}

Raster_ptr MainControllerImpl::cursor()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return Raster::_duplicate(my_cursor);
}

CORBA::Boolean MainControllerImpl::receive_focus(Focus_ptr focus)
{
    Trace trace(this, "MainControllerImpl::receive_focus");
    Input::Device d = focus->device();
    bool ret = ControllerImpl::receive_focus(focus);
    if (ret && d == 1 && !CORBA::is_nil(my_cursor))
	focus->set_cursor(my_cursor);
    return ret;
}

