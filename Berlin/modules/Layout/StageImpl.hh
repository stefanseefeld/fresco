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
#ifndef _LayoutKit_StageImpl_hh
#define _LayoutKit_StageImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/Stage.hh>
#include <Fresco/Traversal.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/RegionImpl.hh>
#include <Berlin/Geometry.hh>

namespace Berlin
{
  namespace LayoutKit
  {

    class StageHandleImpl;

    class StageImpl : public virtual POA_Layout::Stage,
                      public GraphicImpl
    {
        class Iterator;
        friend class Iterator;

        class Sequence;
        class QuadTree;
      public:
        StageImpl();
        ~StageImpl();

        Fresco::GraphicIterator_ptr first_child_graphic();
        Fresco::GraphicIterator_ptr last_child_graphic();

        virtual void request(Fresco::Graphic::Requisition &);

        virtual void traverse(Fresco::Traversal_ptr);

        virtual void allocate(Fresco::Tag, const Fresco::Allocation::Info &);
        virtual void need_redraw();
        virtual void need_redraw_region(Fresco::Region_ptr);
        //. relayout the children. If the bounding box changes call
        //. need_resize on the parent
        virtual void need_resize();

        virtual Fresco::Region_ptr bbox();
        virtual CORBA::Long layers();
        virtual Layout::StageHandle_ptr layer(Layout::Stage::Index);
        virtual void lock();
        virtual void unlock();
        virtual Layout::StageHandle_ptr insert(Fresco::Graphic_ptr,
                                               const Fresco::Vertex &,
                                               const Fresco::Vertex &,
                                               Layout::Stage::Index);
        virtual void remove(Layout::StageHandle_ptr);

        void move(StageHandleImpl *, const Fresco::Vertex &);
        void resize(StageHandleImpl *, const Fresco::Vertex &);
        void relayer(StageHandleImpl *, Layout::Stage::Index);

        virtual const char *object_name() { return "Layout/StageImpl";}
      private:
        //. Return a new unique tag in the scope of this parent
        Fresco::Tag unique_tag();
        //. Return a handle to the child of the Stage that has the given
    //. tag. It returns 0 if no child has the given tag.
        StageHandleImpl *tag_to_handle(Fresco::Tag);
        //. Mark the region occupied by the given StageHandle as damaged.
        //. This is done by either merging that region with the one already
        //. damaged or by creating a new onw
        void damage(StageHandleImpl *);

        Sequence            *my_children;
        QuadTree            *my_tree;
        long                 my_nesting;
        Impl_var<RegionImpl> my_damage;
        Impl_var<RegionImpl> my_bbregion;
        bool                 my_need_redraw : 1;
        bool                 my_need_resize : 1;
        Prague::Mutex        my_mutex;
    };

    class StageHandleImpl : public virtual POA_Layout::StageHandle
    {
      public:
        StageHandleImpl(StageImpl *, Fresco::Graphic_ptr, Fresco::Tag,
                        const Fresco::Vertex &, const Fresco::Vertex &,
                        Layout::Stage::Index);
        virtual Layout::Stage_ptr parent();
        virtual Fresco::Graphic_ptr child();
        virtual void remove();
        virtual Fresco::Vertex position();
        virtual void position(const Fresco::Vertex &);
        virtual Fresco::Vertex size();
        virtual void size(const Fresco::Vertex &);
        virtual Layout::Stage::Index layer();
        virtual void layer(Layout::Stage::Index);

        const Geometry::Rectangle<Fresco::Coord> &bbox();
        void bbox(RegionImpl &);
      // private:
    // FIXME: These variables should be private!

        //. Calculate the bounding box of the graphic in this StageHandle
    //. and stores the result in _bbox.
        void cache_bbox();
        //. The stage this StageHandle belongs into.
        StageImpl                         *my_parent;
        //. The graphic forming this StageHandle.
        Fresco::Graphic_var                my_child;
        //. This tag is unique for the parent-Stage and identifies this
    //. StageHandle.
        Fresco::Tag                        my_tag;
        //. The position of the graphic forming this StageHandle.
        Fresco::Vertex                     my_position;
        //. The size of the graphic forming this StageHandle
        Fresco::Vertex                     my_size;
        //. The bounding box of the graphic of this StageHandle as
    //. calculated by cache_bbox().
        Geometry::Rectangle<Fresco::Coord> my_bbox;
        //. The alignment along the x-axis.
        Fresco::Alignment                  my_xalign;
        //. The alignment along the y-axis.
        Fresco::Alignment                  my_yalign;
        //. A mutex for thread safety.
        Prague::Mutex                      my_mutex;
    //. The layer this StageHandle has.
        Layout::Stage::Index               my_layer;
    };

  } // namespace
} // namespace

#endif
