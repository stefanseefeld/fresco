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

#ifndef _ServerContextManagerImpl_hh
#define _ServerContextManagerImpl_hh

// the ServerContextManager just hands out new ServerContexts to
// people who are connecting.  it might want to do some checking on
// the incoming ClientContext's credentials, but at the moment it doesn't.

#include "Warsaw/config.hh"
#include "Warsaw/ServerContext.hh"
#include "Warsaw/Graphic.hh"
#include "Berlin/FactoryFinderImpl.hh"
#include "Berlin/GenericFactoryImpl.hh"
#include "Berlin/Thread.hh"

class ServerContextManagerImpl : implements(ServerContextManager) {

public:  
  ServerContextManagerImpl(GenericFactoryImpl *factory, Stage_ptr g);
  bool verify();

  // declared in IDL
  ServerContext_ptr newServerContext(ClientContext_ptr c) throw (SecurityException);

protected:
  FactoryFinderImpl *myFactoryFinder;
  Mutex myMutex;
  vector<ServerContext_var> allocatedServerContexts;
  Stage_var mySceneRoot;

};

#endif
