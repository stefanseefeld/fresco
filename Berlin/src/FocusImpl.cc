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

#include <Berlin/FocusImpl.hh>
#include <Berlin/ScreenImpl.hh>
#include <Berlin/PickTraversalImpl.hh>
#include <Berlin/Logger.hh>

FocusImpl::FocusImpl(ScreenImpl *s) : screen(s), traversal(0) {}
FocusImpl::~FocusImpl() { if (traversal) traversal->_dispose();}

void FocusImpl::request(Controller_ptr c)
{
  // not granted !
}

void FocusImpl::damage(Region_ptr region)
{
  MutexGuard guard(mutex);
  if (!traversal) return;
  Region_var allocation = traversal->allocation();
  if (allocation->intersects(region))
    {
      traversal->_dispose();
      traversal = 0;
    }
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
void FocusImpl::dispatch(const Event::Pointer &pointer)
{
  MutexGuard guard(mutex);
  SectionLog section(Logger::picking, "FocusImpl::dispatch(pointer)");
  /*
   * if we have no traversal, create one
   * and start from root...
   */
  if (!traversal)
    {
      traversal = new PickTraversalImpl(Screen_var(screen->_this()),
					Region_var(screen->getRegion()),
					Transform_var(Transform::_nil()),
					pointer);
      traversal->_obj_is_ready(CORBA::BOA::getBOA());
      screen->traverse(Traversal_var(traversal->_this()));
    }
  /*
   * ...else start at the Controller holding the focus
   */
  else
    {
      traversal->reset(pointer);
      Controller_var top = controllers.back();
      while (!CORBA::is_nil(top))
	{
	  top->traverse(Traversal_var(traversal->_this()));
	  if (traversal->picked()) break;
	  top = traversal->topController();
	  traversal->popController();
	}
    }
  PickTraversalImpl *picked = traversal->memento();
  if (!picked)
    {
      cerr << "FocusImpl::dispatch : no Controller found ! (position is " << pointer.location << ")" << endl;
      if (traversal)
	{
	  traversal->_dispose();
	  traversal = 0;
	}
      return;
    }
  /*
   * ...now do the [lose/receive]Focus stuff,...
   */
  vector<Controller_var>::const_iterator nf = picked->controllerStack().begin();
  cstack_t::iterator of = controllers.begin();
  /*
   * ...skip the unchanged controllers,...
   */
  while (nf != picked->controllerStack().end() &&
	 of != controllers.end() &&
	 (*nf)->_is_equivalent(*of)) nf++, of++;
  /*
   * ...remove the old controllers in reverse order,...
   */
  for (cstack_t::iterator o = controllers.end(); o != of; o--)
    (*(o - 1))->loseFocus(Focus_var(_this()));
  controllers.erase(of, controllers.end());
  /*
   * ...add the new controllers,...
   */
  for (; nf != picked->controllerStack().end(); nf++)
    {
      (*nf)->receiveFocus(Focus_var(_this()));
      controllers.push_back(*nf);
    }
  /*
   * ...and finally dispatch the event
   */
  traversal->_dispose();
  traversal = picked;
  traversal->_obj_is_ready(_boa());
  CORBA::Any any;
  any <<= pointer;
  controllers.back()->handle(PickTraversal_var(traversal->_this()), any);
}
