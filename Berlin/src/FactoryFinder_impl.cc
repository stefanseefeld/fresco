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
#include "berlin/cos/FactoryFinder_impl.hh"
#include "berlin/debug.hh"

// this is the simplest factoryFinder I could think of. It's just a
// placeholder for the time being until we come up with a better
// factory naming scheme built on hostnames or something.

CosLifeCycle::Factories * FactoryFinder_impl::find_factories ( const CosLifeCycle::Key & factory_key ) {
  CosLifeCycle::GenericFactory_var fact = CosLifeCycle::GenericFactory::_narrow((*myFactories)[0]);
  if ((!CORBA::is_nil(fact)) && (fact->supports(factory_key))) {
    return myFactories;
  } else {
    throw CosLifeCycle::NoFactory();
  }
}


FactoryFinder_impl::FactoryFinder_impl(CosLifeCycle::GenericFactory_ptr theFactory) {  
  myFactories = new CosLifeCycle::Factories();  
  myFactories->length(1);
  (*myFactories)[0] = CosLifeCycle::GenericFactory::_duplicate(theFactory);
}

//These two global variables are for storing the
//static member data in FactoryFinder_impl...
omni_mutex FactoryFinder_impl::_instance_mutex;
FactoryFinder_impl *FactoryFinder_impl::_instance;

// this takes care of singleton work.
FactoryFinder_impl *FactoryFinder_impl::getInstance(GenericFactory_impl *theFactory) {
  _instance_mutex.lock();
  FactoryFinder_impl *i;
  if (_instance == NULL) {
    _instance = new FactoryFinder_impl(theFactory->_this());
    _instance->_obj_is_ready(theFactory->_boa());
  } 
  i = _instance;
  _instance_mutex.unlock();
  return i;
}

// this is the dreaded singleton-which-might-explode method.
FactoryFinder_impl *FactoryFinder_impl::getInstance() throw (unInitializedGenericFactoryException) {
  _instance_mutex.lock();
  FactoryFinder_impl *i;
  if (_instance == NULL) {
    _instance_mutex.unlock();
    throw unInitializedGenericFactoryException();
  } else {
    i = _instance;
    _instance_mutex.unlock();
    return i;
  }
}


// never call this ctor. You're asking for trouble. None of the operations will work.
// that's why it's private for chrissake!
FactoryFinder_impl::FactoryFinder_impl() {}


