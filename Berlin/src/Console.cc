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

Console::console_list_t Console::my_available_consoles;

void Console::cache_available_consoles()
{
  static bool cached = false;
  if (cached) return;

  Prague::Path path = RCManager::get_path("modulepath");
  for (Prague::Path::iterator path_elt = path.begin(), path_end = path.end();
       path_elt != path_end; ++path_elt)
  {
    Directory dir(*path_elt + "/Console", Directory::alpha, "\\.so$");
    for (Directory::iterator file = dir.begin(), last_file = dir.end();
         file != last_file; ++file)
    {
      try { plugin = new Plugin<Console::Loader>((*file)->long_name());}
      catch (const std::runtime_error &e)
      { 
        Logger::log(Logger::loader) << "Plugin '" << (*file)->name() 
                                    << "' is not loadable [" << e.what() << "]"
                                    << std::endl;
        continue;
      }
      delete plugin;
      plugin = 0;
      std::string name = (*file)->name();
      unsigned const dotpos = name.find(".so"); // FIXME breaks if in middle
      name = name.substr(0,dotpos);
      my_available_consoles.insert(std::make_pair(name,(*file)->long_name()));
    }
  }
  cached = true;
}

void Console::list_available(std::ostream & o)
{
  cache_available_consoles();
  for (console_list_t::const_iterator iter = my_available_consoles.begin(),
                                       end = my_available_consoles.end();
       iter != end; ++iter)
  {
    o << iter->first << " (" << iter->second << ")" << std::endl;
  }
}

bool Console::is_available(std::string const &console)
{
  cache_available_consoles();
  if (my_available_consoles.find(console) != my_available_consoles.end())
      return true;
  return false;
}

int Console::open(const std::string &console, int argc, char **argv, 
                  PortableServer::POA_ptr poa, 
                  Fresco::PixelCoord x, Fresco::PixelCoord y)

  throw(std::runtime_error)
{
  cache_available_consoles();
  if (my_available_consoles.size()==0)
  {
    throw std::runtime_error("No valid consoles found in modulepath");
  }
  if (!console.empty())
  {
      // Console name given: Load exactly the one specified
      if (!is_available(console))
      {
        std::string const msg = "No console named \"" + console + 
                                "\" found in modulepath.";
        throw std::runtime_error(msg);
      }
      else plugin = new Plugin<Console::Loader>(my_available_consoles[console]);
  }
  else
  {
    // No specific console requested: load the one which is found first
    std::string const & console_name = my_available_consoles.begin()->first;
    try
    {
      plugin = new Plugin<Console::Loader>(my_available_consoles[console_name]);
    }
    catch (std::runtime_error const &)
    {
      std::string const msg = "Previously-found console " + console_name +
                              " not available.";
      throw std::runtime_error(msg);
    }
  }
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
