/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
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
#include <Berlin/RCManager.hh>
#include <Berlin/Logger.hh>
#include <Prague/Sys/User.hh>
#include <fstream>
#include <stdexcept>
#include <map>

#ifdef RC_SYSCONFDIR
const std::string sysconfdir = RC_SYSCONFDIR;
#else
const std::string sysconfdir = "";
#endif

// -----------------------------------------------------------------------------
// Internals
// -----------------------------------------------------------------------------
static std::map<std::string, Prague::Path> _paths;

namespace RCManager_internals
{
  void read_file(const std::string &file)
  {
      std::ifstream ifs(file.c_str());
      if (!ifs) { throw std::runtime_error("RCManager: file not found.");}
      while (ifs)
      {
          std::string name;
          ifs >> name;
          ifs.ignore(1024, '=');
          std::string path;
          ifs >> path;
          _paths.insert(std::make_pair(name, path));
      }
  }

  void add_to_path(const std::string &name, const std::string &value)
  {
      Prague::Path &path = _paths[name];
      path.append(value);
  }
}

// -----------------------------------------------------------------------------
// Public functions
// -----------------------------------------------------------------------------
Prague::Path RCManager::get_path(const std::string &name)
{
    // NOTE: default (empty) path is constructed if not present in _paths yet
    return _paths[name];
}

// Find our resource file:
void RCManager::setup(Prague::GetOpt const &getopt)
{
    std::string value;
    if (getopt.get("resource", &value))
    {
        // Load resourcefile given on the commandline:
        try
        {
            value = Prague::Path::expand_user(value);
            RCManager_internals::read_file(value);
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
            RCManager_internals::read_file(value);
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
            value = std::string(Prague::User().home()) + "/.berlin";

        try
        {
            if (!is_configured) 
            {
                RCManager_internals::read_file(value);
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
}
