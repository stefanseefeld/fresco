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
#include "Berlin/KitImpl.hh"
#include "Berlin/ServantBase.hh"

using namespace Prague;
using namespace Warsaw;

KitImpl::KitImpl(const std::string &id, const Warsaw::Kit::PropertySeq &p)
  : _repo_id(id), _props(new Warsaw::Kit::PropertySeq(p)), _refcount(1)
{
  Trace trace("KitImpl::KitImpl");
}

KitImpl::~KitImpl()
{
  Trace trace("KitImpl::~KitImpl");  
  _poa->destroy(true, true);
  delete _props;
}

CORBA::Boolean KitImpl::supports(const Warsaw::Kit::PropertySeq &p)
{
  Trace trace("KitImpl::supports");
  const Warsaw::Kit::Property *begin2 = p.get_buffer();
  const Warsaw::Kit::Property *end2 = begin2 + p.length();
  for (const Warsaw::Kit::Property *property2 = begin2; property2 != end2; property2++)
    {
      const Warsaw::Kit::Property *begin1 = _props->get_buffer();
      const Warsaw::Kit::Property *end1 = begin1 + _props->length();
      const Warsaw::Kit::Property *property1;
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
  PortableServer::ObjectId *oid = _poa->activate_object(servant);
  servant->poa = PortableServer::POA::_duplicate(_poa);
  servant->_remove_ref();
  delete oid;
  servant->activate_composite();
}

void KitImpl::deactivate(::ServantBase *servant)
{
  Trace trace("KitImpl::deactivate(PortableServer::Servant)");
  PortableServer::ObjectId *oid = _poa->servant_to_id(servant);
  _poa->deactivate_object(*oid);
  delete oid;
}

void KitImpl::deactivate()
{
  Trace trace("KitImpl::deactivate()");
  PortableServer::ObjectId *oid = _poa->servant_to_id(this);
  _poa->deactivate_object(*oid);
  delete oid;
}


