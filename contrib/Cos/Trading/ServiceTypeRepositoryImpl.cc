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
#include "ServiceTypeRepositoryImpl.hh"
#include <string>
#include <list>
#include <iostream>

using namespace CosTrading;
using namespace CosTradingRepos;

ServiceTypeRepositoryImpl::ServiceTypeRepositoryImpl(Trader *t)
  : trader(t)
{
  _incarnation.high = 0;
  _incarnation.low = 0;
}

ServiceTypeRepository::IncarnationNumber ServiceTypeRepositoryImpl::incarnation() { return _incarnation;}

ServiceTypeRepository::IncarnationNumber ServiceTypeRepositoryImpl::add_type(const char *name,
									     const char *if_name,
									     const ServiceTypeRepository::PropStructSeq &props,
									     const ServiceTypeRepository::ServiceTypeNameSeq &super_types)
{
  /*
   * check for duplicate entries
   */
  if (types.find(name) != types.end())
    {
      ServiceTypeRepository::DuplicateServiceTypeName exc;
      exc.name = CORBA::string_dup(name);
      throw exc;
    }
  /*
   * check for validity of super types
   */
  for(CORBA::ULong i = 0; i < super_types.length(); i++)
    if (types.find(string(super_types[i])) != types.end())
      {
	UnknownServiceType exc;
	exc.type = CORBA::string_dup(super_types[i]);
	throw exc;
      }

  TypeStruct type;
  type.if_name = CORBA::string_dup(if_name);
  type.props = props;
  type.super_types = super_types;
  type.masked = false;
  type.incarnation = _incarnation;
  /*
   * check for duplicate properties names
   */
  map<string, bool> properties;
  for(CORBA::ULong j = 0; j < type.props.length(); j++)
    {
      if (properties.find(string(type.props[j].name)) != properties.end())
	{
	  DuplicatePropertyName exc;
	  exc.name = CORBA::string_dup(type.props[j].name);
	  throw exc;
	}
      properties[string(type.props[j].name)] = true;
    }
  
  /*
   * Check for redefinitions of properties
   */
  TypeStruct tmp = type;
  for(CORBA::ULong k = 0; k < type.super_types.length(); k++)
  {
    repository_t::iterator i2 = checkServiceType(type.super_types[k]);
    fully_describe_type(&tmp, (*i2).second);
  }
  map<string,CosTradingRepos::ServiceTypeRepository::PropStruct> map2;
  for(CORBA::ULong l = 0; l < tmp.props.length(); l++)
  {
    map<string,CosTradingRepos::ServiceTypeRepository::PropStruct>::iterator i = map2.find(string(tmp.props[l].name));
    if (i != map2.end())
      {
	if (tmp.props[l] != (*i).second)
	  {
	    ServiceTypeRepository::ValueTypeRedefinition exc;
	    exc.type_1 = CORBA::string_dup("HACK");
	    exc.type_2 = CORBA::string_dup("HACK");
	    exc.definition_1 = tmp.props[l];
	    exc.definition_2 = (*i).second;
	    throw exc;
	  }
      }
    map2[string(tmp.props[l].name)] = tmp.props[l];
  }

  /**
   * Add the new type
   */
  types[name] = type;
  incIncarnationNumber();
  return type.incarnation;
}

void ServiceTypeRepositoryImpl::remove_type(const char *name)
{
repository_t::iterator i = checkServiceType(name);
  
/**
 * Check wether it has sub types.
 */
repository_t::iterator i2 = types.begin();
 for( ; i2 != types.end(); ++i2)
   {
     // Iterate over all super types
     for(int i = 0; (*i2).second.super_types.length(); i++)
       {
	 if (strcmp((*i2).second.super_types[i], name) == 0)
	   {
	     ServiceTypeRepository::HasSubTypes exc;
	     exc.the_type = name;
	     exc.sub_type = CORBA::string_dup((*i2).first.c_str());
	     throw exc;
	   }
       }
   }
 types.erase(i);
}

