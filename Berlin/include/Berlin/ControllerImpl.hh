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
#ifndef _ControllerImpl_hh
#define _ControllerImpl_hh

#include <Prague/Sys/Tracer.hh>
#include <Warsaw/config.hh>
#include <Warsaw/Controller.hh>
#include <Warsaw/Input.hh>
#include <Warsaw/DrawTraversal.hh>
#include <Warsaw/PickTraversal.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/MonoGraphic.hh>
#include <Prague/Sys/Thread.hh>
#include <vector>

class ControllerImpl : public virtual POA_Warsaw::Controller,
                       public MonoGraphic,
                       public SubjectImpl
{
 public:
  ControllerImpl(bool);
  ~ControllerImpl();
  virtual void traverse(Warsaw::Traversal_ptr traversal) { traversal->visit(Warsaw::Graphic_var(_this()));}
  virtual void draw(Warsaw::DrawTraversal_ptr traversal) { MonoGraphic::traverse(traversal);}
  virtual void pick(Warsaw::PickTraversal_ptr);

  virtual Warsaw::Controller_ptr parentController() { Prague::MutexGuard guard(mutex); return Warsaw::Controller::_duplicate(parent);}
  virtual Warsaw::Controller_ptr nextController() { Prague::MutexGuard guard(mutex); return Warsaw::Controller::_duplicate(next);}
  virtual Warsaw::Controller_ptr prevController() { Prague::MutexGuard guard(mutex); return Warsaw::Controller::_duplicate(prev);}
  virtual Warsaw::Controller_ptr firstController() { Prague::MutexGuard guard(mutex); return Warsaw::Controller::_duplicate(first);}
  virtual Warsaw::Controller_ptr lastController() { Prague::MutexGuard guard(mutex); return Warsaw::Controller::_duplicate(last);}
  virtual void appendController(Warsaw::Controller_ptr);
  virtual void prependController(Warsaw::Controller_ptr);
  virtual void insertController(Warsaw::Controller_ptr);
  virtual void replaceController(Warsaw::Controller_ptr);
  virtual void removeController();
  virtual void setControllerLinks(Warsaw::Controller_ptr, Warsaw::Controller_ptr, Warsaw::Controller_ptr);
  virtual void setFirstController(Warsaw::Controller_ptr);
  virtual void setLastController(Warsaw::Controller_ptr);
  virtual CORBA::Boolean requestFocus(Warsaw::Controller_ptr, Warsaw::Input::Device);
  virtual CORBA::Boolean receiveFocus(Warsaw::Focus_ptr);
  virtual void loseFocus(Warsaw::Input::Device);
  virtual CORBA::Boolean firstFocus(Warsaw::Input::Device);
  virtual CORBA::Boolean lastFocus(Warsaw::Input::Device);
  virtual CORBA::Boolean nextFocus(Warsaw::Input::Device);
  virtual CORBA::Boolean prevFocus(Warsaw::Input::Device);
  virtual CORBA::Boolean handlePositional(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
  virtual CORBA::Boolean handleNonPositional(const Warsaw::Input::Event &);

  virtual void set(Warsaw::Telltale::Mask);
  virtual void clear(Warsaw::Telltale::Mask);
  virtual CORBA::Boolean test(Warsaw::Telltale::Mask);
  virtual void modify(Warsaw::Telltale::Mask, CORBA::Boolean);
  virtual void constraint(Warsaw::TelltaleConstraint_ptr);
  virtual Warsaw::TelltaleConstraint_ptr constraint();
 protected:
  virtual bool inside(Warsaw::PickTraversal_ptr);
  virtual void move(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
  virtual void press(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
  virtual void drag(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
  virtual void release(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
  virtual void doubleClick(Warsaw::PickTraversal_ptr, const Warsaw::Input::Event &);
  virtual void keyPress(const Warsaw::Input::Event &);
  virtual void keyRelease(const Warsaw::Input::Event &);
  virtual void other(const Warsaw::Input::Event &);
  void grab(Warsaw::PickTraversal_ptr t) { t->grab(); grabs |= 1 << t->device(); updateState();} 
  void ungrab(Warsaw::PickTraversal_ptr t) { t->ungrab(); grabs &= ~(1 << t->device()); updateState();}
  bool grabbed(Warsaw::Input::Device d) { return grabs & (1 << d);}
  void setFocus(Warsaw::Input::Device d) { focus |= 1 << d; updateState();}
  void clearFocus(Warsaw::Input::Device d) { focus &= ~(1 << d); updateState();}
  virtual void updateState();
 private:
  Warsaw::Controller_var parent;
  Warsaw::Controller_var next;
  Warsaw::Controller_var prev;
  Warsaw::Controller_var first;
  Warsaw::Controller_var last;
  CORBA::ULong telltale;
  CORBA::ULong focus;
  CORBA::ULong grabs;
  bool transparent;
  Warsaw::TelltaleConstraint_var myConstraint;
  Prague::Mutex mutex;
};

#endif 
