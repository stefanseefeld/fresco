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
#include <Warsaw/config.hh>
#include <Warsaw/IO.hh>
#include <Berlin/RefCountVar.hh>
#include <Berlin/TransformImpl.hh>
#include <Berlin/Requestor.hh>
#include <Berlin/Event.hh>
#include "Unidraw/View.hh"

using namespace Prague;
using namespace Warsaw;
using namespace Unidraw;

View::View(Coord width, Coord height, Editor_ptr editor, FigureKit_ptr figures)
  : ControllerImpl(false),
    _editor(RefCount_var<Editor>::increment(editor)),
    _figure(RefCount_var<FigureKit>::increment(figures)),
    _root(_figure->group()),
    _target_tx(new TransformImpl()),
    _width(width),
    _height(height)
{}
View::~View() {}

void View::activate_composite()
{
  Requestor *requestor = new Requestor(0.5, 0.5, _width, _height);
  activate(requestor);
  requestor->body(_root);
  body(requestor->_this());

}

void View::press(Warsaw::PickTraversal_ptr traversal, const Warsaw::Input::Event &event)
{
  Trace trace("View::press");
  Input::Position position;
  if (Input::get_position(event, position) == -1) return; // internal error
  Transform_var trafo = traversal->current_transformation();
  trafo->inverse_transform_vertex(position);
  _start = position;
  bool picked = traversal->forward(); // is there a target graphic ?
  if (picked)
    {
      while (traversal->forward()); // up to the leaf
      cout << "picked !" << endl;
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

void View::drag(Warsaw::PickTraversal_ptr traversal, const Warsaw::Input::Event &event)
{
  Trace trace("View::drag");
}

void View::release(Warsaw::PickTraversal_ptr traversal, const Warsaw::Input::Event &event)
{
  Trace trace("View::release");
  if (_curtool == create_tool) add(_start.x, _start.y);
}

void View::add(Coord x, Coord y)
{
  static int toggle = 0;
  Figure::FigureBase_var fig;
  if (++toggle%2)
    {
      Color green = {0.5, 1., 0.5, 0.8};
      fig = _figure->rectangle(x - 180., y - 180., x + 180., y + 180.);
//       fig = _figure->circle(x, y, 200.);
      fig->type(Figure::fill);
      fig->background(green);
    }
  else
    {
      Color red = {1., 0.5, 0.5, 0.8};
      fig = _figure->rectangle(x - 180., y - 180., x + 180., y + 180.);
      fig->type(Figure::fill);
      fig->background(red);
    }  
  _root->append_graphic(fig);
//   Transform_var tx = fig->transformation();
//   tx->copy(_target_tx->_this());
//   tx->invert();
  fig->need_redraw();
  fig->need_resize();
}
