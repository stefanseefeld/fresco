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
#include <Babylon/Babylon.hh>
#include <Fresco/config.hh>
#include <Fresco/Input.hh>
#include <Fresco/Transform.hh>
#include <Fresco/Region.hh>
#include <Fresco/PickTraversal.hh>
#include <Fresco/Focus.hh>
#include "Berlin/Logger.hh"
#include "Berlin/ControllerImpl.hh"
#include "Berlin/Event.hh"

using namespace Prague;
using namespace Fresco;
using namespace Babylon;
using namespace Berlin;

namespace Berlin
{

  class ControllerImpl::Iterator :
	public virtual POA_Fresco::ControllerIterator,
	public virtual ServantBase
  {
    public:
      Iterator(ControllerImpl *p, Tag c) :
	  my_parent(p),
	  my_cursor(c)
      {
	  Trace trace("ControllerImpl::Iterator::Iterator");
	  my_parent->_add_ref();
      }
      virtual ~Iterator()
      {
	  Trace trace("ControllerImpl::Iterator::~Iterator");
	  my_parent->_remove_ref();
      }
      virtual Fresco::Controller_ptr child()
      {
	  Trace trace("ControllerImpl::Iterator::child");
	  Prague::Guard<Mutex> guard(my_parent->my_cmutex);
	  if (my_cursor >= my_parent->my_children.size())
	      return Fresco::Controller::_nil();
	  return Fresco::Controller::_duplicate(my_parent->my_children[my_cursor]);
      }
      virtual void next() { my_cursor++; }
      virtual void prev() { my_cursor--; }
      virtual void insert(Controller_ptr child)
      {
	  Trace trace("ControllerImpl::Iterator::insert");
	  {
	      Prague::Guard<Mutex> guard(my_parent->my_cmutex);
	      if (my_cursor > my_parent->my_children.size())
		  my_cursor = my_parent->my_children.size();
	      my_parent->my_children.insert(my_parent->my_children.begin() +
					    my_cursor,
					    RefCount_var<Fresco::Controller>::increment(child));
	      child->set_parent_controller(Controller_var(my_parent->_this()));
	  }
	  my_parent->need_resize();
      }
      virtual void replace(Controller_ptr child)
      {
	  Trace trace("ControllerImpl::Iterator::replace");
	  {
	      Prague::Guard<Mutex> guard(my_parent->my_cmutex);
	      if (my_cursor > my_parent->my_children.size()) return;
	      Controller_var old =
		  static_cast<Controller_ptr>(my_parent->my_children[my_cursor]);
	      if (!CORBA::is_nil(old))
		  try
		  { old->remove_parent_controller(); }
		  catch(const CORBA::OBJECT_NOT_EXIST &) { }
		  catch (const CORBA::COMM_FAILURE &) { }
		  catch (const CORBA::TRANSIENT &) { }
	      my_parent->my_children[my_cursor] =
		  RefCount_var<Fresco::Controller>::increment(child);
	      child->set_parent_controller(Controller_var(my_parent->_this()));
	  }
	  my_parent->need_resize();
      }
      virtual void remove()
      {
	  Trace trace("ControllerImpl::Iterator::remove");
	  {
	      Prague::Guard<Mutex> guard(my_parent->my_cmutex);
	      if (my_cursor > my_parent->my_children.size()) return;
	      ControllerImpl::clist_t::iterator i =
		  my_parent->my_children.begin() + my_cursor;
	      try
	      { (*i)->remove_parent_controller(); }
	      catch (const CORBA::OBJECT_NOT_EXIST &) { }
	      catch (const CORBA::COMM_FAILURE &) { }
	      catch (const CORBA::TRANSIENT &) { }
	      my_parent->my_children.erase(i);
	  }
	  my_parent->need_resize();
      }
      virtual void destroy() { deactivate(); }
    private:
      ControllerImpl *my_parent;
      size_t          my_cursor;
  };

} // namespace

ControllerImpl::ControllerImpl(bool t) :
    my_telltale(0), my_focus(0), my_grabs(0), my_transparent(t)
{ Trace trace(this, "ControllerImpl::ControllerImpl"); }

ControllerImpl::~ControllerImpl()
{ Trace trace(this, "ControllerImpl::~ControllerImpl"); }

void ControllerImpl::deactivate()
{
    Trace trace(this, "ControllerImpl::deactivate");
    remove_parent_controller();
    ServantBase::deactivate(this);
}

