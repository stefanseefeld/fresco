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

#include <Prague/Sys/Timer.hh>
#include <Prague/Sys/GetOpt.hh>
#include <Prague/Sys/Path.hh>
#include <Berlin/ServerImpl.hh>
#include <Berlin/RCManager.hh>

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

using namespace Prague;

int main(int argc, char **argv)
{
    GetOpt getopt(argv[0], "a module inspection tool");
    getopt.add('h', "help", GetOpt::novalue, "help message");
    getopt.add('v', "version", GetOpt::novalue, "version number");
    getopt.add('r', "resource", GetOpt::mandatory,
	       "the resource file to load");
    size_t argo = getopt.parse(argc, argv);
    argc -= argo;
    argv += argo;
    if (getopt.is_set("version"))
    {
	std::cout << "version is " << version << std::endl;
	exit(0);
    }
    if (getopt.is_set("help"))
    {
	getopt.usage();
	exit(0);
    }
    
    RCManager::setup(getopt);
    
    CORBA::PolicyList policies;
    ServerImpl *server =
	ServerImpl::create(PortableServer::POA::_nil(),policies);

    Prague::Path path = RCManager::get_path("modulepath");
    for (Prague::Path::iterator i = path.begin(); i != path.end(); ++i)
	server->scan(*i);

    ServerImpl::PluginList listing = server->list();
    for (ServerImpl::PluginList::iterator i = listing.begin();
	 i != listing.end();
	 ++i)
    {
	std::cout << (*i).first << " supports :\n";
	Fresco::Kit::Property *begin = (*i).second->get_buffer();
	Fresco::Kit::Property *end =
	    (*i).second->get_buffer() + (*i).second->length();
	for (Fresco::Kit::Property *p = begin; p != end; ++p)
	    std::cout << "  " << (*p).name << " : " << (*p).value << '\n';
    }
}
