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
#include <Berlin/RefCountVar.hh>
#include "Unidraw/EditorImpl.hh"
#include "Unidraw/View.hh"

using namespace Prague;
using namespace Warsaw;
using namespace Unidraw;

EditorImpl::EditorImpl(FigureKit_ptr figure) : _figure(Warsaw::FigureKit::_duplicate(figure)) {}
EditorImpl::~EditorImpl() {}
Tool_ptr EditorImpl::current_tool() { return Unidraw::Tool::_nil();}
void EditorImpl::current_tool(Tool_ptr) {}
Controller_ptr EditorImpl::create_view(Warsaw::Coord width, Warsaw::Coord height)
{
  View *view = new View(width, height, _this(), _figure);
  activate(view);
  return view->_this();
}
