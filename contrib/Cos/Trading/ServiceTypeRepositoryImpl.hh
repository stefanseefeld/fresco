/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
 * http://www.berlin-consortium.org
 *
 * this file is a port from Mico's trading service implementation
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
#ifndef _ServiceTypeRepositoryImpl_hh
#define _ServiceTypeRepositoryImpl_hh

#include <CosTradingRepos.hh>

#include <string>
#include <map>

bool operator != (const CosTradingRepos::ServiceTypeRepository::PropStruct &p1,
          const CosTradingRepos::ServiceTypeRepository::PropStruct &p2)
{
  if (p1.mode != p2.mode) return true;
  if (!p1.value_type->equal(p2.value_type)) return true;
  return false;
}

bool operator < (const CosTradingRepos::ServiceTypeRepository::IncarnationNumber &i1,
         const CosTradingRepos::ServiceTypeRepository::IncarnationNumber &i2)
{
  if (i1.high < i2.high) return true;
  if (i1.high > i2.high) return false;
  if (i1.low < i2.low) return true;
  return false;
}

class Trader;

class ServiceTypeRepositoryImpl : virtual public CosTradingRepos::_sk_ServiceTypeRepository
{
  typedef map<string, TypeStruct> repository_t;
public:
  ServiceTypeRepositoryImpl(Trader *);
  virtual IncarnationNumber incarnation();
  virtual IncarnationNumber add_type(const char *, const char *, const PropStructSeq &, const ServiceTypeNameSeq &);
  virtual void remove_type(const char *);
  virtual ServiceTypeNameSeq *list_types(const SpecifiedServiceTypes &);
  virtual TypeStruct *describe_type(const char *);
  virtual TypeStruct *fully_describe_type(const char *);
  virtual void mask_type(const char *);
  virtual void unmask_type(const char *);
protected:
  /**
   * Helper function for the recursion.
   */
  void fully_describe_type(TypeStruct *, TypeStruct &);
  /**
   * Increases the incarnation number.
   */
  void incIncarnationNumber();
  /**
   * Checks whether a certain service type is registered and returns an iterator
   * pointing at this service type. If the service type does not exist, then
   * the exception @ref CosTading::UnknownServiceType is thrown.
   */
  repository_t::iterator checkServiceType(const char *);
  Trader *trader;
  IncarnationNumber _incarnation;
  repository_t types;
};

#endif
