/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.ca> 
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
#include <Berlin/FactoryFinderImpl.hh>
#include <Berlin/GenericFactoryImpl.hh>
#include <Berlin/ServerContextManagerImpl.hh>
#include <Berlin/Logger.hh>
#include <Berlin/DesktopImpl.hh>
#include <Prague/Sys/Signal.hh>
#include <Prague/Sys/Profiler.hh>
#include <Prague/Sys/Timer.hh>

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
// 	case Signal::interrupt: exit(0);
	case Signal::abort:
	case Signal::segv: Logger::dump(cerr); exit(-1);
	}
    }
};

template <class T>
typename T::_ptr_type create(GenericFactoryImpl *factory, const char *name)
{
  CosLifeCycle::Key key;
  key.length(1);
  key[0].id   =  name; 
  key[0].kind = (const char*) "Object"; 

  CosLifeCycle::Criteria criteria;
  
  CORBA::Object_var object = factory->create_object(key, criteria);
  return T::_narrow(object);
};

int main(int argc, char **argv)
{
  Dump *dump = new Dump;
  Signal::set(Signal::abort, dump);
  Signal::set(Signal::segv, dump);
  Signal::set(Signal::hangup, dump);
//   Signal::set(Signal::interrupt, dump);
#if 0
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
#endif

#ifdef JPROF
  setupProfilingStuff();
#endif

  CORBA::ORB_ptr orb = CORBA::ORB_init(argc,argv,"omniORB2");
  CORBA::BOA_ptr boa = orb->BOA_init(argc,argv,"omniORB2_BOA");
  boa->impl_is_ready(0,1);
  Logger::log(Logger::corba) << "[0/5] hooked up to corba library" << endl;

  // initialize COS lifecycle service
  GenericFactoryImpl * factory = new GenericFactoryImpl();
  factory->_obj_is_ready(boa);
  char *pluginDir = getenv("BERLIN_ROOT");
  if (!pluginDir)
    {
      cerr << "Please set environment variable BERLIN_ROOT first" << endl;
      exit(-1);
    }
  string modules = string(pluginDir) + "/modules";
  factory->scan(modules.c_str());

  Logger::log(Logger::loader) << "[1/5] initialized loadable modules" << endl;

  DrawingKit_var dk = create<DrawingKit>(factory, DrawingKit_IntfRepoID);

  Logger::log(Logger::drawing) << "[2/5] built drawing system" << endl;

  // make a Screen graphic to hold this server's scene graph
  ScreenImpl *screen = new ScreenImpl(dk);
  screen->_obj_is_ready(boa);
  
  DesktopImpl *desktop = new DesktopImpl;
  desktop->_obj_is_ready(boa);
  screen->body(Desktop_var(desktop->_this()));
  screen->appendController(Desktop_var(desktop->_this()));
  LayoutKit_var lk = create<LayoutKit>(factory, LayoutKit_IntfRepoID);
  Stage_var stage = lk->createStage();
  desktop->init(stage);

  Logger::log(Logger::layout) << "[3/5] created desktop" << endl;

  // initialize the client listener
  ServerContextManagerImpl *scmanager = new ServerContextManagerImpl(factory);
  Logger::log(Logger::layout) << "built scm" << endl;
  scmanager->_obj_is_ready(boa);
  Logger::log(Logger::layout) << "activated scm" << endl;
  scmanager->setSingleton(interface(Desktop), Desktop_var(desktop->_this()));
  Logger::log(Logger::layout) << "set desktop" << endl;
  scmanager->setSingleton(interface(DrawingKit), dk);
  Logger::log(Logger::layout) << "set dk" << endl;
  scmanager->start();
  Logger::log(Logger::layout) << "started scm" << endl;
  bind_name(orb, ServerContextManager_var(scmanager->_this()), interface(ServerContextManager));
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
