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
#ifndef _ServerImpl_hh
#define _ServerImpl_hh

#include <Fresco/config.hh>
#include <Fresco/Server.hh>
#include <Fresco/Graphic.hh>
#include <Berlin/DefaultPOA.hh>
#include <Berlin/KitImpl.hh>
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/Plugin.hh>
#include <vector>
#include <string>
#include <map>

class ServerContextImpl;

//. the Server just hands out new ServerContexts to
//. people who are connecting.  it might want to do some checking on
//. the incoming ClientContext's credentials, but at the moment it doesn't.
class ServerImpl : public virtual POA_Fresco::Server,
                   public virtual PortableServer::RefCountServantBase
{
  friend class ServerContextImpl;

  typedef std::vector<ServerContextImpl *> clist_t;
  typedef std::vector<Prague::Plugin<KitImpl> *> pmap_t;
  typedef std::vector<KitImpl *> kmap_t;
  typedef std::map<std::string, CORBA::Object_var> smap_t;

public:
  PortableServer::POA_ptr _default_POA() { return PortableServer::POA::_duplicate(my_poa);}

  typedef std::multimap<std::string, Fresco::Kit::PropertySeq_var> PluginList;

  //. Create() can be called once only! It creates the one server-object.
  static ServerImpl *create(PortableServer::POA_ptr poa, const CORBA::PolicyList &);
  //. Get a reference to the server in use.
  static ServerImpl *instance();
  
  //. Create a ServerContext. This is what is called by a client that
  //. wants to connect to this server. A ServerContext holds all objects
  //. generated by a client and gets deleted (destructing all those objects)
  //. as soon as the client terminated (or the server is no longer
  //. able to ping the client).
  virtual Fresco::ServerContext_ptr
  create_server_context(Fresco::ClientContext_ptr c)
    throw (Fresco::SecurityException);

  //. Set_singleton() 'publishes' a given Object under a given name.
  //. Clients then can request access to this object with get_singleton.
  //. The server makes sure that there are no two objects by the same name,
  //. throwing an SingletonFailureException as soon as someone tries to
  //. give a name allready known to the server,
  virtual void set_singleton(const char *, CORBA::Object_ptr)
    throw (Fresco::SecurityException, Fresco::SingletonFailureException);
  //. This method removes the object of the given name from the
  //. list of known singletons. It does not destruct the object
  virtual void remove_singleton(const char *)
    throw (Fresco::SecurityException, Fresco::SingletonFailureException);
  virtual CORBA::Object_ptr get_singleton(const char *) 
    throw (Fresco::SecurityException, Fresco::SingletonFailureException);
  
  //. Finds the requested Kit and returns a reference to it.
  template <class K>
  typename K::_ptr_type resolve(const char *,
				const Fresco::Kit::PropertySeq &,
				PortableServer::POA_ptr);

  //. Starts the server.
  void start();
  //. Stops the server.
  void stop();
  //. Pings all ServerContexts and destroys those that do not
  //. respond (aka. crashed).
  void ping();
  //. This scans all directories given as modulepath in berlinrc for Kits
  //. and loads the whole lot of them.
  void scan(const std::string &);
  //. Deletes all known Kits.
  void clear();
  //. Returns a list of all known Pluginnames (kits) and their properties.
  PluginList list();

protected:
  //. Finds the requested kit and loads it. This is a helper function only.
  //. Use resolve,
  KitImpl *create(const char *,
		  const Fresco::Kit::PropertySeq &,
		  PortableServer::POA_ptr,
		  ServerContextImpl *);

private:
  ServerImpl(const CORBA::PolicyList &);
  
  //. Called every second to ping the clients.
  static void *run(void *);

  //. Destroys a given Servercontext (and with that the client's resources
  //. in this server).
  static void destroy_context(ServerContextImpl *);
  PortableServer::POA_var my_poa;
  CORBA::PolicyList       my_policies;
  Prague::Thread          my_thread;
  Prague::Mutex           my_mutex;
  smap_t                  my_singletons;
  clist_t                 my_contexts;
  pmap_t                  my_plugins;
  kmap_t                  my_kits;
  static ServerImpl      *my_server;
};

template <class K>
typename K::_ptr_type ServerImpl::resolve(const char *type,
					  const Fresco::Kit::PropertySeq &properties,
					  PortableServer::POA_ptr poa)
{
  KitImpl *kit = create(type, properties, poa, 0);
  if (!kit) return K::_nil();
  typename K::_var_type reference;
  try
  {
    reference = K::_narrow(Fresco::Kit_var(kit->_this()));
  }
  catch (CORBA::Exception &e)
  {
    std::cerr << "Cannot narrow reference: " << e << std::endl;
    return K::_nil();
  }
  if (CORBA::is_nil(reference))
  {
    std::cerr << "Reference has incorrect type" << std::endl;
    return K::_nil();
  }
  my_kits.push_back(kit);
  return reference._retn();
}

#endif
