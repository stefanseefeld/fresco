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
#include "ShapeOf.hh"

using namespace Fresco;

using namespace Berlin::LayoutKit;

ShapeOf::ShapeOf(Graphic_ptr xx, Graphic_ptr yy, Graphic_ptr zz) :
    my_x(Fresco::Graphic::_duplicate(xx)),
    my_y(Fresco::Graphic::_duplicate(yy)),
    my_z(Fresco::Graphic::_duplicate(zz))
{ }

ShapeOf::~ShapeOf() { }

void ShapeOf::request(Fresco::Graphic::Requisition &r)
{
    if (CORBA::is_nil(my_y) && CORBA::is_nil(my_z)) my_x->request(r);
    else
    {
	Fresco::Graphic::Requisition req;
	GraphicImpl::init_requisition(req);
	if (!CORBA::is_nil(my_x))
	{
	    my_x->request(req);
	    r.x = req.x;
	}
	if (!CORBA::is_nil(my_y))
	{
	    my_y->request(req);
	    r.y = req.y;
	}
	if (CORBA::is_nil(my_z))
	{
	    my_z->request(req);
	    r.z = req.z;
	}
    }
}
