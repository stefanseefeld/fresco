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
#include "daVinci/Models.hh"
#include <algorithm>
#include <functional>

using namespace Prague;
using namespace Fresco;
using namespace Unidraw;

namespace daVinci
{

Fresco::FigureKit_var   Model::_figures;
Fresco::ToolKit_var     Model::_tools;
Unidraw::UnidrawKit_var Model::_unidraw;

Model::Model()
{
  _color.red = _color.green = _color.blue = 0.6;
  _color.alpha = 0.7;
  _matrix[0][0] = _matrix[1][1] = _matrix[2][2] = _matrix[3][3] = 1.;
  _matrix[1][0] = _matrix[1][2] = _matrix[1][3] = 0.;
  _matrix[2][0] = _matrix[2][1] = _matrix[2][3] = 0.;
  _matrix[3][0] = _matrix[3][1] = _matrix[3][2] = 0.;
}

Model::~Model()
{
}

Fresco::Color             &Model::color() { return _color;}
Fresco::Transform::Matrix &Model::matrix() { return _matrix;}

void Model::figures(FigureKit_ptr figures) { _figures = Fresco::FigureKit::_duplicate(figures);}
FigureKit_ptr Model::figures() { return Fresco::FigureKit::_duplicate(_figures);}
void Model::tools(ToolKit_ptr tools) { _tools = Fresco::ToolKit::_duplicate(tools);}
ToolKit_ptr Model::tools() { return Fresco::ToolKit::_duplicate(_tools);}
void Model::unidraw(Unidraw::UnidrawKit_ptr unidraw) { _unidraw = Unidraw::UnidrawKit::_duplicate(unidraw);}
UnidrawKit_ptr Model::unidraw() { return Unidraw::UnidrawKit::_duplicate(_unidraw);}

Rectangle::Rectangle() {}
Rectangle::~Rectangle() {}
Unidraw::View_ptr Rectangle::create_view()
{
  FigureKit_var figures = Model::figures();
  ToolKit_var tools = Model::tools();
  UnidrawKit_var unidraw = Model::unidraw();
  Figure::Rectangle_var rectangle = figures->rectangle(0., 0., 1., 1.);
  Transform_var transform = rectangle->transformation();
  transform->load_matrix(matrix());
  DrawingState_var state = tools->decorator(rectangle);
  state->foreground(color());
//   state->surface_fillstyle(Fresco::DrawingKit::outlined);
  _views.push_back(Graphic::_duplicate(state));
  Unidraw::View_var view = unidraw->create_view(state, Model_var(_this()));
  return view._retn();
}

Circle::Circle() {}
Circle::~Circle() {}
Unidraw::View_ptr Circle::create_view()
{
  FigureKit_var figures = Model::figures();
  ToolKit_var tools = Model::tools();
  UnidrawKit_var unidraw = Model::unidraw();
  Figure::Circle_var circle = figures->circle(0., 0., 1.);
  Transform_var transform = circle->transformation();
  transform->load_matrix(matrix());
  DrawingState_var state = tools->decorator(circle);
  state->foreground(color());
  state->surface_fillstyle(Fresco::DrawingKit::outlined);
  _views.push_back(Graphic::_duplicate(state));
  Unidraw::View_var view = unidraw->create_view(state, Model_var(_this()));
  return view._retn();
}
Polygon::Polygon() : _path(new Fresco::Path()) {}
Polygon::Polygon(const Fresco::Path &path) : _path(new Fresco::Path(path)) {}
Polygon::~Polygon() {}
Unidraw::View_ptr Polygon::create_view()
{
  FigureKit_var figures = Model::figures();
  ToolKit_var tools = Model::tools();
  UnidrawKit_var unidraw = Model::unidraw();
  Figure::Path_var polygon = figures->polygon(_path);

  DrawingState_var state = tools->decorator(polygon);
  state->foreground(color());
  state->surface_fillstyle(Fresco::DrawingKit::solid);
  _views.push_back(Graphic::_duplicate(state));
  Unidraw::View_var view = unidraw->create_view(state, Model_var(_this()));
  return view._retn();
}
};
