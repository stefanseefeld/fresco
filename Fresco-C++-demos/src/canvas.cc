 /*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include <Prague/Sys/GetOpt.hh>
#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/resolve.hh>
#include <Fresco/Server.hh>
#include <Fresco/ClientContextImpl.hh>
#include <Fresco/DesktopKit.hh>
#include <Fresco/ToolKit.hh>
#include <Fresco/Canvas.hh>
#include <Fresco/MainController.hh>
#include <unistd.h>
#include <iostream>
#include <strstream>
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
  getopt.add('f', "frequency", GetOpt::optional, "the frequency with which to poll the ggi visual");
  getopt.parse(argc - 1, argv + 1);
  std::string value;
  getopt.get("help", &value);
  if (value == "true") { getopt.usage(); exit(0);}
  value = "";  
  getopt.get("run", &value);
  if (value.empty()) { getopt.usage(); exit(0);}
  std::string program = value;
  value = "";
  getopt.get("frequency", &value);
  int wait = 250;
  if (value.length())
    {
      std::istrstream iss(value.c_str());
      iss >> wait;
    };
  
  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
  PortableServer::POA_var poa = resolve_init<PortableServer::POA>(orb, "RootPOA");
  PortableServer::POAManager_var pman = poa->the_POAManager();
  pman->activate();

  ClientContextImpl *client = new ClientContextImpl("Canvas");

  Server_var s = resolve_server(argc, argv, orb);
  ServerContext_var server = s->create_server_context(ClientContext_var(client->_this()));

  DesktopKit_var desktop = resolve_kit<DesktopKit>(server);
  ToolKit_var tool = resolve_kit<ToolKit>(server);
  Canvas_var canvas = tool->create_canvas(256, 256);

  Window_var window = desktop->shell(Controller_var(tool->group(canvas)),
                     ClientContext_var(client->_this()));

  /*
   * set up the client side visual part...
   */
  ggiInit();
  std::ostrstream oss;
  oss << "display-memory:-input:shmid:" << canvas->shm_id() << std::ends;
  const char *name = oss.str();
  setenv("GGI_DISPLAY", name, 1);
  delete [] name;

  Fresco::Canvas::BufferFormat bformat = canvas->buffer_format();
  Fresco::Canvas::PixelFormat pformat = canvas->pixel_format();
  ggi_mode mode;
  mode.frames = 1;
  mode.visible.x = mode.virt.x = bformat.width;
  mode.visible.y = mode.virt.y = bformat.height;
  switch (pformat.depth/8)
    {
    case 1: mode.graphtype = GT_8BIT; break;
    case 2: mode.graphtype = GT_16BIT; break;
    case 3: mode.graphtype = GT_24BIT; break;
    case 4: mode.graphtype = GT_32BIT; break;
    default: mode.graphtype = GGI_AUTO; break;
    };
  mode.dpp.x = mode.dpp.y = 1;
  char buffer[256];
  ggiSPrintMode(buffer, &mode);
  setenv("GGI_DEFMODE", buffer, 1);
  switch (fork())
    {
    case -1: std::cerr << "can't fork !" << std::endl; exit(-1); break;
    case 0:
      execlp("/bin/sh","/bin/sh","-c", program.c_str(), 0);
      exit(127);
    default:
      while (1)
    {
      canvas->need_redraw();
      Thread::delay(wait);
    }
    }
};
