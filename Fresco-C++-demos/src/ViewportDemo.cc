/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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

#include "ViewportDemo.hh"
#include "Fresco/Image.hh"
#include "Fresco/Viewport.hh"

using namespace Fresco;

ViewportDemo::ViewportDemo(Application *a)
  : Demo(a)
{
  RasterKit_var rasters = application->resolve<RasterKit>("IDL:fresco.org/Fresco/RasterKit:1.0");
  FigureKit_var figures = application->resolve<FigureKit>("IDL:fresco.org/Fresco/FigureKit:1.0");
  LayoutKit_var layout = application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
  CommandKit_var commands = application->resolve<CommandKit>("IDL:fresco.org/Fresco/CommandKit:1.0");
  ToolKit_var tools = application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
  WidgetKit_var widgets = application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");

  Raster_var raster = rasters->create_raster("landscape.png");
  Image_var pixmap = figures->pixmap(raster);
  Layout::Viewport_var viewport = layout->scrollable(pixmap);
  Controller_var panner = widgets->panner(BoundedRange_var(viewport->adjustment(xaxis)), BoundedRange_var(viewport->adjustment(yaxis)));
  Controller_var xscroller = widgets->scrollbar(BoundedRange_var(viewport->adjustment(xaxis)), xaxis);
  Controller_var yscroller = widgets->scrollbar(BoundedRange_var(viewport->adjustment(yaxis)), yaxis);
  Graphic_var hbox1 = layout->hbox();
  hbox1->append_graphic(viewport);
  hbox1->append_graphic(yscroller);
  Graphic_var hbox2 = layout->hbox();
  hbox2->append_graphic(xscroller);
  hbox2->append_graphic(Graphic_var(layout->fixed_size(Graphic_var(Graphic::_nil()), 200., 200.)));
  Graphic_var vbox1 = layout->vbox();
  vbox1->append_graphic(hbox1);
  vbox1->append_graphic(hbox2);
  Graphic_var margin = layout->margin_flexible(panner, 500., 2000., 500.);
  Graphic_var hbox = layout->hbox();
  hbox->append_graphic(margin);
  hbox->append_graphic(vbox1);
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::outset);
  Graphic_var background = tools->frame(hbox, 10., spec, true);
  Controller_var group  = tools->group(background);
  group->append_controller(panner);
  group->append_controller(xscroller);
  group->append_controller(yscroller);

  application->append(group, Babylon::String("viewport"));
}
