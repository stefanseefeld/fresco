/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@pobox.com> 
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
#include <Warsaw/LayoutKit.hh>
#include <Warsaw/WidgetKit.hh>
#include <Warsaw/DrawingKit.hh>
#include <Berlin/ScreenImpl.hh>
#include <Berlin/ScreenManager.hh>
#include <Berlin/ServerImpl.hh>
#include <Berlin/Logger.hh>
#include <Berlin/DesktopImpl.hh>
#include <Prague/Sys/Signal.hh>
#include <Prague/Sys/Profiler.hh>
#include <Prague/Sys/Timer.hh>
#include <Prague/Sys/GetOpt.hh>

#ifdef JPROF
// probably need to change include path
#include "jprof.h"
#endif

using namespace Prague;

struct Dump : Signal::Notifier 
{
  void notify(int signo)
    {
      switch (signo)
	{
	case Signal::hangup: Profiler::dump(cerr); break;
	case Signal::abort:
	case Signal::segv: Logger::dump(cerr); exit(-1);
	}
    }
};

int main(int argc, char **argv)
{
  Dump *dump = new Dump;
  Signal::set(Signal::abort, dump);
  Signal::set(Signal::segv, dump);
  Signal::set(Signal::hangup, dump);

  CORBA::ORB_ptr orb = CORBA::ORB_init(argc,argv,"omniORB2");
  CORBA::BOA_ptr boa = orb->BOA_init(argc,argv,"omniORB2_BOA");

  GetOpt getopt(argv[0], "a berlin display server");
  getopt.add('v', "version", GetOpt::novalue, "version number");
  getopt.add('h', "help", GetOpt::novalue, "help message");
  getopt.add('l', "logging", GetOpt::novalue, "switch logging on");
  getopt.add('p', "profiling", GetOpt::novalue, "switch profiling on");
  getopt.add('d', "drawing", GetOpt::mandatory, "the DrawingKit to choose");
  getopt.parse(argc - 1, argv + 1);
  string value;
  getopt.get("version", &value);
  if (value == "true") { cout << "version is " << "0.2" << endl; exit(0);}
  value == "";
  getopt.get("help", &value);
  if (value == "true") { getopt.usage(); exit(0);}
  value == "";  
  getopt.get("logging", &value);
  if (value == "true")
    {
      Logger::set(Logger::corba);
      Logger::set(Logger::focus);
      Logger::set(Logger::image);
      Logger::set(Logger::loader);
      Logger::set(Logger::subject);
      Logger::set(Logger::layout);
      Logger::set(Logger::picking);
      Logger::set(Logger::drawing);
      Logger::set(Logger::traversal);
      Logger::set(Logger::widget);
    }

#ifdef JPROF
  value == "";
  getopt.get("profiling", &value);
  if (value == "true") setupProfilingStuff();
#endif

  boa->impl_is_ready(0,1);
  Logger::log(Logger::corba) << "[0/5] BOA is running" << endl;

  ServerImpl *server = new ServerImpl;

  char *pluginDir = getenv("BERLIN_ROOT");
  if (!pluginDir)
    {
      cerr << "Please set environment variable BERLIN_ROOT first" << endl;
      exit(-1);
    }
  string modules = string(pluginDir) + "/modules";
  server->scan(modules.c_str());

  Logger::log(Logger::loader) << "[1/5] initialized loadable modules" << endl;

  Kit::PropertySeq props;
  props.length(1);
  props[0].name = CORBA::string_dup("implementation");
  value = "";
  getopt.get("drawing", &value);
  if (!value.empty()) props[0].value = CORBA::string_dup(value.c_str());
  else props[0].value = CORBA::string_dup("GLDrawingKit");
  DrawingKit_var drawing = server->resolve<DrawingKit>(interface(DrawingKit), props);
  if (CORBA::is_nil(drawing))
    {
      cerr << "unable to open " << interface(DrawingKit) << " with " << props[0].name << '=' << props[0].value << endl;
      exit(-1);
    }

  Logger::log(Logger::drawing) << "[2/5] built drawing system" << endl;

  // make a Screen graphic to hold this server's scene graph
  ScreenImpl *screen = new ScreenImpl(drawing);
  screen->_obj_is_ready(boa);
  
  DesktopImpl *desktop = new DesktopImpl;
  desktop->_obj_is_ready(boa);
  screen->body(Desktop_var(desktop->_this()));
  screen->appendController(Desktop_var(desktop->_this()));
  props.length(0);
  LayoutKit_var layout = server->resolve<LayoutKit>(interface(LayoutKit), props);
  Stage_var stage = layout->createStage();
  desktop->init(stage);

  Logger::log(Logger::layout) << "[3/5] created desktop" << endl;

  // initialize the client listener
  server->setSingleton(interface(Desktop), Desktop_var(desktop->_this()));
  server->setSingleton(interface(DrawingKit), drawing);
  server->_obj_is_ready(boa);
  server->start();

  Logger::log(Logger::layout) << "started server" << endl;
  bind_name(orb, Server_var(server->_this()), interface(Server));

  Logger::log(Logger::corba) << "[4/5] listening for clients" << endl;
  // initialize the event distributor and draw thread
  ScreenManager *smanager = screen->manager();
  Logger::log(Logger::corba) << "[5/5] event distributor constructed, about to enter main loop" << endl;
  try
    {
      smanager->run();
    }
  catch (CORBA::SystemException &se)
    {
      cout << "system exception " << se.NP_RepositoryId() << endl;
    }
  catch(omniORB::fatalException &fe)
    {
      cerr << "fatal exception at " << fe.file() << " " << fe.line() << ":" << fe.errmsg() << endl;
    }
  catch (...)
    {
      cout << "unknown exception caught" << endl;
    };
  return 0;
}
