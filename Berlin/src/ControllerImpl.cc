/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#include "Warsaw/Input.hh"
#include "Warsaw/Transform.hh"
#include "Warsaw/Region.hh"
#include "Warsaw/PickTraversal.hh"
#include "Warsaw/Focus.hh"
#include "Berlin/Logger.hh"
#include "Berlin/Event.hh"
#include "Prague/Unicode/Unicode.hh"

using namespace Prague;

ControllerImpl::ControllerImpl(bool t) : telltale(0), focus(0), grabs(0), transparent(t) {}
void ControllerImpl::pick(PickTraversal_ptr traversal)
{
  SectionLog section("ControllerImpl::pick");
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
  if (!CORBA::is_nil(Controller_var(c->parentController()))) return;
  MutexGuard guard(mutex);
  Controller_ptr nc = Controller::_duplicate(c);
  nc->setControllerLinks(Controller_var(_this()), last, Controller_var(Controller::_nil()));
  last = nc;
  if (CORBA::is_nil(first)) first = last;
}

void ControllerImpl::prependController(Controller_ptr c)
{
  if (!CORBA::is_nil(Controller_var(c->parentController()))) return;
  MutexGuard guard(mutex);
  Controller_ptr nc = Controller::_duplicate(c);
  nc->setControllerLinks(Controller_var(_this()), Controller_var(Controller::_nil()), first);
  first = nc;
  if (CORBA::is_nil(last)) last = nc;
}

void ControllerImpl::insertController(Controller_ptr c)
{
  Controller_ptr nc = Controller::_duplicate(c);
  nc->setControllerLinks(parent, prev, Controller_var(_this()));
//   if (is_eq(this, Viewer_var(parent_->first_viewer())))
  if (CORBA::is_nil(prev)) parent->setFirstController(nc);
  prev = nc;
}

void ControllerImpl::replaceController(Controller_ptr c)
{
  c->setControllerLinks(parent, prev, next);
  if (CORBA::is_nil(parent)) return;
  if (CORBA::is_nil(prev)) parent->setFirstController(c);
  if (CORBA::is_nil(next)) parent->setLastController(c);
  prev = Controller::_nil();
  next = Controller::_nil();
//   CORBA::release(Viewer_ptr(this));
}

void ControllerImpl::removeController()
{
  if (CORBA::is_nil(parent)) return;
  if (CORBA::is_nil(prev)) parent->setFirstController(next);
  else prev->setControllerLinks(Controller_var(Controller::_nil()), Controller_var(prev->prevController()), next);
  if (CORBA::is_nil(next)) parent->setLastController(prev);
  else next->setControllerLinks(Controller_var(Controller::_nil()), prev, Controller_var(next->nextController()));
  parent = Controller::_nil();
  prev = Controller::_nil();
  next = Controller::_nil();
}

void ControllerImpl::setControllerLinks(Controller_ptr pa, Controller_ptr pr, Controller_ptr ne)
{
  if (!CORBA::is_nil(pa))
    {
      parent = Controller::_duplicate(pa);
      prev = Controller::_duplicate(pr);
      if (!CORBA::is_nil(pr))
	{
	  pr->setControllerLinks(Controller_var(Controller::_nil()),
				 Controller_var(pr->prevController()), Controller_var(_this()));
	}
      next = ne;
      if (!CORBA::is_nil(ne))
	{
	  ne->setControllerLinks(Controller_var(Controller::_nil()),
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
  first = Controller::_duplicate(c);
  if (CORBA::is_nil(c)) last = Controller::_nil();
}

void ControllerImpl::setLastController(Controller_ptr c)
{
  last = c;
  if (CORBA::is_nil(c)) first = Controller::_nil();
}

CORBA::Boolean ControllerImpl::requestFocus(Controller_ptr c, Input::Device d)
{
  SectionLog section("ControllerImpl::requestFocus");  
  return CORBA::is_nil(parent) ? false : parent->requestFocus(c, d);
}

CORBA::Boolean ControllerImpl::receiveFocus(Focus_ptr f)
{
  SectionLog section("ControllerImpl::receiveFocus");  
  setFocus(f->device());
  if (f->device() == 0) set(Telltale::active);
  return true;
}

void ControllerImpl::loseFocus(Input::Device d)
{
  SectionLog section("ControllerImpl::loseFocus");
  clearFocus(d);
  if (d == 0) clear(Telltale::active);
}

CORBA::Boolean ControllerImpl::firstFocus(Input::Device d)
{
  Controller_ptr ne = Controller::_nil();
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
  Controller_ptr pr = Controller::_nil();
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

void ControllerImpl::set(Telltale::Flag f)
{
  SectionLog section("ControllerImpl::set");
  if (!CORBA::is_nil(myConstraint)) myConstraint->trymodify(Telltale_var(_this()), f, true);
  else modify(f, true);
}

void ControllerImpl::clear(Telltale::Flag f)
{
  SectionLog section("ControllerImpl::clear");
  if (!CORBA::is_nil(myConstraint)) myConstraint->trymodify(Telltale_var(_this()), f, false);
  else modify(f, false);
}

CORBA::Boolean ControllerImpl::test(Telltale::Flag f)
{
  MutexGuard guard(mutex);
  return telltale & (1 << f);
}

void ControllerImpl::modify(Telltale::Flag f, CORBA::Boolean on)
{
  unsigned long fs = 1 << f;
  unsigned long nf = on ? telltale | fs : telltale & ~fs;
  {
    MutexGuard guard(mutex);
    if (nf == telltale) return;
    else telltale = nf;
  }
  CORBA::Any any;
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
  SectionLog section("ControllerImpl::handlePositional");
  Input::Position position;
  if (!Input::getPosition(event, position))
    {
      cerr << "ControllerImpl::handlePositional fatal error : non positional event" << endl;
      return false;
    }
  if (event[0].attr._d() == Input::button)
    {
      const Input::Toggle &toggle = event[0].attr.bselection();
      if (toggle.actuation == Input::Toggle::press) press(traversal, event);
      else if (toggle.actuation == Input::Toggle::release) release(traversal, event);
    }
  else if (event[0].attr._d() == Input::positional)
    {
      if (test(Telltale::toggle)) drag(traversal, event);
      else move(traversal, event);
    }
  else other(event);
  return true;
}

CORBA::Boolean ControllerImpl::handleNonPositional(const Input::Event &event)
{
  SectionLog section("ControllerImpl::handleNonPositional");
  if (event[0].dev != 0 || event[0].attr._d() != Input::key)
    {
      cerr << "ControllerImpl::handleNonPositional fatal error : unknown event" << endl;
      return false;
    }
  if (event[0].attr.kselection().actuation != Input::Toggle::press) return false;
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
  set(Telltale::toggle);
}

void ControllerImpl::drag(PickTraversal_ptr, const Input::Event &)
{
}

void ControllerImpl::release(PickTraversal_ptr traversal, const Input::Event &)
{
  clear(Telltale::toggle);
  ungrab(traversal);
}

void ControllerImpl::doubleClick(PickTraversal_ptr, const Input::Event &)
{
}

void ControllerImpl::keyPress(const Input::Event &event)
{
  SectionLog section("ControllerImpl::keyPress");
  const Input::Toggle &toggle = event[0].attr.kselection();
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
