/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include <Warsaw/config.hh>
#include <Warsaw/IO.hh>
#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Profiler.hh>
#include "Berlin/PositionalFocus.hh"
#include "Berlin/ScreenImpl.hh"
#include "Berlin/PickTraversalImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/Provider.hh"
#include "Berlin/Console.hh"
#include "Berlin/Event.hh"
#include "Berlin/Vertex.hh"

using namespace Prague;
using namespace Warsaw;


PositionalFocus::PositionalFocus(Input::Device d, Graphic_ptr g, Region_ptr r)
  : FocusImpl(d), _root(g), _pointer(new Pointer(Console::drawable())), _traversal(0), _grabbed(false)
{
  Trace trace("PositionalFocus::PositionalFocus");
  _traversal_cache[0] = new PickTraversalImpl(_root, r, Transform::_nil(), this);
  _traversal_cache[1] = new PickTraversalImpl(_root, r, Transform::_nil(), this);
  _traversal_cache[0]->set_memento(_traversal_cache[1]);
  _traversal_cache[1]->set_memento(_traversal_cache[0]);
  _traversal = _traversal_cache[0];
}

PositionalFocus::~PositionalFocus()
{
  Trace trace("PositionalFocus::~PositionalFocus");
  Impl_var<PickTraversalImpl>::deactivate(_traversal_cache[0]);
  Impl_var<PickTraversalImpl>::deactivate(_traversal_cache[1]);  
  delete _pointer;
}

void PositionalFocus::activate_composite()
{
  Trace trace("PositionalFocus::activate_composite");

}

void PositionalFocus::grab()
{
//   MutexGuard guard(mutex);
  _grabbed = true;
}

void PositionalFocus::ungrab()
{
//   MutexGuard guard(mutex);
  _grabbed = false;
}

void PositionalFocus::add_filter(Input::Filter_ptr)
{
  // not implemented
}

bool PositionalFocus::request(Controller_ptr c)
{
  return false; // not granted !
}

void PositionalFocus::restore(Region_ptr region)
{
  Vertex l, u;
  region->bounds(l, u);
  if (_pointer->intersects(l.x, u.x, l.y, u.y)) 
    _pointer->restore();
}

void PositionalFocus::damage(Region_ptr region)
{
  Trace trace("PositionalFocus::damage");
  Vertex l, u;
  region->bounds(l, u);
  if (_pointer->intersects(l.x, u.x, l.y, u.y))
    {
      _pointer->save();
      _pointer->draw();
    }
  MutexGuard guard(_mutex);
  if (!_grabbed) return;
  Region_var allocation = _traversal->current_allocation();
  Transform_var transformation = _traversal->current_transformation();
  allocation->bounds(l, u);
  transformation->transform_vertex(l);
  transformation->transform_vertex(u);

  Lease_var<RegionImpl> bbox(Provider<RegionImpl>::provide());

  bbox->valid = true;
  bbox->lower.x = min(l.x, u.x);
  bbox->lower.y = min(l.y, u.y);
  bbox->upper.x = max(l.x, u.x);
  bbox->upper.y = max(l.y, u.y);
  if (bbox->intersects(region)) _traversal->update();
}

/*
 * the dispatching strategy is the following:
 * we keep a PickTraversal cached which points
 * to the controller currently holding focus.
 *
 * dispatching means to call traverse on this
 * controller which should, if the controller
 * or one of it's children 'hits', result in
 * a memento (traversal->memento()).
 *
 * if the traversal doesn't contain a memento,
 * it means that the controller should lose
 * focus, so we start over at the parent controller...
 */
void PositionalFocus::dispatch(Input::Event &event)
{
  MutexGuard guard(_mutex);
  Trace trace("PositionalFocus::dispatch");
  Input::Position position;
  int pidx = Input::get_position(event, position);
  if (pidx == -1)
    {
      cerr << "PositionalFocus::dispatch error : non positional event" << endl;
      return;
    }
  /*
   * update the pointer object / image
   */
  _pointer->move(position.x, position.y);
  _traversal->reset(position);
  /*
   * if we hold a device grab, start the traversal at the current
   * controller...
   */
  if (_grabbed)
    {
      Controller_var top = _controllers.back();
      while (!CORBA::is_nil(top))
	{
	  try { top->traverse(Traversal_var(_traversal->_this()));}
	  catch (const CORBA::OBJECT_NOT_EXIST &) {}
	  catch (const CORBA::COMM_FAILURE &) {}
	  if (_traversal->picked()) break;
	  top = _traversal->top_controller();
	  _traversal->pop_controller();
	}
    }
  /*
   * ...else start at screen level
   */
  else
    {
      _traversal->clear();
      _root->traverse(Traversal_var(_traversal->_this()));
    }
  PickTraversalImpl *picked = _traversal->memento();
  if (!picked)
    {
      cerr << "PositionalFocus::dispatch : no Controller found ! (position is " << position << ")" << endl;
      return;
    }
  else _traversal = picked;
  /*
   * ...now do the [lose/receive]Focus stuff,...
   */
  vector<Controller_var>::const_iterator nf = _traversal->controllers().begin();
  cstack_t::iterator of = _controllers.begin();
  /*
   * ...skip the unchanged controllers,...
   */
  while (nf != _traversal->controllers().end() &&
	 of != _controllers.end() &&
	 (*nf)->is_identical(*of)) nf++, of++;
  /*
   * ...remove the old controllers in reverse order,...
   */
  for (cstack_t::reverse_iterator o = _controllers.rbegin(); o.base() != of; o++)
    try { (*o)->lose_focus(device());}
    catch (const CORBA::OBJECT_NOT_EXIST &) {}
    catch (const CORBA::COMM_FAILURE &) {}
  _controllers.erase(of, _controllers.end());
  /*
   * ...add the new controllers,...
   */
  Focus_var __this = _this();
  for (; nf != picked->controllers().end(); nf++)
    {
      (*nf)->receive_focus (__this);
      _controllers.push_back(*nf);
    }
  /*
   * ...and finally dispatch the event
   */
//   _traversal->debug();
//   Transform_var(_traversal->current_transformation())->inverse_transform_vertex(position);
//   event[pidx].attr.location(position);
  _controllers.back()->handle_positional(PickTraversal_var(_traversal->_this()), event);
}
