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
#include "Unidraw/ManipulatorImpl.hh"

using namespace Prague;
using namespace Warsaw;
using namespace Unidraw;

ManipulatorImpl::ManipulatorImpl() {}
ManipulatorImpl::~ManipulatorImpl() {}
CORBA::Boolean ManipulatorImpl::grasp(PickTraversal_ptr, const Input::Event &) { return false;}
CORBA::Boolean ManipulatorImpl::manipulate(PickTraversal_ptr, const Input::Event &) { return false;}
Unidraw::Command_ptr ManipulatorImpl::effect(PickTraversal_ptr, const Input::Event &) { return Unidraw::Command::_nil();}

SelectManipulator::SelectManipulator() {}
SelectManipulator::~SelectManipulator() {}
CORBA::Boolean SelectManipulator::grasp(PickTraversal_ptr traversal, const Input::Event &event)
{
  return false;
}

CORBA::Boolean SelectManipulator::manipulate(PickTraversal_ptr traversal, const Input::Event &event)
{
  return false;
}

Unidraw::Command_ptr SelectManipulator::effect(PickTraversal_ptr traversal, const Input::Event &event)
{
  return Unidraw::Command::_nil();
}

