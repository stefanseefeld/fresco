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
#include "Berlin/Requestor.hh"

using namespace Fresco;
using namespace Berlin;

Requestor::Requestor(Alignment xalign, Alignment yalign,
             Coord xspan, Coord yspan)
{
    GraphicImpl::default_requisition(my_requisition);
    Fresco::Graphic::Requirement *rx =
    GraphicImpl::requirement(my_requisition, xaxis);
    Fresco::Graphic::Requirement *ry =
    GraphicImpl::requirement(my_requisition, yaxis);
    rx->align = xalign;
    ry->align = yalign;
    rx->natural = rx->maximum = rx->minimum = xspan;
    ry->natural = ry->maximum = ry->minimum = yspan; 
}

Requestor::Requestor(const Fresco::Graphic::Requisition &r) :
    my_requisition(r)
{ }
Requestor::~Requestor() { }
void Requestor::request(Fresco::Graphic::Requisition &r)
{ r = my_requisition; }
