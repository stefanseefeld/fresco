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
#include <Warsaw/resolve.hh>
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/Image.hh>
#include <Warsaw/Window.hh>
#include "Application.hh"

using namespace Prague;
using namespace Warsaw;

class Application::Mapper : public Application::CommandImpl
{
public:
  Mapper(Application::list_t &d, Warsaw::Selection_ptr s) : demos(d), selection(Warsaw::Selection::_duplicate(s)) {}
  virtual void execute(const CORBA::Any &);
private:
  Application::list_t &demos;
  Warsaw::Selection_var selection;
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

Application::Application(ServerContext_ptr sc)
  : _server(ServerContext::_duplicate(sc)),
    _tk(resolve_kit<TextKit>(_server, "IDL:Warsaw/TextKit:1.0")),
    _dk(resolve_kit<DesktopKit>(_server, "IDL:Warsaw/DesktopKit:1.0")),
    _lk(resolve_kit<LayoutKit>(_server, "IDL:Warsaw/LayoutKit:1.0")),
    _ttk(resolve_kit<ToolKit>(_server, "IDL:Warsaw/ToolKit:1.0")),
    _wk(resolve_kit<WidgetKit>(_server, "IDL:Warsaw/WidgetKit:1.0")),
    _fk(resolve_kit<FigureKit>(_server, "IDL:Warsaw/FigureKit:1.0")),
    _ck(resolve_kit<CommandKit>(_server, "IDL:Warsaw/CommandKit:1.0")),
    _ik(resolve_kit<ImageKit>(_server, "IDL:Warsaw/ImageKit:1.0")),
    _gk(resolve_kit<GadgetKit>(_server, "IDL:Warsaw/GadgetKit:1.0")),
    _pk(resolve_kit<PrimitiveKit>(_server, "IDL:Warsaw/PrimitiveKit:1.0")),
    _vbox(_lk->vbox()),
    _choice(_wk->toggle_choice()),
    _mapper(new Mapper(_demos, Selection_var(_choice->state())))
{
  _background.red = _background.green = _background.blue = 0.6; _background.alpha = 1.;
  Raster_var raster = _ik->create("berlin-48.png");
  Image_var  image = _fk->pixmap(raster);
  Graphic_var hbox = _lk->hbox();
  hbox->append_graphic(image);
  hbox->append_graphic(Graphic_var(_lk->hfill()));
  _vbox->append_graphic(hbox);

  Graphic_var glyph = _tk->chunk(Unicode::to_CORBA(Babylon::String("close")));
  _done = _lk->margin(Graphic_var(_ttk->rgb(glyph, 0., 0., 0.)), 20.);
  glyph = _tk->chunk(Unicode::to_CORBA(Babylon::String("settings")));
  _settings = _lk->margin(Graphic_var(_ttk->rgb(glyph, 0., 0., 0.)), 20.);
}

void Application::append(Controller_ptr demo, const Babylon::String &name)
{
  Item item = make_item(name);

  Graphic_var hbox = _lk->hbox();
  hbox->append_graphic(Graphic_var(_lk->hfill()));
  Trigger_var button1 = _wk->button(_done, Command_var(Command::_nil()));
  hbox->append_graphic(button1);
  hbox->append_graphic(Graphic_var(_lk->hspace(200.)));
  Trigger_var button2 = _wk->button(_settings, item.settings);
  hbox->append_graphic(button2);
  hbox->append_graphic(Graphic_var(_lk->hfill()));
  Graphic_var vb = _lk->vbox();
  vb->append_graphic(demo);
  vb->append_graphic(hbox);

  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::outset);
  Graphic_var decorator = _ttk->frame(vb, 20., spec, true);
  decorator = _gk->alpha(decorator, item.alpha);
  decorator = _gk->lighting(decorator, item.red, item.green, item.blue);
  decorator = _gk->rotator(decorator, item.zrotation, zaxis);
  decorator = _gk->rotator(decorator, item.yrotation, yaxis);
  decorator = _gk->zoomer(decorator, item.zoom);

  Controller_var group = _ttk->group(Graphic_var(_lk->align(decorator, 0., 0.)));
  group->append_controller(demo);
  group->append_controller(button1);
  group->append_controller(button2);
  Window_var window = _dk->transient(group);
  button1->action(Command_var(_dk->map(window, false)));
  item.mapper = _dk->map(window, true);
  _demos.push_back(item);
}

void Application::run()
{

  _vbox->append_graphic(Graphic_var(_lk->vspace(200.)));
  ToolKit::FrameSpec spec;
  spec.brightness(0.5); spec._d(ToolKit::concav);
  _vbox->append_graphic(Graphic_var(_ttk->frame(_choice, 40., spec, false)));
  _vbox->append_graphic(Graphic_var(_lk->vspace(200.)));
  Graphic_var glyph1 = _tk->chunk(Unicode::to_CORBA(Babylon::String("run")));
  Graphic_var label1 = _lk->margin(glyph1, 20.);
  Trigger_var run = _wk->button(Graphic_var(_ttk->rgb(label1, 0., 0., 0.)), Command_var(_mapper->_this()));
  Graphic_var glyph2 = _tk->chunk(Unicode::to_CORBA(Babylon::String("quit")));
  Graphic_var label2 = _lk->margin(glyph2, 20.);
  ExitCommand *cmd = new ExitCommand();
  Trigger_var quit = _wk->button(Graphic_var(_ttk->rgb(label2, 0., 0., 0.)), Command_var(cmd->_this()));

  _vbox->append_graphic(Graphic_var(_lk->vspace(200.)));

  Graphic_var hbox = _lk->hbox();
  hbox->append_graphic(Graphic_var(_lk->hglue(200., 0., 10000.)));
  hbox->append_graphic(run);
  hbox->append_graphic(Graphic_var(_lk->hspace(200.)));
  hbox->append_graphic(quit);
  hbox->append_graphic(Graphic_var(_lk->hglue(200., 0., 10000.)));
  _vbox->append_graphic(hbox);
  Graphic_var margin = _lk->margin(_vbox, 200.);
  
  spec.brightness(1.0); spec._d(ToolKit::outset);
  Controller_var group = _ttk->group(Graphic_var(_ttk->frame(margin, 10., spec, true)));
  group->append_controller(_choice);
  group->append_controller(run);
  group->append_controller(quit);
  Window_var window = _dk->shell(group);
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
  Controller_var root = _ttk->group(Graphic_var(_ttk->frame(Graphic_var(_lk->margin(vbox, 100.)), 20., outset, true)));
  Window_var window = _dk->transient(root);
  item.settings = _dk->map(window, true);
  done->action(Command_var(_dk->map(window, false)));
  return item;
}
