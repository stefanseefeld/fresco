/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Signal.hh>
#include <Prague/Sys/Profiler.hh>
#include <Prague/Sys/Timer.hh>
#include <Prague/Sys/Path.hh>
#include <Prague/Sys/User.hh>
#include <Prague/Sys/Fork.hh>
#include <Prague/Sys/GetOpt.hh>
#include <Warsaw/config.hh>
#include <Warsaw/resolve.hh>
#include <Warsaw/LayoutKit.hh>
#include <Warsaw/ToolKit.hh>
#include <Warsaw/DrawingKit.hh>
#include <Berlin/ScreenImpl.hh>
#include <Berlin/ScreenManager.hh>
#include <Berlin/Console.hh>
#include <Berlin/Logger.hh>
#include <Berlin/DesktopImpl.hh>
#include <Berlin/RCManager.hh>
#include "ServerImpl.hh"
#include <fstream>
#include <strstream>

#ifdef RC_PREFIX
const std::string prefix = RC_PREFIX;
#else
const std::string prefix = "";
#endif

#ifdef VERSION
const std::string version = VERSION;
#else
const std::string version = "unknown";
#endif

#ifdef JPROF
// probably need to change include path
#include "jprof.h"
#endif

using namespace Prague;
using namespace Warsaw;

struct Dump : Signal::Notifier 
{
  void notify(int signo) /*FOLD00*/
    {
      switch (signo)
	{
	case Signal::usr2: 
	  Console::instance()->activate_autoplay(); 
	  Console::instance()->wakeup();
	  return;
	case Signal::hangup: Profiler::dump(cerr); break;
	case Signal::abort:
	case Signal::segv:
          {
            std::string output = "server.log";
            std::ofstream ofs(output.c_str());
	    ofs << "I used to be version " << version
		<< " of the Fresco Display Server.\n\n";
	    Logger::dump(ofs);
	    Tracer::dump(ofs);
	    std::cerr << "Something went wrong. '" << output
		      << "' contains a debugging log.\n"
		      << "Please mail this output to bugs@fresco.org "
                      << "(together with a description\n"
                      << "of your configuration and what you were doing"
                      << " before the crash).\n\n";
            exit(-1);
          }
	}
    }
};

//. Execute a client using the command in 'value'. The process is stored in
//. client
void exec_child(Fork*& child, std::string& value) /*fold00*/
{
  // Fork to create child process to execute client in
  child = new Fork(true, true);
  if (child->child())
    {
      std::vector<char*> args;
      // Split 'value' into command and arguments for execvp
      int start = 0, index = 0;
      value.push_back('\0');
      while ( (index = value.find(' ', index)) != std::string::npos)
	{
	  value[index] = '\0';
	  args.push_back(&*value.begin() + start);
	  start = index + 1;
	}
      args.push_back(&*value.begin() + start);
      args.push_back(0);
      
      // Execute command
      execvp(args[0], &*args.begin());
      
      // Should not get here
      perror("client execvp");
      exit(1);
    }
  // Attempt to kill client on these signals
  child->suicide_on_signal(Signal::interrupt);
  child->suicide_on_signal(Signal::quit);
  child->suicide_on_signal(Signal::abort);
  child->suicide_on_signal(Signal::segv);
}

