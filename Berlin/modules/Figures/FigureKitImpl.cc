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

#include "Warsaw/config.hh"
#include "Figure/FigureKitImpl.hh"
#include "Berlin/Plugin.hh"

FigureKitImpl::FigureKitImpl() {}
FigureKitImpl::~FigureKitImpl() {}

Graphic_ptr FigureKitImpl::rect(BoundedValue_ptr width, BoundedValue_ptr height) {
    Rect *rect = new Rect(width, height);
    rect->_obj_is_ready(applyscope(skeletonize(FigureKit), _boa()));
    rect->init();
    rects.push_back(rect);
    return rect->_this();
}

Graphic_ptr FigureKitImpl::ellipse(BoundedValue_ptr width, BoundedValue_ptr height) {
    Rect *rect = new Rect(width, height);
    rect->_obj_is_ready(applyscope(skeletonize(FigureKit), _boa()));
    rect->init();
    rects.push_back(rect);
    return rect->_this();
}

EXPORT_PLUGIN(FigureKitImpl, interface(FigureKit))
