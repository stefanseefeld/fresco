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
#include <Fresco/State.hh>
#include <Fresco/IO.hh>
#include "daVinci/Components.hh"
#include <algorithm>
#include <functional>

using namespace Prague;
using namespace Fresco;
using namespace Unidraw;

namespace daVinci
{

Fresco::FigureKit_var Component::_figures;
Fresco::ToolKit_var   Component::_tools;

Component::Component()
{
  _color.red = _color.green = _color.blue = 0.6;
  _color.alpha = 0.7;
  _matrix[0][0] = _matrix[1][1] = _matrix[2][2] = _matrix[3][3] = 1.;
  _matrix[1][0] = _matrix[1][2] = _matrix[1][3] = 0.;
  _matrix[2][0] = _matrix[2][1] = _matrix[2][3] = 0.;
  _matrix[3][0] = _matrix[3][1] = _matrix[3][2] = 0.;
}

Component::~Component()
{
}

Fresco::Color             &Component::color() { return _color;}
Fresco::Transform::Matrix &Component::matrix() { return _matrix;}

void Component::figures(FigureKit_ptr figures) { _figures = Fresco::FigureKit::_duplicate(figures);}
FigureKit_ptr Component::figures() { return Fresco::FigureKit::_duplicate(_figures);}
void Component::tools(ToolKit_ptr tools) { _tools = Fresco::ToolKit::_duplicate(tools);}
ToolKit_ptr Component::tools() { return Fresco::ToolKit::_duplicate(_tools);}

Rectangle::Rectangle() {}
Rectangle::~Rectangle() {}
Graphic_ptr Rectangle::create_view()
{
  FigureKit_var figures = Component::figures();
  ToolKit_var tools = Component::tools();
  Figure::Rectangle_var rectangle = figures->rectangle(0., 0., 1., 1.);
  Transform_var transform = rectangle->transformation();
  transform->load_matrix(matrix());
  DrawingState_var state = tools->decorator(rectangle);
  state->foreground(color());
  state->surface_fillstyle(Fresco::DrawingKit::outlined);
  _views.push_back(Graphic::_duplicate(state));
  return state._retn();
}

Circle::Circle() {}
Circle::~Circle() {}
Graphic_ptr Circle::create_view()
{
  FigureKit_var figures = Component::figures();
  ToolKit_var tools = Component::tools();
  Figure::Circle_var circle = figures->circle(0., 0., 1.);
  Transform_var transform = circle->transformation();
  transform->load_matrix(matrix());
  DrawingState_var state = tools->decorator(circle);
  state->foreground(color());
  state->surface_fillstyle(Fresco::DrawingKit::outlined);
  _views.push_back(Graphic::_duplicate(state));
  return state._retn();
}
Polygon::Polygon(const Fresco::Path &path) : _path(new Fresco::Path(path)) {}
Polygon::~Polygon() {}
Graphic_ptr Polygon::create_view()
{
  _path->length(_path->length() + 1);
  _path[_path->length() - 1] = _path[0];
  FigureKit_var figures = Component::figures();
  ToolKit_var tools = Component::tools();
  Figure::Path_var polygon = figures->polygon(_path);

//   Transform_var transform = polygon->transformation();
//   transform->load_matrix(matrix());
  DrawingState_var state = tools->decorator(polygon);
  state->foreground(color());
  state->surface_fillstyle(Fresco::DrawingKit::solid);
  _views.push_back(Graphic::_duplicate(state));
  return state._retn();
}
};
