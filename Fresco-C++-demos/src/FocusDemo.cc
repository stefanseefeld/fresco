/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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

#include "FocusDemo.hh"

Controller_ptr makeGroup(LayoutKit_ptr lk, ToolKit_ptr tk, WidgetKit_ptr wk)
{
  vector<Controller_var> toggles(5);
  vector<Graphic_var> margins(5);
  for (size_t i = 0; i != 5; i++)
    {
      toggles[i] = wk->toggle(Graphic_var(lk->fixedSize(Graphic_var(Graphic::_nil()), 50., 50.)));
      margins[i] = lk->margin(toggles[i], 100.);
    }
  Graphic_var vbox = lk->vbox();
  for (size_t i = 0; i != 5; i++) vbox->append(margins[i]);
  Graphic_var margin = lk->margin(vbox, 100.);
  ToolKit::FrameSpec spec;
  spec.cbrightness(0.5);
  Graphic_var frame  = tk->frame(margin, 30., spec, true);
  Controller_var gr  = tk->group(frame);
  for (size_t i = 0; i != 5; i++) gr->appendController(toggles[i]);
  return gr._retn();
};

FocusDemo::FocusDemo(Application *a)
  : Demo(a)
{
  TextKit_var text = application->text();
  LayoutKit_var layout = application->layout();
  CommandKit_var command = application->command();
  ImageKit_var image = application->image();
  FigureKit_var figure = application->figure();
  ToolKit_var   tool = application->tool();
  WidgetKit_var widget = application->widget();
  Graphic_var      vbox = layout->vbox();
  Graphic_var     hbox1 = layout->hbox();
  Controller_var  c1    = makeGroup(layout, tool, widget);
  Controller_var  c2    = makeGroup(layout, tool, widget);
  hbox1->append(c1);
  hbox1->append(c2);
  Graphic_var     hbox2 = layout->hbox();
  Controller_var  c3    = makeGroup(layout, tool, widget);
  Controller_var  c4    = makeGroup(layout, tool, widget);
  hbox2->append(c3);
  hbox2->append(c4);
  vbox->append(hbox1);
  vbox->append(hbox2);
  Raster_var raster = image->create("../etc/PNG/marble.png");
  Graphic_var texture = figure->texture(vbox, raster);
  Controller_var gr = tool->group(texture);
  gr->appendController(c1);
  gr->appendController(c2);
  gr->appendController(c3);
  gr->appendController(c4);
  application->append(gr, Unicode::String("focus demo"));
};
