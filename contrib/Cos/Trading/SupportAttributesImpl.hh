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
#ifndef _SupportAttributesImpl_hh
#define _SupportAttributesImpl_hh

#include <CosTrading.hh>
#include <CosTradingRepos.hh>
#include <Prague/Sys/Thread.hh>

class SupportAttributesImpl : virtual public CosTrading::_sk_SupportAttributes
{
public:
  SupportAttributesImpl();
  CORBA::Boolean supports_modifiable_properties();
  CORBA::Boolean supports_dynamic_properties();
  CORBA::Boolean supports_proxy_offers();
  CosTrading::TypeRepository_ptr type_repos();

  CosTradingRepos::ServiceTypeRepository_ptr service_type_repos();
  void service_type_repos(CosTradingRepos::ServiceTypeRepository_ptr);
  void supports_modifiable_properties (bool);
  void supports_dynamic_properties (bool);
  void supports_proxy_offers (bool);
private:
  Prague::Mutex mutex;
  bool modifiable;
  bool dynamic;
  bool proxy;
  CosTradingRepos::ServiceTypeRepository_var repository;
};
#endif
