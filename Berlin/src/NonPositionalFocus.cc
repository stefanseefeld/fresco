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

#include "Berlin/NonPositionalFocus.hh"
#include "Berlin/ScreenImpl.hh"
#include "Berlin/PickTraversalImpl.hh"
#include "Berlin/RegionImpl.hh"
#include <Prague/Sys/Profiler.hh>
#include <Prague/Sys/Tracer.hh>

using namespace Prague;
using namespace Warsaw;

NonPositionalFocus::NonPositionalFocus(Input::Device d, ScreenImpl *s) : FocusImpl(d), screen(s) {}
NonPositionalFocus::~NonPositionalFocus() {}

void NonPositionalFocus::add_filter(Input::Filter_ptr)
{
  // not implemented
}

bool NonPositionalFocus::request(Controller_ptr c)
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
      p = p->parent_controller();
    }
  cstack_t::iterator of = controllers.begin();
  vector<Controller_var>::iterator nf = tmp.begin();
  /*
   * ...skip the unchanged controllers,...
   */
  while (nf != tmp.end() &&
	 of != controllers.end() &&
	 (*nf)->is_identical(*of)) nf++, of++;
  /*
   * ...remove the old controllers in reverse order,...
   */
  for (cstack_t::reverse_iterator o = controllers.rbegin(); o.base() != of; o++)
    (*o)->lose_focus(device());
  controllers.erase(of, controllers.end());
  /*
   * ...add the new controllers,...
   */
  for (; nf != tmp.end(); nf++)
    {
      (*nf)->receive_focus(Focus_var(_this()));
      controllers.push_back(*nf);
    }
  return true;
}

void NonPositionalFocus::dispatch(Input::Event &event)
{
  Trace trace("NonPositionalFocus::dispatch");
  MutexGuard guard(mutex);
  if (controllers.size())
    controllers.back()->handle_non_positional(event);
}
