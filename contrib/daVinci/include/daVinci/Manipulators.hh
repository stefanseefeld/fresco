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
#ifndef _daVinci_Manipulators_hh
#define _daVinci_Manipulators_hh

#include <Fresco/config.hh>
#include <Fresco/Transform.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/ToolKit.hh>
#include <daVinci/Tool.hh>

namespace daVinci
{
  class Manipulator
  {
  public:
    Manipulator(Fresco::Controller_ptr);
    virtual ~Manipulator();
    virtual CORBA::Boolean grasp(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    virtual CORBA::Boolean manipulate(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    virtual void effect(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
  protected:
    Fresco::Controller_var _controller;
  };

  class SelectManipulator : public Manipulator
  {
  public:
    SelectManipulator(Fresco::Controller_ptr);
    virtual ~SelectManipulator();
    virtual CORBA::Boolean grasp(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    virtual CORBA::Boolean manipulate(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
  };
  
  class DragManipulator : public Manipulator
  {
  public:
    DragManipulator(Fresco::Controller_ptr, Fresco::Graphic_ptr);
    virtual ~DragManipulator();
    virtual CORBA::Boolean grasp(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    virtual CORBA::Boolean manipulate(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    virtual void effect(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    Fresco::Vertex begin() { return _relative_begin;}
    Fresco::Vertex end() { return _relative_end;}
  private:
    Fresco::GraphicIterator_var _iterator;
    Fresco::Transform::Matrix   _matrix;
    Fresco::Graphic_var         _graphic;
    Fresco::Vertex              _begin;
    Fresco::Vertex              _end;
    Fresco::Vertex              _relative_begin;
    Fresco::Vertex              _relative_end;
  };

  class VertexManipulator : public Manipulator
  {
  public:
    VertexManipulator(Fresco::Controller_ptr, Figure::Path_ptr);
    virtual ~VertexManipulator();
    virtual CORBA::Boolean grasp(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    virtual CORBA::Boolean manipulate(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    virtual void effect(Fresco::PickTraversal_ptr, const Fresco::Input::Event &);
    Fresco::Path *path() { return new Fresco::Path(_path);};    
  private:
    Fresco::GraphicIterator_var _iterator;
    Figure::Path_var _figure;
    Fresco::Path_var _path;
  };
};

#endif
