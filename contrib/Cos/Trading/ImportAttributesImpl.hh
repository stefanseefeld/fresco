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
#ifndef _ImportAttributesImpl_hh
#define _ImportAttributesImpl_hh

#include <CosTrading.hh>
#include "Trader.hh"

class ImportAttributesImpl : virtual public CosTrading::_sk_ImportAttributes
{
public:
  ImportAttributesImpl(Trader *t) : trader(t) {}
  CORBA::ULong def_search_card() { return trader->defSearchCard();}
  CORBA::ULong max_search_card() { return trader->maxSearchCard();}
  CORBA::ULong def_match_card() { return trader->defMatchCard();}
  CORBA::ULong max_match_card() { return trader->maxMatchCard();}
  CORBA::ULong def_return_card() { return trader->defReturnCard();}
  CORBA::ULong max_return_card() { return trader->maxReturnCard();}
  CORBA::ULong max_list() { return trader->maxList();}
  CORBA::ULong def_hop_count() { return trader->defHopCount();}
  CORBA::ULong max_hop_count() { return trader->maxHopCount();}
  CosTrading::FollowOption def_follow_policy() { return trader->defLinkFollowPolicy();}
  CosTrading::FollowOption max_follow_policy() { return trader->maxLinkFollowPolicy();}
private:
  Trader *trader;
};

#endif
