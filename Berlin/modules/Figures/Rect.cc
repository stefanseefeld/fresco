/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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


#include "Figure/Rect.hh"
#include "Warsaw/DrawingKit.hh"
#include "Warsaw/Traversal.hh"
#include "Warsaw/Pencil.hh"

void Rect::request(Requisition &r)
{
    r.x.defined = true;
    r.x.maximum = r.x.minimum = r.x.natural = myWidth->value();
    r.x.align = 0.;
    r.y.defined = true;
    r.y.maximum = r.y.minimum = r.y.natural = myHeight->value();
    r.y.align = 0.;
}

void Rect::draw(DrawTraversal_ptr dt) {

    DrawingKit_ptr dp = dt->kit();
    Pencil_ptr p = dp->solidPen();

    Vertex p1, p2, p3, p4;
    p1.x = 0; 
    p1.y = 0; 
    p1.z = 0.;
    p2.x = myWidth->value();
    p2.y = 0;
    p2.z = 0.;
    p3.x = myWidth->value();
    p3.y = myHeight->value();
    p3.z = 0.;
    p4.x = 0;
    p4.y = myHeight->value();
    p4.z = 0.;
    
    p->drawLine(p1, p2);
    p->drawLine(p2, p3);
    p->drawLine(p3, p4);
    p->drawLine(p4, p1);
}

Rect::Rect(BoundedValue_ptr width, BoundedValue_ptr height) {
    myWidth = BoundedValue::_duplicate(width);
    myHeight = BoundedValue::_duplicate(myHeight);
}

Rect::~Rect() {}
