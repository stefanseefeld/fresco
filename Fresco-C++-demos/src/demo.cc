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

#include <Fresco/config.hh>
#include <Fresco/resolve.hh>
#include "Application.hh"
#include "LayoutDemo.hh"
#include "TextDemo.hh"
#include "EditTextDemo.hh"
#include "RasterDemo.hh"
#include "ColorDemo.hh"
#include "LogoDemo.hh"
#include "FocusDemo.hh"
#include "ViewportDemo.hh"
#include "DocDemo.hh"
#include "TermDemo.hh"

using namespace Prague;
using namespace Fresco;

bool running;

int main(int argc, char **argv)
{
  try
    {
      CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
      CosNaming::NamingContext_var context = resolve_init<CosNaming::NamingContext>(orb, "NameService");
      PortableServer::POA_var poa = resolve_init<PortableServer::POA>(orb, "RootPOA");
      DefaultPOA::default_POA(poa);
      PortableServer::POAManager_var pman = poa->the_POAManager();
      pman->activate();

      ClientContextImpl *client = new ClientContextImpl("Demo application");

      Server_var s = resolve_name<Server>(context, "IDL:Fresco/Server:1.0");
      ServerContext_var server = s->create_server_context(ClientContext_var(client->_this()));

      Application *application = new Application(server, ClientContext_var(client->_this()));

      Demo *layout    = new LayoutDemo(application);
      Demo *text      = new TextDemo(application);
      Demo *edit      = new EditTextDemo(application);
      Demo *raster    = new RasterDemo(application);
      Demo *color     = new ColorDemo(application);
      Demo *logo      = new LogoDemo(application);
      Demo *focus     = new FocusDemo(application);
      Demo *viewport  = new ViewportDemo(application);
      Demo *document  = new DocDemo(application);
      Demo *terminal  = new TermDemo(application);
      application->run();
      delete terminal;
      delete document;
      delete viewport;
      delete focus;
      delete logo;
      delete color;
      delete raster;
      delete edit;
      delete text;
      delete layout;
      delete application;
    }
  catch (const CORBA::COMM_FAILURE &c)
    {
      std::cerr << "Could not connect to the display server (CORBA::COMM_FAILURE)." << std::endl;
    }
  catch (const std::exception &e)
    {
      std::cerr << "Exception: " << e.what() << std::endl;
    }
}
