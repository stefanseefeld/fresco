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
#include <Fresco/Subject.hh>
#include <Fresco/Widget.hh>
#include <Fresco/MainController.hh>
#include <Berlin/ObserverImpl.hh>
#include "FocusDemo.hh"

using namespace Fresco;
using namespace Widget;

class FocusDemo::Observer : public ObserverImpl
{
 public:
  virtual void update(const CORBA::Any &any)
    {
      Fresco::Selection::Item *item;
      if (any >>= item)
	std::cout << "new selection" << std::endl;
    }
};

FocusDemo::FocusDemo(Application *a)
  : Demo(a), observer(new Observer)
{
  ImageKit_var images = application->resolve<ImageKit>("IDL:fresco.org/Fresco/ImageKit:1.0");
  FigureKit_var figures = application->resolve<FigureKit>("IDL:fresco.org/Fresco/FigureKit:1.0");
  LayoutKit_var layout = application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
  CommandKit_var commands = application->resolve<CommandKit>("IDL:fresco.org/Fresco/CommandKit:1.0");
  ToolKit_var tools = application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
  WidgetKit_var widgets = application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");
  TextKit_var text = application->resolve<TextKit>("IDL:fresco.org/Fresco/TextKit:1.0");

  Graphic_var      vbox = layout->vbox();
  Graphic_var     hbox1 = layout->hbox();
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::concav);
  /*
   * first group
   */
  Choice_var c1 = widgets->toggle_choice();
  for (size_t i = 0; i != 5; i++)
    c1->append_item(Graphic_var(Graphic::_nil()));
  c1->attach(Observer_var(observer->_this()));
  /*
   * second group
   */
  Choice_var c2 = widgets->checkbox_choice();
  for (size_t i = 0; i != 5; i++)
    c2->append_item(Graphic_var(Graphic::_nil()));
  c2->attach(Observer_var(observer->_this()));
  hbox1->append_graphic(Graphic_var(layout->margin(Graphic_var(tools->frame(Graphic_var(layout->margin(c1, 100.)),
									   20., spec, true)), 100.)));
  hbox1->append_graphic(Graphic_var(layout->margin(Graphic_var(tools->frame(Graphic_var(layout->margin(c2, 100.)),
									   20., spec, true)), 100.)));
  Graphic_var     hbox2 = layout->hbox();
  /*
   * third group
   */
  Choice_var c3 = widgets->toggle_choice();
  for (size_t i = 0; i != 5; i++)
    c3->append_item(Graphic_var(Graphic::_nil()));
  c3->attach(Observer_var(observer->_this()));
  /*
   * fourth group
   */
  Choice_var c4 = widgets->checkbox_choice();
  for (size_t i = 0; i != 5; i++)
    c4->append_item(Graphic_var(Graphic::_nil()));
  c4->attach(Observer_var(observer->_this()));
  hbox2->append_graphic(Graphic_var(layout->margin(Graphic_var(tools->frame(Graphic_var(layout->margin(c3, 100.)),
									   20., spec, true)), 100.)));
  hbox2->append_graphic(Graphic_var(layout->margin(Graphic_var(tools->frame(Graphic_var(layout->margin(c4, 100.)),
									   20., spec, true)), 100.)));
  vbox->append_graphic(hbox1);
  vbox->append_graphic(hbox2);
  Raster_var raster = images->create("marble.png");
  Graphic_var texture = figures->texture(vbox, raster);
  MainController_var gr = tools->group(texture);
  Raster_var pointer = images->create("ur-cursor.png");
  gr->cursor(pointer);
  gr->append_controller(c1);
  gr->append_controller(c2);
  gr->append_controller(c3);
  gr->append_controller(c4);
  application->append(gr, Babylon::String("focus demo"));
};