void ControllerImpl::traverse(Traversal_ptr traversal)
{
    Trace trace(this, "ControllerImpl::traverse");
    traversal->visit(Graphic_var(_this()));
}

void ControllerImpl::draw(DrawTraversal_ptr traversal)
{
    Trace trace(this, "ControllerImpl::draw");
    MonoGraphic::traverse(traversal);
}

void ControllerImpl::pick(PickTraversal_ptr traversal)
{
    Trace trace(this, "ControllerImpl::pick");
    if (traversal->intersects_allocation())
    {
	traversal->enter_controller(Controller_var(_this()));
	MonoGraphic::traverse(traversal);
	if (!my_transparent && !traversal->picked()) traversal->hit();
	traversal->leave_controller();
    }
}

void ControllerImpl::append_controller(Controller_ptr c)
{
    Trace trace(this, "ControllerImpl::append_controller");
    if (CORBA::is_nil(c) ||
	!CORBA::is_nil(Controller_var(c->parent_controller())))
	return;
    Prague::Guard<Mutex> guard(my_cmutex);
    my_children.push_back(RefCount_var<Fresco::Controller>::increment(c));
    c->set_parent_controller(Controller_var(_this()));
}

void ControllerImpl::prepend_controller(Controller_ptr c)
{
    Trace trace(this, "ControllerImpl::prepend_controller");
    if (CORBA::is_nil(c) ||
	!CORBA::is_nil(Controller_var(c->parent_controller()))) return;
    Prague::Guard<Mutex> guard(my_cmutex);
    my_children.insert(my_children.begin(),
		       RefCount_var<Fresco::Controller>::increment(c));
    c->set_parent_controller(Controller_var(_this()));
}

void ControllerImpl::remove_controller(Controller_ptr c)
{
    Trace trace(this, "ControllerImpl::remove_controller");
    if (CORBA::is_nil(c) ||
	!CORBA::is_nil(Controller_var(c->parent_controller()))) return;
    Prague::Guard<Mutex> guard(my_cmutex);
    for (clist_t::iterator i = my_children.begin();
	 i != my_children.end(); ++i)
	if ((*i)->is_identical(c))
	{
	    (*i)->remove_parent_controller();
	    my_children.erase(i);
	    return;
	}
}

void ControllerImpl::set_parent_controller(Controller_ptr p)
{
    Trace trace(this, "ControllerImpl::set_parent_controller");
    Prague::Guard<Mutex> guard(my_pmutex);
    my_parent = Fresco::Controller::_duplicate(p);
}

void ControllerImpl::remove_parent_controller()
{
    Trace trace(this, "ControllerImpl::remove_parent_controller");
    Prague::Guard<Mutex> guard(my_pmutex);
    my_parent = Fresco::Controller::_nil();
}

Controller_ptr ControllerImpl::parent_controller()
{
    Trace trace(this, "ControllerImpl::parent_controller");
    Prague::Guard<Mutex> guard(my_pmutex);
    return Fresco::Controller::_duplicate(my_parent);
}

Fresco::ControllerIterator_ptr ControllerImpl::first_child_controller()
{
    Trace trace(this, "ControllerImpl::first_child_controller");
    Iterator *iterator = new Iterator(this, 0);
    activate(iterator);
    return iterator->_this();
}

Fresco::ControllerIterator_ptr ControllerImpl::last_child_controller()
{
    Trace trace(this, "ControllerImpl::last_child_controller");
    Prague::Guard<Mutex> guard(my_cmutex);
    Iterator *iterator = new Iterator(this, my_children.size() - 1);
    activate(iterator);
    return iterator->_this();
}

CORBA::Boolean ControllerImpl::request_focus(Controller_ptr c,
					     Input::Device d)
{
    Trace trace(this, "ControllerImpl::request_focus");  
    Logger::log(Logger::focus) << this << " requesting focus for " << d
			       << std::endl;
    Controller_var parent = parent_controller();
    return CORBA::is_nil(parent) ? false : parent->request_focus(c, d);
}

CORBA::Boolean ControllerImpl::receive_focus(Focus_ptr f)
{
    Trace trace(this, "ControllerImpl::receive_focus");
    Input::Device d = f->device();
    Logger::log(Logger::focus) << this << " receiving focus for " << d
			       << std::endl;
    set_focus(d);
    if (d == 0) set(Fresco::Controller::active);
    return true;
}

