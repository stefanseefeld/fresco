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
#ifndef _daVinci_Models_hh
#define _daVinci_Models_hh

#include <Fresco/config.hh>
#include <Fresco/Observer.hh>
#include <Fresco/Transform.hh>
#include <Fresco/FigureKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/UnidrawKit.hh>
#include <daVinci/RefCountBase.hh>
#include <vector>

namespace daVinci
{

class Model : public virtual POA_Unidraw::Model,
          public virtual RefCountBase
{
  typedef std::vector<Fresco::Graphic_var> vlist_t;
public:
  Model();
  virtual ~Model();
  virtual Unidraw::View_ptr create_view() = 0;
  Fresco::Color             &color();
  Fresco::Transform::Matrix &matrix();
  static void figures(Fresco::FigureKit_ptr);
  static Fresco::FigureKit_ptr figures();
  static void tools(Fresco::ToolKit_ptr);
  static Fresco::ToolKit_ptr tools();
  static void unidraw(Unidraw::UnidrawKit_ptr);
  static Unidraw::UnidrawKit_ptr unidraw();
protected:
  vlist_t                        _views;
private:
  Fresco::Color                  _color;
  Fresco::Transform::Matrix      _matrix;  
  static Fresco::FigureKit_var   _figures;
  static Fresco::ToolKit_var     _tools;
  static Unidraw::UnidrawKit_var _unidraw;
};

class Rectangle : public Model
{
public:
  Rectangle();
  virtual ~Rectangle();
  virtual Unidraw::View_ptr create_view();
};

class Circle : public Model
{
public:
  Circle();
  virtual ~Circle();
  virtual Unidraw::View_ptr create_view();
};

class Polygon : public Model
{
public:
  Polygon();
  Polygon(const Fresco::Path &);
  virtual ~Polygon();
  virtual Unidraw::View_ptr create_view();
private:
  Fresco::Path_var _path;
};
};

#endif
