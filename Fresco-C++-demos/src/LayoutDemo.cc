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

#include "LayoutDemo.hh"

LayoutDemo::LayoutDemo(Application *a)
  : Demo(a)
{
  TextKit_var text = application->text();
  LayoutKit_var layout = application->layout();
  CommandKit_var command = application->command();
  WidgetKit_var widget = application->widget();
  Graphic_var label1 = text->chunk(Unicode::toCORBA(Unicode::String("first button")));
  Graphic_var label2 = text->chunk(Unicode::toCORBA(Unicode::String("second button")));
  Graphic_var label3 = text->chunk(Unicode::toCORBA(Unicode::String("third button")));
  
  Color red = {1.0, 0.5, 0.5, 1.0};
  Color green = {0.5, 1.0, 0.5, 1.0};
  Color blue = {0.5, 0.5, 1.0, 1.0};
  Color gray = {0.5, 0.5, 0.5, 1.0};
  
  Graphic_var hbox = layout->hbox();
  Command_var command1 = command->log("hello World 1");
  Command_var command2 = command->log("hello World 2");
  Command_var command3 = command->log("hello World 3");
  Controller_var button1 = widget->button(label1, red, command1);
  hbox->append(button1);
  hbox->append(Graphic_var(layout->hglue(100., 500., 0.)));
  Controller_var button2 = widget->button(label2, green, command2);
  hbox->append(button2);
  hbox->append(Graphic_var(layout->hglue(100., 500., 0.)));
  Controller_var button3 = widget->button(label3, blue, command3);
  hbox->append(button3);
  Graphic_var margin = layout->marginFlexible(hbox, 100., 500., 100.);
  Graphic_var demo =   widget->outset(margin, gray, true);
  Controller_var group = widget->group(demo);
  group->appendController(button1);
  group->appendController(button2);
  group->appendController(button3);
  application->append(group, Unicode::String("layout demo"));
};
