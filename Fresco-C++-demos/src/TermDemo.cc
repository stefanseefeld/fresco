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

#include "TermDemo.hh"
#include <fstream>

using namespace Prague;
using namespace Fresco;

TermDemo::TermDemo(Application *a) : Demo(a)
{
    LayoutKit_var layout = my_application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
    CommandKit_var commands = my_application->resolve<CommandKit>("IDL:fresco.org/Fresco/CommandKit:1.0");
    ToolKit_var tools = my_application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
    WidgetKit_var widgets = my_application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");
    TextKit_var text = my_application->resolve<TextKit>("IDL:fresco.org/Fresco/TextKit:1.0");

    Controller_var terminal = widgets->terminal();
    Controller_var scrollable = widgets->scrollable(Graphic_var(tools->rgb(terminal, 0., 0., 0.)));
    scrollable->append_controller(terminal);
    Controller_var group = tools->group(Graphic_var(layout->fixed_size(scrollable, 4000., 3000.)));
    group->append_controller(scrollable);
    my_application->append(group, Babylon::String("terminal"));
};
