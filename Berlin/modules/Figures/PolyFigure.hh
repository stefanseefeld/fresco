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
#ifndef _PolyFigure_hh
#define _PolyFigure_hh

#include <Fresco/config.hh>
#include <Fresco/Figure.hh>
#include <Berlin/ImplVar.hh>
#include <Berlin/PolyGraphic.hh>

class TransformImpl;

class PolyFigure : public virtual POA_Figure::FigureBase,
		   public PolyGraphic
{
public:
    PolyFigure();
    PolyFigure(const PolyFigure &);
    virtual ~PolyFigure();

    virtual void request(Fresco::Graphic::Requisition &);
    virtual void extension(const Fresco::Allocation::Info &, Fresco::Region_ptr);
    virtual void traverse(Fresco::Traversal_ptr);
    virtual Fresco::Transform_ptr transformation();
    virtual void need_redraw();
    virtual void need_resize();
    virtual void allocate(Fresco::Tag, const Fresco::Allocation::Info &);

    /*
     * shameless hack !!!: eventually these settings are dealt with
     *                     by styles so PolyFigures simply ignore it...
     *                     -stefan
     */
    Figure::Mode type() { return 0;}
    void type(Figure::Mode) {}
    Fresco::Color foreground() { return Fresco::Color();}
    void foreground(const Fresco::Color &) {}
    Fresco::Color background() { return Fresco::Color();}
    void background(const Fresco::Color &) {}
    virtual void resize() {}

protected:
    void update_bbox();
    Impl_var<TransformImpl> _tx;
    Impl_var<RegionImpl>    _bbox;
};

class UPolyFigure : public PolyFigure
{
public:
  UPolyFigure() {}
  UPolyFigure(const UPolyFigure &);
  virtual void traverse(Fresco::Traversal_ptr);
};

#endif
