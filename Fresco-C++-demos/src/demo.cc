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
#include "GridDemo.hh"
#include <memory>

using namespace Prague;
using namespace Fresco;

int main(int argc, char **argv)
{
    Prague::GetOpt getopt(argv[0], "C++ fresco demo");
    getopt.add('h', "help", Prague::GetOpt::novalue, "help message");
    add_resolving_options_to_getopt(getopt);
    size_t argo = getopt.parse(argc, argv);
    argc -= argo;
    argv += argo;

    if (getopt.is_set('h'))
    {
        getopt.usage();
        exit(0);
    }

   try
   {
       CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
       PortableServer::POA_var poa =
         resolve_init<PortableServer::POA>(orb, "RootPOA");
       DefaultPOA::default_POA(poa);
       PortableServer::POAManager_var pman = poa->the_POAManager();
       pman->activate();

       Server_var server = resolve_server(getopt, orb);

       ClientContextImpl *client = new ClientContextImpl("Demo application");
       ClientContext_var client_ref = client->_this();

       ServerContext_var server_context =
         server->create_server_context(client_ref);

       Application *application = new Application(server_context, client_ref);

       std::auto_ptr<Demo> layout(create_demo<LayoutDemo>(application));
       std::auto_ptr<Demo> text(create_demo<TextDemo>(application));
       std::auto_ptr<Demo> edit(create_demo<EditTextDemo>(application));
       std::auto_ptr<Demo> raster(create_demo<RasterDemo>(application));
       std::auto_ptr<Demo> grid(create_demo<GridDemo>(application));
       std::auto_ptr<Demo> color(create_demo<ColorDemo>(application));
       std::auto_ptr<Demo> logo(create_demo<LogoDemo>(application));
       std::auto_ptr<Demo> focus(create_demo<FocusDemo>(application));
       std::auto_ptr<Demo> viewport(create_demo<ViewportDemo>(application));
       std::auto_ptr<Demo> document(create_demo<DocDemo>(application));
       std::auto_ptr<Demo> terminal(create_demo<TermDemo>(application));

       application->run();
       delete application;
       delete client;
   }
   catch (const CORBA::COMM_FAILURE &c)
   {
       std::cerr << "Could not connect to the display server "
                 << "(CORBA::COMM_FAILURE)." << std::endl;
   }
   catch (const std::exception &e)
   {
       std::cerr << "Exception: " << e.what() << std::endl;
   }
}
