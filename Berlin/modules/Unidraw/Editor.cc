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
#include <Berlin/TransformImpl.hh>
#include <Berlin/Requestor.hh>
#include <Berlin/Event.hh>
#include "Unidraw/Editor.hh"

using namespace Prague;
using namespace Warsaw;
using namespace Unidraw;

Editor::Editor(Coord width, Coord height, FigureKit_ptr figures)
  : ControllerImpl(false),
    _figures(RefCount_var<FigureKit>::increment(figures)),
    _root(_figures->group()),
    _target_tx(new TransformImpl()),
    _width(width),
    _height(height)
{}
Editor::~Editor() {}

void Editor::activate_composite()
{
  Requestor *requestor = new Requestor(0.5, 0.5, _width, _height);
  activate(requestor);
  requestor->body(_root);
  body(requestor->_this());

}

void Editor::press(Warsaw::PickTraversal_ptr traversal, const Warsaw::Input::Event &event)
{
  Trace trace("Editor::press");
  cout << "Editor::press" << endl;
  Input::Position position;
  if (Input::get_position(event, position) == -1) return; // internal error
  _start = position;
  bool picked = traversal->forward(); // is there a target graphic ?
  if (picked)
    {
      while (traversal->forward()); // up to the leaf
      _target = traversal->current_graphic();
      _target_tx->copy(Transform_var(traversal->current_transformation()));
//       if (e->modifier_is_down(Event::shift))    _curtool = scale_tool;
//       else if (e->modifier_is_down(Event::alt))	_curtool = rotate_tool;
//       else	                                _curtool = move_tool;
      _curtool = move_tool;
    }
  else
    {
      _target = _root;
      _target_tx->copy(Transform_var(traversal->current_transformation()));
      _target_tx->premultiply(Transform_var(_root->transformation()));
//       if (e->modifier_is_down(Event::shift)) 	    _curtool = scale_root_tool;
//       else if (e->modifier_is_down(Event::control)) _curtool = move_root_tool;
//       else if (e->modifier_is_down(Event::alt))     _curtool = rotate_root_tool;
//       else	                                    _curtool = create_tool;
      _curtool = create_tool;
    }
  return;
}

void Editor::drag(Warsaw::PickTraversal_ptr traversal, const Warsaw::Input::Event &event)
{
  Trace trace("Editor::drag");
}

void Editor::release(Warsaw::PickTraversal_ptr traversal, const Warsaw::Input::Event &event)
{
  Trace trace("Editor::release");
}
