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
#ifndef _Berlin_PolyGraphic_hh
#define _Berlin_PolyGraphic_hh

#include <Berlin/GraphicImpl.hh>
#include <Berlin/Pool.hh>
#include <vector>

namespace Berlin
{

  class PolyGraphic : public GraphicImpl
  {
      class Iterator;
      friend class Iterator;
    public:
      PolyGraphic();
      virtual ~PolyGraphic();
      
      virtual void append_graphic(Fresco::Graphic_ptr);
      virtual void prepend_graphic(Fresco::Graphic_ptr);
      virtual void remove_graphic(Fresco::Tag);
      virtual void remove_child_graphic(Fresco::Tag);
      virtual Fresco::GraphicIterator_ptr first_child_graphic();
      virtual Fresco::GraphicIterator_ptr last_child_graphic();
      
      virtual void need_resize();
      virtual void need_resize(Fresco::Tag);
    protected:
      CORBA::ULong num_children();
      Fresco::Tag unique_child_id();
      glist_t::iterator child_id_to_iterator(Fresco::Tag);
      CORBA::Long child_id_to_index(Fresco::Tag);
      Fresco::Graphic::Requisition *children_requests();
      void deallocate_requisitions(Fresco::Graphic::Requisition *);
      void child_extension(size_t, const Fresco::Allocation::Info &,
               Fresco::Region_ptr);
// private:
      static Pool<Fresco::Graphic::Requisition> my_pool;
      glist_t my_children;
      Prague::Mutex my_mutex;
  };

/*
 * the following methods are inlined for speed.
 * Attention : they must be used within a PolyGraphic::childMutex locked
 * section!
 */
  inline Fresco::Tag PolyGraphic::unique_child_id()
  {
      Fresco::Tag localId;
      for (localId = 0;
       find_if(my_children.begin(), my_children.end(),
           localId_eq(localId)) != my_children.end();
       localId++);
      return localId;
  }
  
  inline PolyGraphic::glist_t::iterator
  PolyGraphic::child_id_to_iterator(Fresco::Tag localId)
  {
      return find_if(my_children.begin(), my_children.end(),
             localId_eq(localId));
  }

  inline CORBA::Long PolyGraphic::child_id_to_index(Fresco::Tag localId)
  {
      return find_if(my_children.begin(), my_children.end(),
             localId_eq(localId)) - my_children.begin();
  }
  
} // namespace

#endif 
