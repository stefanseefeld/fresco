/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include <Prague/Sys/Tracer.hh>
#include "Berlin/ServantBase.hh"
#include "Berlin/KitImpl.hh"

using namespace Prague;
using namespace Warsaw;

void ServantBase::deactivate()
{
  Trace trace("ServantBase::deactivate");
  assert(!CORBA::is_nil(poa));
  PortableServer::ObjectId *oid = poa->servant_to_id(this);
  poa->deactivate_object(*oid);
  delete oid;
};

void ServantBase::activate(ServantBase *servant)
{
  Trace trace("ServantBase::activate");
  assert(!CORBA::is_nil(poa));
  PortableServer::ObjectId *oid = poa->activate_object(servant);
  servant->poa = PortableServer::POA::_duplicate(poa);
  servant->_remove_ref();
  delete oid;
  servant->activateComposite();
};

