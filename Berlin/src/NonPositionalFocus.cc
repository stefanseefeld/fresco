/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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
#include "Berlin/NonPositionalFocus.hh"
#include "Berlin/ScreenImpl.hh"
#include "Berlin/PickTraversalImpl.hh"
#include "Berlin/RegionImpl.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

NonPositionalFocus::NonPositionalFocus(Input::Device d, Controller_ptr root) :
    FocusImpl(d)
{ my_controllers.push_back(Fresco::Controller::_duplicate(root)); }

NonPositionalFocus::~NonPositionalFocus() { }
void NonPositionalFocus::activate_composite()
{ my_controllers.back()->receive_focus(Focus_var(_this())); }
void NonPositionalFocus::add_filter(Input::Filter_ptr)
{
  // not implemented
}

bool NonPositionalFocus::request(Controller_ptr c)
{
    Trace trace("NonPositionalFocus::request");
    /*
     * brute force method:
     * construct stack of parent controllers and then
     * call lose/receiveFocus as appropriate...
     *
     * a refinement will test in the neighborhood of
     * the old controller holding the focus
     *       -stefan
     */
    std::vector<Controller_var> tmp;
    Controller_var p = Controller::_duplicate(c);
    while (!CORBA::is_nil(p))
    {
    tmp.insert(tmp.begin(), p);
    p = p->parent_controller();
    }
    Guard<Mutex> guard(my_mutex);
    cstack_t::iterator of = my_controllers.begin();
    std::vector<Controller_var>::iterator nf = tmp.begin();
    // ... skip the unchanged controllers, ...
    while (nf != tmp.end() &&
       of != my_controllers.end() &&
       (*nf)->is_identical(*of)) ++nf, ++of;
    // ... remove the old controllers in reverse order, ...
    for (cstack_t::reverse_iterator o = my_controllers.rbegin();
     o.base() != of;
     ++o)
    try
    { (*o)->lose_focus(device()); }
    catch (const CORBA::OBJECT_NOT_EXIST &) { }
    catch (const CORBA::COMM_FAILURE &) { }
    catch (const CORBA::TRANSIENT &) { }

    my_controllers.erase(of, my_controllers.end());
    // ... add the new controllers, ...
    Focus_var __this = _this ();
    for (; nf != tmp.end(); ++nf)
    {
    (*nf)->receive_focus (__this);
    my_controllers.push_back(Fresco::Controller::_duplicate(*nf));
    }
    return true;
}

/*
 * Dispatch a non-positional event. Try the controllers in turn, until
 * one handles the event. Remove from the list non-existent
 * controllers.
 */
void NonPositionalFocus::dispatch(Input::Event &event)
{
    Trace trace("NonPositionalFocus::dispatch");
    CORBA::Boolean done = false;
    Prague::Guard<Mutex> guard(my_mutex);
    for (int i = my_controllers.size() - 1; i >= 0 && !done; --i)
    {
    try { done = my_controllers [i]->handle_non_positional(event);}
    catch (const CORBA::OBJECT_NOT_EXIST &)
    { my_controllers.resize(i); }
    catch (const CORBA::COMM_FAILURE &)
    { my_controllers.resize(i); }
    catch (const CORBA::TRANSIENT &)
    { my_controllers.resize(i); }
    }
}