int main(int argc, char **argv) /*FOLD00*/
{
  // ---------------------------------------------------------------
  // Setup signalhandling
  // ---------------------------------------------------------------
	
  Dump *dump = new Dump;
  Signal::set(Signal::usr2, dump);
  Signal::set(Signal::abort, dump);
  Signal::set(Signal::segv, dump);
  Signal::set(Signal::hangup, dump);
	
  // ---------------------------------------------------------------
  // Search for berlinrc
  // ---------------------------------------------------------------
	
  if (~prefix.empty()) RCManager::read(prefix + "/share/berlin/berlinrc");
  const char *rcfile = getenv("BERLINRC");
  if (rcfile) RCManager::read(Prague::Path::expand_user(rcfile));
  else RCManager::read(std::string(User().home()) + "/.berlin");
	
  // ---------------------------------------------------------------
  // Parse commandline arguments
  // ---------------------------------------------------------------
  
  GetOpt getopt(argv[0], "a berlin display server");
  getopt.add('h', "help", GetOpt::novalue, "help message");
  getopt.add('v', "version", GetOpt::novalue, "version number");
  getopt.add('l', "logger", GetOpt::optional, "switch logging on");
  getopt.add('t', "tracer", GetOpt::novalue, "switch tracing on");
  getopt.add('p', "profiler", GetOpt::novalue, "switch profiling on");
  getopt.add('d', "drawing", GetOpt::mandatory, "the DrawingKit to choose");
  getopt.add('r', "resource", GetOpt::mandatory, "the resource file to load (mandatory)");
  getopt.add('e', "execute", GetOpt::mandatory, "the command to execute upon startup");
  getopt.add('c', "console", GetOpt::mandatory, "the console to choose");
  size_t argo = getopt.parse(argc, argv);
  argc -= argo;
  argv += argo;
  if (getopt.is_set("version")) { cout << "version is " << version << endl; return 0;}
  if (getopt.is_set("help")) { getopt.usage(); return 0;}
  std::string value;
  if (getopt.get("resource", &value))
    RCManager::read(Prague::Path::expand_user(value));
  else {
    getopt.usage();
    exit(1);
  }
  value = "";  
  if (getopt.get("logger", &value))
    {
      if (!value.empty())
	{
	  std::istrstream iss(value.c_str());
	  std::string token;
	  while (iss >> token)
	    {
	      if (token == "corba") Logger::set(Logger::corba);
	      else if (token == "lifecycle") Logger::set(Logger::lifecycle);
	      else if (token == "focus") Logger::set(Logger::focus);
	      else if (token == "image") Logger::set(Logger::image);
	      else if (token == "loader") Logger::set(Logger::loader);
	      else if (token == "console") Logger::set(Logger::console);
	      else if (token == "subject") Logger::set(Logger::subject);
	      else if (token == "layout") Logger::set(Logger::layout);
	      else if (token == "picking") Logger::set(Logger::picking);
	      else if (token == "drawing") Logger::set(Logger::drawing);
	      else if (token == "traversal") Logger::set(Logger::traversal);
	      else if (token == "widget") Logger::set(Logger::widget);
	      else if (token == "text") Logger::set(Logger::text);
	      else if (token == "desktop") Logger::set(Logger::desktop);
	    }
	}
      else Logger::setall();
    }
  if (getopt.is_set("tracer")) Tracer::logging(true);

#ifdef JPROF
  if (getopt.is_set("profiler")) setupProfilingStuff();
#endif

  Fork *child = 0;
  
  // ---------------------------------------------------------------
  // Setup CORBA
  // ---------------------------------------------------------------
	
  CORBA::ORB_var orb;
  try
    {
       orb = CORBA::ORB_init(argc, argv);
       PortableServer::POA_var poa = resolve_init<PortableServer::POA>(orb, "RootPOA");
       PortableServer::POAManager_var pman = poa->the_POAManager();
       pman->activate();
       Logger::log(Logger::corba) << "root POA is activated" << std::endl;
       
       CORBA::PolicyList policies;
#ifdef COLOCATION_OPTIMIZATION
#  if defined(ORB_omniORB)
       {
	 // create a POA for global objects derived from ServantBase
	 policies.length(2);
	 policies[0] = poa->create_implicit_activation_policy(PortableServer::IMPLICIT_ACTIVATION);
	 CORBA::Any value;
	 value <<= omniPolicy::LOCAL_CALLS_SHORTCUT; 
	 policies[1] = orb->create_policy(omniPolicy::LOCAL_SHORTCUT_POLICY_TYPE, value);
	 poa = poa->create_POA("shortcut", pman, policies);
	 
	 // create a policy list to be used by kit specific POAs
	 policies.length(1);
	 policies[0] = orb->create_policy(omniPolicy::LOCAL_SHORTCUT_POLICY_TYPE, value);
       }
#  elif defined(ORB_TAO)
       // fillin TAO-specific initialisation here...
#  endif
#endif
      
       DefaultPOA::default_POA(poa);
       
       // ---------------------------------------------------------------
       // Open the Console
       // ---------------------------------------------------------------
      
       value = "";
       getopt.get("console",&value);
       Console::open(value, argc, argv, poa);
       
       Logger::log(Logger::console) << "console is initialized" << std::endl;
       
       // ---------------------------------------------------------------
       // Construct Server
       // ---------------------------------------------------------------
       
       ServerImpl *server = ServerImpl::create(policies);
       
       Prague::Path path = RCManager::get_path("modulepath");
       for (Prague::Path::iterator i = path.begin(); i != path.end(); ++i)
	   server->scan(*i);
       Logger::log(Logger::loader) << "modules are loaded" << std::endl;
       
       // ---------------------------------------------------------------
       // Setup default DrawingKit
       // ---------------------------------------------------------------
       
       Kit::PropertySeq props;
       props.length(1);
       props[0].name = CORBA::string_dup("implementation");
       value = "";
       getopt.get("drawing", &value);
       if (!value.empty()) props[0].value = CORBA::string_dup(value.c_str());
       else props[0].value = CORBA::string_dup("LibArtDrawingKit");
       DrawingKit_var drawing = server->resolve<DrawingKit>("IDL:Warsaw/DrawingKit:1.0", props, poa);
       if (CORBA::is_nil(drawing))
	 {
	   std::cerr << "unable to open " << "IDL:Warsaw/DrawingKit:1.0"
		     << " with attribute " << props[0].name << '=' << props[0].value << std::endl;
	   return -1;
	 }
       
       Logger::log(Logger::drawing) << "drawing system is built" << std::endl;
      
       // ---------------------------------------------------------------
       // make a Screen graphic to hold this server's scene graph
       // ---------------------------------------------------------------
       
       ScreenImpl *screen = new ScreenImpl();
       EventManager *emanager = new EventManager(Controller_var(screen->_this()), screen->allocation());
       ScreenManager *smanager = new ScreenManager(Graphic_var(screen->_this()), emanager, drawing);
       screen->bind_managers(emanager, smanager);

       Logger::log(Logger::loader) << "screen is setup and managers are bound to it." << std::endl;

       props.length(0);
       LayoutKit_var layout = server->resolve<LayoutKit>("IDL:Warsaw/LayoutKit:1.0", props, poa);
       Layout::Stage_var stage = layout->create_stage();
       DesktopImpl *desktop = new DesktopImpl(orb, stage);
       screen->body(Desktop_var(desktop->_this()));
       screen->append_controller(Desktop_var(desktop->_this()));
       
       Logger::log(Logger::layout) << "desktop is created" << std::endl;
       
       // initialize the client listener
       server->set_singleton("IDL:Warsaw/Desktop:1.0", Desktop_var(desktop->_this()));
       server->set_singleton("IDL:Warsaw/DrawingKit:1.0", drawing);
       server->start();
      
       Logger::log(Logger::layout) << "started server" << std::endl;
       try
	 {
	   bind_name(orb, Server_var(server->_this()), "IDL:Warsaw/Server:1.0");
	 } 
       catch (CORBA::COMM_FAILURE)
	 {
	   std::cerr << "CORBA communications failure finding Warsaw." << std::endl
		     << "Are you sure the name service is running?" << std::endl;
	   return -1;
	 }
       catch (...)
	 {
	   std::cerr << "Unknown exception finding Warsaw" << std::endl;
	   return -1;
	 }
       
       Logger::log(Logger::corba) << "listening for clients" << std::endl;
       
       // Start client via --execute argument
       value = "";
       getopt.get("execute", &value);
       if (!value.empty()) {
	   exec_child(child, value);
	   Logger::log(Logger::loader) << "client started." << std::endl;
       }

       smanager->run();
    }
  catch (const CORBA::SystemException &e)
    {
      std::cout << "system exception " << e << std::endl;
    }
#ifdef ORB_omniORB
  catch(const omniORB::fatalException &fe)
    {
      std::cerr << "fatal exception at " << fe.file() << " " << fe.line() << ":"
		<< fe.errmsg() << std::endl;
    }
#endif
  catch (const CORBA::Exception &e)
    {
      std::cout << " exception " << e << std::endl;
    }
  catch (const std::exception &e)
    {
      std::cerr << "exception: " << e.what() << std::endl;
    }
  catch (...)
    {
      std::cout << "unknown exception caught" << std::endl;
    };

  delete child;
  if (!CORBA::is_nil(orb)) orb->destroy();
  return 0;
}
