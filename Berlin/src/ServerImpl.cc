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

#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/Directory.hh>
#include "Berlin/Logger.hh"
#include "Berlin/ImplVar.hh"
#include "Berlin/ServerImpl.hh"
#include "Berlin/ServerContextImpl.hh"

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

ServerImpl *ServerImpl::my_server = 0;;

ServerImpl *ServerImpl::create(PortableServer::POA_ptr poa, const CORBA::PolicyList &policies)
{
  assert(my_server == 0);
  my_server = new ServerImpl(policies);
  my_server->my_poa = PortableServer::POA::_duplicate(poa);
  return my_server;
}

ServerImpl *ServerImpl::instance()
{
  return my_server;
}

ServerImpl::ServerImpl(const CORBA::PolicyList &policies)
  : my_policies(policies),
    my_thread(&ServerImpl::run, this)
{
}

//. This is called by the client to get its server context!
ServerContext_ptr ServerImpl::create_server_context(ClientContext_ptr c)
    throw (SecurityException)
{
  Trace trace("ServerImpl::create_server_context");
  Prague::Guard<Mutex> guard(my_mutex);
  Impl_var<ServerContextImpl> sc(new ServerContextImpl(this, my_policies, c));
  my_contexts.push_back(sc);
  return sc._retn()->_this();
}

void ServerImpl::set_singleton(const char *name,
                   CORBA::Object_ptr singleton) 
  throw (SecurityException, SingletonFailureException)
{
  Prague::Guard<Mutex> guard(my_mutex);
  // test wether the name is allready in use:
  smap_t::iterator p = my_singletons.find(name);
  if (p != my_singletons.end()) throw SingletonFailureException();
  else my_singletons[name] = singleton;
}

void ServerImpl::remove_singleton(const char *name) 
  throw (SecurityException, SingletonFailureException)
{
  Prague::Guard<Mutex> guard(my_mutex);
  smap_t::iterator p = my_singletons.find(name);
  if (p != my_singletons.end()) my_singletons.erase(p);
  throw SingletonFailureException();
}

CORBA::Object_ptr ServerImpl::get_singleton(const char *name) 
  throw (SecurityException, SingletonFailureException)
{
  Prague::Guard<Mutex> guard(my_mutex);
  smap_t::iterator p = my_singletons.find(name);
  if (p != my_singletons.end()) return CORBA::Object::_duplicate(p->second);
  throw SingletonFailureException();
}

void ServerImpl::start()
{
  my_thread.start();
}

void ServerImpl::stop()
{
  Trace trace("ServerImpl::stop");
  Prague::Guard<Mutex> guard (my_mutex);
  for (clist_t::iterator i = my_contexts.begin(); i != my_contexts.end(); i++)
    ServerImpl::destroy_context(*i);
  my_contexts.clear();
}

void ServerImpl::ping()
{
  Trace trace("ServerImpl::ping");
  Prague::Guard<Mutex> guard(my_mutex);
  clist_t updated_contexts;
  for (clist_t::iterator i = my_contexts.begin(); i != my_contexts.end(); i++)
  {
    if ((*i)->ping())
      updated_contexts.push_back(*i);
    else
      destroy_context(*i);
  }
  my_contexts = updated_contexts;
};

void ServerImpl::scan(const std::string &name)
{
  Prague::Guard<Mutex> guard(my_mutex);
  /*
   * load all files in <name> according to the regexp '\\.so$'
   */
  Directory directory(name, Directory::alpha, "Kit\\.so$");
  Logger::log(Logger::loader) << "ServerImpl: scanning plugin dir " << name << std::endl;
  for (Directory::iterator i = directory.begin(); i != directory.end(); i++)
    {
      Plugin<KitImpl> *plugin;
      try { plugin = new Plugin<KitImpl>((*i)->long_name());}
      catch(const std::runtime_error &e)
    {
      // not loadable, skip over it
      Logger::log(Logger::loader) << (*i)->name() << " not loadable " << e.what() << std::endl;
      continue;
    }
      my_plugins.push_back(plugin);
      Logger::log(Logger::loader) << "ServerImpl: loaded plugin for " << (*plugin)->repo_id() << " from " << (*i)->name() << std::endl;
    }
}

//. hope you know what you are doing if you call this...
void ServerImpl::clear()
{
  Prague::Guard<Mutex> guard(my_mutex);
  for (pmap_t::iterator i = my_plugins.begin(); i != my_plugins.end(); ++i) delete *i;
  my_plugins.clear();
}

ServerImpl::PluginList ServerImpl::list()
{
  PluginList pl;
  for (pmap_t::iterator i = my_plugins.begin(); i != my_plugins.end(); ++i)
    pl.insert(PluginList::value_type((**i)->repo_id(), (**i)->properties()));
  return pl;
}

KitImpl *ServerImpl::create(const char *type,
                const Kit::PropertySeq &properties,
                PortableServer::POA_ptr poa,
                ServerContextImpl *context)
{
  Trace trace("ServerImpl::create");
  for (pmap_t::iterator i = my_plugins.begin(); i != my_plugins.end(); ++i)
    if ((**i)->_is_a(type) && (**i)->supports(properties))
    {
      KitImpl *kit = (**i)->clone(properties, context);
      kit->my_poa = PortableServer::POA::_duplicate(poa);
      PortableServer::POA_var root = kit->_default_POA();
      PortableServer::ObjectId *oid = root->activate_object(kit);
      kit->_remove_ref();
      delete oid;
      return kit;
    }
  return 0;
}

void *ServerImpl::run(void *X)
{
  ServerImpl *server = reinterpret_cast<ServerImpl *>(X);
  while (true)
  {
    Thread::delay(1000);
    server->ping();
  }
  return 0;
}

void ServerImpl::destroy_context(ServerContextImpl *context)
{
  Trace trace("ServerImpl::destroy_context");
  PortableServer::POA_var poa = context->_default_POA();
  PortableServer::ObjectId * oid = poa->servant_to_id(context);
  try { poa->deactivate_object(*oid); }
  /*
   * should this output go to Logger::log(Logger::corba) ?
   * -stefan
   */
  catch (const CORBA::OBJECT_NOT_EXIST &)
  {
    std::cerr << "Caught CORBA::OBJECT_NOT_EXIST while cleaning up "
          << "a ServerContext" << std::endl;
  }
  catch (const CORBA::COMM_FAILURE &)
  {
    std::cerr << "Caught CORBA::COMM_FAILURE while cleaning up "
          << "a ServerContext" << std::endl;
  }
  catch (const CORBA::TRANSIENT &)
  {
    std::cerr << "Caught CORBA::TRANSIENT while cleaning up "
          << "a ServerContext" << std::endl;
  }
  catch (const PortableServer::POA::ObjectNotActive &)
  {
    std::cerr << "Caught POA::ObjectNotActive while cleaning up "
          << "a ServerContext" << std::endl;
  }
  catch (const PortableServer::POA::WrongPolicy &)
  {
    std::cerr << "Caught POA::WrongPolicy while cleaning up "
          << "a ServerContext" << std::endl;
  }
  catch(const std::exception & e)
  {
    std::cerr << "Caught a std::exeception while cleaning up "
          << "a ServerContext (" << e.what() << ")" << std::endl;
  }
  catch(...)
  {
    std::cerr << "Caught unknown exception while cleaning up "
          << "a ServerContext" << std::endl;
  }
  delete oid;
}
