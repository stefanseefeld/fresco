/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
 * Copyright (C) 1999 Graydon Hoare <graydon@fresco.org> 
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

#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Signal.hh>
#include <Prague/Sys/Profiler.hh>
#include <Prague/Sys/Timer.hh>
#include <Prague/Sys/Path.hh>
#include <Prague/Sys/User.hh>
#include <Prague/Sys/Fork.hh>
#include <Prague/Sys/GetOpt.hh>
#include <Fresco/config.hh>
#include <Fresco/resolve.hh>
#include <Fresco/LayoutKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/DrawingKit.hh>
#include <Berlin/ScreenImpl.hh>
#include <Berlin/ScreenManager.hh>
#include <Berlin/Console.hh>
#include <Berlin/Logger.hh>
#include <Berlin/DesktopImpl.hh>
#include <Berlin/RCManager.hh>
#include <Berlin/ServerImpl.hh>
#include <Berlin/GraphicDictionary.hh>
#include <Berlin/GraphDebugger.hh>

// to allow to override the default Babylon path:
#include <Babylon/Dictionary.hh>

#include <fstream>
#include <sstream>

#ifdef RC_PREFIX
const std::string prefix = RC_PREFIX;
#else
const std::string prefix = "";
#endif

#ifdef RC_SYSCONFDIR
const std::string sysconfdir = RC_SYSCONFDIR;
#else
const std::string sysconfdir = "";
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
using namespace Fresco;

namespace
{
  Berlin::GraphDebugger * debugger;
}

struct Dump : Signal::Notifier 
{
  private:
  Prague::Semaphore & my_semaphore;
  Dump(Dump const &);                   // no impl
  Dump const & operator=(Dump const &); // no impl
  public:
  Dump(Prague::Semaphore & semaphore)
          : my_semaphore(semaphore){}
  void notify(int signo) /*FOLD00*/
  {
      switch (signo)
      {
	case Signal::usr1:
            if (debugger)
            {
                Logger::log(Logger::loader)
                    << "Starting scenegraph debugger." << std::endl;
                debugger->debug();
		Logger::log(Logger::loader)
                    << "Scenegraph debugger run finished." << std::endl;
            }
            else
                Logger::log(Logger::loader)
                    << "Debugger not activated on "
                    << "command line. Not entering debug mode."
                    << std::endl;
            return;
        case Signal::usr2: 
          if (Console::instance())
          {
            Console::instance()->activate_autoplay(); 
            Console::instance()->wakeup();
          }
          return;
        case Signal::interrupt: break;
        case Signal::hangup: Profiler::dump(std::cerr); break;
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
            exit(-1); // NOTE: Must exit after getting segv:
                      // behaviour is undefined if not!
          }
      }
      my_semaphore.post();
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

      // FIXME: Where should we log this to?
      std::ostringstream oss;
      oss << "Starting client ";
      char fill_char = '\"';
      for (std::vector<char *>::const_iterator i = args.begin();
           i != args.end() && 0 != *i;
           ++i)
      {
	   std::string tmp(*i);
	   oss << fill_char << tmp;
           fill_char = ' ';
      }
      oss << "\"" << std::endl;
      Logger::log(Logger::loader) << oss.str();

      // Execute command
      execvp(args[0], &*args.begin());
      
      // Should not get here
      std::cerr << "ERROR: Client could not get started." << std::endl;
      exit(100);
  }
  // Attempt to kill client on these signals
  child->suicide_on_signal(Signal::interrupt);
  child->suicide_on_signal(Signal::quit);
  child->suicide_on_signal(Signal::abort);
  child->suicide_on_signal(Signal::segv);
}

