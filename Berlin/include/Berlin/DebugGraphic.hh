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
#ifndef _Berlin_DebugGraphic_hh
#define _Berlin_DebugGraphic_hh

#include <Berlin/MonoGraphic.hh>
#include <iostream>
#include <string>

namespace Berlin
{

  class DebugGraphic : public MonoGraphic
  {
    public:
      enum Flags
      {
      none = 0x0,
      requests = 0x1,
      draws = 0x2,
      picks = 0x4,
      traversals = 0x7
      };
      DebugGraphic(std::ostream &, const std::string &,
           unsigned int f = traversals);
      virtual ~DebugGraphic();
      
      virtual void request(Fresco::Graphic::Requisition &);
      virtual void traverse(Fresco::Traversal_ptr);
      virtual void draw(Fresco::DrawTraversal_ptr);
      virtual void pick(Fresco::PickTraversal_ptr);
      virtual void allocate(Fresco::Tag, const Fresco::Allocation::Info &);
    private:
      void         heading(const char *);
      std::ostream &my_os;
      std::string   my_message;
      unsigned int  my_flags;
  };

} // namespace

#endif 
