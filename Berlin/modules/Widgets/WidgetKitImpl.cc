/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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

#include "Widget/WidgetKitImpl.hh"
#include "Widget/TelltaleImpl.hh"
#include "Widget/BoundedValueImpl.hh"
#include "Widget/BoundedRangeImpl.hh"
#include "Berlin/Plugin.hh"

WidgetKitImpl::WidgetKitImpl()
{
}

WidgetKitImpl::~WidgetKitImpl()
{
}

TelltaleConstraint_ptr WidgetKitImpl::exclusive()
{
  ExclusiveChoice *constraint = new ExclusiveChoice();
  constraint->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));
  return constraint->_this();
}

TelltaleConstraint_ptr WidgetKitImpl::selectionRequired()
{
  SelectionRequired *constraint = new SelectionRequired;
  constraint->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));
  return constraint->_this();
}

Telltale_ptr WidgetKitImpl::normalTelltale()
{
  TelltaleImpl *telltale = new TelltaleImpl(0);
  telltale->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));
  return telltale->_this();
}

Telltale_ptr WidgetKitImpl::constrainedTelltale(TelltaleConstraint_ptr constraint)
{
    TelltaleImpl *telltale = new TelltaleImpl(constraint);
    telltale->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));
    constraint->add(telltale->_this());
    return telltale->_this();
}

BoundedValue_ptr WidgetKitImpl::bvalue(Coord l, Coord u, Coord v, Coord s, Coord p)
{
   BoundedValueImpl *bounded = new BoundedValueImpl(l, u, v, s, p);
  bounded->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));

  return bounded->_this();  
}

BoundedRange_ptr WidgetKitImpl::brange(Coord l, Coord u, Coord lv, Coord uv, Coord s, Coord p)
{
  BoundedRangeImpl *bounded = new BoundedRangeImpl(l, u, lv, uv, s, p);
  bounded->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));

  return bounded->_this();  
}


EXPORT_PLUGIN(WidgetKitImpl,interface(WidgetKit))