void ControllerImpl::lose_focus(Input::Device d)
{
    Trace trace(this, "ControllerImpl::lose_focus");
    Logger::log(Logger::focus) << this << " losing focus for " << d
			       << std::endl;
    clear_focus(d);
    if (d == 0) clear(Fresco::Controller::active);
}

CORBA::Boolean ControllerImpl::first_focus(Input::Device d)
{
    Trace trace(this, "ControllerImpl::first_focus");
    // if we have children, ask them if they take the focus...
    {
	Prague::Guard<Mutex> guard(my_cmutex);
	for (clist_t::iterator i = my_children.begin();
	     i != my_children.end();
	     ++i)
	    if ((*i)->first_focus(d)) return true;
    }
    // ... else we have to request it ourself
    Controller_var parent = parent_controller();
    if (CORBA::is_nil(parent)) return false;
    return parent->request_focus(Controller_var(_this()), d);
}

CORBA::Boolean ControllerImpl::last_focus(Input::Device d)
{
    Trace trace(this, "ControllerImpl::last_focus");
    // if we have children, ask them if they take the focus...
    {
	Prague::Guard<Mutex> guard(my_cmutex);
	for (clist_t::reverse_iterator i = my_children.rbegin();
	     i != my_children.rend();
	     ++i)
	    if ((*i)->last_focus(d)) return true;
    }
    // ... else we have to request it ourself
    Controller_var parent = parent_controller();
    if (CORBA::is_nil(parent)) return false;
    return parent->request_focus(Controller_var(_this()), d);
}

CORBA::Boolean ControllerImpl::next_focus(Input::Device d)
{
    Trace trace(this, "ControllerImpl::next_focus");
    Fresco::Controller_var parent = parent_controller();
    if (CORBA::is_nil(parent)) return false;
    // first locate the next controller in the control graph...
    Fresco::ControllerIterator_var iterator =
	parent->first_child_controller();
    Fresco::Controller_var next;
    // set the iterator to refer to 'this' child...
    for (next = iterator->child();
	 !CORBA::is_nil(next) && !is_identical(next);
	 iterator->next(), next = iterator->child())
	;
    // 'this' not being contained in the parent's child list indicates
    // an internal error
    assert(!CORBA::is_nil(next));
    iterator->next();
    next = iterator->child();
    iterator->destroy();
    // ... now try to pass the focus to it ...
    if (!CORBA::is_nil(next)) return next->first_focus(d);
    // ...else pass up to the parent
    else return parent->next_focus(d);
}

CORBA::Boolean ControllerImpl::prev_focus(Input::Device d)
{
    Trace trace(this, "ControllerImpl::prev_focus");
    Fresco::Controller_var parent = parent_controller();
    if (CORBA::is_nil(parent)) return false;
    // first locate the previous controller in the control graph...
    Fresco::ControllerIterator_var iterator = parent->last_child_controller();
    Fresco::Controller_var prev;
    // set the iterator to refer to 'this' child...
    for (prev = iterator->child();
	 !CORBA::is_nil(prev) && !is_identical(prev);
	 iterator->prev(), prev = iterator->child())
	;
    // 'this' not being contained in the parent's child list indicates an
    // internal error
    assert(!CORBA::is_nil(prev));
    iterator->prev();
    prev = iterator->child();
    iterator->destroy();
    // ... now try to pass the focus to it ...
    if (!CORBA::is_nil(prev)) return prev->last_focus(d);
    // ... else pass up to the parent
    else return parent->prev_focus(d);
}

void ControllerImpl::set(Fresco::Telltale::Mask m)
{
    Trace trace(this, "ControllerImpl::set");
    if (!CORBA::is_nil(my_constraint))
	my_constraint->trymodify(Telltale_var(_this()), m, true);
    else modify(m, true);
}

void ControllerImpl::clear(Fresco::Telltale::Mask m)
{
    Trace trace(this, "ControllerImpl::clear");
    if (!CORBA::is_nil(my_constraint))
	my_constraint->trymodify(Telltale_var(_this()), m, false);
    else modify(m, false);
}

CORBA::Boolean ControllerImpl::test(Fresco::Telltale::Mask m)
{
    Prague::Guard<Mutex> guard(my_mutex);
    return (my_telltale & m) == m;
}

