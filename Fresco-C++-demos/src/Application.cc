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
#include <Fresco/resolve.hh>
#include <Fresco/DrawingKit.hh>
#include <Fresco/Image.hh>
#include <Fresco/Window.hh>
#include "Application.hh"

using namespace Prague;
using namespace Fresco;

class Application::PrintCommand : public Application::CommandImpl
{
  public:
    PrintCommand(Window_var w, Application *a) : my_w(w), my_a(a) { }
    virtual void execute(const CORBA::Any &any)
    {
    Command_var(my_a->my_ck->print(my_a->my_ttk->rgb(my_a->my_lk->fixed_size(my_a->my_lk->align(my_w, 0., 0.), my_w->size().x, my_w->size().y), 0.8, 0.8, 0.8)))->execute(any);
    }
  private:
    Window_var my_w;
    Application *my_a;
};

class Application::Mapper : public Application::CommandImpl
{
  public:
    Mapper(Application::list_t &d, Fresco::Selection_ptr s) :
    my_demos(d),
    my_selection(Fresco::Selection::_duplicate(s))
    { }
    virtual void execute(const CORBA::Any &);
  private:
    Application::list_t &my_demos;
    Fresco::Selection_var my_selection;
};

void Application::CommandImpl::destroy()
{
    PortableServer::POA_var poa = _default_POA();
    PortableServer::ObjectId *oid = poa->servant_to_id(this);
    poa->deactivate_object(*oid);
    delete oid;
}

void Application::Mapper::execute(const CORBA::Any &)
{
    Selection::Items *items = my_selection->toggled();
    if (!items->length()) return;
    Tag t = (*items)[items->length() - 1];
    delete items;
    CORBA::Any any;
    for (Application::list_t::iterator i = my_demos.begin();
     i != my_demos.end();
     ++i)
    if (t == i->id) i->mapper->execute(any);
}

class ExitCommand : public Application::CommandImpl
{
  public:
    void execute(const CORBA::Any &) { exit(0); }
};

Application::Application(ServerContext_ptr sc, ClientContext_ptr cc) :
    my_server(ServerContext::_duplicate(sc)),
    my_client(ClientContext::_duplicate(cc)),
    my_tk(::resolve_kit<TextKit>(my_server)),
    my_dk(::resolve_kit<DesktopKit>(my_server)),
    my_lk(::resolve_kit<LayoutKit>(my_server)),
    my_ttk(::resolve_kit<ToolKit>(my_server)),
    my_wk(::resolve_kit<WidgetKit>(my_server)),
    my_fk(::resolve_kit<FigureKit>(my_server)),
    my_ck(::resolve_kit<CommandKit>(my_server)),
    my_rk(::resolve_kit<RasterKit>(my_server)),
    my_gk(::resolve_kit<GadgetKit>(my_server)),
    my_vbox(my_lk->vbox()),
    my_choice(my_wk->toggle_choice()),
    my_mapper(new Mapper(my_demos, Selection_var(my_choice->state())))
{
    my_background.red = my_background.green = my_background.blue = 0.6;
    my_background.alpha = 1.;
    Raster_var raster = my_rk->create_raster("fresco.png");
    Image_var image = my_fk->pixmap(raster);
    Graphic_var hbox = my_lk->hbox();
    Graphic_var vbox = my_lk->vbox();
    Graphic_var use1 =
    my_tk->chunk(Unicode::to_CORBA(Babylon::String("Select a")));
    Graphic_var use2 =
    my_tk->chunk(Unicode::to_CORBA(Babylon::String("demo:")));
    vbox->append_graphic(Graphic_var(my_lk->vfill()));
    vbox->append_graphic(use1);
    vbox->append_graphic(use2);
    vbox->append_graphic(Graphic_var(my_lk->vfill()));
    Graphic_var black_usage = my_ttk->rgb(vbox, 0., 0., 0.);
    hbox->append_graphic(Graphic_var(my_lk->hfill()));
    hbox->append_graphic(black_usage);
    hbox->append_graphic(Graphic_var(my_lk->hfill()));
    hbox->append_graphic(image);
    my_vbox->append_graphic(hbox);

    Graphic_var glyph =
    my_tk->chunk(Unicode::to_CORBA(Babylon::String("close")));
    my_done =
    my_lk->margin(Graphic_var(my_ttk->rgb(glyph, 0., 0., 0.)), 20.);
    glyph = my_tk->chunk(Unicode::to_CORBA(Babylon::String("settings")));
    my_settings =
    my_lk->margin(Graphic_var(my_ttk->rgb(glyph, 0., 0., 0.)), 20.);
    glyph = my_tk->chunk(Unicode::to_CORBA(Babylon::String("print")));
    my_print =
    my_lk->margin(Graphic_var(my_ttk->rgb(glyph, 0., 0., 0.)), 20.);
}

