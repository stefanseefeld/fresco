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

void Rect::update(Subject_ptr p) {
    if (myWidth->_is_equivalent(p) || myHeight->_is_equivalent(p)) this->needRedraw();
}

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

//     Vertex p1, p2, p3, p4;
//     p1.x = 0; 
//     p1.y = 0; 
//     p1.z = 0.;
//     p2.x = myWidth->value();
//     p2.y = 0;
//     p2.z = 0.;
//     p3.x = myWidth->value();
//     p3.y = myHeight->value();
//     p3.z = 0.;
//     p4.x = 0;
//     p4.y = myHeight->value();
//     p4.z = 0.;
    
    Path path;
    path.p.length(4);
    
    RegionImpl region(dt->allocation(), dt->transformation());

    path.p[0].x = region.lower.x, path.p[0].y = region.lower.y, path.p[0].z = 0;
    path.p[1].x = region.upper.x, path.p[1].y = region.lower.y, path.p[1].z = 0;
    path.p[2].x = region.upper.x, path.p[2].y = region.upper.y, path.p[1].z = 0;
    path.p[3].x = region.lower.x, path.p[3].y = region.upper.y, path.p[1].z = 0;
    p->fillPath(path);    
}

// this method has to happen in a non-ctor method because (surprise!)
// you can't get a corba reference to yourself while you're still
// being constructed and have yet to be registered with the boa.
void Rect::init() {
    myWidth->attach(this->_this());
    myHeight->attach(this->_this());
}

Rect::Rect(BoundedValue_ptr width, BoundedValue_ptr height) {
    myWidth = BoundedValue::_duplicate(width);
    myHeight = BoundedValue::_duplicate(height);
}

Rect::~Rect() {}