void ControllerImpl::modify(Fresco::Telltale::Mask m, CORBA::Boolean on)
{
    CORBA::ULong nf = on ? my_telltale | m : my_telltale & ~m;
    {
	Prague::Guard<Mutex> guard(my_mutex);
	if (nf == my_telltale) return;
	else my_telltale = nf;
    }
    CORBA::Any any;
    any <<= nf;
    notify(any);
}

void ControllerImpl::constraint(TelltaleConstraint_ptr c)
{
    Prague::Guard<Mutex> guard(my_mutex);
    my_constraint = TelltaleConstraint::_duplicate(c);
}

TelltaleConstraint_ptr ControllerImpl::constraint()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return TelltaleConstraint::_duplicate(my_constraint);
}

CORBA::Boolean ControllerImpl::handle_positional(PickTraversal_ptr traversal,
						 const Input::Event &event)
{
    Trace trace(this, "ControllerImpl::handle_positional");
    Input::Position position;
    if (Input::get_position(event, position) == -1)
    {
	std::cerr << "ControllerImpl::handle_positional fatal error: "
		  << "non positional event" << std::endl;
	return false;
    }
    if (event[0].attr._d() == Input::button)
    {
	const Input::Toggle &toggle = event[0].attr.selection();
	if (toggle.actuation == Input::Toggle::press)
	    press(traversal, event);
	else if (toggle.actuation == Input::Toggle::release)
	    release(traversal, event);
    }
    else if (event[0].attr._d() == Input::positional)
    {
	if (test(Fresco::Controller::pressed))
	    drag(traversal, event);
	else
	    move(traversal, event);
    }
    else other(event);
    return true;
}

CORBA::Boolean ControllerImpl::handle_non_positional(const Input::Event &event)
{
    Trace trace(this, "ControllerImpl::handle_non_positional");
    if (event[0].dev != 0 || event[0].attr._d() != Input::key)
    {
	std::cerr << "ControllerImpl::handleNonPositional fatal error: "
		  << "unknown event" << std::endl;
	return false;
    }
    if (event[0].attr.selection().actuation != Input::Toggle::press)
	return false;
    key_press(event);
    return true;
}

bool ControllerImpl::inside(PickTraversal_ptr traversal)
    //. default implementation: use bounding box
{
    return traversal->intersects_allocation();
}

void ControllerImpl::move(PickTraversal_ptr, const Input::Event &) { }

void ControllerImpl::press(PickTraversal_ptr traversal, const Input::Event &)
{
    grab(traversal);
    // FIXME: This needs to be configurable! Hardcoding in the keyboard
    //        is bad.
    request_focus(Controller_var(_this()), 0); // request focus for the
                                               // keyboard
                                               // (click to focus)
    set(Fresco::Controller::pressed);
}

void ControllerImpl::drag(PickTraversal_ptr, const Input::Event &) { }

void ControllerImpl::release(PickTraversal_ptr traversal,
const Input::Event &)
{
    clear(Fresco::Controller::pressed);
    ungrab(traversal);
}

void ControllerImpl::double_click(PickTraversal_ptr, const Input::Event &) { }

void ControllerImpl::key_press(const Input::Event &event)
{
    Trace trace(this, "ControllerImpl::key_press");
    const Input::Toggle &toggle = event[0].attr.selection();
    switch (toggle.number)
    {
    case Babylon::UC_KEY_CURSOR_LEFT:          // left
	prev_focus(event[0].dev);
	break;
    case Babylon::UC_HORIZONTAL_TABULATION: // tab
    case Babylon::UC_KEY_CURSOR_RIGHT:         // right
	next_focus(event[0].dev);
	break;
    default: break;
    }
}

void ControllerImpl::key_release(const Input::Event &) { }

void ControllerImpl::other(const Input::Event &) { }

void ControllerImpl::grab(Fresco::PickTraversal_ptr traversal)
{
    Focus_var focus = traversal->get_focus();
    if (CORBA::is_nil(focus)) return;
    focus->grab();
    my_grabs |= 1 << focus->device();
    update_state();
}

void ControllerImpl::ungrab(Fresco::PickTraversal_ptr traversal)
{
    Focus_var focus = traversal->get_focus();
    if (CORBA::is_nil(focus)) return;
    focus->ungrab();
    my_grabs &= ~(1 << focus->device());
    update_state();
}

void ControllerImpl::update_state() { }
