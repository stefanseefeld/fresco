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

#include "ColorDemo.hh"
#include <Berlin/Color.hh>

ColorDemo::ColorDemo(Application *a)
  : Demo(a)
{
  LayoutKit_var layout = application->layout();
  ToolKit_var   tool = application->tool();
  WidgetKit_var widget = application->widget();
  TextKit_var text = application->text();
  CommandKit_var command = application->command();
  GadgetKit_var gadget = application->gadget();
  
  for (size_t i = 0; i != 6; ++i)
    {
      adapter[i] = new Adapter(this, i);
      adapter[i]->_obj_is_ready(CORBA::BOA::getBOA());
    }
  
  red = command->bvalue(0., 1., 0., .1, .5);
  green = command->bvalue(0., 1., 0., .1, .5);
  blue = command->bvalue(0., 1., 0., .1, .5);

  red->attach(Observer_var(adapter[0]->_this()));
  green->attach(Observer_var(adapter[1]->_this()));
  blue->attach(Observer_var(adapter[2]->_this()));

  hue = command->bvalue(0., 360., 0., 10., 50.);
  saturation = command->bvalue(0., 1., 0., 0.1, 0.1);
  value = command->bvalue(0., 1., 0., 0.1, 0.1);
  
  hue->attach(Observer_var(adapter[3]->_this()));
  saturation->attach(Observer_var(adapter[4]->_this()));
  value->attach(Observer_var(adapter[5]->_this()));

  Graphic_var hbox = layout->hbox();
  Graphic_var panel = layout->fixedSize(Graphic_var(Graphic::_nil()), 1000., 1000.);
  ToolKit::FrameSpec inset;
  inset.abrightness(0.5);
  hbox->append(Graphic_var(layout->margin(Graphic_var(gadget->rgb(Graphic_var(tool->frame(panel, 20., inset, true)), red, green, blue)), 500.)));

  Graphic_var vbox = layout->vbox();

  Graphic_var hbox21 = layout->hbox();
  hbox21->append(Graphic_var(layout->hfil()));
  hbox21->append(Graphic_var(tool->rgb(Graphic_var(text->chunk(Unicode::toCORBA(Unicode::String("RGB Color Model")))), 0., 0., 0.)));
  hbox21->append(Graphic_var(layout->hfil()));
  vbox->append(hbox21);

  Graphic_var hbox22 = layout->hbox();
  hbox22->append(Graphic_var(tool->rgb(Graphic_var(text->chunk(Unicode::toCORBA(Unicode::String("R  ")))), 0., 0., 0.)));
  hbox22->append(Graphic_var(widget->slider(red, xaxis)));
  vbox->append(hbox22);
 
  Graphic_var hbox23 = layout->hbox();
  hbox23->append(Graphic_var(tool->rgb(Graphic_var(text->chunk(Unicode::toCORBA(Unicode::String("G  ")))), 0., 0., 0.)));
  hbox23->append(Graphic_var(widget->slider(green, xaxis)));
  vbox->append(hbox23);

  Graphic_var hbox24 = layout->hbox();
  hbox24->append(Graphic_var(tool->rgb(Graphic_var(text->chunk(Unicode::toCORBA(Unicode::String("B  ")))), 0., 0., 0.)));
  hbox24->append(Graphic_var(widget->slider(blue, xaxis)));
  vbox->append(hbox24);

  Graphic_var hbox25 = layout->hbox();
  hbox25->append(Graphic_var(layout->hfil()));
  hbox25->append(Graphic_var(tool->rgb(Graphic_var(text->chunk(Unicode::toCORBA(Unicode::String("HSV Color Model")))), 0., 0., 0.)));
  hbox25->append(Graphic_var(layout->hfil()));
  vbox->append(hbox25);

  Graphic_var hbox26 = layout->hbox();
  hbox26->append(Graphic_var(tool->rgb(Graphic_var(text->chunk(Unicode::toCORBA(Unicode::String("H  ")))), 0., 0., 0.)));
  hbox26->append(Graphic_var(widget->slider(hue, xaxis)));
  vbox->append(hbox26);
 
  Graphic_var hbox27 = layout->hbox();
  hbox27->append(Graphic_var(tool->rgb(Graphic_var(text->chunk(Unicode::toCORBA(Unicode::String("S  ")))), 0., 0., 0.)));
  hbox27->append(Graphic_var(widget->slider(saturation, xaxis)));
  vbox->append(hbox27);

  Graphic_var hbox28 = layout->hbox();
  hbox28->append(Graphic_var(tool->rgb(Graphic_var(text->chunk(Unicode::toCORBA(Unicode::String("V  ")))), 0., 0., 0.)));
  hbox28->append(Graphic_var(widget->slider(value, xaxis)));
  vbox->append(hbox28);
  hbox->append(vbox);
  Controller_var root = tool->group(Graphic_var(layout->margin(hbox, 100.)));
  application->append(root, Unicode::String("Color demo"));
}

void ColorDemo::adjust(Tag tag)
  //. this is a hack of a constraint solver.
  //. the reason to do this serialization is
  //. that we update the three values one at
  //. a time, though only after all three
  //. have been set the color is in a coherent
  //. state...
  //.  -stefan
{
  static bool processing = false;
  if (processing) return;
  processing = true;
  if (tag < 3) // set hsv sliders
    {
      Color color;
      color.red = red->value();
      color.green = green->value();
      color.blue = blue->value();
      Coord h, s, v;
      RGBtoHSV(color, h, s, v);
      //. the following three calls need to be atomic
      hue->value(h);
      saturation->value(s);
      value->value(v);
    }
  else // set rgb sliders
    {
      Color color;
      Coord h = hue->value();
      Coord s = saturation->value();
      Coord v = value->value();
      HSVtoRGB(h, s, v, color);
      // the following three calls need to be atomic
      red->value(color.red);
      green->value(color.green);
      blue->value(color.blue);
    }
  processing = false;
}
