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

#include "Warsaw/config.hh"
#include "Warsaw/resolve.hh"
#include "Application.hh"
#include "Warsaw/DrawingKit.hh"
#include "Warsaw/Image.hh"
#include "Warsaw/Window.hh"

using namespace Prague;

void Application::Mapper::execute(const CORBA::Any &)
{
  for (Application::list_t::iterator i = examples.begin(); i != examples.end(); i++)
    if ((*i).toggle->test(Telltale::chosen))
      {
	CORBA::Any any;
	(*i).map->execute(any);
	return;
      }
}

class ExitCommand : implements(Command) 
{
 public:
  void execute(const CORBA::Any &) {
    exit(0);
  }
};

Application::Application(Server_ptr server)
  : client(new ClientContextImpl),
    context(server->newServerContext(ClientContext_var(client->_this()))),
    tk(resolve<TextKit>(context, TextKit_IntfRepoID)),
    dk(resolve<DesktopKit>(context, DesktopKit_IntfRepoID)),
    lk(resolve<LayoutKit>(context, LayoutKit_IntfRepoID)),
    wk(resolve<WidgetKit>(context, WidgetKit_IntfRepoID)),
    fk(resolve<FigureKit>(context, FigureKit_IntfRepoID)),
    ck(resolve<CommandKit>(context, CommandKit_IntfRepoID)),
    ik(resolve<ImageKit>(context, ImageKit_IntfRepoID)),
    vbox(lk->vbox()),
    exclusive(wk->exclusive()),
    mapper(new Mapper(examples))
{
  char *berlin_root = getenv("BERLIN_ROOT");
  background.red = background.green = background.blue = 0.6; background.alpha = 1.;
  Raster_var raster = ik->create((string(berlin_root) + string("/etc/PNG/berlin-48.png")).c_str());
  Image_var  image = fk->pixmap(raster);
  Graphic_var hbox = lk->hbox();
  hbox->append(image);
  hbox->append(Graphic_var(lk->hfil()));
  vbox->append(hbox);

  Graphic_var glyph1 = tk->chunk(Unicode::toCORBA(Unicode::String("close")));
  done = lk->margin(glyph1, 20.);
}

void Application::append(Controller_ptr demo, const Unicode::String &name)
{
  Controller_var toggle = wk->toggle(Graphic_var(lk->fixedSize(Graphic_var(Graphic::_nil()), 50., 50.)), background);
  exclusive->add(toggle);
  Graphic_var hbox = lk->hbox();
  Trigger_var button = wk->button(done, background, Command_var(Command::_nil()));
  hbox->append(Graphic_var(lk->hfil()));
  hbox->append(button);
  hbox->append(Graphic_var(lk->hfil()));
  Graphic_var vb = lk->vbox();
  vb->append(demo);
  vb->append(hbox);
  Controller_var group = wk->group(vb);
  group->appendController(demo);
  group->appendController(button);
  Window_var window = dk->transient(group);
  Command_var unmap = window->map(false);
  button->action(unmap);
  examples.push_back(item(toggle, Command_var(window->map(true))));
  hbox = lk->hbox();
  Graphic_var space = lk->hspace(200.);
  Graphic_var label = tk->chunk(Unicode::toCORBA(name));
  hbox->append(Graphic_var(lk->align(toggle, 0., 0.)));
  hbox->append(space);
  hbox->append(label);
  vbox->append(hbox);
}

void Application::run()
{
  vbox->append(Graphic_var(lk->vspace(200.)));
  Graphic_var hbox = lk->hbox();
  hbox->append(Graphic_var(lk->hglue(200., 0., 10000.)));
  Graphic_var glyph1 = tk->chunk(Unicode::toCORBA(Unicode::String("run")));
  Graphic_var label1 = lk->margin(glyph1, 20.);
  Trigger_var run = wk->button(label1, background, Command_var(mapper->_this()));
  hbox->append(run);
  hbox->append(Graphic_var(lk->vspace(200.)));
  Graphic_var glyph2 = tk->chunk(Unicode::toCORBA(Unicode::String("quit")));
  Graphic_var label2 = lk->margin(glyph2, 20.);
  ExitCommand *cmd = new ExitCommand();
  cmd->_obj_is_ready(CORBA::BOA::getBOA());
  Trigger_var quit = wk->button(label2, background, Command_var(cmd->_this()));
  hbox->append(quit);
  hbox->append(Graphic_var(lk->hglue(200., 0., 10000.)));
  vbox->append(hbox);
  Graphic_var margin = lk->margin(vbox, 200.);
  Controller_var group = wk->group(Graphic_var(wk->outset(margin, background, true)));
  for (list_t::iterator i = examples.begin(); i != examples.end(); i++)
    group->appendController((*i).toggle);
  group->appendController(run);
  group->appendController(quit);
  Window_var window = dk->shell(group);
  while (true) Thread::delay(Prague::Time(1000));
}
