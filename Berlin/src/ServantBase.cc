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
#include "Berlin/ServantBase.hh"
#include <typeinfo>

using namespace Prague;
using namespace Fresco;
using namespace Berlin;

namespace
{
  Mutex mutex;
}

ServantBase::ServantBase() :
    my_refcount(1), my_poa(_default_POA())
{
#ifdef LCLOG
    Logger::log(Logger::lifecycle)
	<< "ServantBase::ServantBase: " << this << " constructed"
	<< std::endl;
#endif
}

ServantBase::ServantBase(const ServantBase &) :
    my_refcount(1), my_poa(_default_POA())
{
#ifdef LCLOG
    Logger::log(Logger::lifecycle)
	<< "ServantBase::ServantBase: " << this << " constructed"
	<< std::endl;
#endif
}

ServantBase::~ServantBase()
{
#ifdef LCLOG
    Logger::log(Logger::lifecycle)
	<< "ServantBase::~ServantBase: " << this << " destructed"
	<< std::endl;
#endif
}

ServantBase &ServantBase::operator = (const ServantBase &)
{ return *this; }

void ServantBase::_add_ref()
{
  Guard<Mutex> guard(mutex);
  ++my_refcount;
#ifdef LCLOG
  Logger::log(Logger::lifecycle)
      << "ServantBase::_add_ref on " << this
      << " (" << typeid(*this).name() << "): new count is "
      << my_refcount << std::endl;
#endif
}

PortableServer::POA_ptr ServantBase::_default_POA()
{ return DefaultPOA::_default_POA(); }

void ServantBase::_remove_ref()
{
    bool done;
    {
	Guard<Mutex> guard(mutex);
	done = --my_refcount;
#ifdef LCLOG
	Logger::log(Logger::lifecycle)
	    << "ServantBase::_remove_ref on " << this << " ("
	    << typeid(*this).name() << "): new count is " << my_refcount
	    << std::endl;
#endif
    }
    if (done) return;
#ifdef LCLOG
    Logger::log(Logger::lifecycle) << "deleting " << this << std::endl;
#endif
    delete this;
}

void ServantBase::deactivate() { ServantBase::deactivate(this); }

void ServantBase::deactivate(ServantBase *servant)
{
    Trace trace("ServantBase::deactivate(ServantBase *)");
    assert(!CORBA::is_nil(servant->my_poa));
    PortableServer::ObjectId *oid =
	servant->my_poa->servant_to_id(servant);
#ifdef LCLOG
    Logger::log(Logger::lifecycle)
	<< "deactivating " << servant << " (" << typeid(*servant).name()
	<< ")" << std::endl;
#endif
    servant->my_poa->deactivate_object(*oid);
    delete oid;
}

void ServantBase::activate(ServantBase *servant)
{
    Trace trace("ServantBase::activate");
    assert(!CORBA::is_nil(my_poa));
#ifdef LCLOG
    Logger::log(Logger::lifecycle)
	<< "activating " << servant << " (" << typeid(*servant).name()
	<< ")" << std::endl;
#endif
    PortableServer::ObjectId *oid = my_poa->activate_object(servant);
    servant->my_poa = PortableServer::POA::_duplicate(my_poa);
    servant->_remove_ref();
    delete oid;
    servant->activate_composite();
}
