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
#ifndef _Berlin_Vertex_hh
#define _Berlin_Vertex_hh

#include <Fresco/config.hh>
#include <Fresco/Types.hh>
#include <iostream>

inline Fresco::Vertex &operator += (Fresco::Vertex &p,
				    const Fresco::Vertex &q)
{
    p.x += q.x;
    p.y += q.y;
    p.z += q.z;
    return p;
}

inline Fresco::Vertex &operator -= (Fresco::Vertex &p,
				    const Fresco::Vertex &q)
{
    p.x -= q.x;
    p.y -= q.y;
    p.z -= q.z;
    return p;
}

inline Fresco::Vertex operator + (const Fresco::Vertex &p,
				  const Fresco::Vertex &q)
{
    Fresco::Vertex r;
    r.x = p.x + q.x;
    r.y = p.y + q.y;
    r.z = p.z + q.z;
    return r;
}

inline Fresco::Vertex operator - (const Fresco::Vertex &p,
				  const Fresco::Vertex &q)
{
    Fresco::Vertex r;
    r.x = p.x - q.x;
    r.y = p.y - q.y;
    r.z = p.z - q.z;
    return r;
}

#endif
