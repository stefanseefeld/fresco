/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Berlin/Vertex.hh"
#include "Berlin/Logger.hh"
#include "Tool/Dragger.hh"

Dragger::Dragger(Command_ptr c)
  : ControllerImpl(false), command(Command::_duplicate(c))
{
}

Dragger::~Dragger()
{
}

void Dragger::press(PickTraversal_ptr traversal, const Input::Event &event)
{
  ControllerImpl::press(traversal, event);
  offset = event[1].attr.location();
}

void Dragger::drag(PickTraversal_ptr traversal, const Input::Event &event)
{
  Vertex delta = event[0].attr.location() - offset;
  CORBA::Any any;
  any <<= delta;
  command->execute(any);
  offset += delta;
}

void Dragger::release(PickTraversal_ptr traversal, const Input::Event &event)
{
  ControllerImpl::release(traversal, event);
}
