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
#include "TraderComponentsImpl.hh"

using namespace Prague;
using namespace CosTrading;

TraderComponentsImpl::TraderComponentsImpl() {}
Lookup_ptr TraderComponentsImpl::lookup_if() { MutexGuard guard(mutex); return Lookup::_duplicate(lookup);}
Register_ptr TraderComponentsImpl::register_if() { MutexGuard guard(mutex); return Register::_duplicate(register_);}
Link_ptr TraderComponentsImpl::link_if() { MutexGuard guard(mutex); return Link::_duplicate(link);}
Proxy_ptr TraderComponentsImpl::proxy_if() { MutexGuard guard(mutex); return Proxy::_duplicate(proxy);}
Admin_ptr TraderComponentsImpl::admin_if() { MutexGuard guard(mutex); return Admin::_duplicate(admin);}

void TraderComponentsImpl::lookup_if(Lookup_ptr l) { MutexGuard guard(mutex); lookup = Lookup::_duplicate(l);}
void TraderComponentsImpl::register_if(Register_ptr r) { MutexGuard guard(mutex); register_ = Register::_duplicate(r);}
void TraderComponentsImpl::link_if(Link_ptr l) { MutexGuard guard(mutex); link = Link::_duplicate(l);}
void TraderComponentsImpl::proxy_if(Proxy_ptr p) { MutexGuard guard(mutex); proxy = Proxy::_duplicate(p);}
void TraderComponentsImpl::admin_if(Admin_ptr a) { MutexGuard guard(mutex); admin = Admin::_duplicate(a);}

