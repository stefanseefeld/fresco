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
#ifndef _Glue_hh
#define _Glue_hh

#include <Berlin/GraphicImpl.hh>

namespace Berlin {
namespace LayoutKit {

class Glue : public GraphicImpl
{
public:
  Glue(Fresco::Axis, Fresco::Coord, Fresco::Coord, Fresco::Coord, Fresco::Alignment);
  Glue(const Fresco::Graphic::Requisition &);
  virtual ~Glue();

  virtual void request(Fresco::Graphic::Requisition &);

  virtual const char *object_name() { return "Layout/Glue";}
private:
  Fresco::Graphic::Requisition _requisition;
};

} // namespace
} // namespace

#endif
