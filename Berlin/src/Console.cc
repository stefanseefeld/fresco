/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@fresco.org> 
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
#include <Prague/Sys/GetOpt.hh>
#include <Prague/Sys/Path.hh>
#include <Prague/Sys/Directory.hh>
#include <Prague/Sys/Plugin.hh>
#include "Berlin/Logger.hh"
#include "Berlin/RCManager.hh"
#include "Berlin/Console.hh"

using namespace Prague;

namespace
{
  Plugin<Console::Loader> *plugin = 0;
};



// ---------------------------------------------------------------
// class Console
// ---------------------------------------------------------------

Console *Console::_console = 0;

Console::Reaper::~Reaper()
{
  delete Console::_console;
  delete plugin;
}

int Console::open(const std::string &console, int argc, char **argv, 
                  PortableServer::POA_ptr poa, 
                  Fresco::PixelCoord x, Fresco::PixelCoord y)

  throw(std::runtime_error)
{
  Prague::Path path = RCManager::get_path("modulepath");
  
  if (!console.empty())
    {
      // Console name given: Load exactly the one specified
      std::string name = path.lookup_file(std::string("Console/") + console + ".so");
      if (name.empty())
        {
          std::string msg = "No console named \"" + console + "\" found in modulepath.";
          throw std::runtime_error(msg);
        }
      else plugin = new Plugin<Console::Loader>(name);
    }
  else
    // No specific console requested: load whichever is found first
    for (Prague::Path::iterator i = path.begin(); i != path.end(); ++i)
      {
	Directory directory(*i + "/Console", Directory::alpha, "\\.so$");
	for (Directory::iterator j = directory.begin();
	     j != directory.end() && !plugin;
	     ++j)
	  try { plugin = new Plugin<Console::Loader>((*j)->long_name());}

	  catch (const std::runtime_error &e)
	    { 
	      Logger::log(Logger::loader) << (*j)->name() << " not loadable "
					  << e.what() << std::endl;
	      continue;
	    }
      }
  if (!plugin) throw std::runtime_error("No console found in modulepath.");
  _console = (*plugin)->load(argc, argv, x, y);
  _console->_poa = PortableServer::POA::_duplicate(poa);
  return argc;
}

Console *Console::instance() { return _console;}

PortableServer::Servant Console::reference_to_servant(Fresco::Drawable_ptr drawable)
{
  Trace trace("Console::reference_to_servant");
  try { return _poa->reference_to_servant(drawable);}
  catch (const PortableServer::POA::ObjectNotActive &) {}
  catch (const PortableServer::POA::WrongAdapter &) {}
  catch (const CORBA::OBJECT_NOT_EXIST &) {}
  return 0;
}

Fresco::Drawable_ptr Console::activate_drawable(Console::Drawable *d)
{
  Trace trace("Console::activate_drawable");
  PortableServer::ObjectId_var oid = _poa->activate_object(d);
  d->_remove_ref();
  return d->_this();
}
