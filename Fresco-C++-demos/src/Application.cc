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
  PrintCommand(Window_var w, Application *a) : _w(w), _a(a) {}
  virtual void execute(const CORBA::Any &any)
  {
    Command_var(_a->_ck->print(_a->_ttk->rgb(_a->_lk->fixed_size(_a->_lk->align(_w, 0., 0.), _w->size().x, _w->size().y), 0.8, 0.8, 0.8)))->execute(any);
  }
private:
  Window_var _w;
  Application *_a;
};

class Application::Mapper : public Application::CommandImpl
{
public:
  Mapper(Application::list_t &d, Fresco::Selection_ptr s) : demos(d), selection(Fresco::Selection::_duplicate(s)) {}
  virtual void execute(const CORBA::Any &);
private:
  Application::list_t &demos;
  Fresco::Selection_var selection;
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
  Selection::Items *items = selection->toggled();
  if (!items->length()) return;
  Tag t = (*items)[items->length() - 1];
  delete items;
  CORBA::Any any;
  for (Application::list_t::iterator i = demos.begin(); i != demos.end(); i++)
    if (t == (*i).id) (*i).mapper->execute(any);
}

class ExitCommand : public Application::CommandImpl
{
 public:
  void execute(const CORBA::Any &) { exit(0); }
};

Application::Application(ServerContext_ptr sc, ClientContext_ptr cc)
  : _server(ServerContext::_duplicate(sc)),
    _client(ClientContext::_duplicate(cc)),
    _tk(::resolve_kit<TextKit>(_server, "IDL:fresco.org/Fresco/TextKit:1.0")),
    _dk(::resolve_kit<DesktopKit>(_server, "IDL:fresco.org/Fresco/DesktopKit:1.0")),
    _lk(::resolve_kit<LayoutKit>(_server, "IDL:fresco.org/Fresco/LayoutKit:1.0")),
    _ttk(::resolve_kit<ToolKit>(_server, "IDL:fresco.org/Fresco/ToolKit:1.0")),
    _wk(::resolve_kit<WidgetKit>(_server, "IDL:fresco.org/Fresco/WidgetKit:1.0")),
    _fk(::resolve_kit<FigureKit>(_server, "IDL:fresco.org/Fresco/FigureKit:1.0")),
    _ck(::resolve_kit<CommandKit>(_server, "IDL:fresco.org/Fresco/CommandKit:1.0")),
    _ik(::resolve_kit<ImageKit>(_server, "IDL:fresco.org/Fresco/ImageKit:1.0")),
    _gk(::resolve_kit<GadgetKit>(_server, "IDL:fresco.org/Fresco/GadgetKit:1.0")),
    _vbox(_lk->vbox()),
    _choice(_wk->toggle_choice()),
    _mapper(new Mapper(_demos, Selection_var(_choice->state())))
{
  _background.red = _background.green = _background.blue = 0.6; _background.alpha = 1.;
  Raster_var raster = _ik->create("fresco.png");
  Image_var  image = _fk->pixmap(raster);
  Graphic_var hbox = _lk->hbox();
  Graphic_var vbox = _lk->vbox();
  Graphic_var use1 = _tk->chunk(Unicode::to_CORBA(Babylon::String("Select a")));
  Graphic_var use2 = _tk->chunk(Unicode::to_CORBA(Babylon::String("demo:")));
  vbox->append_graphic(Graphic_var(_lk->vfill()));
  vbox->append_graphic(use1);
  vbox->append_graphic(use2);
  vbox->append_graphic(Graphic_var(_lk->vfill()));
  Graphic_var black_usage = _ttk->rgb(vbox, 0., 0., 0.);
  hbox->append_graphic(Graphic_var(_lk->hfill()));
  hbox->append_graphic(black_usage);
  hbox->append_graphic(Graphic_var(_lk->hfill()));
  hbox->append_graphic(image);
  _vbox->append_graphic(hbox);

  Graphic_var glyph = _tk->chunk(Unicode::to_CORBA(Babylon::String("close")));
  _done = _lk->margin(Graphic_var(_ttk->rgb(glyph, 0., 0., 0.)), 20.);
  glyph = _tk->chunk(Unicode::to_CORBA(Babylon::String("settings")));
  _settings = _lk->margin(Graphic_var(_ttk->rgb(glyph, 0., 0., 0.)), 20.);
  glyph = _tk->chunk(Unicode::to_CORBA(Babylon::String("print")));
  _print = _lk->margin(Graphic_var(_ttk->rgb(glyph, 0., 0., 0.)), 20.);
}

