/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#ifndef _Motif_Gauge_hh
#define _Motif_Gauge_hh

#include <Fresco/config.hh>
#include <Fresco/View.hh>
#include <Fresco/BoundedValue.hh>
#include <Berlin/ViewImpl.hh>
#include <Berlin/GraphicImpl.hh>
#include <Berlin/RefCountVar.hh>

namespace Motif
{

class Gauge : public virtual ViewImpl,
	      public GraphicImpl
{
 public:
  Gauge(Fresco::BoundedValue_ptr v, const Fresco::Color &c)
    : value(RefCount_var<Fresco::BoundedValue>::increment(v)), color(c), width(2000.), height(200.) {}
  ~Gauge() {}
  virtual void request(Fresco::Graphic::Requisition &);
  virtual void draw(Fresco::DrawTraversal_ptr);
  virtual void update(const CORBA::Any &);
private:
  RefCount_var<Fresco::BoundedValue> value;
  Fresco::Color color;
  Fresco::Coord width, height;
};

};

#endif
