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
#ifndef _Berlin_AllocationImpl_hh
#define _Berlin_AllocationImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Graphic.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/ServantBase.hh>
#include <Berlin/Provider.hh>
#include <vector>

namespace Berlin
{

  class RegionImpl;
  class TransformImpl;
  class AllocationImpl;
  
  template <> struct Initializer<AllocationImpl>;
  
  class AllocationImpl : public virtual POA_Fresco::Allocation,
             public virtual ServantBase
  {
      struct State
      {
      RegionImpl        *allocation;
      TransformImpl     *transformation;
      Fresco::Screen_var root;
      };
      typedef std::vector<State> list_t;
      friend class Provider<AllocationImpl>;
    public:
      AllocationImpl();
      ~AllocationImpl();
      void add(Fresco::Region_ptr, Fresco::Screen_ptr);
      CORBA::Long size();
      Fresco::Allocation::Info *get(CORBA::Long);
      void clear();
    private:
      bool my_active : 1;
      list_t my_list;
  };
  
  template <> struct Initializer<AllocationImpl>
  {
      static void initialize(AllocationImpl *a) { a->clear();}
  };

} // namespace

#endif 
