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

#include "ColorDemo.hh"
#include <Berlin/Color.hh>

using namespace Fresco;

ColorDemo::ColorDemo(Application *a) :
    Demo(a)
{
    RasterKit_var images =
    my_application->resolve<RasterKit>("IDL:fresco.org/Fresco/RasterKit:1.0");
    FigureKit_var figures =
    my_application->resolve<FigureKit>("IDL:fresco.org/Fresco/FigureKit:1.0");
    LayoutKit_var layout =
    my_application->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0");
    CommandKit_var commands =
    my_application->resolve<CommandKit>("IDL:fresco.org/Fresco/CommandKit:1.0");
    ToolKit_var tools =
    my_application->resolve<ToolKit>("IDL:fresco.org/Fresco/ToolKit:1.0");
    WidgetKit_var widgets =
    my_application->resolve<WidgetKit>("IDL:fresco.org/Fresco/WidgetKit:1.0");
    TextKit_var text =
    my_application->resolve<TextKit>("IDL:fresco.org/Fresco/TextKit:1.0");
    GadgetKit_var gadgets =
    my_application->resolve<GadgetKit>("IDL:fresco.org/Fresco/GadgetKit:1.0");
  
    Layout::Grid::Index index;
    index.col = 3;
    index.row = 3;
    Layout::Grid_var rgb_grid = layout->fixed_grid(index);
    Layout::Grid_var hsv_grid = layout->fixed_grid(index);
    
    Graphic_var spacer =
    layout->valign(Graphic_var(tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("  ")))), 0., 0., 0.)), 0.);
    
    index.col = 1; index.row = 0;
    rgb_grid->replace(spacer, index);
    hsv_grid->replace(spacer, index);
    index.col = 1; index.row = 1;
    rgb_grid->replace(spacer, index);
    hsv_grid->replace(spacer, index);
    index.col = 1; index.row = 2;
    rgb_grid->replace(spacer, index);
    hsv_grid->replace(spacer, index);
    
    for (size_t i = 0; i != 6; ++i)
    my_adapter[i] = new Adapter(this, i);
  
    my_red = commands->bvalue(0., 1., 0., .1, .5);
    my_green = commands->bvalue(0., 1., 0., .1, .5);
    my_blue = commands->bvalue(0., 1., 0., .1, .5);

    my_red->attach(Observer_var(my_adapter[0]->_this()));
    my_green->attach(Observer_var(my_adapter[1]->_this()));
    my_blue->attach(Observer_var(my_adapter[2]->_this()));
    
    my_hue = commands->bvalue(0., 360., 0., 10., 50.);
    my_saturation = commands->bvalue(0., 1., 0., 0.1, 0.1);
    my_value = commands->bvalue(0., 1., 0., 0.1, 0.1);
  
    my_hue->attach(Observer_var(my_adapter[3]->_this()));
    my_saturation->attach(Observer_var(my_adapter[4]->_this()));
    my_value->attach(Observer_var(my_adapter[5]->_this()));

    Graphic_var hbox = layout->hbox();
    Graphic_var panel =
    layout->fixed_size(Graphic_var(Graphic::_nil()), 1000., 1000.);
    ToolKit::FrameSpec spec;
    spec.brightness(0.5); spec._d(ToolKit::inset);
    hbox->append_graphic(Graphic_var(layout->margin(Graphic_var(gadgets->rgb(Graphic_var(tools->frame(panel, 20., spec, true)), my_red, my_green, my_blue)), 500.)));

    Graphic_var vbox = layout->vbox();

    Graphic_var rgb_label = layout->hbox();
    rgb_label->append_graphic(Graphic_var(layout->hfill()));
    rgb_label->append_graphic(Graphic_var(tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("RGB Color Model")))), 0., 0., 0.)));
    rgb_label->append_graphic(Graphic_var(layout->hfill()));
    vbox->append_graphic(rgb_label);

    Graphic_var hfill = layout->hfill();
    Graphic_var vfill = layout->vfill();
    
    index.col = 0; index.row = 0;
    Graphic_var hbox21 = layout->hbox();
    hbox21->append_graphic(hfill);
    hbox21->append_graphic(Graphic_var(layout->valign(Graphic_var(tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("R")))), 0., 0., 0.)), 0.)));
    rgb_grid->replace(hbox21, index);
    index.col = 2;
    Graphic_var vbox21 = layout->vbox();
    vbox21->append_graphic(Graphic_var(widgets->slider(my_red, xaxis)));
    vbox21->append_graphic(vfill);
    rgb_grid->replace(vbox21, index);
    
    index.col = 0; index.row = 1;
    Graphic_var hbox22 = layout->hbox();
    hbox22->append_graphic(hfill);
    hbox22->append_graphic(Graphic_var(layout->valign(Graphic_var(tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("G")))), 0., 0., 0.)), 0.)));
    rgb_grid->replace(hbox22, index);
    index.col = 2;
    Graphic_var vbox22 = layout->vbox();
    vbox22->append_graphic(Graphic_var(widgets->slider(my_green, xaxis)));
    vbox22->append_graphic(vfill);
    rgb_grid->replace(vbox22, index);

    index.col = 0; index.row = 2;
    Graphic_var hbox23 = layout->hbox();
    hbox23->append_graphic(hfill);
    hbox23->append_graphic(Graphic_var(layout->valign(Graphic_var(tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("B")))), 0., 0., 0.)), 0.)));
    rgb_grid->replace(hbox23, index);
    index.col = 2;
    Graphic_var vbox23 = layout->vbox();
    vbox23->append_graphic(Graphic_var(widgets->slider(my_blue, xaxis)));
    vbox23->append_graphic(vfill);
    rgb_grid->replace(vbox23, index);

    vbox->append_graphic(rgb_grid);

    Graphic_var hbox25 = layout->hbox();
    hbox25->append_graphic(Graphic_var(layout->hfill()));
    hbox25->append_graphic(Graphic_var(tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("HSV Color Model")))), 0., 0., 0.)));
    hbox25->append_graphic(Graphic_var(layout->hfill()));
    vbox->append_graphic(hbox25);

    index.col = 0; index.row = 0;
    Graphic_var hbox26 = layout->hbox();
    hbox26->append_graphic(hfill);
    hbox26->append_graphic(Graphic_var(layout->valign(Graphic_var(tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("H")))), 0., 0., 0.)), 0.)));
    hsv_grid->replace(hbox26, index);
    index.col = 2;
    Graphic_var vbox26 = layout->vbox();
    vbox26->append_graphic(Graphic_var(widgets->slider(my_hue, xaxis)));
    vbox26->append_graphic(vfill);
    hsv_grid->replace(vbox26, index);

    index.col = 0; index.row = 1;
    Graphic_var hbox27 = layout->hbox();
    hbox27->append_graphic(hfill);
    hbox27->append_graphic(Graphic_var(layout->valign(Graphic_var(tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("S")))), 0., 0., 0.)), 0.)));
    hsv_grid->replace(hbox27, index);
    index.col = 2;
    Graphic_var vbox27 = layout->vbox();
    vbox27->append_graphic(Graphic_var(widgets->slider(my_saturation,
                               xaxis)));
    vbox27->append_graphic(vfill);
    hsv_grid->replace(vbox27, index);

    index.col = 0; index.row = 2;
    Graphic_var hbox28 = layout->hbox();
    hbox28->append_graphic(hfill);
    hbox28->append_graphic(Graphic_var(layout->valign(Graphic_var(tools->rgb(Graphic_var(text->chunk(Unicode::to_CORBA(Babylon::String("V")))), 0., 0., 0.)), 0.)));
    hsv_grid->replace(hbox28, index);
    index.col = 2;
    Graphic_var vbox28 = layout->vbox();
    vbox28->append_graphic(Graphic_var(widgets->slider(my_value, xaxis)));
    vbox28->append_graphic(vfill);
    hsv_grid->replace(vbox28, index);
    
    vbox->append_graphic(hsv_grid);
    
    hbox->append_graphic(vbox);
    Controller_var root = tools->group(Graphic_var(layout->margin(hbox, 100.)));
    my_application->append(root, Babylon::String("Color"));
}

void ColorDemo::adjust(Tag tag)
    //. this is a hack of a constraint solver.
    //. the reason to do this serialization is
    //. that we update the three values one at
    //. a time, though only after all three
    //. have been set the color is in a coherent
    //. state...
    //.  -stefan
{
    static bool processing = false;
    if (processing) return;
    processing = true;
    if (tag < 3) // set hsv sliders
    {
    Color color;
    color.red = my_red->value();
    color.green = my_green->value();
    color.blue = my_blue->value();
    Coord h, s, v;
    Berlin::RGBtoHSV(color, h, s, v);
    //. the following three calls need to be atomic
    my_hue->value(h);
    my_saturation->value(s);
    my_value->value(v);
    }
    else // set rgb sliders
    {
    Color color;
    Coord h = my_hue->value();
    Coord s = my_saturation->value();
    Coord v = my_value->value();
    Berlin::HSVtoRGB(h, s, v, color);
    // the following three calls need to be atomic
    my_red->value(color.red);
    my_green->value(color.green);
    my_blue->value(color.blue);
    }
    processing = false;
}
