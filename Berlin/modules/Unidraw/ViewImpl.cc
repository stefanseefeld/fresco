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
#include "ViewImpl.hh"

using namespace Prague;
using namespace Fresco;

using namespace Berlin::UnidrawKit;

UViewImpl::UViewImpl(Unidraw::Model_ptr model) : ControllerImpl(false), _model(Unidraw::Model::_duplicate(model)) {}
UViewImpl::~UViewImpl() {}

void UViewImpl::traverse(Traversal_ptr traversal)
{
  Trace trace("UViewImpl::traverse");
  traversal->visit(Graphic_var(_this()));
}

void UViewImpl::draw(DrawTraversal_ptr traversal)
{
  Trace trace("UViewImpl::draw");
  MonoGraphic::traverse(traversal);
}

void UViewImpl::pick(PickTraversal_ptr traversal)
{
  Trace trace("UViewImpl::pick");
  if (traversal->intersects_allocation())
    {
      traversal->enter_controller(Controller_var(_this()));
      MonoGraphic::traverse(traversal);
      if (traversal->ok()) traversal->hit();
      traversal->leave_controller();
    }
}

Unidraw::Model_ptr UViewImpl::subject() { return Unidraw::Model::_duplicate(_model);}
CORBA::Boolean UViewImpl::handle_positional(PickTraversal_ptr traversal, const Input::Event &event)
{
  std::cout << "handle_positional" << std::endl;
  return false;
}
