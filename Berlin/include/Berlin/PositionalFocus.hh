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
#ifndef _PositionalFocus_hh
#define _PositionalFocus_hh

#include <Warsaw/config.hh>
#include <Warsaw/Controller.hh>
#include <Warsaw/Region.hh>
#include <Prague/Sys/Thread.hh>
#include <Berlin/FocusImpl.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/Pointer.hh>
#include <vector>

class PickTraversalImpl;
class ScreenImpl;

class PositionalFocus : public FocusImpl
{
  typedef vector<Controller_var> cstack_t;
 public:
  PositionalFocus(Input::Device, ScreenImpl *);
  virtual ~PositionalFocus();
  virtual void grab();
  virtual void ungrab();
  virtual void addFilter(Input::Filter_ptr);

  virtual bool request(Controller_ptr);
  virtual void damage(Region_ptr);
  virtual void dispatch(const Input::Event &);
 private:
  ScreenImpl        *screen;
  Pointer           *pointer;
  PickTraversalImpl *traversal;
  cstack_t           controllers;
  bool               grabbed;
  Prague::Mutex      mutex;
};

#endif /* _PositionalFocus_hh */