ServiceTypeRepository::ServiceTypeNameSeq *
ServiceTypeRepositoryImpl::list_types(const ServiceTypeRepository::SpecifiedServiceTypes& which_types)
{
  /**
   * Handle the switch
   */
  bool all = true;
  ServiceTypeRepository::IncarnationNumber inc;
  if (which_types._d() == CosTradingRepos::ServiceTypeRepository::since)
  {
    all = false;
    inc = which_types.incarnation();
  }

  /**
   * Find list of service types
   */
  list<string> lst;
  repository_t::iterator i = types.begin();
  for( ; i != types.end(); ++i)
    if (all) lst.push_back((*i).first);
    else
      {
	ServiceTypeRepository::IncarnationNumber n = (*i).second.incarnation;
	if (_incarnation < n) lst.push_back((*i).first);
      }
  /**
   * Create answer
   */
  ServiceTypeRepository::ServiceTypeNameSeq *seq = new ServiceTypeRepository::ServiceTypeNameSeq;
  seq->length(lst.size());
  
  list<string>::iterator i2 = lst.begin();
  int k = 0;
  for( ; i2 != lst.end(); ++i2)
    (*seq)[k++] = CORBA::string_dup((*i2).c_str());
  return seq;
}

ServiceTypeRepository::TypeStruct *ServiceTypeRepositoryImpl::describe_type(const char *name)
{
  /**
   * Does the service type exist ?
   */
  repository_t::iterator i = checkServiceType( name );
  ServiceTypeRepository::TypeStruct *t = new ServiceTypeRepository::TypeStruct;
  *t = (*i).second;
  return t;
}

ServiceTypeRepository::TypeStruct *
ServiceTypeRepositoryImpl::fully_describe_type(const char *name)
{
  /**
   * Does the service type exist ?
   */
  repository_t::iterator i = checkServiceType(name);
  ServiceTypeRepository::TypeStruct *t = new ServiceTypeRepository::TypeStruct;
  *t = (*i).second;
  /**
   * Recursion over all super types
   */
  for(CORBA::ULong i = 0; i < t->super_types.length(); i++)
    {
      repository_t::iterator i2 = checkServiceType(t->super_types[i]);
      fully_describe_type(t, (*i2).second);
    }
  return t;
}

void ServiceTypeRepositoryImpl::fully_describe_type(ServiceTypeRepository::TypeStruct *result,
						    ServiceTypeRepository::TypeStruct &super_type)
{
  /*
   * Add properties
   */
  int len = result->props.length();
  result->props.length(len + super_type.props.length());
  for(CORBA::ULong k = 0; k < super_type.props.length(); k++)
    result->props[len + k] = super_type.props[k];
  /*
   * Recursion over all super types
   */
  for(CORBA::ULong i = 0; i < super_type.super_types.length(); i++)
    {
      // Add supertypes
      int len = result->super_types.length();
      result->super_types.length(len + 1);
      result->super_types[len] = super_type.super_types[i];
      // Recursion
      repository_t::iterator j = checkServiceType(super_type.super_types[i]);
      fully_describe_type(result, (*j).second);
    }
}

void ServiceTypeRepositoryImpl::mask_type(const char *name)
{
  /*
   * Does the service type exist ?
   */
  repository_t::iterator i = checkServiceType(name);
  /*
   * Is it already masked ?
   */
  if ((*i).second.masked)
    {
      ServiceTypeRepository::AlreadyMasked esc;
      esc.name = CORBA::string_dup( name );
      throw esc;
    }
  /*
   * Mask i
   */
  (*i).second.masked = true;
}

void ServiceTypeRepositoryImpl::unmask_type(const char *name)
{
  /*
   * Does the service type exist ?
   */
  repository_t::iterator i = checkServiceType(name);
  /*
   * Is it not masked ?
   */
  if (!(*i).second.masked)
    {
      ServiceTypeRepository::NotMasked esc;
      esc.name = CORBA::string_dup(name);
      throw esc;
  }
  /*
   * Unmask i
   */
  (*i).second.masked = false;
}

void ServiceTypeRepositoryImpl::incIncarnationNumber()
{
  _incarnation.low++;
  if (_incarnation.low == 0) _incarnation.high++;
}

ServiceTypeRepositoryImpl::repository_t::iterator
ServiceTypeRepositoryImpl::checkServiceType(const char *name)
{
  /*
   * Does the service type exist ?
   */
  repository_t::iterator i = types.find(name);
  if (i == types.end())
    {
      UnknownServiceType exc;
      exc.type = CORBA::string_dup(name);
      throw exc;
    }
  return i;
}
