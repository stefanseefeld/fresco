/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999,2000 Tobias Hunger <Tobias@fresco.org>
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

#ifndef _Client_hh
#define _Client_hh

#include <Fresco/config.hh>
#include <Fresco/resolve.hh>
#include <Fresco/exception.hh>
#include <Fresco/ClientContextImpl.hh>
#include <Fresco/Server.hh>
#include <Fresco/Graphic.hh>
#include <Fresco/Window.hh>
#include <Fresco/Trigger.hh>
#include <Fresco/Unicode.hh>
#include <Fresco/Controller.hh>

#include <Berlin/CommandImpl.hh>
#include <Berlin/ControllerImpl.hh>

class Berlin_Server {
public:
    Berlin_Server(int argc, char** argv, char const * appname) {

	// CORBA initialization
	orb = CORBA::ORB_init(argc, argv);
	name = resolve_init<CosNaming::NamingContext>(orb, "NameService");
	poa = resolve_init<PortableServer::POA>(orb, "RootPOA");
	poa_manager = poa->the_POAManager();
	poa_manager->activate();
	
	// Berlin initialization
	client = new ClientContextImpl(appname);
	server = resolve_name<Fresco::Server>(name, "IDL:fresco.org/Fresco/Server:1.0");
	server_context =
	    server->create_server_context(Fresco::ClientContext_var(client->_this()));
    }
 
    template<class T>
    typename T::_ptr_type get_kit(const char *name,
				  const Fresco::Kit::PropertySeq &props = 0) {
	return resolve_kit<T>(server_context, name, props);
    }

    CORBA::ORB_ptr get_ORB() { return orb; }
    CosNaming::NamingContext_ptr get_naming_context() { return name; }
    PortableServer::POA_ptr get_POA() { return poa; }
    PortableServer::POAManager_ptr get_POAManager() { return poa_manager; }

    ClientContextImpl * get_client_context() { return client; }
    Fresco::Server_ptr get_server() { return server; }
    Fresco::ServerContext_ptr get_server_context() { return server_context;}

    Fresco::ServerContext_var operator() () { return server_context; }

    ~Berlin_Server() { delete client; };
private:
    Berlin_Server() {};
    Berlin_Server(const Berlin_Server &) {};

    // CORBA
    CORBA::ORB_var orb;
    CosNaming::NamingContext_var name;
    PortableServer::POA_var poa;
    PortableServer::POAManager_var poa_manager;

    // BERLIN
    ClientContextImpl * client;
    Fresco::Server_var server;
    Fresco::ServerContext_var server_context;
};

#define REGISTER_KIT(server,name,kit,version) Fresco::##kit##_var name = server##.get_kit<Fresco::##kit>("IDL:fresco.org/Fresco/" #kit ":" #version)

#endif // Client_hh
