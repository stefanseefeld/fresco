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
#ifndef _daVinci_Create_hh
#define _daVinci_Create_hh

#include <Fresco/config.hh>
#include <Fresco/Transform.hh>
#include <Fresco/State.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/ToolKit.hh>
#include <daVinci/Tool.hh>
#include <daVinci/Models.hh>
#include <daVinci/Manipulators.hh>
#include <daVinci/Commands.hh>
#include <daVinci/Document.hh>

namespace daVinci
{

  inline void identity(Fresco::Transform::Matrix &matrix)
  {
    matrix[0][0] = matrix[1][1] = matrix[2][2] = matrix[3][3] = 1.;
    matrix[0][1] = matrix[0][2] = matrix[0][3] = 0.;
    matrix[1][0] = matrix[1][2] = matrix[1][3] = 0.;
    matrix[2][0] = matrix[2][1] = matrix[2][3] = 0.;
    matrix[3][0] = matrix[3][1] = matrix[3][2] = 0.;
  }

  /*
   * just to show how a CreationTraits should look like...
   */
  class CreationTraits
  {
  public:
    static Manipulator         *create_manipulator(Fresco::Controller_ptr);
    static Unidraw::Command_ptr create_command(Manipulator *);
  };

  template <typename Traits>
  class CreateTool : public Tool
  {
  public:
    Manipulator *create_manipulator(Fresco::Controller_ptr c, Fresco::PickTraversal_ptr, const Fresco::Input::Event &)
    { return Traits::create_manipulator(c);}
    virtual Unidraw::Command_ptr interpret_manipulator(Manipulator *m) { return Traits::interpret_manipulator(m);}
  };

  /*
   * Rectangle
   */
  class CreateRectangleCommand : public daVinci::Command
  {
  public:
    CreateRectangleCommand(const Fresco::Vertex &b, const Fresco::Vertex &e) : _begin(b), _end(e) {}
    virtual void execute()
    {
      Rectangle *rectangle = new Rectangle();
      Fresco::Transform::Matrix &matrix = rectangle->matrix();
      identity(matrix);
      matrix[0][0] = _end.x - _begin.x;
      matrix[1][1] = _end.y - _begin.y;
      matrix[0][3] = _begin.x;
      matrix[1][3] = _begin.y;
      Document::instance()->append_model(rectangle);
    }
  private:
    Fresco::Vertex _begin, _end;
  };

  class RectangleCreator
  {
  public:
    static Manipulator *create_manipulator(Fresco::Controller_ptr controller)
    {
      Fresco::FigureKit_var figures = Model::figures();
      Fresco::ToolKit_var tools = Model::tools();
      Figure::Rectangle_var rectangle = figures->rectangle(0., 0., 1., 1.);
      Fresco::DrawingState_var state = tools->decorator(rectangle);
      Fresco::Color color = { 0., 0., 0., 1.};
      state->foreground(color);
//       state->surface_fillstyle(Fresco::DrawingKit::outlined);
      return new DragManipulator(controller, state);
    }
    static Unidraw::Command_ptr interpret_manipulator(Manipulator *m)
    {
      DragManipulator *dm = static_cast<DragManipulator *>(m);
      daVinci::Command *command = new CreateRectangleCommand(dm->begin(), dm->end());
      ServantBase::activate(command);
      return command->_this();
    }
  };

  /*
   * Polygon
   */
  class CreatePolygonCommand : public Command
  {
  public:
    CreatePolygonCommand(const Fresco::Path &path) : _path(new Fresco::Path(path)) {}
    virtual void execute()
    {
      Polygon *polygon = new Polygon(_path);
      Document::instance()->append_model(polygon);
    }
  private:
    Fresco::Path_var _path;
  };
  
  class PolygonCreator
  {
  public:
    static Manipulator *create_manipulator(Fresco::Controller_ptr c)
    {
      Fresco::FigureKit_var figures = Model::figures();
      Fresco::Path empty;
      empty.shape = Fresco::convex;
//       vertices.length(0);
      return new VertexManipulator(c, figures->polygon(empty));
    }
    static Unidraw::Command_ptr interpret_manipulator(Manipulator *m)
    {
      VertexManipulator *vm = static_cast<VertexManipulator *>(m);
      daVinci::Command *command = new CreatePolygonCommand(Fresco::Path_var(vm->path()));
      ServantBase::activate(command);
      return command->_this();
    }
  };
};

#endif
