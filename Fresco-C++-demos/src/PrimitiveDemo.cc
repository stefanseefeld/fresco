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

#include <Fresco/config.hh>
#include <Fresco/Command.hh>
#include <Fresco/Desktop.hh>
#include <Fresco/MainController.hh>
#include <Fresco/PrimitiveKit.hh>
#include "PrimitiveDemo.hh"

using namespace Fresco;

namespace
{
class Forward : public Application::CommandImpl
{
 public:
  Forward(Fresco::BoundedValue_ptr v) : value(Fresco::BoundedValue::_duplicate(v)) {}
  void execute(const CORBA::Any &) { value->forward();}
 private:
  Fresco::BoundedValue_var value;
};

class Backward : public Application::CommandImpl
{
 public:
  Backward(Fresco::BoundedValue_ptr v) : value(Fresco::BoundedValue::_duplicate(v)) {}
  void execute(const CORBA::Any &) { value->backward();}
 private:
  Fresco::BoundedValue_var value;
};

};

PrimitiveDemo::Rotator::Rotator(BoundedValue_ptr v, Graphic_ptr c, Graphic_ptr p, Axis a)
  : value(BoundedValue::_duplicate(v)),
    child(Graphic::_duplicate(c)),
    parent(Graphic::_duplicate(p)),
    axis(a)
{
  CORBA::Any dummy;
  update(dummy);
}

void PrimitiveDemo::Rotator::update(const CORBA::Any &)
{
  Coord ydegree = value->value();
  Transform_var tx = child->transformation();
  tx->load_identity();
  tx->rotate(ydegree, axis);
  parent->need_redraw();
}

PrimitiveDemo::PrimitiveDemo(Application *a)
  : Demo(a),
    tx1(new TransformImpl),
    tx2(new TransformImpl)
{
  RasterKit_var images = application->resolve<RasterKit>("IDL:fresco.org/Fresco/RasterKit:1.0");
  PrimitiveKit_var primitives = application->resolve<PrimitiveKit>("IDL:fresco.org/Fresco/PrimitiveKit:1.0");
  LayoutKit_var layout = application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
  CommandKit_var commands = application->resolve<CommandKit>("IDL:fresco.org/Fresco/CommandKit:1.0");
  ToolKit_var tools = application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
  WidgetKit_var widgets = application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");
  
  phi = commands->bvalue(0., 360., 0., 5., 5.);
  psi = commands->bvalue(0., 360., 0., 5., 5.);
  
  Coord c = 2000.;
  Vertex offset;
  offset.x = -c/2., offset.y = -3./2.*c, offset.z = 0.;
  Fresco::Mesh mesh;
  mesh.nodes.length(4);
  Coord w = 3000.;
  Coord h = 3000.;
  Coord d = 3000.;
  mesh.nodes[0].x = -w/2, mesh.nodes[0].y = -h/2, mesh.nodes[0].z = -d/2;
  mesh.nodes[1].x =  w/2, mesh.nodes[1].y = -h/2, mesh.nodes[1].z = -d/2;
  mesh.nodes[2].x =  0, mesh.nodes[2].y = -h/2, mesh.nodes[2].z =  d/2;
  mesh.nodes[3].x =  0, mesh.nodes[3].y =  h/2, mesh.nodes[3].z = 0;
  mesh.triangles.length(4);
  mesh.triangles[0].a = 0, mesh.triangles[0].b = 1, mesh.triangles[0].c = 3;
  mesh.triangles[1].a = 1, mesh.triangles[1].b = 2, mesh.triangles[1].c = 3;
  mesh.triangles[2].a = 2, mesh.triangles[2].b = 0, mesh.triangles[2].c = 3;
  mesh.triangles[3].a = 0, mesh.triangles[3].b = 2, mesh.triangles[3].c = 1;
  mesh.normals.length(4);
  mesh.normals[0].x = 0., mesh.normals[0].y = .8, mesh.normals[0].z = .2;
  mesh.normals[1].x = .8, mesh.normals[1].y = .2, mesh.normals[1].z = .2;
  mesh.normals[2].x = -.2, mesh.normals[2].y = .2, mesh.normals[2].z = .2;
  mesh.normals[3].x = 0., mesh.normals[3].y = -1., mesh.normals[3].z = 0.;
  
  Graphic_var geometry = primitives->geometry(mesh);
  Graphic_var transformer1 = primitives->transformer(Graphic_var(tools->rgb(geometry, 0.6, 0.6, 1.0)));
  Graphic_var transformer2 = primitives->transformer(Graphic_var(transformer1));
  Color white = {1., 1., 1., 1.};
  Vertex direction = {0., 0., 1.};

  Graphic_var light = primitives->directional_light(transformer2, white, 1., direction);
  
  Graphic_var root = primitives->root(light);

  rotator1 = new Rotator(phi, transformer1, root, zaxis);
  phi->attach(Observer_var(rotator1->_this()));
  rotator2 = new Rotator(psi, transformer2, root, yaxis);
  psi->attach(Observer_var(rotator2->_this()));
  
  Graphic_var hbox1 = layout->hbox();
  hbox1->append_graphic(Graphic_var(layout->hfill()));
  hbox1->append_graphic(Graphic_var(widgets->slider(phi, xaxis)));
  hbox1->append_graphic(Graphic_var(layout->hfill()));
  Graphic_var hbox2 = layout->hbox();
  hbox2->append_graphic(Graphic_var(layout->hfill()));
  hbox2->append_graphic(Graphic_var(widgets->slider(psi, xaxis)));
  hbox2->append_graphic(Graphic_var(layout->hfill()));
  Graphic_var box = layout->vbox();
  box->append_graphic(Graphic_var(layout->align(root, 0., 0.)));
  box->append_graphic(hbox1);
  box->append_graphic(hbox2);
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::inset);
  Graphic_var foo = tools->frame(box, 10., spec, true);
  MainController_var bar = tools->group(foo);
  application->append(bar, Babylon::String("Geometry"));
}

Graphic_ptr PrimitiveDemo::make_controller(BoundedValue_ptr value, const Color &color)
{
  ToolKit_var tools = application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
  WidgetKit_var widgets = application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");
  LayoutKit_var layout = application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
  Graphic_var gauge = widgets->gauge(value);
  Forward *forward = new Forward(value);
  Backward *backward = new Backward(value);
  Graphic_var rectangle = layout->fixed_size(Graphic_var(Graphic::_nil()), 200., 200.);
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::inset);
  Controller_var begin = tools->stepper(Graphic_var(tools->frame(rectangle, 10., spec, true)), Command_var(backward->_this()));
  Controller_var end = tools->stepper(Graphic_var(tools->frame(rectangle, 10., spec, true)), Command_var(forward->_this()));
  Graphic_var box = layout->hbox();
  box->append_graphic(begin);
  box->append_graphic(gauge);
  box->append_graphic(end);
  return Graphic::_duplicate(box);
}
