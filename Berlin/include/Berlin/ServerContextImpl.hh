/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1998 Graydon Hoare <graydon@fresco.org> 
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
#ifndef _ServerContextImpl_hh
#define _ServerContextImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/Server.hh>
#include <Berlin/DefaultPOA.hh>
#include <Berlin/KitImpl.hh>
#include <map>

class ServerImpl;

//. this is an encapsulated "entry point" which a client uses to manufacture
//. new objects, look up singletons, look up the scene root, etc.
class ServerContextImpl : public virtual POA_Fresco::ServerContext,
			  public virtual PortableServer::RefCountServantBase,
			  public DefaultPOA
{
  typedef std::multimap<std::string, KitImpl *> klist_t;
  friend class KitImpl;
public:
  ServerContextImpl(ServerImpl *, const CORBA::PolicyList &, Fresco::ClientContext_ptr);
  ~ServerContextImpl();
  PortableServer::POA_ptr _default_POA() { return DefaultPOA::_default_POA();}

  Fresco::ClientContext_ptr client();
  Fresco::Kit_ptr resolve(const char *, const Fresco::Kit::PropertySeq &)
    throw (Fresco::SecurityException, Fresco::CreationFailureException);
  void set_singleton(const char *, CORBA::Object_ptr) 
    throw (Fresco::SecurityException, Fresco::SingletonFailureException);
  void remove_singleton(const char *) 
    throw (Fresco::SecurityException, Fresco::SingletonFailureException);
  CORBA::Object_ptr get_singleton(const char *) 
    throw (Fresco::SecurityException, Fresco::SingletonFailureException);
  bool ping();
private:
  void erase(KitImpl *);
  static unsigned long      my_counter;
  ServerImpl               *my_server;
  CORBA::PolicyList         my_policies;
  Fresco::ClientContext_var my_client;
  klist_t                   my_kits;
  Prague::Mutex             my_mutex;
};

#endif
