/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Berlin/ControllerImpl.hh"
#include <Warsaw/Input.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/PickTraversal.hh>
#include <Warsaw/Focus.hh>
#include "Berlin/Event.hh"
#include <Prague/Sys/Tracer.hh>
#include <Prague/Unicode/Unicode.hh>

using namespace Prague;
using namespace Warsaw;

ControllerImpl::ControllerImpl(bool t) : telltale(0), focus(0), grabs(0), transparent(t) {}
void ControllerImpl::pick(PickTraversal_ptr traversal)
{
  Trace trace("ControllerImpl::pick");
  if (grabbed(traversal->device()) || traversal->intersectsAllocation())
    {
      traversal->enterController(Controller_var(_this()));
      MonoGraphic::traverse(traversal);
      if (!transparent && !traversal->picked()) traversal->hit();
      traversal->leaveController();
    }
}

void ControllerImpl::appendController(Controller_ptr c)
{
  Trace trace("ControllerImpl::appendController");
  if (CORBA::is_nil(c) || !CORBA::is_nil(Controller_var(c->parentController()))) return;
  MutexGuard guard(mutex);
  Controller_ptr nc = Warsaw::Controller::_duplicate(c);
  nc->setControllerLinks(Controller_var(_this()), last, Controller_var(Warsaw::Controller::_nil()));
  last = nc;
  if (CORBA::is_nil(first)) first = last;
}

void ControllerImpl::prependController(Controller_ptr c)
{
  Trace trace("ControllerImpl::prependController");
  if (CORBA::is_nil(c) || !CORBA::is_nil(Controller_var(c->parentController()))) return;
  MutexGuard guard(mutex);
  Controller_ptr nc = Warsaw::Controller::_duplicate(c);
  nc->setControllerLinks(Controller_var(_this()), Controller_var(Warsaw::Controller::_nil()), first);
  first = nc;
  if (CORBA::is_nil(last)) last = nc;
}

void ControllerImpl::insertController(Controller_ptr c)
{
  Trace trace("ControllerImpl::insertController");
  if (CORBA::is_nil(c)) return;
  Controller_ptr nc = Warsaw::Controller::_duplicate(c);
  nc->setControllerLinks(parent, prev, Controller_var(_this()));
//   if (is_eq(this, Viewer_var(parent_->first_viewer())))
  if (CORBA::is_nil(prev)) parent->setFirstController(nc);
  prev = nc;
}

void ControllerImpl::replaceController(Controller_ptr c)
{
  Trace trace("ControllerImpl::replaceController");
  if (CORBA::is_nil(c)) removeController();
  else
    {
      c->setControllerLinks(parent, prev, next);
      if (CORBA::is_nil(parent)) return;
      if (CORBA::is_nil(prev)) parent->setFirstController(c);
      if (CORBA::is_nil(next)) parent->setLastController(c);
      prev = Warsaw::Controller::_nil();
      next = Warsaw::Controller::_nil();
    }
}

void ControllerImpl::removeController()
{
  Trace trace("ControllerImpl::removeController");
  if (CORBA::is_nil(parent)) return;
  if (CORBA::is_nil(prev)) parent->setFirstController(next);
  else prev->setControllerLinks(Controller_var(Warsaw::Controller::_nil()), Controller_var(prev->prevController()), next);
  if (CORBA::is_nil(next)) parent->setLastController(prev);
  else next->setControllerLinks(Controller_var(Warsaw::Controller::_nil()), prev, Controller_var(next->nextController()));
  parent = Warsaw::Controller::_nil();
  prev = Warsaw::Controller::_nil();
  next = Warsaw::Controller::_nil();
}

void ControllerImpl::setControllerLinks(Controller_ptr pa, Controller_ptr pr, Controller_ptr ne)
{
  Trace trace("ControllerImpl::setControllerLinks");
  if (!CORBA::is_nil(pa))
    {
      parent = Warsaw::Controller::_duplicate(pa);
      prev = Warsaw::Controller::_duplicate(pr);
      if (!CORBA::is_nil(pr))
	{
	  pr->setControllerLinks(Controller_var(Warsaw::Controller::_nil()),
				 Controller_var(pr->prevController()), Controller_var(_this()));
	}
      next = ne;
      if (!CORBA::is_nil(ne))
	{
	  ne->setControllerLinks(Controller_var(Warsaw::Controller::_nil()),
				 Controller_var(_this()), Controller_var(next->nextController()));
	}
    }
  else
    {
      prev = pr;
      next = ne;
    }
}

void ControllerImpl::setFirstController(Controller_ptr c)
{
  Trace trace("ControllerImpl::setFirstController");
  first = Warsaw::Controller::_duplicate(c);
  if (CORBA::is_nil(c)) last = Warsaw::Controller::_nil();
}

void ControllerImpl::setLastController(Controller_ptr c)
{
  Trace trace("ControllerImpl::setLastController");
  last = c;
  if (CORBA::is_nil(c)) first = Warsaw::Controller::_nil();
}

CORBA::Boolean ControllerImpl::requestFocus(Controller_ptr c, Input::Device d)
{
  Trace trace("ControllerImpl::requestFocus");  
  return CORBA::is_nil(parent) ? false : parent->requestFocus(c, d);
}

CORBA::Boolean ControllerImpl::receiveFocus(Focus_ptr f)
{
  Trace trace("ControllerImpl::receiveFocus");  
  setFocus(f->device());
  if (f->device() == 0) set(Warsaw::Controller::active);
  return true;
}

void ControllerImpl::loseFocus(Input::Device d)
{
  Trace trace("ControllerImpl::loseFocus");
  clearFocus(d);
  if (d == 0) clear(Warsaw::Controller::active);
}

