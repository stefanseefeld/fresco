/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@fresco.org>
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
#ifndef _PrimitiveImpl_hh
#define _PrimitiveImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Primitive.hh>
#include <Fresco/DrawTraversal.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/GraphicImpl.hh>

class TransformImpl;
class RegionImpl;

namespace Berlin
{
  namespace PrimitiveKit
  {

    static bool _error = false;

    class TransformPrimitive : public virtual POA_Primitive::PrimitiveBase,
                               public GraphicImpl
    {
      public:
        TransformPrimitive();
        ~TransformPrimitive();
        virtual Fresco::Transform_ptr transformation();
        virtual void request(Fresco::Graphic::Requisition &);
        virtual void extension(const Fresco::Allocation::Info &, Fresco::Region_ptr);
        virtual void pick(Fresco::PickTraversal_ptr);
        virtual void need_redraw();

        // Figure::Mode type() { return _mode;}
        // void type(Figure::Mode m) { _mode = m; need_redraw();}
        // Fresco::Color foreground() { return _fg;}
        // void foreground(const Fresco::Color &f) { _fg = f; need_redraw();}
        // Fresco::Color background() { return _bg;}
        // void background(const Fresco::Color &b) { _bg = b; need_redraw();}

        virtual void resize();

        void copy(const TransformPrimitive &);
      protected:
        // Figure::Mode            _mode;
        // Fresco::Color           _fg, _bg;
        Impl_var<TransformImpl> _tx;
        Impl_var<RegionImpl>    _ext;
    };

    class PrimitiveImpl : public TransformPrimitive
    {
      public:
        PrimitiveImpl();
        virtual ~PrimitiveImpl();

        void reset();
        virtual void resize();

        virtual void draw(Fresco::DrawTraversal_ptr);
        virtual void pick(Fresco::PickTraversal_ptr);

        void copy(const PrimitiveImpl &);
      protected:
        Fresco::Mesh_var _mesh;
    };

  } // namespace
} // namespace

#endif
