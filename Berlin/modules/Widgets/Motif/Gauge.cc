/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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

#include <Fresco/config.hh>
#include <Fresco/DrawTraversal.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/Transform.hh>
#include <Berlin/Color.hh>
#include "Gauge.hh"

using namespace Fresco;

using namespace Berlin::WidgetKit::Motif;

void Gauge::request(Fresco::Graphic::Requisition &requisition)
{
  requisition.x.defined = true;
  requisition.x.natural = requisition.x.maximum = requisition.x.minimum = width;
  requisition.x.align = 0.;
  requisition.y.defined = true;
  requisition.y.natural = requisition.y.maximum = requisition.y.minimum = height;
  requisition.y.align = 0.;
}

void Gauge::draw(DrawTraversal_ptr traversal)
{
  DrawingKit_var drawing = traversal->drawing();
  drawing->save();
  Coord l = value->lower();
  Coord u = value->upper();
  Coord v = value->value();
  Path path;
  path.shape = convex;
  path.nodes.length(5);
  path.nodes[0].x = path.nodes[0].y = path.nodes[0].z = 0;
  path.nodes[2].x = width, path.nodes[2].y = height, path.nodes[2].z = 0;
  path.nodes[1].x = path.nodes[2].x, path.nodes[1].y = path.nodes[0].y, path.nodes[1].z = 0.;
  path.nodes[3].x = path.nodes[0].x, path.nodes[3].y = path.nodes[2].y, path.nodes[3].z = 0.;
  path.nodes[4] = path.nodes[0];
//   Transform_var transform = traversal->transformation();
//   for (unsigned int i = 0; i != path.p.length(); i++) transform->transformVertex(path.p[i]);
  drawing->surface_fillstyle(DrawingKit::solid);
  drawing->foreground(brightness(color, -0.2));
  drawing->draw_path(path);
  path.nodes[0].x = path.nodes[0].y = path.nodes[0].z = 0;
  path.nodes[2].x = v/(u-l)*width, path.nodes[2].y = height, path.nodes[2].z = 0;
  path.nodes[1].x = path.nodes[2].x, path.nodes[1].y = path.nodes[0].y, path.nodes[1].z = 0.;
  path.nodes[3].x = path.nodes[0].x, path.nodes[3].y = path.nodes[2].y, path.nodes[3].z = 0.;
  path.nodes[4] = path.nodes[0];
//   for (unsigned int i = 0; i != path.p.length(); i++) transform->transformVertex(path.p[i]);
  drawing->foreground(brightness(color, -0.7));
  drawing->draw_path(path);  
  drawing->restore();
}

void Gauge::update(const CORBA::Any &)
{
  need_redraw();
}
