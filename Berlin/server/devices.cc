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

#include <Prague/Sys/Path.hh>
#include <Prague/Sys/User.hh>
#include <Prague/Sys/GetOpt.hh>
#include <Berlin/RCManager.hh>
#include <Berlin/Console.hh>

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
    GetOpt getopt(argv[0], "input device info for the berlin display server");
    getopt.add('h', "help", GetOpt::novalue, "help message");
    getopt.add('v', "version", GetOpt::novalue, "version number");
    getopt.add('c', "console", GetOpt::mandatory, "the console to choose");
    getopt.add('r', "resource", GetOpt::mandatory,
	       "the resource file to load");
    size_t argo = getopt.parse(argc, argv);
    argc -= argo;
    argv += argo;
    if (getopt.is_set("version"))
    {
	std::cout << "version is " << version << std::endl;
	return 0;
    }
    if (getopt.is_set("help"))
    {
	getopt.usage();
	return 0;
    }

    Berlin::RCManager::setup(getopt);
    
    std::string value;
    getopt.get("console",&value);
    try
    {
	Berlin::Console::open(value, argc, argv,
			      PortableServer::POA::_nil(), 1, 1);
    }
    catch (const std::exception &e)
    {
	std::cerr << "Exception: " << e.what() << std::endl;
	return 1;
    }
    catch (...)
    {
	std::cerr << "ERROR: *UNKNOWN* exception caught" << std::endl;
    }
    Berlin::Console::instance()->device_info(std::cout);
    return 0;
}
