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
#include "Application.hh"
#include <Warsaw/DrawingKit.hh>
#include <Warsaw/Image.hh>
#include <Warsaw/Window.hh>

using namespace Prague;

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

class ExitCommand : implements(Command) 
{
 public:
  void execute(const CORBA::Any &) { exit(0);}
};

Application::Application(Warsaw *warsaw)
  : tk(warsaw->resolve<TextKit>(interface(TextKit))),
    dk(warsaw->resolve<DesktopKit>(interface(DesktopKit))),
    lk(warsaw->resolve<LayoutKit>(interface(LayoutKit))),
    ttk(warsaw->resolve<ToolKit>(interface(ToolKit))),
    wk(warsaw->resolve<WidgetKit>(interface(WidgetKit))),
    fk(warsaw->resolve<FigureKit>(interface(FigureKit))),
    ck(warsaw->resolve<CommandKit>(interface(CommandKit))),
    ik(warsaw->resolve<ImageKit>(interface(ImageKit))),
    gk(warsaw->resolve<GadgetKit>(interface(GadgetKit))),
    vbox(lk->vbox()),
    choice(wk->toggleChoice()),
    mapper(new Mapper(demos, Selection_var(choice->state())))
{
  char *berlin_root = getenv("BERLIN_ROOT");
  // This should be changed to throwing a InitException or something - Jonas
  if (!berlin_root)
    {
      cerr << "Please set environment variabled BERLIN_ROOT first" << endl;
      exit(-1);
    }

  background.red = background.green = background.blue = 0.6; background.alpha = 1.;
  Raster_var raster = ik->create((string(berlin_root) + string("/etc/PNG/berlin-48.png")).c_str());
  Image_var  image = fk->pixmap(raster);
  Graphic_var hbox = lk->hbox();
  hbox->append(image);
  hbox->append(Graphic_var(lk->hfil()));
  vbox->append(hbox);

  Graphic_var glyph = tk->chunk(Unicode::toCORBA(Unicode::String("close")));
  done = lk->margin(Graphic_var(ttk->rgb(glyph, 0., 0., 0.)), 20.);
  glyph = tk->chunk(Unicode::toCORBA(Unicode::String("settings")));
  settings = lk->margin(Graphic_var(ttk->rgb(glyph, 0., 0., 0.)), 20.);
}

void Application::append(Controller_ptr demo, const Unicode::String &name)
{
  Item item = makeItem(name);

  Graphic_var hbox = lk->hbox();
  hbox->append(Graphic_var(lk->hfil()));
  Trigger_var button1 = wk->button(done, Command_var(Command::_nil()));
  hbox->append(button1);
  hbox->append(Graphic_var(lk->hspace(200.)));
  Trigger_var button2 = wk->button(settings, item.settings);
  hbox->append(button2);
  hbox->append(Graphic_var(lk->hfil()));
  Graphic_var vb = lk->vbox();
  vb->append(demo);
  vb->append(hbox);

  ToolKit::FrameSpec spec;
  spec.bbrightness(0.5);
  Graphic_var decorator = ttk->frame(vb, 20., spec, true);
  decorator = gk->alpha(decorator, item.alpha);
  decorator = gk->lighting(decorator, item.red, item.green, item.blue);
  decorator = gk->rotator(decorator, item.zrotation, zaxis);
  decorator = gk->rotator(decorator, item.yrotation, yaxis);
  decorator = gk->zoomer(decorator, item.zoom);

  Controller_var group = ttk->group(Graphic_var(lk->align(decorator, 0., 0.)));
  group->appendController(demo);
  group->appendController(button1);
  group->appendController(button2);
  Window_var window = dk->transient(group);
  button1->action(Command_var(window->map(false)));
  item.mapper = window->map(true);
  demos.push_back(item);
}

void Application::run()
{
  vbox->append(Graphic_var(lk->vspace(200.)));
  ToolKit::FrameSpec spec;
  spec.dbrightness(0.5);
  vbox->append(Graphic_var(ttk->frame(choice, 20., spec, false)));
  vbox->append(Graphic_var(lk->vspace(200.)));
  Graphic_var glyph1 = tk->chunk(Unicode::toCORBA(Unicode::String("run")));
  Graphic_var label1 = lk->margin(glyph1, 20.);
  Trigger_var run = wk->button(Graphic_var(ttk->rgb(label1, 0., 0., 0.)), Command_var(mapper->_this()));
  Graphic_var glyph2 = tk->chunk(Unicode::toCORBA(Unicode::String("quit")));
  Graphic_var label2 = lk->margin(glyph2, 20.);
  ExitCommand *cmd = new ExitCommand();
  cmd->_obj_is_ready(CORBA::BOA::getBOA());
  Trigger_var quit = wk->button(Graphic_var(ttk->rgb(label2, 0., 0., 0.)), Command_var(cmd->_this()));

  vbox->append(Graphic_var(lk->vspace(200.)));

  Graphic_var hbox = lk->hbox();
  hbox->append(Graphic_var(lk->hglue(200., 0., 10000.)));
  hbox->append(run);
  hbox->append(Graphic_var(lk->hspace(200.)));
  hbox->append(quit);
  hbox->append(Graphic_var(lk->hglue(200., 0., 10000.)));
  vbox->append(hbox);
  Graphic_var margin = lk->margin(vbox, 200.);
  
  spec.bbrightness(1.0);
  Controller_var group = ttk->group(Graphic_var(ttk->frame(margin, 10., spec, true)));
  group->appendController(choice);
  group->appendController(run);
  group->appendController(quit);
  Window_var window = dk->shell(group);
  while (true) Thread::delay(Prague::Time(1000));
}

