/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _Warsaw_IO_hh
#define _Warsaw_IO_hh

#include <Warsaw/Graphic.hh>
#include <Warsaw/Region.hh>
#include <Warsaw/Transform.hh>
#include <iostream>

inline ostream &operator << (ostream &os, const Warsaw::Vertex &v) { return os << '(' << v.x << ',' << v.y << ',' << v.z << ')';}
ostream &operator << (ostream &, const Warsaw::Color &);
ostream &operator << (ostream &, const Warsaw::Graphic::Requirement &);
ostream &operator << (ostream &, const Warsaw::Graphic::Requisition &);
ostream &operator << (ostream &, const Warsaw::Region::Allotment &);
ostream &operator << (ostream &, Warsaw::Region_ptr);
ostream &operator << (ostream &, const Warsaw::Transform::Matrix &);
ostream &operator << (ostream &, Warsaw::Transform_ptr);

#endif
