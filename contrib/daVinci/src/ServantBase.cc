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
#include "daVinci/ServantBase.hh"
#include <typeinfo>

using namespace Prague;
using namespace Fresco;

namespace daVinci
{

PortableServer::POA_var ServantBase::_poa;

void ServantBase::deactivate()
{
  ServantBase::deactivate(this);
};

void ServantBase::deactivate(ServantBase *servant)
{
  Trace trace("ServantBase::deactivate(ServantBase *)");
  assert(!CORBA::is_nil(_poa));
  PortableServer::ObjectId *oid = _poa->servant_to_id(servant);
  _poa->deactivate_object(*oid);
  delete oid;
};

void ServantBase::activate(ServantBase *servant)
{
  Trace trace("ServantBase::activate");
  assert(!CORBA::is_nil(_poa));
  PortableServer::ObjectId *oid = _poa->activate_object(servant);
  servant->_remove_ref();
  delete oid;
  servant->activate_composite();
};

void ServantBase::poa(PortableServer::POA_ptr poa)
{
  _poa = PortableServer::POA::_duplicate(poa);
}

PortableServer::POA_ptr ServantBase::poa()
{
  return PortableServer::POA::_duplicate(_poa);
}
};
