 /*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.ca> 
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
#include "Warsaw/ServerContext.hh"
#include "Application.hh"
#include "LayoutDemo.hh"
#include "TextDemo.hh"
#include "EditTextDemo.hh"
#include "RasterDemo.hh"
#include "TransformDemo.hh"
#include "LogoDemo.hh"
#include "FocusDemo.hh"
#include "ViewportDemo.hh"

using namespace Prague;

bool running;

struct Dump : Signal::Notifier 
{
  void notify(int signal)
    {
      if (signal != Signal::interrupt)
	{
	  Logger::dump(cerr);
	  exit(-1);
	}
      else running = false;
    }
};

int main(int argc, char **argv)
{
  Dump *dump = new Dump;
  Signal::set(Signal::abort, dump);
  Signal::set(Signal::segv, dump);
  CORBA::ORB_ptr orb = CORBA::ORB_init(argc,argv,"omniORB2");
  CORBA::BOA_ptr boa = orb->BOA_init(argc,argv,"omniORB2_BOA");
  boa->impl_is_ready(0,1);
  Logger::log(Logger::corba) << "connected to CORBA library" << endl;

  CosNaming::NamingContext_var context = resolve_init<CosNaming::NamingContext>(orb, "NameService");
  ServerContextManager_var manager = resolve_name<ServerContextManager>(context, interface(ServerContextManager));
  Logger::log(Logger::corba) << "got server context manager" << endl;

  Application *application = new Application(manager);
  Logger::log(Logger::corba) << "built application object" << endl;

  LayoutDemo *layout = new LayoutDemo(application);
  Logger::log(Logger::corba) << "built layout demo" << endl;

  TextDemo *text = new TextDemo(application);
  Logger::log(Logger::corba) << "built text demo" << endl;

  EditTextDemo *etext = new EditTextDemo(application);
  Logger::log(Logger::corba) << "built editable text demo" << endl;

  RasterDemo *raster = new RasterDemo(application);
  Logger::log(Logger::corba) << "built raster demo" << endl;

  TransformDemo *transform = new TransformDemo(application);
  Logger::log(Logger::corba) << "built transform demo" << endl;

  LogoDemo *logo = new LogoDemo(application);
  Logger::log(Logger::corba) << "built logo demo" << endl;

  FocusDemo *focus = new FocusDemo(application);
  Logger::log(Logger::corba) << "built focus demo" << endl;

  ViewportDemo *viewport = new ViewportDemo(application);
  Logger::log(Logger::corba) << "built focus demo" << endl;

  application->run();
  delete viewport;
  delete focus;
  delete logo;
  delete transform;
  delete raster;
  delete etext;
  delete text;
  delete layout;
  delete application;
}