void Application::append(Controller_ptr demo, const Babylon::String &name)
{
    Item item = make_item(name);
    
    Graphic_var vb = my_lk->vbox();
    
    ToolKit::FrameSpec spec;
    spec.brightness(0.5); spec._d(ToolKit::outset);
    Graphic_var decorator = my_ttk->frame(vb, 10., spec, true);

    Graphic_var hbox = my_lk->hbox();
    hbox->append_graphic(Graphic_var(my_lk->hfill()));
    Trigger_var button1 = my_wk->button(my_done,
                    Command_var(Command::_nil()));
    hbox->append_graphic(button1);
    hbox->append_graphic(Graphic_var(my_lk->hspace(200.)));
    Trigger_var button2 = my_wk->button(my_settings, item.settings);
    hbox->append_graphic(button2);
    hbox->append_graphic(Graphic_var(my_lk->hspace(200.)));
    Trigger_var button3 = my_wk->button(my_print,
                    Command_var(Command::_nil()));
    hbox->append_graphic(button3);
    hbox->append_graphic(Graphic_var(my_lk->hfill()));
    vb->append_graphic(demo);
    vb->append_graphic(hbox);
    
    decorator = my_gk->alpha(decorator, item.alpha);
    decorator = my_gk->lighting(decorator,
                item.red, item.green, item.blue);
    decorator = my_gk->rotator(decorator, item.zrotation, zaxis);
    decorator = my_gk->rotator(decorator, item.yrotation, yaxis);
    decorator = my_gk->zoomer(decorator, item.zoom);
    
    Controller_var group =
    my_ttk->group(Graphic_var(my_lk->align(decorator, 0., 0.)));
    group->append_controller(demo);
    group->append_controller(button1);
    group->append_controller(button2);
    group->append_controller(button3);
    Window_var window = my_dk->transient(group);
    PrintCommand *my_pc = new PrintCommand(window, this);
    button1->action(Command_var(my_dk->map(window, false)));
    button3->action(Command_var(my_pc->_this()));
    item.mapper = my_dk->map(window, true);
    my_demos.push_back(item);
}

void Application::run()
{
    my_vbox->append_graphic(Graphic_var(my_lk->vspace(200.)));
    ToolKit::FrameSpec spec;
    spec.brightness(0.5); spec._d(ToolKit::concav);
    my_vbox->append_graphic(Graphic_var(my_ttk->frame(my_choice,
                              20., spec, false)));
    my_vbox->append_graphic(Graphic_var(my_lk->vspace(200.)));

    // run button
    Graphic_var glyph1 =
    my_tk->chunk(Unicode::to_CORBA(Babylon::String("run")));
    Graphic_var label1 = my_lk->margin(glyph1, 20.);
    Graphic_var label1f = my_lk->hmargin_lr_flexible(label1, 0, 100000, 0,
                             0, 100000, 0);
    Trigger_var run = my_wk->button(Graphic_var(my_ttk->rgb(label1f,
                                0., 0., 0.)), 
                    Command_var(my_mapper->_this()));

    // quit button
    Graphic_var glyph2 =
    my_tk->chunk(Unicode::to_CORBA(Babylon::String("quit")));
    Graphic_var label2 = my_lk->margin(glyph2, 20.);
    ExitCommand *cmd = new ExitCommand();
    Graphic_var label2f = my_lk->hmargin_lr_flexible(label2, 0, 100000, 0,
                             0, 100000, 0);
    Trigger_var quit = my_wk->button(Graphic_var(my_ttk->rgb(label2f,
                               0., 0., 0.)), 
                     Command_var(cmd->_this()));
    
    Graphic_var hbox = my_lk->hbox();
    hbox->append_graphic(run);
    hbox->append_graphic(Graphic_var(my_lk->hspace(200.)));
    hbox->append_graphic(quit);
    my_vbox->append_graphic(hbox);
    Graphic_var margin = my_lk->margin(my_vbox, 200.);
  
    spec.brightness(1.0); spec._d(ToolKit::outset);
    Controller_var group =
    my_ttk->group(Graphic_var(my_ttk->frame(margin, 10., spec, true)));
    group->append_controller(my_choice);
    group->append_controller(run);
    group->append_controller(quit);
    Window_var window = my_dk->shell(group, my_client);
    while (true) Thread::delay(Prague::Time(1000));
}

