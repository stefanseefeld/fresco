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

// what used to be the "plugin loader" is now, in line with corba lifecycle service,
// an implementation of GenericFactory. The idea with this factory is that it looks
// up objects in dynamically loadable modules, on the disk, and tries to find one which
// claims to be the correct key

#ifndef __GENERICFACTORY_IMPL__
#define __GENERICFACTORY_IMPL__

#include <Warsaw/config.hh>
#include <Warsaw/LifeCycle.hh>
#include <Berlin/CloneableImpl.hh>
#include <Berlin/ServerContextImpl.hh>
#include <Berlin/ClientContextImpl.hh>
#include <Berlin/Thread.hh>
#include <string>
#include <map>

class noSuchProtoException {};
class noSuchPluginException {};
class SeverContextImpl;

// this is a comparator for our lookup table
class keyComp {
public:
  bool operator()(const CosLifeCycle::Key &a, const CosLifeCycle::Key &b);

};

class GenericFactoryImpl : implementsscoped(CosLifeCycle,GenericFactory) {
  
public:
  
  GenericFactoryImpl();
  
  // stuff declared in IDL
  virtual CORBA::Boolean  supports ( const CosLifeCycle::Key & k );
  virtual CORBA::Object_ptr create_object 
  ( const CosLifeCycle::Key & k, const CosLifeCycle::Criteria & the_criteria );
  
  // this builds the function pointer table
  void init();
  
protected:
  
  // this is a simple helper function to make it easier to find the
  // LifeCycyleInfo object in criteria
  omniLifeCycleInfo_ptr extractLifeCycleFromCriteria(const CosLifeCycle::Criteria &criteria);
  
  // this does the call into the function pointer
  CloneableImpl *loadPlugin(const CosLifeCycle::Key &k) 
    throw (noSuchPluginException);
  
  // lock the whole thing during a load.
  Mutex _loader_mutex;  
  
  // this stores the function pointers loaded through libdl
  map<CosLifeCycle::Key, CloneableImpl *(*)(), keyComp> _pluginLoadingFunctionTable;
  
  // this is responsible for trying to start new threads.
  //   void startThread(CORBA::Object_ptr o);
  //   reactorManager *_rm;
};



#endif
