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
#include <Warsaw/ToolKit.hh>
#include <Warsaw/DrawingKit.hh>
#include <Berlin/ScreenImpl.hh>
#include <Berlin/ScreenManager.hh>
#include <Berlin/ServerImpl.hh>
#include <Berlin/GGI.hh>
#include <Berlin/Logger.hh>
#include <Berlin/DesktopImpl.hh>
#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Signal.hh>
#include <Prague/Sys/Profiler.hh>
#include <Prague/Sys/Timer.hh>
#include <Prague/Sys/GetOpt.hh>
#include <fstream>

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
	case Signal::usr2: 
	  GGI::drawable()->activate_autoplay(); 
	  GGI::drawable()->wakeup();
	  return;
	case Signal::hangup: Profiler::dump(cerr); break;
	case Signal::abort:
	case Signal::segv:
          {
            string output = "server.log";
            ofstream ofs(output.c_str());
	    Logger::dump(ofs);
	    Tracer::dump(ofs);
	    cerr << "Something went wrong. '" << output << "' contains a debugging log.\n"
                 << "Please mail this output to bugs@berlin-consortium.org\n\n";
            exit(-1);
          }
	}
    }
};

int main(int argc, char **argv)
{
  /*
   * start with some administrative stuff...
   */
  Dump *dump = new Dump;
  Signal::set(Signal::usr2, dump);
  Signal::set(Signal::abort, dump);
  Signal::set(Signal::segv, dump);
  Signal::set(Signal::hangup, dump);

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
      Logger::set(Logger::text);
      Tracer::logging(true);
    }

#ifdef JPROF
  value == "";
  getopt.get("profiling", &value);
  if (value == "true") setupProfilingStuff();
#endif

  /*
   * ...then start the ORB...
   */
  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "omniORB3");
  CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
  PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
  PortableServer::POAManager_var pman = poa->the_POAManager();
  pman->activate();

  Logger::log(Logger::corba) << "[0/5] POA is activated" << endl;

  /*
   * ...and finally construct the server.
   */
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
  else props[0].value = CORBA::string_dup("LibArtDrawingKit");
  DrawingKit_var drawing = server->resolve<DrawingKit>(DrawingKit::_PD_repoId, props);
  if (CORBA::is_nil(drawing))
    {
      cerr << "unable to open " << DrawingKit::_PD_repoId << " with " << props[0].name << '=' << props[0].value << endl;
      exit(-1);
    }

  Logger::log(Logger::drawing) << "[2/5] built drawing system" << endl;

  // make a Screen graphic to hold this server's scene graph
  ScreenImpl *screen = new ScreenImpl(drawing);
  cout << "here" << endl;
  props.length(0);
  ToolKit_var tools = server->resolve<ToolKit>(ToolKit::_PD_repoId, props);
  cout << "here" << endl;
  DesktopImpl *desktop = new DesktopImpl;
  cout << "here" << endl;
//   ToolKit::FrameSpec spec;
//   Color color = {0.7, 1.0, 0.7, 1.0};
//   spec.foreground(color);
//   screen->body(Graphic_var(tools->frame(Desktop_var(desktop->_this()), 10., spec, true)));
  screen->body(Desktop_var(desktop->_this()));
  cout << "here" << endl;
  screen->appendController(Desktop_var(desktop->_this()));
  cout << "here" << endl;
  LayoutKit_var layout = server->resolve<LayoutKit>(LayoutKit::_PD_repoId, props);
  cout << "here" << endl;
  Stage_var stage = layout->createStage();
  cout << "here" << endl;
  desktop->init(stage);

  Logger::log(Logger::layout) << "[3/5] created desktop" << endl;

  // initialize the client listener
  server->setSingleton(Desktop::_PD_repoId, Desktop_var(desktop->_this()));
  server->setSingleton(DrawingKit::_PD_repoId, drawing);
  server->start();

  Logger::log(Logger::layout) << "started server" << endl;
  bind_name(orb, Server_var(server->_this()), Server::_PD_repoId);

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
      cout << "system exception " << endl;//se.NP_RepositoryId() << endl;
    }
  catch(omniORB::fatalException &fe)
    {
      cerr << "fatal exception at " << fe.file() << " " << fe.line() << ":" << fe.errmsg() << endl;
    }
  catch (...)
    {
      cout << "unknown exception caught" << endl;
    };
  orb->destroy();
  return 0;
}
