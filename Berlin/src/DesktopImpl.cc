/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Berlin/DesktopImpl.hh"
#include "Berlin/Vertex.hh"
#include "Berlin/Logger.hh"
#include <Warsaw/DrawTraversal.hh>
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/Transform.hh>
#include <Warsaw/Region.hh>

using namespace Warsaw;

DesktopImpl::DesktopImpl(Stage_ptr s)
  : ControllerImpl(false), stage(Warsaw::Stage::_duplicate(s))
{
  /*
   * Attention !!: this invokes _this(), which implicitely activates the desktop.
   */
  ControllerImpl::body(stage);
}
DesktopImpl::~DesktopImpl() {}
// void DesktopImpl::draw(DrawTraversal_ptr traversal)
// {  
//   Region_var allocation = traversal->allocation();
//   Vertex upper, lower;
//   allocation->bounds(lower, upper);
//   DrawingKit_var drawing = traversal->kit();
//   drawing->saveState();
//   Color background;
//   background.red = 1.0;
//   background.green = 0.9;
//   background.blue = 0.8;
//   background.alpha = 1.0;
//   drawing->foreground(background);
//   drawing->drawRect(lower, upper);
//   drawing->restoreState();
//   MonoGraphic::traverse(traversal);
// }

Warsaw::StageHandle_ptr DesktopImpl::insert(Warsaw::Graphic_ptr g, const Warsaw::Vertex &p, const Warsaw::Vertex &s, Warsaw::Stage::Index l)
{
  return stage->insert(g, p, s, l);
}
