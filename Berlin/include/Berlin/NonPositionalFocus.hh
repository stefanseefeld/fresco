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
#ifndef _NonPositionalFocus_hh
#define _NonPositionalFocus_hh

#include <Warsaw/config.hh>
#include <Warsaw/Focus.hh>
#include <Warsaw/Controller.hh>
#include <Warsaw/Region.hh>
#include <Prague/Sys/Thread.hh>
#include <Berlin/ImplVar.hh>
#include <vector>

class ScreenImpl;

class NonPositionalFocus : implements(Focus)
{
  typedef vector<Controller_var> cstack_t;
 public:
  NonPositionalFocus(ScreenImpl *);
  virtual ~NonPositionalFocus();

  virtual Event::Device device() { return 0;}
  virtual void grab();
  virtual void ungrab();
  virtual void addFilter(Event::Filter_ptr);

  void request(Controller_ptr);
  void damage(Region_ptr) {}
  void dispatch(const Event::Key &);
 private:
  ScreenImpl        *screen;
  cstack_t           controllers;
  bool               grabbed;
  Prague::Mutex      mutex;
};

#endif /* _NonPositionalFocus_hh */
