/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "ViewportDemo.hh"
#include "Warsaw/Image.hh"
#include "Warsaw/Viewport.hh"

ViewportDemo::ViewportDemo(Application *a)
  : Demo(a)
{
  LayoutKit_var layout = application->layout();
  ToolKit_var   tool = application->tool();
  WidgetKit_var widget = application->widget();
  ImageKit_var image = application->image();
  FigureKit_var figure = application->figure();

  Raster_var raster = image->create("../etc/PNG/landscape.png");
  Image_var pixmap = figure->pixmap(raster);
  Viewport_var viewport = layout->scrollable(pixmap);
  Controller_var panner = widget->panner(viewport->adjustment(xaxis), viewport->adjustment(yaxis));
  Controller_var xscroller = widget->scrollbar(viewport->adjustment(xaxis), xaxis);
  Controller_var yscroller = widget->scrollbar(viewport->adjustment(yaxis), yaxis);
  Graphic_var hbox1 = layout->hbox();
  hbox1->append(viewport);
  hbox1->append(yscroller);
  Graphic_var hbox2 = layout->hbox();
  hbox2->append(xscroller);
  hbox2->append(Graphic_var(layout->fixedSize(Graphic_var(Graphic::_nil()), 200., 200.)));
  Graphic_var vbox1 = layout->vbox();
  vbox1->append(hbox1);
  vbox1->append(hbox2);
  Graphic_var margin = layout->marginFlexible(panner, 500., 2000., 500.);
  Graphic_var hbox = layout->hbox();
  hbox->append(margin);
  hbox->append(vbox1);
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::outset);
  Graphic_var background = tool->frame(hbox, 10., spec, true);
  Controller_var group  = tool->group(background);
  group->appendController(panner);
  group->appendController(xscroller);
  group->appendController(yscroller);

  application->append(group, Unicode::String("viewport demo"));
}
