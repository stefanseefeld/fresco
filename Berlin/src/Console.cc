/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2001 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include <Prague/Sys/GetOpt.hh>
#include <Prague/Sys/Path.hh>
#include <Prague/Sys/Plugin.hh>
#include "Berlin/RCManager.hh"
#include "Berlin/Console.hh"

using namespace Prague;

namespace
{
  Plugin<Console::Loader> *plugin = 0;
};

Console *Console::_console = 0;

Console::Reaper::~Reaper()
{
  delete Console::_console;
  delete plugin;
}

int Console::open(int argc, char **argv, PortableServer::POA_ptr poa) throw(std::runtime_error)
{
  GetOpt getopt("Console");
  getopt.add('c', "console", GetOpt::mandatory, "the console to choose");
  int argo = getopt.parse(argc, argv);
  std::string value;
  if (!getopt.get("console", &value)) value = "GGIConsole";
  Prague::Path path = RCManager::get_path("modulepath");
  std::string name = path.lookup_file(value + ".so");
  plugin = new Plugin<Console::Loader>(name);
  _console = (*plugin)->load(argo, argv);
  _console->_poa = PortableServer::POA::_duplicate(poa);
  return argo;
}

Console *Console::instance() { return _console;}

PortableServer::Servant Console::reference_to_servant(Warsaw::Drawable_ptr drawable)
{
  Trace trace("Console::reference_to_servant");
  try { return _poa->reference_to_servant(drawable);}
  catch (const PortableServer::POA::ObjectNotActive &) {}
  catch (const PortableServer::POA::WrongAdapter &) {}
  catch (const CORBA::OBJECT_NOT_EXIST &) {}
  return 0;
}

Warsaw::Drawable_ptr Console::activate_drawable(Console::Drawable *d)
{
  Trace trace("Console::activate_drawable");
  PortableServer::ObjectId_var oid = _poa->activate_object(d);
  d->_remove_ref();
  return d->_this();
}
