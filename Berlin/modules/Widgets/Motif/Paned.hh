/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _Motif_Paned_hh
#define _Motif_Paned_hh

#include <Warsaw/config.hh>
#include <Warsaw/Widget.hh>
#include <Warsaw/BoundedValue.hh>
#include <Berlin/ControllerImpl.hh>

namespace Motif
{
  class Paned : public virtual POA_Widget::Paned,
		public GraphicImpl
  {
    class Adjustment;
  public:
    Paned(Warsaw::Axis, Warsaw::Alignment);
    ~Paned();
    void init(Warsaw::Graphic_ptr, Warsaw::Graphic_ptr);
//     virtual void resize_policy(Warsaw::Alignment a) { _alignment = a;}
    virtual Warsaw::Alignment resize_policy() { return _alignment;}
    virtual Warsaw::BoundedValue_ptr adjustment();
    virtual void traverse(Warsaw::Traversal_ptr);
    virtual void allocate(Warsaw::Tag, const Warsaw::Allocation::Info &);
  private:
    const Warsaw::Axis _axis;
    Warsaw::Alignment  _alignment;
    Adjustment        *_adjustment;
  };
};

#endif
