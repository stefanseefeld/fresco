/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Signal.hh>
#include <Prague/Sys/Profiler.hh>
#include <Prague/Sys/Timer.hh>
#include <Prague/Sys/GetOpt.hh>
#include <fstream>

using namespace Prague;

int main(int argc, char **argv)
{
//  CORBA::ORB_ptr orb = CORBA::ORB_init(argc, argv, "omniORB3");

//   GetOpt getopt(argv[0], "a berlin display server");
//   getopt.add('h', "help", GetOpt::novalue, "help message");
//   getopt.parse(argc - 1, argv + 1);
//   string value;
//   getopt.get("help", &value);
//   if (value == "true") { getopt.usage(); exit(0);}

  ServerImpl *server = ServerImpl::instance();
  char *pluginDir = getenv("BERLIN_ROOT");
  if (!pluginDir)
    {
      cerr << "Please set environment variable BERLIN_ROOT first" << endl;
      exit(-1);
    }
  string modules = string(pluginDir) + "/modules";
  server->scan(modules.c_str());

  ServerImpl::FactoryList listing = server->list();
  for (ServerImpl::FactoryList::iterator i = listing.begin(); i != listing.end(); ++i)
    {
      cout << (*i).first << " supports :\n";
      Warsaw::Kit::Property *begin = (*i).second->get_buffer();
      Warsaw::Kit::Property *end = (*i).second->get_buffer() + (*i).second->length();
      for (Warsaw::Kit::Property *p = begin; p != end; ++p)
	cout << (*p).name << " : " << (*p).value << '\n';
    }
}
