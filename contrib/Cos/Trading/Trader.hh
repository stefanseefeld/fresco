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
#ifndef _Trader_hh
#define _Trader_hh

#include <CosTrading.hh>
#include <CosTradingRepos.hh>

#include <list>

class ServiceTypeRepositoryImpl;
class LinkImpl;
class ProxyImpl;
class LookupImpl;
class RegisterImpl;

struct Offer
{
  CORBA::Object_var vReference;
  CosTrading::ServiceTypeName_var vType;
  CosTrading::PropertySeq properties;
  CosTrading::OfferId_var vOfferId;
  CosTrading::Proxy::ProxyInfo_var vProxy;
  bool isProxy;
};

class Trader
{
public:
//   Trader(CORBA::Object_ptr);
//   Trader(const CORBA::BOA::ReferenceData &tag);
  
  CosTrading::Lookup_ptr lookup_if();
  CosTrading::Register_ptr register_if();
  CosTrading::Link_ptr link_if();
  CosTrading::Proxy_ptr proxy_if();
  CosTrading::TypeRepository_ptr typeRepository();
  CosTradingRepos::ServiceTypeRepository_ptr serviceTypeRepository();
  
  // Hack
  ServiceTypeRepositoryImpl *hack() { return _typeRepository;}
  
  /*
   * @param _offer is deleted by this class if needed.
   *               After this call you are no longer allowed to delete
   *               the _offer yourself.
   *               The field 'offerid' in struct Offer does not need to have
   *               a meaningfull value. It is set by this function.
   *
   * @return _offer gets a valid OfferId.
   */
  void export_offer (Offer *);
  void import(const char *type, const char *constr, const char *pref, const CosTrading::PolicySeq &policies,
	      const CosTrading::Lookup::SpecifiedProps &desired_props, CORBA::ULong how_many,
	      CosTrading::OfferSeq *&offers, CosTrading::OfferIterator_ptr &offer_itr,
	      CosTrading::PolicyNameSeq*& limits_applied);
  void remove(const char *);
  CosTrading::Register::OfferInfo *describe(const char *);
  void modify(const char *, const CosTrading::PropertyNameSeq &, const CosTrading::PropertySeq &);
  void withdraw_using_constraint(const char *, const char *);
  char *export_proxy(CosTrading::Lookup_ptr, const char *, const CosTrading::PropertySeq &, CORBA::Boolean,
		     const char *, const CosTrading::PolicySeq &);
  void withdraw_proxy(const char *);
  CosTrading::Proxy::ProxyInfo *describe_proxy(const char *);
  CORBA::ULong defSearchCard();
  CORBA::ULong maxSearchCard();
  CORBA::ULong defMatchCard();
  CORBA::ULong maxMatchCard();
  CORBA::ULong defReturnCard();
  CORBA::ULong maxReturnCard();
  CORBA::ULong maxList();
  CORBA::ULong defHopCount();
  CORBA::ULong maxHopCount();
  CosTrading::FollowOption defLinkFollowPolicy();
  CosTrading::FollowOption maxLinkFollowPolicy();
protected:
  RegisterImpl *_register;
  LookupImpl *lookup;
  ServiceTypeRepositoryImpl *_typeRepository;
  LinkImpl *link;
  ProxyImpl *proxy;
  CosTrading::Admin::OctetSeq requestIdStem;
  list<CosTrading::Admin::OctetSeq> lstStems;
  list<Offer *> lstOffers;
  int uniqueId;
};

#endif
