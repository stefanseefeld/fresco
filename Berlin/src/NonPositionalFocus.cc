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

#include "Berlin/NonPositionalFocus.hh"
#include "Berlin/ScreenImpl.hh"
#include "Berlin/PickTraversalImpl.hh"
#include "Berlin/RegionImpl.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/Logger.hh"
#include "Prague/Sys/Profiler.hh"

using namespace Prague;

NonPositionalFocus::NonPositionalFocus(ScreenImpl *s) : screen(s), grabbed(false) {}
NonPositionalFocus::~NonPositionalFocus() {}

void NonPositionalFocus::grab()
{
//   MutexGuard guard(mutex);
  grabbed = true;
}

void NonPositionalFocus::ungrab()
{
//   MutexGuard guard(mutex);
  grabbed = false;
}

void NonPositionalFocus::addFilter(Event::Filter_ptr)
{
  // not implemented
}

void NonPositionalFocus::request(Controller_ptr c)
{
  /*
   * brute force method:
   * construct stack of parent controllers and then
   * call lose/receiveFocus as appropriate...
   *
   * a refinement will test in the neighborhood of
   * the old controller holding the focus
   *       -stefan
   */
  vector<Controller_var> tmp;
  Controller_var p = Controller::_duplicate(c);
  while (!CORBA::is_nil(p))
    {
      tmp.insert(tmp.begin(), p);
      p = p->parentController();
    }
  cstack_t::iterator of = controllers.begin();
  vector<Controller_var>::iterator nf = tmp.begin();
  /*
   * ...skip the unchanged controllers,...
   */
  while (nf != tmp.end() &&
	 of != controllers.end() &&
	 (*nf)->_is_equivalent(*of)) nf++, of++;
  /*
   * ...remove the old controllers in reverse order,...
   */
  for (cstack_t::reverse_iterator o = controllers.rbegin(); o.base() != of; o++)
    {
      (*o)->loseFocus(Focus_var(_this()));
    }
  controllers.erase(of, controllers.end());
  /*
   * ...add the new controllers,...
   */
  for (; nf != tmp.end(); nf++)
    {
      (*nf)->receiveFocus(Focus_var(_this()));
      controllers.push_back(*nf);
    }
}

void NonPositionalFocus::dispatch(const Event::Key &key)
{
  MutexGuard guard(mutex);
  Prague::Profiler prf("NonPositionalFocus::dispatch");
  SectionLog section("NonPositionalFocus::dispatch");
  CORBA::Any any;
  any <<= key;
  controllers.back()->handleNonPositional(any);
}
