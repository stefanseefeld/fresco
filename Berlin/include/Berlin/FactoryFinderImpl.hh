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

// factoryFinder is an implementation of one part of the COS interface. 
// this one is dead simple. It always finds the same factory -- the one
// you need to initialize it with using the first call to getInstance. Because
// it is so simple, it's a singleton, there's no need to ever make more than 
// one of these things. 

#ifndef _FactoryFinderImpl_hh
#define _FactoryFinderImpl_hh

#include <Warsaw/config.hh>
#include <Warsaw/Cloneable.hh>
#include <Berlin/GenericFactoryImpl.hh>
#include <Berlin/Thread.hh>

class unInitializedGenericFactoryException {};
class FactoryFinderImpl;

class FactoryFinderImpl : implementsscoped(CosLifeCycle,FactoryFinder) {
  
public:

  static FactoryFinderImpl * getInstance(GenericFactoryImpl * theFactory);
  static FactoryFinderImpl * getInstance() throw (unInitializedGenericFactoryException);

  // declared in IDL
  CosLifeCycle::Factories *find_factories(const CosLifeCycle::Key & factory_key );

protected:

  CosLifeCycle::Factories *myFactories;
  FactoryFinderImpl(CosLifeCycle::GenericFactory_ptr theFactory);

private:
  static FactoryFinderImpl *_instance;
  static Mutex _instance_mutex;

  // never call this! It does not exist! I am hiding it from you!
  FactoryFinderImpl();
};

#endif
