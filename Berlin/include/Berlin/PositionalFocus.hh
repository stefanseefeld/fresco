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
#ifndef _PositionalFocus_hh
#define _PositionalFocus_hh

#include <Warsaw/config.hh>
#include <Warsaw/Controller.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/Raster.hh>
#include <Berlin/ImplVar.hh>
#include <Prague/Sys/Thread.hh>
#include <Berlin/FocusImpl.hh>
#include <Berlin/Console.hh>
#include <Berlin/ObjectCache.hh>
#include <vector>
#include <stack>

class CachingPickTraversal;
class ScreenImpl;
class RasterImpl;

class PositionalFocus : public FocusImpl
{
  typedef std::vector<Warsaw::Controller_var> cstack_t;
  class Traversal;
  struct PointerCacheTrait;
  typedef ObjectCache<Warsaw::Raster_var, Console::Pointer, PointerCacheTrait> PointerCache;
  struct Resources
  {
    enum state { set_pointer = 0x1};
    Resources() : flags(0) {}
    unsigned long     flags;
    Console::Pointer *pointer;

  };
  typedef std::stack<Resources> rstack_t;
public:
  PositionalFocus(Warsaw::Input::Device, Warsaw::Graphic_ptr, Warsaw::Region_ptr);
  virtual ~PositionalFocus();
  virtual void grab();
  virtual void ungrab();
  virtual void set_cursor(Warsaw::Raster_ptr);
  virtual void add_filter(Warsaw::Input::Filter_ptr);

  virtual bool request(Warsaw::Controller_ptr);
  virtual void restore(Warsaw::Region_ptr);
  virtual void damage(Warsaw::Region_ptr);
  virtual void dispatch(Warsaw::Input::Event &);
protected:
  virtual void activate_composite();
private:
  Warsaw::Graphic_ptr _root;
  RasterImpl         *_default_raster;
  PointerCache       *_pointers;
  Console::Pointer   *_pointer;
  rstack_t            _resources;
  Traversal          *_traversal_cache[2];
  Traversal          *_traversal;
  cstack_t            _controllers;
  bool                _grabbed;
  Prague::Mutex       _mutex;
};

#endif 