Application::Item Application::make_item(const Babylon::String &name)
{
    Item item;

    // insert an item into the choice
    Graphic_var label = my_tk->chunk(Unicode::to_CORBA(name));
    item.id = my_choice->append_item(Graphic_var(my_ttk->rgb(label,
                                 0., 0., 0.)));
    // create the control elements
    item.alpha = my_ck->bvalue(0., 1., 1., 0.1, 0.1);
    item.red = my_ck->bvalue(0., 1., 1., 0.1, 0.1);
    item.blue = my_ck->bvalue(0., 1., 1., 0.1, 0.1);
    item.green = my_ck->bvalue(0., 1., 1., 0.1, 0.1);
    item.zrotation = my_ck->bvalue(0., 360., 0., 5., 5.);
    item.yrotation = my_ck->bvalue(0., 360., 0., 5., 5.);
    item.zoom = my_ck->bvalue(-1., 1., 0., 0.1, 0.1);
  
    // create the settings window
    Layout::Grid::Index index;
    index.col = 2, index.row = 7;
    Layout::Grid_var grid = my_lk->fixed_grid(index);
    index.row = 0;
    index.col = 0;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_ttk->rgb(Graphic_var(my_tk->chunk(Unicode::to_CORBA(Babylon::String("alpha")))), 0., 0., 0.)), 0.5)), index);
    index.col = 1;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_lk->margin_flexible(Graphic_var(my_wk->slider(item.alpha, xaxis)), 100., 100., 100.)), 0.5)), index);

    index.row = 1;
    index.col = 0;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_ttk->rgb(Graphic_var(my_tk->chunk(Unicode::to_CORBA(Babylon::String("red")))), 0., 0., 0.)), 0.5)), index);
    index.col = 1;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_lk->margin_flexible(Graphic_var(my_wk->slider(item.red, xaxis)), 100., 100., 100.)), 0.5)), index);

    index.row = 2;
    index.col = 0;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_ttk->rgb(Graphic_var(my_tk->chunk(Unicode::to_CORBA(Babylon::String("green")))), 0., 0., 0.)), 0.5)), index);
    index.col = 1;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_lk->margin_flexible(Graphic_var(my_wk->slider(item.green, xaxis)), 100., 100., 100.)), 0.5)), index);

    index.row = 3;
    index.col = 0;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_ttk->rgb(Graphic_var(my_tk->chunk(Unicode::to_CORBA(Babylon::String("blue")))), 0., 0., 0.)), 0.5)), index);
    index.col = 1;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_lk->margin_flexible(Graphic_var(my_wk->slider(item.blue, xaxis)), 100., 100., 100.)), 0.5)), index);

    index.row = 4;
    index.col = 0;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_ttk->rgb(Graphic_var(my_tk->chunk(Unicode::to_CORBA(Babylon::String("z rotation")))), 0., 0., 0.)), 0.5)), index);
    index.col = 1;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_lk->margin_flexible(Graphic_var(my_wk->slider(item.zrotation, xaxis)), 100., 100., 100.)), 0.5)), index);
    
    index.row = 5;
    index.col = 0;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_ttk->rgb(Graphic_var(my_tk->chunk(Unicode::to_CORBA(Babylon::String("y rotation")))), 0., 0., 0.)), 0.5)), index);
    index.col = 1;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_lk->margin_flexible(Graphic_var(my_wk->slider(item.yrotation, xaxis)), 100., 100., 100.)), 0.5)), index);

    index.row = 6;
    index.col = 0;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_ttk->rgb(Graphic_var(my_tk->chunk(Unicode::to_CORBA(Babylon::String("zoom")))), 0., 0., 0.)), 0.5)), index);
    index.col = 1;
    grid->replace(Graphic_var(my_lk->valign(Graphic_var(my_lk->margin_flexible(Graphic_var(my_wk->slider(item.zoom, xaxis)), 100., 100., 100.)), 0.5)), index);

    Graphic_var hbox = my_lk->hbox();
    hbox->append_graphic(Graphic_var(my_lk->hfill()));
    Graphic_var glyph =
    my_tk->chunk(Unicode::to_CORBA(Babylon::String("done")));
    Graphic_var dlabel = my_lk->margin(glyph, 20.);
    Trigger_var done =
    my_wk->button(Graphic_var(my_ttk->rgb(dlabel, 0., 0., 0.)),
              Command::_nil());
    hbox->append_graphic(done);
    hbox->append_graphic(Graphic_var(my_lk->hfill()));

    Graphic_var vbox = my_lk->vbox();
    vbox->append_graphic(Graphic_var(my_lk->vspace(200.)));
    vbox->append_graphic(grid);
    vbox->append_graphic(Graphic_var(my_lk->vspace(200.)));
    vbox->append_graphic(hbox);
    ToolKit::FrameSpec outset;
    outset.brightness(0.5); outset._d(ToolKit::outset);
    Controller_var root = my_ttk->group(Graphic_var(my_ttk->frame(Graphic_var(my_lk->margin(vbox, 100.)), 10., outset, true)));
    Window_var window = my_dk->transient(root);
    item.settings = my_dk->map(window, true);
    done->action(Command_var(my_dk->map(window, false)));
    return item;
}