// ---------------------------------------------------------------
// Server
// ---------------------------------------------------------------
int main(int argc, char **argv) /*FOLD00*/
{
  bool use_debugger = 0; // turn on scenegraph debugger?
  debugger = 0;

  // ---------------------------------------------------------------
  // Setup signalhandling
  // ---------------------------------------------------------------
  
  Prague::Semaphore sem;
  Dump *dump = new Dump(sem);
  Signal::set(Signal::usr1, dump);
  Signal::set(Signal::usr2, dump);
  Signal::set(Signal::abort, dump);
  Signal::set(Signal::segv, dump);
  Signal::set(Signal::hangup, dump);
  Signal::set(Signal::interrupt, dump);
  
  // ---------------------------------------------------------------
  // Parse commandline arguments
  // ---------------------------------------------------------------
  
  GetOpt getopt(argv[0], "a fresco display server");
  getopt.add('h', "help", GetOpt::novalue, "help message");
  add_resolving_options_to_getopt(getopt);
  getopt.add('v', "version", GetOpt::novalue, "version number");
  getopt.add('l', "logger", GetOpt::optional, "switch logging on");
  getopt.add('t', "tracer", GetOpt::novalue, "switch tracing on");
  getopt.add('D', "debug", GetOpt::novalue,
             "switch on the SceneGraph Debugger.");
  getopt.add('p', "profiler", GetOpt::novalue, "switch profiling on");
  getopt.add('d', "drawing", GetOpt::mandatory, "the DrawingKit to choose");
  getopt.add('r', "resource", GetOpt::mandatory,
             "the resource file to load");
  getopt.add('e', "execute", GetOpt::mandatory,
             "the command to execute upon startup");
  getopt.add('c', "console", GetOpt::mandatory, 
             "console to use (use -C for possible values)");
  getopt.add('C', "list-available-consoles", GetOpt::novalue, 
             "list known consoles");
  getopt.add('s', "pixels", GetOpt::mandatory, 
             "number of pixels (eg. '640x480')");
  size_t argo = getopt.parse(argc, argv);
  argc -= argo;
  argv += argo;

  if (getopt.is_set("help")) 
  { 
    getopt.usage(); 
    return 0;
  }

  if (getopt.is_set("version")) 
  { 
    std::cout << "version is " << version << std::endl; 
    return 0;
  }
  
  if (getopt.is_set("debug")) use_debugger = 1;

  std::string value;

  if (getopt.is_set("export-ref"))
  {
    getopt.get("export-ref",&value);
    set_server_reference_export_method(value);
  }

  value="";
  if (getopt.get("logger", &value))
  {
      if (!value.empty())
      {
          std::istringstream iss(value);
          std::ostringstream oss;
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
              else token == "";

              if (!token.empty()) oss << token << " ";
          }
          Logger::log(Logger::loader) << "Logging of types \""
                                      << oss.str() << "\" activated."
                                      << std::endl;
      }
      else
      {
          Logger::setall();
          Logger::log(Logger::loader) << "Logging of all types activated."
                                      << std::endl;
      }
  }
  value = "";
  
  // Find our resource file:
  if (getopt.get("resource", &value))
  {
      // Load resourcefile given on the commandline:
      try
      {
          value = Prague::Path::expand_user(value);
          RCManager::read(value);
          Logger::log(Logger::loader) << "Resourcefile \""
                                      << value << "\" read."
                                      << std::endl;
      }
      catch (const std::runtime_error &e)
      {
          std::cerr << "ERROR: Resourcefile \"" << value
                    << "\" given on the commandline failed to load: "
                    << e.what() << std::endl;
          exit (1);
      }
  }
  else
  {
      // Search for berlinrc in default places:
      value = sysconfdir + "/berlinrc";

      bool is_configured = 0;
      try
      {
          RCManager::read(value);
          is_configured = 1;
          Logger::log(Logger::loader) << "Resourcefile \""
                                      << value << "\" read."
                                      << std::endl;

      }
      catch (const std::runtime_error &e)
      {
          std::cerr << "Warning: Default resourcefile \"" << value
                    << "\" failed to load: "
                    << e.what() << std::endl;
      }

      // FIXME: merge additional configuration:
      if(getenv("BERLINRC")) value = std::string(getenv("BERLINRC"));
      else value ="";

      if (value.empty())
          value = std::string(User().home()) + "/.berlin";

      try
      {
          if (!is_configured) 
          {
              RCManager::read(value);
              Logger::log(Logger::loader) << "Resourcefile \""
                                          << value << "\" read."
                                          << std::endl;
          }
      }
      catch (const std::runtime_error &e)
      {
          std::cerr << "ERROR: System resourcefile is missing and "
                    << "user's resourcefile \"" << value
                    << "\" failed to load too: "
                    << e.what() << std::endl;
          exit(1);
      }
  }
  
  if (getopt.is_set("tracer"))
  {
      Tracer::logging(true);
      Logger::log(Logger::loader) << "Tracing enabled." << std::endl;
  }

  if (getopt.is_set("list-available-consoles"))
  {
      std::cout << "Available consoles:" << std::endl;
      Console::list_available(std::cout);
      return 0;
  }

