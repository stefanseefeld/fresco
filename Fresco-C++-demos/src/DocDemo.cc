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

#include "DocDemo.hh"
#include <fstream>

using namespace Fresco;

DocDemo::DocDemo(Application *a) : Demo(a)
{
    TextKit_var text = my_application->resolve<TextKit>("IDL:fresco.org/Fresco/TextKit:1.0");
    LayoutKit_var layout = my_application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
    CommandKit_var commands = my_application->resolve<CommandKit>("IDL:fresco.org/Fresco/CommandKit:1.0");
    ToolKit_var tools = my_application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
    WidgetKit_var widgets = my_application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");

    Graphic_var column = layout->vbox();
    std::string file = "/etc/passwd";
    std::ifstream ifs(file.c_str());
    while (ifs)
    {
    std::string buf;
    getline(ifs, buf);
    Graphic_var line;
    if (buf.length())
        line = text->chunk(Unicode::to_CORBA(Babylon::String(buf)));
    else line = text->strut();
    column->append_graphic(line);
    }
    Controller_var page = widgets->scrollable(Graphic_var(tools->rgb(column, 0., 0., .0)));
    Controller_var root = tools->group(Graphic_var(layout->fixed_size(page, 3000., 2000.)));
    root->append_controller(page);
    my_application->append(root, Babylon::String("multiline text"));
}

