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
#ifndef _Berlin_Requestor_hh
#define _Berlin_Requestor_hh

#include <Berlin/MonoGraphic.hh>

namespace Berlin
{

  class Requestor : public MonoGraphic
  {
    public:
      Requestor(Fresco::Alignment xalign = .5,
        Fresco::Alignment yalign = .5,
        Fresco::Coord xspan = 1,
        Fresco::Coord yspan = 1);
      Requestor(const Fresco::Graphic::Requisition &);
      ~Requestor();
      
      virtual void request(Fresco::Graphic::Requisition &);
    protected:
      Fresco::Graphic::Requisition my_requisition;
  };

} // namespace

#endif 
