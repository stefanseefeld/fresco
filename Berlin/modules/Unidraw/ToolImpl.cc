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
#include "Unidraw/ToolImpl.hh"
#include "Unidraw/ManipulatorImpl.hh"
#include "Unidraw/CommandImpl.hh"

using namespace Prague;
using namespace Warsaw;
using namespace Unidraw;

ToolImpl::ToolImpl() {}
ToolImpl::~ToolImpl() {}
Manipulator_ptr ToolImpl::create_manipulator(PickTraversal_ptr, const Input::Event &) { return Unidraw::Manipulator::_nil();}
Unidraw::Command_ptr ToolImpl::interpret_manipulator(Manipulator_ptr) { return Unidraw::Command::_nil();}

SelectTool::SelectTool() {}
SelectTool::~SelectTool() {}
Manipulator_ptr SelectTool::create_manipulator(PickTraversal_ptr traversal, const Input::Event &event)
{
  SelectManipulator *select = new SelectManipulator();
  activate(select);
  return select->_this();
}

Unidraw::Command_ptr SelectTool::interpret_manipulator(Manipulator_ptr)
{
  return Unidraw::Command::_nil();
}
