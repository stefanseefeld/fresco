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
#include <Fresco/config.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/Transform.hh>
#include <Fresco/IO.hh>
#include "daVinci/Manipulators.hh"

using namespace Prague;
using namespace Fresco;
using namespace Unidraw;

namespace daVinci
{

Manipulator::Manipulator(Fresco::Controller_ptr controller) : _controller(Controller::_duplicate(controller)) {}
Manipulator::~Manipulator() {}
CORBA::Boolean Manipulator::grasp(PickTraversal_ptr, const Input::Event &) { return false;}
CORBA::Boolean Manipulator::manipulate(PickTraversal_ptr, const Input::Event &) { return false;}
void Manipulator::effect(PickTraversal_ptr, const Input::Event &) {}

SelectManipulator::SelectManipulator(Fresco::Controller_ptr controller) : Manipulator(controller) {}
SelectManipulator::~SelectManipulator() {}
CORBA::Boolean SelectManipulator::grasp(PickTraversal_ptr traversal, const Input::Event &event)
{
  return false;
}

CORBA::Boolean SelectManipulator::manipulate(PickTraversal_ptr traversal, const Input::Event &event)
{
  return false;
}

DragManipulator::DragManipulator(Fresco::Controller_ptr controller, Graphic_ptr graphic)
  : Manipulator(controller), _graphic(Graphic::_duplicate(graphic)) {}
DragManipulator::~DragManipulator() {}
CORBA::Boolean DragManipulator::grasp(PickTraversal_ptr traversal, const Input::Event &event)
{
  _begin = event[1].attr.location();
  _relative_begin = _begin;
  Transform_var trafo = traversal->current_transformation();
  trafo->inverse_transform_vertex(_relative_begin);
  _matrix[0][0] = _matrix[0][1] = _matrix[0][2] = 0.;
  _matrix[1][0] = _matrix[1][1] = _matrix[1][2] = 0.;
  _matrix[2][0] = _matrix[2][1] = _matrix[2][2] = 0.;
  _matrix[3][0] = _matrix[3][1] = _matrix[3][2] = _matrix[3][3] = 0.;
  _matrix[0][3] = _begin.x;
  _matrix[1][3] = _begin.y;
  _matrix[2][3] = _begin.z;
  Transform_var(_graphic->transformation())->load_matrix(_matrix);
  _iterator = _controller->last_child_graphic();
  _iterator->insert(_graphic);
  return true;
}

CORBA::Boolean DragManipulator::manipulate(PickTraversal_ptr traversal, const Input::Event &event)
{
  if (event[0].attr._d() == Fresco::Input::button) return false;
  _end = event[0].attr.location();
  _relative_end = _end;
  Transform_var trafo = traversal->current_transformation();
  trafo->inverse_transform_vertex(_relative_end);
  _matrix[0][0] = _end.x - _begin.x;
  _matrix[1][1] = _end.y - _begin.y;
  _matrix[2][2] = _end.z - _begin.z;
  Transform_var(_graphic->transformation())->load_matrix(_matrix);
  _graphic->need_resize();
  return true;
}

void DragManipulator::effect(PickTraversal_ptr traversal, const Input::Event &event)
{
  _iterator->remove();
}

VertexManipulator::VertexManipulator(Fresco::Controller_ptr controller, Figure::Path_ptr figure)
  : Manipulator(controller), _figure(Figure::Path::_duplicate(figure)), _path(new Fresco::Path())
{
   _path->shape = Fresco::convex;
}
VertexManipulator::~VertexManipulator() {}
CORBA::Boolean VertexManipulator::grasp(PickTraversal_ptr traversal, const Input::Event &event)
{
  Vertex begin = event[1].attr.location();
  Transform_var trafo = traversal->current_transformation();
  trafo->inverse_transform_vertex(begin);
  _path->nodes.length(1);
  _path->nodes[0] = begin;
  _figure->handles(_path);
  _iterator = _controller->last_child_graphic();
  _iterator->insert(_figure);
  return true;
}

CORBA::Boolean VertexManipulator::manipulate(PickTraversal_ptr traversal, const Input::Event &event)
{
  if (event[0].attr._d() == Fresco::Input::button &&
      event[0].attr.selection().actuation == Input::Toggle::press)
    {
      Vertex current = event[1].attr.location();
      Transform_var trafo = traversal->current_transformation();
      trafo->inverse_transform_vertex(current);

      size_t i = _path->nodes.length() - 1;
      _path->nodes.length(i + 2);
      _path->nodes[i] = current;
      _path->nodes[i + 1] = current;
      _figure->handles(_path);
      _figure->need_resize();

      if (event[0].attr.selection().number == 1) return true; // left
      else if (event[0].attr.selection().number == 3) return false; // middle button
      else if (event[0].attr.selection().number == 2) return false; // right
      else return false;
    }
  else if (event[0].attr._d() == Fresco::Input::button &&
	   event[0].attr.selection().actuation == Input::Toggle::release)
    {
      return false;
    }
  else
    {
      Vertex current = event[0].attr.location();
      Transform_var trafo = traversal->current_transformation();
      trafo->inverse_transform_vertex(current);
      size_t i = _path->nodes.length() - 1;
      _path->nodes[i] = current;
      _figure->handles(_path);
      _figure->need_resize();
      return true;
    }
}

void VertexManipulator::effect(Fresco::PickTraversal_ptr, const Fresco::Input::Event &)
{
}

};
