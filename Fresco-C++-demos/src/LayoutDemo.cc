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

#include "LayoutDemo.hh"

using namespace Fresco;

LayoutDemo::LayoutDemo(Application *a)
  : Demo(a)
{
  TextKit_var text = application->resolve<TextKit>("IDL:fresco.org/Fresco/TextKit:1.0");
  LayoutKit_var layout = application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
  CommandKit_var commands = application->resolve<CommandKit>("IDL:fresco.org/Fresco/CommandKit:1.0");
  ToolKit_var tools = application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
  WidgetKit_var widgets = application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");
  Graphic_var label1 = tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("first button")))), 0.0,0.0,0.0);
  Graphic_var label2 = tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("second button")))), 0.0,0.0,0.0);
  Graphic_var label3 = tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("third button")))), 0.0,0.0,0.0);
  
  Graphic_var hbox = layout->hbox();
  Command_var command1 = commands->log("hello World 1");
  Command_var command2 = commands->log("hello World 2");
  Command_var command3 = commands->log("hello World 3");
  Controller_var button1 = widgets->button(label1, command1);
  hbox->append_graphic(Graphic_var(tools->rgb(button1, 1.0, 0.5, 0.5)));
  hbox->append_graphic(Graphic_var(layout->hglue(100., 500., 0.)));
  Controller_var button2 = widgets->button(label2, command2);
  hbox->append_graphic(Graphic_var(tools->rgb(button2, 0.5, 1., 0.5)));
  hbox->append_graphic(Graphic_var(layout->hglue(100., 500., 0.)));
  Controller_var button3 = widgets->button(label3, command3);
  hbox->append_graphic(Graphic_var(tools->rgb(button3, 0.5, 0.5, 1.)));
  Graphic_var margin = layout->margin_flexible(hbox, 100., 500., 100.);
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::outset);
  Graphic_var demo = tools->frame(margin, 10., spec, true);
  Controller_var group = tools->group(demo);
  group->append_controller(button1);
  group->append_controller(button2);
  group->append_controller(button3);
  application->append(group, Babylon::String("layout demo"));
};