CORBA::Boolean ControllerImpl::firstFocus(Input::Device d)
{
  Controller_ptr ne = Warsaw::Controller::_nil();
  for (Controller_var c = firstController(); !CORBA::is_nil(c); c = ne)
    {
      if (c->firstFocus(d)) return true;
      ne = c->nextController();
    }
  if (CORBA::is_nil(parent)) return false;
  return parent->requestFocus(Controller_var(_this()), d);
}

CORBA::Boolean ControllerImpl::lastFocus(Input::Device d)
{
  Controller_ptr pr = Warsaw::Controller::_nil();
  for (Controller_var c = lastController(); !CORBA::is_nil(c); c = pr)
    {
      if (c->lastFocus(d)) return true;
      pr = c->prevController();
    }
  if (CORBA::is_nil(parent)) return false;
  return parent->requestFocus(Controller_var(_this()), d);
}

CORBA::Boolean ControllerImpl::nextFocus(Input::Device d)
{
  if (!CORBA::is_nil(next)) return next->firstFocus(d);
  if (CORBA::is_nil(parent)) return false;
  return parent->nextFocus(d);
}

CORBA::Boolean ControllerImpl::prevFocus(Input::Device d)
{
  if (!CORBA::is_nil(prev)) return prev->lastFocus(d);
  if (CORBA::is_nil(parent)) return false;
  else return parent->prevFocus(d);
}

void ControllerImpl::set(Warsaw::Telltale::Mask m)
{
  Trace trace("ControllerImpl::set");
  if (!CORBA::is_nil(myConstraint)) myConstraint->trymodify(Telltale_var(_this()), m, true);
  else modify(m, true);
}

void ControllerImpl::clear(Warsaw::Telltale::Mask m)
{
  Trace trace("ControllerImpl::clear");
  if (!CORBA::is_nil(myConstraint)) myConstraint->trymodify(Telltale_var(_this()), m, false);
  else modify(m, false);
}

CORBA::Boolean ControllerImpl::test(Warsaw::Telltale::Mask m)
{
  MutexGuard guard(mutex);
  return (telltale & m) == m;
}

void ControllerImpl::modify(Warsaw::Telltale::Mask m, CORBA::Boolean on)
{
  unsigned long nf = on ? telltale | m : telltale & ~m;
  {
    MutexGuard guard(mutex);
    if (nf == telltale) return;
    else telltale = nf;
  }
  CORBA::Any any;
  any <<= nf;
  notify(any);
}

void ControllerImpl::constraint(TelltaleConstraint_ptr c)
{
  MutexGuard guard(mutex);
  myConstraint = c;
}

TelltaleConstraint_ptr ControllerImpl::constraint()
{
  MutexGuard guard(mutex);
  return TelltaleConstraint::_duplicate(myConstraint);
}

CORBA::Boolean ControllerImpl::handlePositional(PickTraversal_ptr traversal, const Input::Event &event)
{
  Trace trace("ControllerImpl::handlePositional");
  Input::Position position;
  if (Input::getPosition(event, position) == -1)
    {
      cerr << "ControllerImpl::handlePositional fatal error : non positional event" << endl;
      return false;
    }
  if (event[0].attr._d() == Input::button)
    {
      const Input::Toggle &toggle = event[0].attr.selection();
      if (toggle.actuation == Input::Toggle::press) press(traversal, event);
      else if (toggle.actuation == Input::Toggle::release) release(traversal, event);
    }
  else if (event[0].attr._d() == Input::positional)
    {
      if (test(Warsaw::Controller::pressed)) drag(traversal, event);
      else move(traversal, event);
    }
  else other(event);
  return true;
}

CORBA::Boolean ControllerImpl::handleNonPositional(const Input::Event &event)
{
  Trace trace("ControllerImpl::handleNonPositional");
  if (event[0].dev != 0 || event[0].attr._d() != Input::key)
    {
      cerr << "ControllerImpl::handleNonPositional fatal error : unknown event" << endl;
      return false;
    }
  if (event[0].attr.selection().actuation != Input::Toggle::press) return false;
  keyPress(event);
  return true;
}

bool ControllerImpl::inside(PickTraversal_ptr traversal)
  //. default implementation: use bounding box
{
  return traversal->intersectsAllocation();
}

void ControllerImpl::move(PickTraversal_ptr, const Input::Event &)
{
}

void ControllerImpl::press(PickTraversal_ptr traversal, const Input::Event &)
{
  grab(traversal);
  requestFocus(Controller_var(_this()), 0);
  set(Warsaw::Controller::pressed);
}

void ControllerImpl::drag(PickTraversal_ptr, const Input::Event &)
{
}

void ControllerImpl::release(PickTraversal_ptr traversal, const Input::Event &)
{
  clear(Warsaw::Controller::pressed);
  ungrab(traversal);
}

void ControllerImpl::doubleClick(PickTraversal_ptr, const Input::Event &)
{
}

void ControllerImpl::keyPress(const Input::Event &event)
{
  Trace trace("ControllerImpl::keyPress");
  const Input::Toggle &toggle = event[0].attr.selection();
//   cout << "ControllerImpl::keyPress : " << toggle.number << ' ' << (char) toggle.number << endl;
  switch (toggle.number)
    {
    case Unicode::KEY_CURSOR_LEFT:          // left
      {
	prevFocus(event[0].dev);
	break;
      }
    case Unicode::UC_HORIZONTAL_TABULATION: // tab
    case Unicode::KEY_CURSOR_RIGHT:         // right
      {
	nextFocus(event[0].dev);
	break;
      }
    default: break;
    }
}

void ControllerImpl::keyRelease(const Input::Event &)
{
}

void ControllerImpl::other(const Input::Event &)
{
}

void ControllerImpl::updateState()
{
}