void Application::append(Controller_ptr demo, const Babylon::String &name)
{
  Item item = make_item(name);

  Graphic_var vb = _lk->vbox();

  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::outset);
  Graphic_var decorator = _ttk->frame(vb, 10., spec, true);

  Graphic_var hbox = _lk->hbox();
  hbox->append_graphic(Graphic_var(_lk->hfill()));
  Trigger_var button1 = _wk->button(_done, Command_var(Command::_nil()));
  hbox->append_graphic(button1);
  hbox->append_graphic(Graphic_var(_lk->hspace(200.)));
  Trigger_var button2 = _wk->button(_settings, item.settings);
  hbox->append_graphic(button2);
  hbox->append_graphic(Graphic_var(_lk->hspace(200.)));
  Trigger_var button3 = _wk->button(_print, Command_var(Command::_nil()));
  hbox->append_graphic(button3);
  hbox->append_graphic(Graphic_var(_lk->hfill()));
  vb->append_graphic(demo);
  vb->append_graphic(hbox);

  decorator = _gk->alpha(decorator, item.alpha);
  decorator = _gk->lighting(decorator, item.red, item.green, item.blue);
  decorator = _gk->rotator(decorator, item.zrotation, zaxis);
  decorator = _gk->rotator(decorator, item.yrotation, yaxis);
  decorator = _gk->zoomer(decorator, item.zoom);

  Controller_var group = _ttk->group(Graphic_var(_lk->align(decorator, 0., 0.)));
  group->append_controller(demo);
  group->append_controller(button1);
  group->append_controller(button2);
  group->append_controller(button3);
  Window_var window = _dk->transient(group);
  PrintCommand *_pc = new PrintCommand(window, this);
  button1->action(Command_var(_dk->map(window, false)));
  button3->action(Command_var(_pc->_this()));
  item.mapper = _dk->map(window, true);
  _demos.push_back(item);
}

void Application::run()
{
  _vbox->append_graphic(Graphic_var(_lk->vspace(200.)));
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::concav);
  _vbox->append_graphic(Graphic_var(_ttk->frame(_choice, 20., spec, false)));
  _vbox->append_graphic(Graphic_var(_lk->vspace(200.)));

  // run button
  Graphic_var glyph1 = _tk->chunk(Unicode::to_CORBA(Babylon::String("run")));
  Graphic_var label1 = _lk->margin(glyph1, 20.);
  Graphic_var label1f = _lk->hmargin_lr_flexible(label1,
                                                0,100000,0,
                                                0,100000,0);
  Trigger_var run = _wk->button(Graphic_var(_ttk->rgb(label1f, 0., 0., 0.)), 
                                Command_var(_mapper->_this()));

  // quit button
  Graphic_var glyph2 = _tk->chunk(Unicode::to_CORBA(Babylon::String("quit")));
  Graphic_var label2 = _lk->margin(glyph2, 20.);
  ExitCommand *cmd = new ExitCommand();
  Graphic_var label2f = _lk->hmargin_lr_flexible(label2,
                                                0,100000,0,
                                                0,100000,0);
  Trigger_var quit = _wk->button(Graphic_var(_ttk->rgb(label2f, 0., 0., 0.)), 
                                 Command_var(cmd->_this()));

  Graphic_var hbox = _lk->hbox();
  hbox->append_graphic(run);
  hbox->append_graphic(Graphic_var(_lk->hspace(200.)));
  hbox->append_graphic(quit);
  _vbox->append_graphic(hbox);
  Graphic_var margin = _lk->margin(_vbox, 200.);
  
  spec.brightness(1.0); spec._d(ToolKit::outset);
  Controller_var group = _ttk->group(Graphic_var(_ttk->frame(margin, 10., spec, true)));
  group->append_controller(_choice);
  group->append_controller(run);
  group->append_controller(quit);
  Window_var window = _dk->shell(group, _client);
  while (true) Thread::delay(Prague::Time(1000));
}

