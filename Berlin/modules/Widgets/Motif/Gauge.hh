/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _Motif_Gauge_hh
#define _Motif_Gauge_hh

#include <Warsaw/config.hh>
#include <Warsaw/View.hh>
#include <Warsaw/BoundedValue.hh>
#include <Berlin/GraphicImpl.hh>

namespace Motif
{

class Gauge : public virtual POA_View, public GraphicImpl
{
 public:
  Gauge(BoundedValue_ptr v, const Color &c) : value(BoundedValue::_duplicate(v)), color(c), width(2000.), height(200.) {}
  ~Gauge() {}
  virtual void request(Requisition &);
  virtual void draw(DrawTraversal_ptr);
  virtual void update(const CORBA::Any &);
private:
  BoundedValue_var value;
  Color color;
  Coord width, height;
};

};

#endif /* _Motif_Gauge_hh */
