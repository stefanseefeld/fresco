/*$Id$
 *
 * This source file is a part of the Fresco Project.
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
#include <Prague/Sys/Thread.hh>
#include <Berlin/config.hh>
#include <Berlin/Logger.hh>
#include <Berlin/KitImpl.hh>
#include <Berlin/ServantBase.hh>
#include <Berlin/ServerContextImpl.hh>
#include <typeinfo>

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

namespace
{
  Mutex mutex;
}

KitImpl::KitImpl(const std::string &id,
         const Fresco::Kit::PropertySeq &p,
         ServerContextImpl *c) :
    my_repo_id(id),
    my_props(new Fresco::Kit::PropertySeq(p)),
    my_refcount(1),
    my_context(c)
{
  Trace trace("KitImpl::KitImpl");
#ifdef LCLOG
  Logger::log(Logger::lifecycle)
      << "KitImpl::KitImpl: " << this << " constructed" << std::endl;
#endif
}

KitImpl::~KitImpl()
{
  Logger::log(Logger::lifecycle)
      << "destroying POA... " << my_poa << std::endl;
  my_poa->destroy(true, false);
  Logger::log(Logger::lifecycle)
      << "destroying POA done " << my_poa << std::endl;
#ifdef LCLOG
  Logger::log(Logger::lifecycle) 
      << "KitImpl::~KitImpl: " << this << " destructed" << std::endl;
#endif
  delete my_props;
  if (my_context) my_context->erase(this);
}

CORBA::Boolean KitImpl::supports(const Fresco::Kit::PropertySeq &p)
{
  Trace trace("KitImpl::supports");
  const Fresco::Kit::Property *begin2 = p.get_buffer();
  const Fresco::Kit::Property *end2 = begin2 + p.length();
  for (const Fresco::Kit::Property *property2 = begin2;
       property2 != end2; property2++)
  {
    const Fresco::Kit::Property *begin1 = my_props->get_buffer();
    const Fresco::Kit::Property *end1 = begin1 + my_props->length();
    const Fresco::Kit::Property *property1;
    for (property1 = begin1; property1 != end1; property1++)
      if (strcmp(property1->name, property2->name) == 0)
      {
    if (strcmp(property1->value, property2->value) == 0) break;
    else return false; // value not supported
      }
    if (property1 == end1) return false; // property not supported
  }
  return true;
}

void KitImpl::activate(::ServantBase *servant)
{
  Trace trace("KitImpl::activate(PortableServer::Servant)");
#ifdef LCLOG
  Logger::log(Logger::lifecycle)
      << "activating " << servant << " (" << typeid(*servant).name() << ")"
      << std::endl;
#endif
  PortableServer::ObjectId *oid = my_poa->activate_object(servant);
  servant->my_poa = PortableServer::POA::_duplicate(my_poa);
  servant->_remove_ref();
  delete oid;
  servant->activate_composite();
}

void KitImpl::deactivate(::ServantBase *servant)
{
  Trace trace("KitImpl::deactivate(PortableServer::Servant)");
  PortableServer::ObjectId *oid = my_poa->servant_to_id(servant);
#ifdef LCLOG
  Logger::log(Logger::lifecycle)
      << "deactivating " << servant << " (" << typeid(*servant).name() << ")"
      << std::endl;
#endif
  my_poa->deactivate_object(*oid);
  delete oid;
}

void KitImpl::increment()
{
  Trace trace("KitImpl::increment");
  Prague::Guard<Mutex> guard(mutex);
  ++my_refcount;
#ifdef LCLOG
  Logger::log(Logger::lifecycle)
      << "KitImpl::increment on " << this << " (" << typeid(*this).name()
      << "): new count is " << _refcount << std::endl;
#endif
}

void KitImpl::decrement()
{
  Trace trace("KitImpl::decrement");
  bool done;
  {
    Prague::Guard<Mutex> guard(mutex);
    done = --my_refcount;
#ifdef LCLOG
    Logger::log(Logger::lifecycle)
    << "KitImpl::decrement on " << this << " (" << typeid(*this).name()
    << "): new count is " << _refcount << std::endl;
#endif
  }
  if (done) return;
  else deactivate();
}

void KitImpl::deactivate()
{
  Trace trace("KitImpl::deactivate()");
  PortableServer::POA_var poa = _default_POA();
  PortableServer::ObjectId *oid = poa->servant_to_id(this);
#ifdef LCLOG
  Logger::log(Logger::lifecycle) << "deactivating " << this << std::endl;
#endif
  poa->deactivate_object(*oid);
  delete oid;
}
