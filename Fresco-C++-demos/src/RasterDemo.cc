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

#include "RasterDemo.hh"
#include <Fresco/Image.hh>

using namespace Fresco;

RasterDemo::RasterDemo(Application *a)
  : Demo(a)
{
  ImageKit_var images = application->resolve<ImageKit>("IDL:fresco.org/Fresco/ImageKit:1.0");
  FigureKit_var figures = application->resolve<FigureKit>("IDL:fresco.org/Fresco/FigureKit:1.0");
  LayoutKit_var layout = application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
  CommandKit_var commands = application->resolve<CommandKit>("IDL:fresco.org/Fresco/CommandKit:1.0");
  ToolKit_var tools = application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
  WidgetKit_var widgets = application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");
  
  Command_var command1 = commands->log("hello World 1");
  Command_var command2 = commands->log("hello World 2");
  Command_var command3 = commands->log("hello World 3");
  
  Raster_var raster = images->create("png.png");
  Image_var  im = figures->pixmap(raster);
  
  Graphic_var hbox = layout->hbox();
  hbox->append_graphic(Graphic_var(widgets->button(im, command1)));
  hbox->append_graphic(Graphic_var(widgets->button(im, command2)));
  hbox->append_graphic(Graphic_var(widgets->button(im, command3)));
  Controller_var group = tools->group(hbox);

  application->append(group, Babylon::String("raster"));
};
