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

#include "LogoDemo.hh"
#include "Warsaw/config.hh"
#include "Warsaw/Command.hh"
#include "Warsaw/Desktop.hh"

Rotator::Rotator(BoundedValue_ptr v, Graphic_ptr c, Graphic_ptr p, Coord d)
  : value(BoundedValue::_duplicate(v)),
    child(Graphic::_duplicate(c)),
    parent(Graphic::_duplicate(p)),
    zdegree(d)
{
  CORBA::Any dummy;
  update(dummy);
}

void Rotator::update(const CORBA::Any &)
{
  Coord ydegree = value->value();
  Transform_var tx = child->transformation();
  tx->loadIdentity();
  tx->rotate(ydegree, yaxis);
  tx->rotate(zdegree, zaxis);
  parent->needRedraw();
}

LogoDemo::LogoDemo(Application *a)
  : Demo(a),
    tx1(new TransformImpl),
    tx2(new TransformImpl),
    tx3(new TransformImpl)
{
  LayoutKit_var layout = application->layout();
  ToolKit_var   tool = application->tool();
  WidgetKit_var widget = application->widget();
  FigureKit_var figure = application->figure();
  CommandKit_var command = application->command();
  
  bv1 = command->bvalue(0., 360., 0., 5., 5.);
  bv2 = command->bvalue(0., 360., 0., 5., 5.);
  bv3 = command->bvalue(0., 360., 0., 5., 5.);
  
  tx1->rotate(10., zaxis);
  tx2->rotate(-10., zaxis);
  tx3->rotate(-20., zaxis);
  
  Coord a = 2000.;
  Vertex offset;
  offset.x = -a/2., offset.y = -3./2.*a, offset.z = 0.;
  Figure::Vertices path; path.length(4);
  path[0].x = a/2 + offset.x, path[0].y = + offset.y, path[0].z = offset.z;
  path[1].x = a + offset.x, path[1].y = 0.866*a + offset.y, path[1].z = offset.z;
  path[2].x = offset.x, path[2].y = 0.866*a + offset.y, path[2].z = offset.z;
  path[3].x = a/2 + offset.x, path[3].y = + offset.y, path[3].z = offset.z;

  
  Color red = {1.0, 0.5, 0.5, 0.5};
  Color green = {0.5, 1.0, 0.5, 0.5};
  Color blue = {0.5, 0.5, 1.0, 0.5};
//   Color white = {1.0, 1.0, 1.0, 1.0};
  
  Figures::Path_var triangle1 = figure->polygon(path);
  triangle1->type(Figure::fill);
  triangle1->background(green);
  Figures::Path_var triangle2 = figure->polygon(path);
  triangle2->type(Figure::fill);
  triangle2->background(blue);
  Figures::Path_var triangle3 = figure->polygon(path);
  triangle3->type(Figure::fill);
  triangle3->background(red);
  Graphic_var transformer1 = figure->transformer(triangle1);
  Graphic_var transformer2 = figure->transformer(triangle2);
  Graphic_var transformer3 = figure->transformer(triangle3);
  
  Graphic_var group = figure->group();
  
  rotator1 = new Rotator(bv1, transformer1, group, 20.);
  bv1->attach(Observer_var(rotator1->_this()));
  rotator2 = new Rotator(bv2, transformer2, group, 10.);
  bv2->attach(Observer_var(rotator2->_this()));
  rotator3 = new Rotator(bv3, transformer3, group, -10.);
  bv3->attach(Observer_var(rotator3->_this()));
  
  Graphic_var root = figure->root(group);
  group->append(transformer1);
  group->append(transformer2);
  group->append(transformer3);
  
  Graphic_var hbox1 = layout->hbox();
  hbox1->append(Graphic_var(layout->hfil()));
  hbox1->append(Graphic_var(widget->slider(bv1, xaxis)));
  hbox1->append(Graphic_var(layout->hfil()));
  Graphic_var hbox2 = layout->hbox();
  hbox2->append(Graphic_var(layout->hfil()));
  hbox2->append(Graphic_var(widget->slider(bv2, xaxis)));
  hbox2->append(Graphic_var(layout->hfil()));
  Graphic_var hbox3 = layout->hbox();
  hbox3->append(Graphic_var(layout->hfil()));
  hbox3->append(Graphic_var(widget->slider(bv3, xaxis)));
  hbox3->append(Graphic_var(layout->hfil()));
  Graphic_var box = layout->vbox();
  box->append(Graphic_var(layout->align(group, 0., 0.)));
  box->append(hbox1);
  box->append(hbox2);
  box->append(hbox3);
  ToolKit::FrameSpec spec;
  spec.bbrightness(0.5);
  Graphic_var foo = tool->frame(box, 10., spec, true);
  Controller_var bar = tool->group(foo);
  application->append(bar, Unicode::String("MVC demo"));
}

Graphic_ptr LogoDemo::makeController(BoundedValue_ptr value, const Color &color)
{
  ToolKit_var tool = application->tool();
  WidgetKit_var widget = application->widget();
  LayoutKit_var layout = application->layout();
  Graphic_var gauge = widget->gauge(value);
  Forward *forward = new Forward(value);
  forward->_obj_is_ready(CORBA::BOA::getBOA());
  Backward *backward = new Backward(value);
  backward->_obj_is_ready(CORBA::BOA::getBOA());
  Graphic_var rectangle = layout->fixedSize(Graphic_var(Graphic::_nil()), 200., 200.);
  ToolKit::FrameSpec spec;
  spec.abrightness(0.5);
  Controller_var begin = tool->stepper(Graphic_var(tool->frame(rectangle, 10., spec, true)), Command_var(backward->_this()));
  Controller_var end = tool->stepper(Graphic_var(tool->frame(rectangle, 10., spec, true)), Command_var(forward->_this()));
  Graphic_var box = layout->hbox();
  box->append(begin);
  box->append(gauge);
  box->append(end);
  return Graphic::_duplicate(box);
}
