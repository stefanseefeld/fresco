//
// $Id$
//
// This source file is a part of the Berlin Project.
// Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
// http://www.berlin-consortium.org
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public License
// as published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//

// this is the 1 object you *can* find through nameservice. since nameservice has
// no pretense of having security, we take over and handle security manually
// once you've found the sessionManager. It allocates sessions. It's pretty simple.


#include "Berlin/ServerContextManagerImpl.hh"
#include "Berlin/ServerContextImpl.hh"
#include "Berlin/Debug.hh"

ServerContextManagerImpl::ServerContextManagerImpl(GenericFactoryImpl *factory, Stage_ptr g) {
  myFactoryFinder = FactoryFinderImpl::getInstance(factory);
  mySceneRoot = Stage::_duplicate(g);
}

// this needs to be fleshed out :)
bool ServerContextManagerImpl::verify() {return true;};

// declared in IDL
ServerContext_ptr ServerContextManagerImpl::newServerContext(ClientContext_ptr c) 
throw (SecurityException) {
    myMutex.lock();
    ServerContextImpl *temp = new ServerContextImpl(myFactoryFinder->_this(), c, mySceneRoot);
    temp->_obj_is_ready(this->_boa());
    allocatedServerContexts.push_back(temp->_this());
    myMutex.unlock();
    return temp->_this();
}
  