Application::Item Application::makeItem(const Unicode::String &name)
{
  Item item;

  /*
   * insert an item into the choice
   */
  Graphic_var label = tk->chunk(Unicode::toCORBA(name));
  item.id = choice->appendItem(Graphic_var(ttk->rgb(label, 0., 0., 0.)));
  /*
   * create the control elements
   */
  item.alpha = ck->bvalue(0., 1., 1., 0.1, 0.1);
  item.red = ck->bvalue(0., 1., 1., 0.1, 0.1);
  item.blue = ck->bvalue(0., 1., 1., 0.1, 0.1);
  item.green = ck->bvalue(0., 1., 1., 0.1, 0.1);
  item.zrotation = ck->bvalue(0., 360., 0., 5., 5.);
  item.yrotation = ck->bvalue(0., 360., 0., 5., 5.);
  item.zoom = ck->bvalue(-1., 1., 0., 0.1, 0.1);

  /*
   * create the settings window
   */
  Grid::Index index;
  index.col = 2, index.row = 7;
  Grid_var grid = lk->fixedGrid(index);
  index.row = 0;
  index.col = 0;
  grid->replace(Graphic_var(lk->valign(Graphic_var(ttk->rgb(Graphic_var(tk->chunk(Unicode::toCORBA(Unicode::String("alpha")))),
							    0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(lk->valign(Graphic_var(lk->marginFlexible(Graphic_var(wk->slider(item.alpha, xaxis)),
								      100., 100., 100.)), 0.5)), index);

  index.row = 1;
  index.col = 0;
  grid->replace(Graphic_var(lk->valign(Graphic_var(ttk->rgb(Graphic_var(tk->chunk(Unicode::toCORBA(Unicode::String("red")))),
							    0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(lk->valign(Graphic_var(lk->marginFlexible(Graphic_var(wk->slider(item.red, xaxis)),
								      100., 100., 100.)), 0.5)), index);

  index.row = 2;
  index.col = 0;
  grid->replace(Graphic_var(lk->valign(Graphic_var(ttk->rgb(Graphic_var(tk->chunk(Unicode::toCORBA(Unicode::String("green")))),
							    0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(lk->valign(Graphic_var(lk->marginFlexible(Graphic_var(wk->slider(item.green, xaxis)),
								      100., 100., 100.)), 0.5)), index);

  index.row = 3;
  index.col = 0;
  grid->replace(Graphic_var(lk->valign(Graphic_var(ttk->rgb(Graphic_var(tk->chunk(Unicode::toCORBA(Unicode::String("blue")))),
							    0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(lk->valign(Graphic_var(lk->marginFlexible(Graphic_var(wk->slider(item.blue, xaxis)),
								      100., 100., 100.)), 0.5)), index);

  index.row = 4;
  index.col = 0;
  grid->replace(Graphic_var(lk->valign(Graphic_var(ttk->rgb(Graphic_var(tk->chunk(Unicode::toCORBA(Unicode::String("z rotation")))),
							    0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(lk->valign(Graphic_var(lk->marginFlexible(Graphic_var(wk->slider(item.zrotation, xaxis)),
								      100., 100., 100.)), 0.5)), index);

  index.row = 5;
  index.col = 0;
  grid->replace(Graphic_var(lk->valign(Graphic_var(ttk->rgb(Graphic_var(tk->chunk(Unicode::toCORBA(Unicode::String("y rotation")))),
							    0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(lk->valign(Graphic_var(lk->marginFlexible(Graphic_var(wk->slider(item.yrotation, xaxis)),
								      100., 100., 100.)), 0.5)), index);

  index.row = 6;
  index.col = 0;
  grid->replace(Graphic_var(lk->valign(Graphic_var(ttk->rgb(Graphic_var(tk->chunk(Unicode::toCORBA(Unicode::String("zoom")))),
							    0., 0., 0.)), 0.5)), index);
  index.col = 1;
  grid->replace(Graphic_var(lk->valign(Graphic_var(lk->marginFlexible(Graphic_var(wk->slider(item.zoom, xaxis)),
								      100., 100., 100.)), 0.5)), index);

  Graphic_var hbox = lk->hbox();
  hbox->append(Graphic_var(lk->hfil()));
  Graphic_var glyph = tk->chunk(Unicode::toCORBA(Unicode::String("done")));
  Graphic_var dlabel = lk->margin(glyph, 20.);
  Trigger_var done = wk->button(Graphic_var(ttk->rgb(dlabel, 0., 0., 0.)), Command::_nil());
  hbox->append(done);
  hbox->append(Graphic_var(lk->hfil()));

  Graphic_var vbox = lk->vbox();
  vbox->append(Graphic_var(lk->vspace(200.)));
  vbox->append(grid);
  vbox->append(Graphic_var(lk->vspace(200.)));
  vbox->append(hbox);
  ToolKit::FrameSpec outset;
  outset.bbrightness(0.5);
  Controller_var root = ttk->group(Graphic_var(ttk->frame(Graphic_var(lk->margin(vbox, 100.)), 20., outset, true)));
  Window_var window = dk->transient(root);
  item.settings = window->map(true);
  done->action(Command_var(window->map(false)));
  return item;
}
