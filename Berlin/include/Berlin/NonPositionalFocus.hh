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
#ifndef _Berlin_NonPositionalFocus_hh
#define _Berlin_NonPositionalFocus_hh

#include <Fresco/config.hh>
#include <Fresco/Controller.hh>
#include <Fresco/Region.hh>
#include <Fresco/Raster.hh>
#include <Berlin/ImplVar.hh>
#include <Prague/Sys/Thread.hh>
#include <Berlin/FocusImpl.hh>
#include <vector>

class ScreenImpl;

class NonPositionalFocus : public FocusImpl
{
  typedef std::vector<Fresco::Controller_var> cstack_t;
 public:
  NonPositionalFocus(Fresco::Input::Device, Fresco::Controller_ptr);
  virtual ~NonPositionalFocus();

  virtual void grab() {}
  virtual void ungrab() {}
  virtual void set_cursor(Fresco::Raster_ptr) {}
  virtual void add_filter(Fresco::Input::Filter_ptr);

  virtual bool request(Fresco::Controller_ptr);
  virtual void restore(Fresco::Region_ptr) {}
  virtual void damage(Fresco::Region_ptr) {}
  virtual void dispatch(Fresco::Input::Event &);
protected:
  virtual void activate_composite();
private:
  cstack_t      _controllers;
  Prague::Mutex _mutex;
};

#endif 
