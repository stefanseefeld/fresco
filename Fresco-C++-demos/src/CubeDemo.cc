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
#include "CubeDemo.hh"

using namespace Fresco;

namespace
{
  class Forward : public Application::CommandImpl
  {
    public:
      Forward(Fresco::BoundedValue_ptr v) :
      my_value(Fresco::BoundedValue::_duplicate(v))
      { }
      void execute(const CORBA::Any &) { my_value->forward(); }
    private:
      Fresco::BoundedValue_var my_value;
  };

  class Backward : public Application::CommandImpl
  {
    public:
      Backward(Fresco::BoundedValue_ptr v) :
      my_value(Fresco::BoundedValue::_duplicate(v))
      { }
      void execute(const CORBA::Any &) { my_value->backward(); }
    private:
      Fresco::BoundedValue_var my_value;
  };

} // namespace

CubeDemo::Rotator::Rotator(BoundedValue_ptr v, Graphic_ptr c,
               Graphic_ptr p, Axis a) :
    my_value(BoundedValue::_duplicate(v)),
    my_child(Graphic::_duplicate(c)),
    my_parent(Graphic::_duplicate(p)),
    my_axis(a)
{
    CORBA::Any dummy;
    update(dummy);
}

void CubeDemo::Rotator::update(const CORBA::Any &)
{
    Coord ydegree = my_value->value();
    Transform_var tx = my_child->transformation();
    tx->load_identity();
    tx->rotate(ydegree, my_axis);
    my_parent->need_redraw();
}

CubeDemo::CubeDemo(Application *a) :
    Demo(a),
    my_tx1(new Berlin::TransformImpl),
    my_tx2(new Berlin::TransformImpl)
{
    RasterKit_var images =
    my_application->resolve<RasterKit>("IDL:fresco.org/Fresco/RasterKit:1.0");
    PrimitiveKit_var primitives =
    my_application->resolve<PrimitiveKit>("IDL:fresco.org/Fresco/PrimitiveKit:1.0");
    LayoutKit_var layout =
    my_application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
    CommandKit_var commands =
    my_application->resolve<CommandKit>("IDL:fresco.org/Fresco/CommandKit:1.0");
    ToolKit_var tools =
    my_application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
    WidgetKit_var widgets =
    my_application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");

    my_phi = commands->bvalue(0., 360., 0., 5., 5.);
    my_psi = commands->bvalue(0., 360., 0., 5., 5.);
    
    Graphic_var cube = primitives->cube();
    Graphic_var transformer1 = primitives->transformer(Graphic_var(tools->rgb(cube, 0.6, 0.6, 1.0)));
    Graphic_var transformer2 = primitives->transformer(Graphic_var(transformer1));
    Color white = {1., 1., 1., 1.};
    Vertex direction = {0., 0., -1.};
    Graphic_var light = primitives->directional_light(transformer2, white, 1., direction);
    
    Graphic_var root = primitives->root(light);

    my_rotator1 = new Rotator(my_phi, transformer1, root, zaxis);
    my_phi->attach(Observer_var(my_rotator1->_this()));
    my_rotator2 = new Rotator(my_psi, transformer2, root, yaxis);
    my_psi->attach(Observer_var(my_rotator2->_this()));
  
    Graphic_var hbox1 = layout->hbox();
    hbox1->append_graphic(Graphic_var(layout->hfill()));
    hbox1->append_graphic(Graphic_var(widgets->slider(my_phi, xaxis)));
    hbox1->append_graphic(Graphic_var(layout->hfill()));
    Graphic_var hbox2 = layout->hbox();
    hbox2->append_graphic(Graphic_var(layout->hfill()));
    hbox2->append_graphic(Graphic_var(widgets->slider(my_psi, xaxis)));
    hbox2->append_graphic(Graphic_var(layout->hfill()));
    Graphic_var box = layout->vbox();
    box->append_graphic(Graphic_var(layout->align(root, 0., 0.)));
    box->append_graphic(hbox1);
    box->append_graphic(hbox2);
    ToolKit::FrameSpec spec;
    spec.brightness(0.5); spec._d(ToolKit::inset);
    Graphic_var foo = tools->frame(box, 10., spec, true);
    MainController_var bar = tools->group(foo);
    my_application->append(bar, Babylon::String("Cube"));
}

Graphic_ptr CubeDemo::make_controller(BoundedValue_ptr value,
                      const Color &color)
{
    ToolKit_var tools =
    my_application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
    WidgetKit_var widgets =
    my_application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");
    LayoutKit_var layout =
    my_application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
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
