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
#ifndef _ControllerImpl_hh
#define _ControllerImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Controller.hh>
#include <Warsaw/Input.hh>
#include <Warsaw/DrawTraversal.hh>
#include <Warsaw/PickTraversal.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/MonoGraphic.hh>
#include <Prague/Sys/Thread.hh>
#include <vector>

class ControllerImpl : implements(Controller), public MonoGraphic, public SubjectImpl
{
//   typedef vector<Controller_var> clist_t;
 public:
  ControllerImpl(bool);
  virtual void traverse(Traversal_ptr traversal) { traversal->visit(Graphic_var(_this()));}
  virtual void draw(DrawTraversal_ptr traversal) { MonoGraphic::traverse(traversal);}
  virtual void pick(PickTraversal_ptr);

  virtual Controller_ptr parentController() { Prague::MutexGuard guard(mutex); return Controller::_duplicate(parent);}
  virtual Controller_ptr nextController() { Prague::MutexGuard guard(mutex); return Controller::_duplicate(next);}
  virtual Controller_ptr prevController() { Prague::MutexGuard guard(mutex); return Controller::_duplicate(prev);}
  virtual Controller_ptr firstController() { Prague::MutexGuard guard(mutex); return Controller::_duplicate(first);}
  virtual Controller_ptr lastController() { Prague::MutexGuard guard(mutex); return Controller::_duplicate(last);}
  virtual void appendController(Controller_ptr);
  virtual void prependController(Controller_ptr);
  virtual void insertController(Controller_ptr);
  virtual void replaceController(Controller_ptr);
  virtual void removeController();
  virtual void setControllerLinks(Controller_ptr, Controller_ptr, Controller_ptr);
  virtual void setFirstController(Controller_ptr);
  virtual void setLastController(Controller_ptr);
  virtual CORBA::Boolean requestFocus(Controller_ptr, Input::Device);
  virtual CORBA::Boolean receiveFocus(Focus_ptr);
  virtual void loseFocus(Focus_ptr);
  virtual CORBA::Boolean firstFocus(Input::Device);
  virtual CORBA::Boolean lastFocus(Input::Device);
  virtual CORBA::Boolean nextFocus(Input::Device);
  virtual CORBA::Boolean prevFocus(Input::Device);
  virtual CORBA::Boolean handlePositional(PickTraversal_ptr, const Input::Event &);
  virtual CORBA::Boolean handleNonPositional(const Input::Event &);

  virtual void set(Telltale::Flag);
  virtual void clear(Telltale::Flag);
  virtual CORBA::Boolean test(Telltale::Flag);
  virtual void modify(Telltale::Flag, CORBA::Boolean);
  virtual void constraint(TelltaleConstraint_ptr c);
  virtual TelltaleConstraint_ptr constraint();
// protected:
  virtual bool inside(PickTraversal_ptr);
  virtual void move(PickTraversal_ptr, const Input::Event &);
  virtual void press(PickTraversal_ptr, const Input::Event &);
  virtual void drag(PickTraversal_ptr, const Input::Event &);
  virtual void release(PickTraversal_ptr, const Input::Event &);
  virtual void doubleClick(PickTraversal_ptr, const Input::Event &);
  virtual void keyPress(const Input::Event &);
  virtual void keyRelease(const Input::Event &);
  virtual void other(const Input::Event &);
  void grab(PickTraversal_ptr);
  void ungrab(PickTraversal_ptr);
 private:
  Controller_var parent;
  Controller_ptr next;
  Controller_ptr prev;
  Controller_ptr first;
  Controller_ptr last;
//   clist_t controllers;
  unsigned long flags;
  bool grabbed;
  bool transparent;
  TelltaleConstraint_var myConstraint;
  Prague::Mutex mutex;
};

#endif /* _ControllerImpl_hh */
