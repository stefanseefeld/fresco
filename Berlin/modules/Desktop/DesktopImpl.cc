/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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

#include "Desktop/DesktopImpl.hh"
#include "Desktop/WindowImpl.hh"
#include "Berlin/Vertex.hh"
#include "Berlin/Logger.hh"

DesktopImpl::DesktopImpl()
{
}

DesktopImpl::~DesktopImpl()
{
}

void DesktopImpl::init(Stage_ptr s)
{
  stage = Stage::_duplicate(s);
  ControllerImpl::body(stage);
}

DesktopImpl::Info DesktopImpl::insert(WindowImpl *window, const Vertex &position, const Vertex &size, Index index)
{
  windows.push_back(window);
  stage->begin();
  Info info = stage->insert(Graphic_var(window->_this()), position, size, index);
  stage->end();
  return info;
}

void DesktopImpl::erase(WindowImpl *window)
{
  cerr << "DesktopImpl::erase : not implemented" << endl;
}

void DesktopImpl::reposition(const Info &info, const Vertex &position)
{
  stage->begin();
  stage->reposition(info, position);
  stage->end();
}

void DesktopImpl::relayer(const Info &info, Stage::Index index)
{
  stage->relayer(info, index);
}

