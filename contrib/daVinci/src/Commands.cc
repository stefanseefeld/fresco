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
#include <Fresco/IO.hh>
#include "daVinci/Commands.hh"
#include "daVinci/Models.hh"
#include "daVinci/Document.hh"

using namespace Prague;
using namespace Fresco;
using namespace Unidraw;

namespace daVinci
{

Command::Command() {}
Command::~Command() {}
void Command::execute() {}
void Command::store(Unidraw::Model_ptr, const CORBA::Any &) {}
CORBA::Any *Command::recall(Unidraw::Model_ptr) { return 0;}

CreateCircleCommand::CreateCircleCommand(const Vertex &b, const Vertex &e) : _begin(b), _end(e) {}
void CreateCircleCommand::execute()
{
  Circle *circle = new Circle();
  Fresco::Transform::Matrix &matrix = circle->matrix();
  matrix[0][0] = _end.x - _begin.x;
  matrix[1][1] = _end.y - _begin.y;
  matrix[2][2] = matrix[3][3] = 1.;
  matrix[0][1] = matrix[0][2] = 0.;
  matrix[1][0] = matrix[1][2] = 0.;
  matrix[2][0] = matrix[2][1] = matrix[2][3] = 0.;
  matrix[3][0] = matrix[3][1] = matrix[3][2] = 0.;
  matrix[0][3] = _begin.x;
  matrix[1][3] = _begin.y;
  Document::instance()->append_model(circle);
}

};
