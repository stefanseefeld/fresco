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

Application::Application(Server_ptr server)
  : client(new ClientContextImpl),
    context(server->newServerContext(ClientContext_var(client->_this()))),
    tk(resolve_kit<TextKit>(context, TextKit_IntfRepoID)),
    dk(resolve_kit<DesktopKit>(context, DesktopKit_IntfRepoID)),
    lk(resolve_kit<LayoutKit>(context, LayoutKit_IntfRepoID)),
    ttk(resolve_kit<ToolKit>(context, ToolKit_IntfRepoID)),
    wk(resolve_kit<WidgetKit>(context, WidgetKit_IntfRepoID)),
    fk(resolve_kit<FigureKit>(context, FigureKit_IntfRepoID)),
    ck(resolve_kit<CommandKit>(context, CommandKit_IntfRepoID)),
    ik(resolve_kit<ImageKit>(context, ImageKit_IntfRepoID)),
    gk(resolve_kit<GadgetKit>(context, GadgetKit_IntfRepoID)),
    vbox(lk->vbox()),
    choice(wk->toggleChoice()),
    alpha(ck->bvalue(0., 1., 1., 0.1, 0.1)),
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

  Graphic_var glyph1 = tk->chunk(Unicode::toCORBA(Unicode::String("close")));
  done = lk->margin(Graphic_var(ttk->rgb(glyph1, 0., 0., 0.)), 20.);
}

void Application::append(Controller_ptr demo, const Unicode::String &name)
{
  Graphic_var hbox = lk->hbox();
  Trigger_var button = wk->button(done, Command_var(Command::_nil()));
  hbox->append(Graphic_var(lk->hfil()));
  hbox->append(button);
  hbox->append(Graphic_var(lk->hfil()));
  Graphic_var vb = lk->vbox();
  vb->append(demo);
  vb->append(hbox);
  ToolKit::FrameSpec spec;
  spec.bbrightness(0.5);
  Controller_var group = ttk->group(Graphic_var(gk->alpha(Graphic_var(ttk->frame(vb, 20., spec, true)), alpha)));
  group->appendController(demo);
  group->appendController(button);
  Window_var window = dk->transient(group);
  Command_var unmap = window->map(false);
  button->action(unmap);

  Graphic_var label = tk->chunk(Unicode::toCORBA(name));
  Tag tag = choice->appendItem(Graphic_var(ttk->rgb(label, 0., 0., 0.)));
  demos.push_back(Item(tag, Command_var(window->map(true))));
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

  Graphic_var hbox = lk->hbox();
  hbox->append(Graphic_var(lk->hglue(200., 0., 10000.)));
  hbox->append(Graphic_var(wk->slider(alpha, xaxis)));
  hbox->append(Graphic_var(lk->hglue(200., 0., 10000.)));
  vbox->append(Graphic_var(lk->hspace(200.)));
  vbox->append(hbox);
  vbox->append(Graphic_var(lk->vspace(200.)));

  hbox = lk->hbox();
  hbox->append(Graphic_var(lk->hglue(200., 0., 10000.)));
  hbox->append(run);
  hbox->append(Graphic_var(lk->hspace(200.)));
  hbox->append(quit);
  hbox->append(Graphic_var(lk->hglue(200., 0., 10000.)));
  vbox->append(Graphic_var(lk->margin(hbox, 200.)));
  Graphic_var margin = lk->margin(vbox, 200.);
  
  spec.bbrightness(1.0);
  Controller_var group = ttk->group(Graphic_var(ttk->frame(margin, 10., spec, true)));
  group->appendController(choice);
  group->appendController(run);
  group->appendController(quit);
  Window_var window = dk->shell(group);
  while (true) Thread::delay(Prague::Time(1000));
}
