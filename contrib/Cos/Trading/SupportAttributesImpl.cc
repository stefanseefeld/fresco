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
#include "SupportAttributesImpl.hh"

using namespace Prague;
using namespace CosTrading;
using namespace CosTradingRepos;

SupportAttributesImpl::SupportAttributesImpl() : modifiable(true), dynamic(true), proxy(false) {}
CORBA::Boolean SupportAttributesImpl::supports_modifiable_properties() { MutexGuard guard(mutex); return modifiable;}
CORBA::Boolean SupportAttributesImpl::supports_dynamic_properties() { MutexGuard guard(mutex); return dynamic;}
CORBA::Boolean SupportAttributesImpl::supports_proxy_offers() { MutexGuard guard(mutex); return proxy;}
TypeRepository_ptr SupportAttributesImpl::type_repos()
{
  MutexGuard guard(mutex);
  return TypeRepository::_duplicate(repository);
}
ServiceTypeRepository_ptr SupportAttributesImpl::service_type_repos()
{
  MutexGuard guard(mutex);
  return ServiceTypeRepository::_duplicate(repository);
}
void SupportAttributesImpl::service_type_repos(ServiceTypeRepository_ptr r)
{
  MutexGuard guard(mutex); 
  repository = ServiceTypeRepository::_duplicate(r);
}
void SupportAttributesImpl::supports_modifiable_properties(bool m) { MutexGuard guard(mutex); modifiable = m;}
void SupportAttributesImpl::supports_dynamic_properties(bool d) { MutexGuard guard(mutex); dynamic = d;}
void SupportAttributesImpl::supports_proxy_offers(bool p) { MutexGuard guard(mutex); proxy = p;}
