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
#ifndef _TraderComponentsImpl_hh
#define _TraderComponentsImpl_hh

#include <CosTrading.hh>
#include <Prague/Sys/Thread.hh>

class TraderComponentsImpl : virtual public CosTrading::_sk_TraderComponents
{
public:
  TraderComponentsImpl();
  CosTrading::Lookup_ptr lookup_if();
  CosTrading::Register_ptr register_if();
  CosTrading::Link_ptr link_if();
  CosTrading::Proxy_ptr proxy_if();
  CosTrading::Admin_ptr admin_if();

  void lookup_if (CosTrading::Lookup_ptr);
  void register_if (CosTrading::Register_ptr);
  void link_if (CosTrading::Link_ptr);
  void proxy_if (CosTrading::Proxy_ptr);
  void admin_if (CosTrading::Admin_ptr);
private:
  Prague::Mutex mutex;
  CosTrading::Lookup_var lookup;
  CosTrading::Register_var register_;
  CosTrading::Link_var link;
  CosTrading::Proxy_var proxy;
  CosTrading::Admin_var admin;
};

#endif
