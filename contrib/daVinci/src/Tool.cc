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
#include "daVinci/Tool.hh"
#include "daVinci/Manipulators.hh"
#include "daVinci/Models.hh"
#include "daVinci/Commands.hh"

using namespace Prague;
using namespace Fresco;
using namespace Unidraw;

namespace daVinci
{

Tool::Tool() : _manipulator(0) {}
Tool::~Tool() { delete _manipulator;}
CORBA::Boolean Tool::grasp(Fresco::Controller_ptr controller, Fresco::PickTraversal_ptr traversal, const Fresco::Input::Event &event)
{
  _manipulator = create_manipulator(controller, traversal, event);
  return !_manipulator || _manipulator->grasp(traversal, event);
}

CORBA::Boolean Tool::manipulate(Fresco::PickTraversal_ptr traversal, const Fresco::Input::Event &event)
{
  return !_manipulator || _manipulator->manipulate(traversal, event);
}

Unidraw::Command_ptr Tool::effect(Fresco::PickTraversal_ptr traversal, const Fresco::Input::Event &event)
{
  _manipulator->effect(traversal, event);
  Unidraw::Command_var command = interpret_manipulator(_manipulator);
  delete _manipulator;
  _manipulator = 0;
  return command._retn();
}

};
