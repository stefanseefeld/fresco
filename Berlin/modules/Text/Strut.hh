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
#ifndef _TextKit_Strut_hh
#define _TextKit_Strut_hh

#include <Berlin/GraphicImpl.hh>

namespace Berlin
{
  namespace TextKit
  {

    class Strut : public GraphicImpl
    {
      public:
    Strut(const Fresco::Graphic::Requisition &r) : my_requisition(r)
    { }
    virtual void request(Fresco::Graphic::Requisition &r)
    { r = my_requisition;}
      private:
    Fresco::Graphic::Requisition my_requisition;
    };

  } // namespace
} // namespace

#endif
