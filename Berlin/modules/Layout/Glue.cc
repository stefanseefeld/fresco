/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * this code is based on code from Fresco.
 * Copyright (c) 1987-91 Stanford University
 * Copyright (c) 1991-94 Silicon Graphics, Inc.
 * Copyright (c) 1993-94 Fujitsu, Ltd.
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
#include "Layout/Glue.hh"

Glue::Glue(Axis a, Coord natural, Coord stretch, Coord shrink, Alignment align)
{
  GraphicImpl::initRequisition(requisition);
  Graphic::Requirement *r = GraphicImpl::requirement(requisition, a);
  if (r != 0) GraphicImpl::require(*r, natural, stretch, shrink, align);
}

Glue::Glue(const Graphic::Requisition &r) { requisition = r;}
Glue::~Glue() {}
Graphic_ptr Glue::cloneGraphic () { return new Glue(requisition);}
void Glue::request(Requisition &r) { r = requisition;}

