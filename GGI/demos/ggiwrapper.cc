 /*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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

#include <Prague/Sys/GetOpt.hh>
#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/resolve.hh>
#include <Fresco/Server.hh>
#include <Fresco/ClientContextImpl.hh>
#include <Fresco/DesktopKit.hh>
#include <Fresco/GGIKit.hh>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

extern "C" 
{
#include <ggi/ggi.h>
}

using namespace Prague;
using namespace Fresco;

int main(int argc, char **argv)
{
  GetOpt getopt(argv[0], "a berlin client demonstrating the Canvas");
  getopt.add('h', "help", GetOpt::novalue, "help message");
  getopt.add('r', "run", GetOpt::mandatory, "the ggi program to run");
  getopt.add('w', "width", GetOpt::mandatory, "the width of the visual");
  getopt.add('h', "height", GetOpt::mandatory, "the height of the visual");
  getopt.parse(argc - 1, argv + 1);
  if (getopt.is_set("help")) { getopt.usage(); exit(0);}
  std::string value;
  getopt.get("run", &value);
  if (value.empty()) { getopt.usage(); exit(0);}
  std::string program = value;
  value = "";
  getopt.get("width", &value);
  size_t width = 256;
  if (!value.empty()) { std::istringstream iss(value); iss >> width;}
  value = "";
  getopt.get("height", &value);
  size_t height = 256;
  if (!value.empty()) { std::istringstream iss(value); iss >> height;}

  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
  CosNaming::NamingContext_var context = resolve_init<CosNaming::NamingContext>(orb, "NameService");
  PortableServer::POA_var poa = resolve_init<PortableServer::POA>(orb, "RootPOA");
  PortableServer::POAManager_var pman = poa->the_POAManager();
  pman->activate();

  ClientContextImpl *client = new ClientContextImpl("GGI Wrapper");

  Server_var s = resolve_name<Server>(context, "IDL:fresco.org/Fresco/Server:1.0");
  ServerContext_var server = s->create_server_context(ClientContext_var(client->_this()));

  DesktopKit_var desktop = resolve_kit<DesktopKit>(server, "IDL:fresco.org/Fresco/DesktopKit:1.0");
  GGI::GGIKit_var ggi = resolve_kit<GGI::GGIKit>(server, "IDL:GGI/GGIKit:1.0");
  GGI::Visual_var visual = ggi->create_visual(width, height);
  Window_var window = desktop->shell(visual, ClientContext_var(client->_this()));

  /*
   * set up the client side visual part...
   */
  ggiInit();
  CORBA::String_var name = visual->name();
  std::cout << "visual name " << name << std::endl;
  setenv("GGI_DISPLAY", name, 1);
  CORBA::String_var mode = visual->mode();
  std::cout << "visual mode " << mode << std::endl;
  setenv("GGI_DEFMODE", mode, 1);
  switch (fork())
    {
    case -1: std::cerr << "can't fork !" << std::endl; exit(-1); break;
    case 0:
      execlp("/bin/sh","/bin/sh","-c", program.c_str(), 0);
      exit(127);
    default:
      while (1)
	{
	  visual->need_redraw();
	  Thread::delay(250);
	}
    }
};