Application::Item Application::make_item(const Babylon::String &name)
{
  Item item;

  /*
   * insert an item into the choice
   */
  Graphic_var label = _tk->chunk(Unicode::to_CORBA(name));
  item.id = _choice->append_item(Graphic_var(_ttk->rgb(label, 0., 0., 0.)));
  /*
   * create the control elements
   */
  item.alpha = _ck->bvalue(0., 1., 1., 0.1, 0.1);
  item.red = _ck->bvalue(0., 1., 1., 0.1, 0.1);
  item.blue = _ck->bvalue(0., 1., 1., 0.1, 0.1);
  item.green = _ck->bvalue(0., 1., 1., 0.1, 0.1);
  item.zrotation = _ck->bvalue(0., 360., 0., 5., 5.);
  item.yrotation = _ck->bvalue(0., 360., 0., 5., 5.);
  item.zoom = _ck->bvalue(-1., 1., 0., 0.1, 0.1);
  
  /*
   * create the settings window
   */
  Layout::Grid::Index index;
  index.col = 2, index.row = 7;
  Layout::Grid_var grid = _lk->fixed_grid(index);
  index.row = 0;
  index.col = 0;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_ttk->rgb(Graphic_var(_tk->chunk(Unicode::to_CORBA(Babylon::String("alpha")))),
							      0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_lk->margin_flexible(Graphic_var(_wk->slider(item.alpha, xaxis)),
									 100., 100., 100.)), 0.5)), index);

  index.row = 1;
  index.col = 0;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_ttk->rgb(Graphic_var(_tk->chunk(Unicode::to_CORBA(Babylon::String("red")))),
							      0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_lk->margin_flexible(Graphic_var(_wk->slider(item.red, xaxis)),
									 100., 100., 100.)), 0.5)), index);

  index.row = 2;
  index.col = 0;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_ttk->rgb(Graphic_var(_tk->chunk(Unicode::to_CORBA(Babylon::String("green")))),
							      0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_lk->margin_flexible(Graphic_var(_wk->slider(item.green, xaxis)),
									 100., 100., 100.)), 0.5)), index);

  index.row = 3;
  index.col = 0;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_ttk->rgb(Graphic_var(_tk->chunk(Unicode::to_CORBA(Babylon::String("blue")))),
							      0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_lk->margin_flexible(Graphic_var(_wk->slider(item.blue, xaxis)),
									 100., 100., 100.)), 0.5)), index);

  index.row = 4;
  index.col = 0;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_ttk->rgb(Graphic_var(_tk->chunk(Unicode::to_CORBA(Babylon::String("z rotation")))),
							      0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_lk->margin_flexible(Graphic_var(_wk->slider(item.zrotation, xaxis)),
									 100., 100., 100.)), 0.5)), index);

  index.row = 5;
  index.col = 0;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_ttk->rgb(Graphic_var(_tk->chunk(Unicode::to_CORBA(Babylon::String("y rotation")))),
							      0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_lk->margin_flexible(Graphic_var(_wk->slider(item.yrotation, xaxis)),
									 100., 100., 100.)), 0.5)), index);

  index.row = 6;
  index.col = 0;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_ttk->rgb(Graphic_var(_tk->chunk(Unicode::to_CORBA(Babylon::String("zoom")))),
							      0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(_lk->valign(Graphic_var(_lk->margin_flexible(Graphic_var(_wk->slider(item.zoom, xaxis)),
									 100., 100., 100.)), 0.5)), index);

  Graphic_var hbox = _lk->hbox();
  hbox->append_graphic(Graphic_var(_lk->hfill()));
  Graphic_var glyph = _tk->chunk(Unicode::to_CORBA(Babylon::String("done")));
  Graphic_var dlabel = _lk->margin(glyph, 20.);
  Trigger_var done = _wk->button(Graphic_var(_ttk->rgb(dlabel, 0., 0., 0.)), Command::_nil());
  hbox->append_graphic(done);
  hbox->append_graphic(Graphic_var(_lk->hfill()));

  Graphic_var vbox = _lk->vbox();
  vbox->append_graphic(Graphic_var(_lk->vspace(200.)));
  vbox->append_graphic(grid);
  vbox->append_graphic(Graphic_var(_lk->vspace(200.)));
  vbox->append_graphic(hbox);
  ToolKit::FrameSpec outset;
  outset.brightness(0.5); outset._d(ToolKit::outset);
  Controller_var root = _ttk->group(Graphic_var(_ttk->frame(Graphic_var(_lk->margin(vbox, 100.)), 10., outset, true)));
  Window_var window = _dk->transient(root);
  item.settings = _dk->map(window, true);
  done->action(Command_var(_dk->map(window, false)));
  return item;
}
