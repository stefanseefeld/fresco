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
#ifndef _Layout_Box_hh
#define _Layout_Box_hh

#include <Berlin/PolyGraphic.hh>
#include "LayoutManager.hh"

namespace Berlin
{
  namespace LayoutKit
  {

    class Box : public PolyGraphic
    {
      public:
        Box(LayoutManager *);
        virtual ~Box();

        virtual void request(Fresco::Graphic::Requisition &);
        virtual void extension(const Fresco::Allocation::Info &,
			       Fresco::Region_ptr);

        virtual void traverse(Fresco::Traversal_ptr);
        virtual void need_resize();
        virtual void need_resize(Fresco::Tag);
        virtual void allocate(Fresco::Tag,
			      const Fresco::Allocation::Info &);

        virtual const char* object_name() { return my_obj_name; }

      protected:
        LayoutManager::Allocations
	children_allocations(Fresco::Region_ptr);
        void traverse_with_allocation(Fresco::Traversal_ptr,
				      Fresco::Region_ptr);
        void traverse_without_allocation(Fresco::Traversal_ptr);

        //. The fixed class name of this object, used for constructing
	//. name strings
        const char *my_box_name;
        //. The changing object name. Note that this is allocated as a
	//. buffer and strcpy'd into, since it may change over the course
	//. of a method but cannot be deleted in the scope of a Trace guard
	//. object
        char *my_obj_name;
      private:
        LayoutManager               *my_layout;
        bool                         my_requested;
        Fresco::Graphic::Requisition my_requisition;

        //. The size of the allocation cache
        CORBA::Long                  my_cache_size;
        //. A cache of children allocations to speed traversals
        LayoutManager::Allocations   my_cache_allocations;
    };
    
    class BoxAlignElements : public Box
    {
      public:
        BoxAlignElements(LayoutManager *, Fresco::Axis, Fresco::Alignment);
        virtual ~BoxAlignElements();

        virtual void append_graphic(Fresco::Graphic_ptr);
        virtual void prepend_graphic(Fresco::Graphic_ptr);
      private:
        Fresco::Axis my_axis;
        Fresco::Alignment my_alignment;
    };

    class HBox : public Box
    {
      public:
        HBox() :
            Box(new LayoutSuperpose(new LayoutTile(Fresco::xaxis),
                                    new LayoutAlign(Fresco::yaxis),
                                    new LayoutAlign(Fresco::zaxis)))
        { }
    };

    class VBox : public Box
    {
      public:
        VBox() :
            Box(new LayoutSuperpose(new LayoutTile(Fresco::yaxis),
                                    new LayoutAlign(Fresco::xaxis),
                                    new LayoutAlign(Fresco::zaxis)))
        { }
    };

    class HBoxFirstAligned : public Box
    {
      public:
        HBoxFirstAligned() :
            Box(new LayoutSuperpose(new LayoutTileFirstAligned(Fresco::xaxis),
                                    new LayoutAlign(Fresco::yaxis)))
        { }
    };

    class VBoxFirstAligned : public Box
    {
      public:
        VBoxFirstAligned() :
            Box(new LayoutSuperpose(new LayoutTileReversedFirstAligned(Fresco::yaxis),
                                    new LayoutAlign(Fresco::xaxis)))
        { }
    };

    class HBoxAlignElements : public BoxAlignElements
    {
      public:
        HBoxAlignElements(double align) :
            BoxAlignElements(new LayoutSuperpose(new LayoutTile(Fresco::xaxis),
                            new LayoutAlign(Fresco::yaxis)), Fresco::yaxis, align)
        { }
    };

    class VBoxAlignElements : public BoxAlignElements
    {
      public:
        VBoxAlignElements(double align) :
            BoxAlignElements(new LayoutSuperpose(new LayoutTile(Fresco::yaxis),
                            new LayoutAlign(Fresco::xaxis)), Fresco::xaxis, align)
        { }
    };

    class Overlay : public Box
    {
      public:
        Overlay() :
            Box(new LayoutSuperpose(new LayoutAlign(Fresco::xaxis),
                                    new LayoutAlign(Fresco::yaxis)))
        { }
    };

  } // namespace
} // namespace

#endif
