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

#include <Warsaw/config.hh>
#include <Warsaw/Subject.hh>
#include <Warsaw/Choice.hh>
#include "FocusDemo.hh"

class FocusDemo::Observer : public virtual POA_Observer, public virtual PortableServer::RefCountServantBase
{
 public:
  virtual void update(const CORBA::Any &any)
    {
      Selection::Item *item;
      if (any >>= item)
	cout << "new selection" << endl;
    }
};

FocusDemo::FocusDemo(Application *a)
  : Demo(a), observer(new Observer)
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
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::concav);
  /*
   * first group
   */
  Choice_var c1 = widget->toggleChoice();
  for (size_t i = 0; i != 5; i++)
    c1->appendItem(Graphic_var(Graphic::_nil()));
  c1->attach(Observer_var(observer->_this()));
  /*
   * second group
   */
  Choice_var c2 = widget->checkboxChoice();
  for (size_t i = 0; i != 5; i++)
    c2->appendItem(Graphic_var(Graphic::_nil()));
  c2->attach(Observer_var(observer->_this()));
  hbox1->append(Graphic_var(layout->margin(Graphic_var(tool->frame(Graphic_var(layout->margin(c1, 100.)),
								   20., spec, true)), 100.)));
  hbox1->append(Graphic_var(layout->margin(Graphic_var(tool->frame(Graphic_var(layout->margin(c2, 100.)),
								   20., spec, true)), 100.)));
  Graphic_var     hbox2 = layout->hbox();
  /*
   * third group
   */
  Choice_var c3 = widget->toggleChoice();
  for (size_t i = 0; i != 5; i++)
    c3->appendItem(Graphic_var(Graphic::_nil()));
  c3->attach(Observer_var(observer->_this()));
  /*
   * fourth group
   */
  Choice_var c4 = widget->checkboxChoice();
  for (size_t i = 0; i != 5; i++)
    c4->appendItem(Graphic_var(Graphic::_nil()));
  c4->attach(Observer_var(observer->_this()));
  hbox2->append(Graphic_var(layout->margin(Graphic_var(tool->frame(Graphic_var(layout->margin(c3, 100.)),
								   20., spec, true)), 100.)));
  hbox2->append(Graphic_var(layout->margin(Graphic_var(tool->frame(Graphic_var(layout->margin(c4, 100.)),
								   20., spec, true)), 100.)));
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
