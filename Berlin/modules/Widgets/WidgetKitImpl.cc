/*$Id$
 *
 * This source file is a part of the Berlin Project.
 *
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 *
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
#include "Widget/TextBufferImpl.hh"
#include "Widget/Frame.hh"
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
//   subjects.push_back(constraint);
  return constraint->_this();
}

TelltaleConstraint_ptr WidgetKitImpl::selectionRequired()
{
  SelectionRequired *constraint = new SelectionRequired;
  constraint->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));
//   subjects.push_back(constraint);
  return constraint->_this();
}

Telltale_ptr WidgetKitImpl::normalTelltale()
{
  TelltaleImpl *telltale = new TelltaleImpl(0);
  telltale->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));
  subjects.push_back(telltale);
  return telltale->_this();
}

Telltale_ptr WidgetKitImpl::constrainedTelltale(TelltaleConstraint_ptr constraint)
{
    TelltaleImpl *telltale = new TelltaleImpl(constraint);
    telltale->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));
    subjects.push_back(telltale);
    constraint->add(telltale->_this());
    return telltale->_this();
}

BoundedValue_ptr WidgetKitImpl::bvalue(Coord l, Coord u, Coord v, Coord s, Coord p)
{
  BoundedValueImpl *bounded = new BoundedValueImpl(l, u, v, s, p);
  bounded->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));
  subjects.push_back(bounded);
  return bounded->_this();  
}

BoundedRange_ptr WidgetKitImpl::brange(Coord l, Coord u, Coord lv, Coord uv, Coord s, Coord p)
{
  BoundedRangeImpl *bounded = new BoundedRangeImpl(l, u, lv, uv, s, p);
  bounded->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));
  subjects.push_back(bounded);
  return bounded->_this();  
}

TextBuffer_ptr WidgetKitImpl::text()
{
  TextBufferImpl *buffer = new TextBufferImpl();
  buffer->_obj_is_ready(applyscope(skeletonize(WidgetKit),_boa()));
  subjects.push_back(buffer);
  return buffer->_this();  
}

Graphic_ptr WidgetKitImpl::inset(Graphic_ptr g, const Color &c)
{
  Frame *frame = new Frame(2, c, Frame::concav);
  frame->_obj_is_ready(_boa());
  graphics.push_back(frame);
  frame->body(g);
  return frame->_this();
}

Graphic_ptr WidgetKitImpl::outset(Graphic_ptr g, const Color &c)
{
  Frame *frame = new Frame(2, c, Frame::convex);
  frame->_obj_is_ready(_boa());
  graphics.push_back(frame);
  frame->body(g);
  return frame->_this();
}

View_ptr WidgetKitImpl::pushButtonFrame(Graphic_ptr g, const Color &c, Telltale_ptr t)
{
  DynamicFrame *frame = new DynamicFrame(2, c, Frame::convex, Frame::concav, Telltale::toggle);
  frame->_obj_is_ready(_boa());
  graphics.push_back(frame);
  frame->body(g);
  frame->attach(t);
  return frame->_this();
}

EXPORT_PLUGIN(WidgetKitImpl,interface(WidgetKit))
