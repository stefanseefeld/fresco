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

#include "LogoDemo.hh"
#include "Fresco/config.hh"
#include "Fresco/Command.hh"
#include "Fresco/Desktop.hh"

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

LogoDemo::Rotator::Rotator(BoundedValue_ptr v,
			   Graphic_ptr c, Graphic_ptr p, Coord d)
  : value(BoundedValue::_duplicate(v)),
    child(Graphic::_duplicate(c)),
    parent(Graphic::_duplicate(p)),
    zdegree(d)
{
  CORBA::Any dummy;
  update(dummy);
}

void LogoDemo::Rotator::update(const CORBA::Any &)
{
  Coord ydegree = value->value();
  Transform_var tx = child->transformation();
  tx->load_identity();
  tx->rotate(ydegree, yaxis);
  tx->rotate(zdegree, zaxis);
  parent->need_resize();
}

LogoDemo::LogoDemo(Application *a)
  : Demo(a)
{
  FigureKit_var figures = application->resolve<FigureKit>("IDL:fresco.org/Fresco/FigureKit:1.0");
  LayoutKit_var layout = application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
  CommandKit_var commands = application->resolve<CommandKit>("IDL:fresco.org/Fresco/CommandKit:1.0");
  ToolKit_var tools = application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
  WidgetKit_var widgets = application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");
  
  bv1 = commands->bvalue(0., 360., 0., 5., 5.);
  bv2 = commands->bvalue(0., 360., 0., 5., 5.);
  bv3 = commands->bvalue(0., 360., 0., 5., 5.);
  
  Coord c = 1000.;
  Fresco::Path path;
  path.shape = convex;
  path.nodes.length(3);
  
  path.nodes[0].x =  0.0      , path.nodes[0].y = -1.0 * c,
      path.nodes[0].z = 0.0;
  path.nodes[1].x =  0.866 * c, path.nodes[1].y =  0.5 * c,
      path.nodes[1].z = 0.0;
  path.nodes[2].x = -0.866 * c, path.nodes[2].y =  0.5 * c,
      path.nodes[2].z = 0.0;
  
  Figure::Path_var triangle = figures->polygon(path);
  Graphic_var transformer1 = figures->transformer(Graphic_var(tools->rgb(Graphic_var(tools->alpha(triangle, 0.5)), 1., 0.5, 0.5)));
  Graphic_var transformer2 = figures->transformer(Graphic_var(tools->rgb(Graphic_var(tools->alpha(triangle, 0.5)), 0.5, 1., 0.5)));
  Graphic_var transformer3 = figures->transformer(Graphic_var(tools->rgb(Graphic_var(tools->alpha(triangle, 0.5)), 0.5, 0.5, 1.)));
  
  Graphic_var group = layout->hbox();
  
  Graphic_var fix1 = layout->fixed_size(layout->align(transformer1, 0.5, 0.5), 2.0 * c, 2.0 * c);
  Graphic_var fix2 = layout->fixed_size(layout->align(transformer2, 0.5, 0.5), 2.0 * c, 2.0 * c);
  Graphic_var fix3 = layout->fixed_size(layout->align(transformer3, 0.5, 0.5), 2.0 * c, 2.0 * c);

  Graphic_var glue = layout->hspace(-1.2 * c);

  rotator1 = new Rotator(bv1, transformer1, fix1, -10.0);
  bv1->attach(Observer_var(rotator1->_this()));
  rotator2 = new Rotator(bv2, transformer2, fix2,  10.0);
  bv2->attach(Observer_var(rotator2->_this()));
  rotator3 = new Rotator(bv3, transformer3, fix3,  20.0);
  bv3->attach(Observer_var(rotator3->_this()));
  
  group->append_graphic(fix1);
  group->append_graphic(glue);
  group->append_graphic(fix2);
  group->append_graphic(glue);
  group->append_graphic(fix3);
  
  Graphic_var hbox1 = layout->hbox();
  hbox1->append_graphic(Graphic_var(layout->hfill()));
  hbox1->append_graphic(Graphic_var(widgets->slider(bv1, xaxis)));
  hbox1->append_graphic(Graphic_var(layout->hfill()));
  Graphic_var hbox2 = layout->hbox();
  hbox2->append_graphic(Graphic_var(layout->hfill()));
  hbox2->append_graphic(Graphic_var(widgets->slider(bv2, xaxis)));
  hbox2->append_graphic(Graphic_var(layout->hfill()));
  Graphic_var hbox3 = layout->hbox();
  hbox3->append_graphic(Graphic_var(layout->hfill()));
  hbox3->append_graphic(Graphic_var(widgets->slider(bv3, xaxis)));
  hbox3->append_graphic(Graphic_var(layout->hfill()));
  Graphic_var box = layout->vbox();
  box->append_graphic(Graphic_var(layout->align(group, 0., 0.)));
  box->append_graphic(hbox1);
  box->append_graphic(hbox2);
  box->append_graphic(hbox3);
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::inset);
  Graphic_var foo = tools->frame(box, 10., spec, true);
  Controller_var bar = tools->group(foo);
  application->append(bar, Babylon::String("MVC"));
}

Graphic_ptr LogoDemo::make_controller(BoundedValue_ptr value, const Color &color)
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
