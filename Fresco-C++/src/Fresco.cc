/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include "Warsaw/Warsaw.hh"
#include "Warsaw/Server.hh"

Warsaw::Warsaw(int argc, char **argv)
  : orb(CORBA::ORB_init(argc,argv,"omniORB2")),
    boa(orb->BOA_init(argc,argv,"omniORB2_BOA")),
    client(new ClientContextImpl)
{
  boa->impl_is_ready(0,1);
  client->_obj_is_ready(boa);
  CosNaming::NamingContext_var context = resolve_init<CosNaming::NamingContext>(orb, "NameService");
  Server_var s = resolve_name<Server>(context, interface(Server));
  server = s->newServerContext(ClientContext_var(client->_this()));
}

Warsaw::~Warsaw()
{
  client->_dispose();
}
