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
#ifndef _Berlin_PositionalFocus_hh
#define _Berlin_PositionalFocus_hh

#include <Fresco/config.hh>
#include <Fresco/Controller.hh>
#include <Fresco/Region.hh>
#include <Fresco/Raster.hh>
#include <Berlin/ImplVar.hh>
#include <Prague/Sys/Thread.hh>
#include <Berlin/FocusImpl.hh>
#include <Berlin/Console.hh>
#include <Berlin/ObjectCache.hh>
#include <vector>
#include <stack>

namespace Berlin
{

  class CachingPickTraversal;
  class ScreenImpl;
  class RasterImpl;
  
  class PositionalFocus : public FocusImpl
  {
      typedef std::vector<Fresco::Controller_var> cstack_t;
      class Traversal;
      struct PointerCacheTrait;
      typedef ObjectCache<Fresco::Raster_var, Console::Pointer,
			  PointerCacheTrait> PointerCache;
      struct Resources
      {
	  enum state { set_pointer = 0x1 };
	  Resources() : flags(0) { }
	  unsigned long flags;
	  Console::Pointer *pointer;
      };
      typedef std::stack<Resources> rstack_t;
    public:
      PositionalFocus(Fresco::Input::Device, Fresco::Graphic_ptr,
		      Fresco::Region_ptr);
      virtual ~PositionalFocus();
      virtual void grab();
      virtual void ungrab();
      virtual void set_cursor(Fresco::Raster_ptr);
      virtual void add_filter(Fresco::Input::Filter_ptr);
      
      virtual bool request(Fresco::Controller_ptr);
      virtual void restore(Fresco::Region_ptr);
      virtual void damage(Fresco::Region_ptr);
      virtual void dispatch(Fresco::Input::Event &);
    protected:
      virtual void activate_composite();
    private:
      Fresco::Graphic_ptr my_root;
      RasterImpl         *my_default_raster;
      PointerCache       *my_pointers;
      Console::Pointer   *my_pointer;
      rstack_t            my_resources;
      Traversal          *my_traversal_cache[2];
      Traversal          *my_traversal;
      cstack_t            my_controllers;
      bool                my_grabbed;
      Prague::Mutex       my_mutex;
  };

} // namespace

#endif 