#ifdef JPROF
  if (getopt.is_set("profiler"))
  {
      setupProfilingStuff();
      Logger::log(Logger::loader) << "Profiling enabled." << std::endl;
  }
#endif

  Fork *child = 0;

  Logger::log(Logger::loader) << "Commandline arguments are parsed,"
                              << " configuration is read in." << std::endl;
  
  // ---------------------------------------------------------------
  // Setup CORBA
  // ---------------------------------------------------------------

  CORBA::ORB_var orb;
  try
  {
    orb = CORBA::ORB_init(argc, argv);
    PortableServer::POA_var poa = 
      resolve_init<PortableServer::POA>(orb, "RootPOA");
    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();
    Logger::log(Logger::corba) << "Root POA is activated." << std::endl;
    
    CORBA::PolicyList policies;
#ifdef COLOCATION_OPTIMIZATION
#  if defined(ORB_omniORB)
    {
      // create a POA for global objects derived from ServantBase
      policies.length(2);
      policies[0] = poa->create_implicit_activation_policy(PortableServer::IMPLICIT_ACTIVATION);
      CORBA::Any value;
      value <<= omniPolicy::LOCAL_CALLS_SHORTCUT; 
      policies[1] = orb->create_policy(omniPolicy::LOCAL_SHORTCUT_POLICY_TYPE,
				       value);
      poa = poa->create_POA("shortcut", pman, policies);
      
      // create a policy list to be used by kit specific POAs
      policies.length(1);
      policies[0] = orb->create_policy(omniPolicy::LOCAL_SHORTCUT_POLICY_TYPE,
				       value);
    }
#  elif defined(ORB_TAO)
    // fillin TAO-specific initialisation here...
#  endif
    Logger::log(Logger::corba) << "Colocation optimization activated."
			       << std::endl;
#endif
      
    DefaultPOA::default_POA(poa);

    Logger::log(Logger::corba) << "Default POA set up." << std::endl;

    // ---------------------------------------------------------------
    // Setup Babylon
    // ---------------------------------------------------------------
       
    {
      Prague::Path path = RCManager::get_path("babylonpath");
      Babylon::override_path(path);
    }

    Logger::log(Logger::loader) << "Babylon path set." << std::endl;

    // ---------------------------------------------------------------
    // Open the Console
    // ---------------------------------------------------------------
    
    std::string pixels;
    Fresco::PixelCoord x_pixels(640), y_pixels(480);
    if (getopt.is_set("pixels")) 
    {
      getopt.get("pixels",&pixels);
      unsigned x_position = pixels.find("x");
      bool invalid_format = false;
      if (x_position == std::string::npos) invalid_format = true;
      else
      {
	std::stringstream s(pixels.substr(0,x_position));
	s >> x_pixels;
	std::stringstream t(pixels.substr(x_position+1,pixels.size()));
	t >> y_pixels;
      }
      if ((x_pixels <= 0) || (y_pixels <= 0)) invalid_format = true;
      if (invalid_format)
      {
	std::cerr << "ERROR: Format of 'pixels' option should be:\n"
		  << " --pixels=800x600, with 800 and 600 replaced\n"
		  << "by the desired x and y values"
		  << std::endl;
	exit(1);
      }
    }
       
    value = "";
    getopt.get("console", &value);
    try { Console::open(value, argc, argv, poa, x_pixels, y_pixels); }
    catch (const std::runtime_error &e)
    {
      std::cerr << "ERROR: Failed to open the Console \"" << value
		<< "\":\n\t" << e.what() << std::endl;
      exit(2);
    }
    
    Logger::log(Logger::console) << "Console is initialized." << std::endl;
    
    // ---------------------------------------------------------------
    // Construct Server and load it with kits
    // ---------------------------------------------------------------
    
    // NOTE: currently pass default poa; ideally function would know
    PortableServer::POA_var server_poa = get_server_poa(orb,poa);
    ServerImpl * server = ServerImpl::create(server_poa, policies);
    Logger::log(Logger::loader) << "Server created in server-POA" 
				<< std::endl;
    
    Prague::Path path = RCManager::get_path("modulepath");
    for (Prague::Path::iterator i = path.begin(); i != path.end(); ++i)
      server->scan(*i);
    Logger::log(Logger::loader) << "Kits are loaded." << std::endl;
    
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
    DrawingKit_var drawing =
      server->resolve<DrawingKit>("IDL:fresco.org/Fresco/DrawingKit:1.0",
				  props, poa);
    Logger::log(Logger::drawing) << "DrawingKit is resolved." << std::endl;
    if (CORBA::is_nil(drawing))
    {
      std::cerr << "ERROR: Unable to open "
		<< "IDL:fresco.org/Fresco/DrawingKit:1.0"
		<< " with attribute "
		<< props[0].name << '=' << props[0].value << std::endl;
      exit(3);
    }
    Logger::log(Logger::drawing) << "Drawing system is set up." << std::endl;
    
    // ---------------------------------------------------------------
    // make a Screen graphic to hold this server's scene graph
    // ---------------------------------------------------------------
    
    ScreenImpl *screen = new ScreenImpl();
    EventManager *emanager = 
      new EventManager(Controller_var(screen->_this()), 
		       screen->allocation());
    ScreenManager *smanager = 
      new ScreenManager(Graphic_var(screen->_this()), 
			emanager, drawing);
    screen->bind_managers(emanager, smanager);

    // make sure to setup the debugger before registering graphics!
    if (use_debugger) debugger = new Berlin::GraphDebugger(screen->_this());

    Berlin::GraphicDictionary::instance()->add(screen->_this(), screen,
					       "Server/Screen");

    Logger::log(Logger::loader) << "Screen is set up and managers are "
				<< "bound to it." << std::endl;
    
    props.length(0);
    LayoutKit_var layout = 
      server->resolve<LayoutKit>("IDL:fresco.org/Fresco/LayoutKit:1.0",
				 props, poa);
    Layout::Stage_var stage = layout->create_stage();
    DesktopImpl *desktop = new DesktopImpl(orb, stage, sem);
    screen->body(Desktop_var(desktop->_this()));
    screen->append_controller(Desktop_var(desktop->_this()));
    Logger::log(Logger::layout) << "Desktop is created." << std::endl;
    
    server->set_singleton("IDL:fresco.org/Fresco/Desktop:1.0", 
			  Desktop_var(desktop->_this()));
    server->set_singleton("IDL:fresco.org/Fresco/DrawingKit:1.0", drawing);
    Logger::log(Logger::loader) << "singletons set" << std::endl;
    
    // ---------------------------------------------------------------
    // Start the server thread - start the client listener and publish it
    // ---------------------------------------------------------------
    
    server->start();
    Logger::log(Logger::loader) << "Server started." << std::endl;
    
    Server_var server_ref = server->_this();
    publish_server(server_ref, getopt, orb); 
    
    Logger::log(Logger::corba) << "Server location published."
			       << std::endl;
    
    // ---------------------------------------------------------------
    // Start any clients specified using --execute
    // ---------------------------------------------------------------
    value = "";
    getopt.get("execute", &value);
    if (!value.empty())
    {
      exec_child(child, value);
      Logger::log(Logger::loader) << "Child process started." << std::endl;
    }
    
    // ---------------------------------------------------------------
    // Start ScreenManager thread
    // ---------------------------------------------------------------
    
    smanager->start();
    Logger::log(Logger::loader) << "ScreenManager is running." << std::endl;
    
    // ---------------------------------------------------------------
    // Wait until we receive a request to shut down, then do so
    // NOTE: server/smanager threads assumed to be shut-down implicitly
    // ---------------------------------------------------------------
    
    Logger::log(Logger::loader) << "Blocking waiting for shutdown request." 
				<< std::endl;
    sem.wait();
    Logger::log(Logger::loader) << "Starting server shutdown." << std::endl;
    
    unpublish_server(orb);
    Logger::log(Logger::loader) << "Un-published Server." << std::endl;
    
    server->stop();
    Logger::log(Logger::loader) << "Server stopped." << std::endl;
  }
  catch (const CORBA::SystemException &e)
  {
    std::cerr << "ERROR: Unexpected CORBA::System exception caught: "
	      << e << std::endl;
  }
#ifdef ORB_omniORB
  catch(const omniORB::fatalException &fe)
  {
    std::cerr << "ERROR: OmniORB fatal exception caught at "
	      << fe.file() << " " << fe.line() << ":"
	      << fe.errmsg() << std::endl;
  }
#endif
  catch (const CORBA::Exception &e)
  {
    std::cerr << "ERROR: Unexpected CORBA::Exception caught: "
	      << e << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cerr << "ERROR: Unexpected std::exception: "
	      << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "ERROR: *UNKNOWN* exception caught" << std::endl;
  }
  Logger::log(Logger::corba) << "CORBA servants gone." << std::endl;
  delete child;
  return 0;
}

