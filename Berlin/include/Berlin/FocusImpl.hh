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
#ifndef _FocusImpl_hh
#define _FocusImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/Focus.hh>
#include <stack>
#include <vector>

class FocusImpl : implements(Focus)
{
  typedef stack<Input::Filter_var> fstack_t;
  typedef vector<size_t> memento_t;
 public:
  FocusImpl(Input::Device dd) : d(dd) {}
  virtual ~FocusImpl() {}
  virtual Input::Device device() { return d;}

  virtual bool request(Controller_ptr) = 0;
  virtual void restore(Region_ptr) = 0;
  virtual void damage(Region_ptr) = 0;
  virtual void dispatch(Input::Event &) = 0;
 private:
  const Input::Device d;
  fstack_t filters;
  memento_t memento;
};

#endif /* _FocusImpl_hh */
