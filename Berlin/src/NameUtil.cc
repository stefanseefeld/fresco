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

// this file is a bunch of little utilities for helping with name service, which 
// is so baroque and ugly it mucks up readability if you include code
// inplace to handle it.

#include <Warsaw/config.hh>
#include <Berlin/NameUtil.hh>
#include <Berlin/Debug.hh>

static CosNaming::NamingContext_var rootContext;
static omni_mutex rootContext_mutex;

// this verifies that we have a root context reference. there's really
// no point in trying to catch these. If you have no name service,
// you're sunk.
static void getRootContext(CORBA::ORB_ptr orb) {
  try{
    
    if (CORBA::is_nil(rootContext)) {  
      debug::log("Looking up Root Nameservice", debug::name);
      CORBA::Object_var initServ = orb->resolve_initial_references("NameService");
      rootContext = CosNaming::NamingContext::_narrow(initServ);    
      
      if (CORBA::is_nil(rootContext)) {
	debug::log("Root name context is nil!", debug::name);
	throw CORBA::ORB::InvalidName();
      }
    }
  }  catch(CosNaming::NamingContext::NotFound& ex) {
    debug::log("Root Name Context not found.", debug::name);
    throw ex;
  } catch (CORBA::COMM_FAILURE& ex) { 
    debug::log("had a COMM_FAILURE during root name service lookup", debug::name);
    throw ex;
  } catch (...) { 
    debug::log("unknown exception during root name service lookup", debug::name);
    throw CosNaming::NamingContext::NotFound();
  }
}


const CosNaming::Name charPtrToName(char *ch) {
  CosNaming::Name objectName;
  objectName.length(1);
  objectName[0].id   = (const char*) ch; 
  objectName[0].kind = (const char*) "Object"; 
  return objectName;
}


void bindObjectToName(CORBA::ORB_ptr orb, CORBA::Object_ptr obj, char *ch) {
  rootContext_mutex.lock();
  getRootContext(orb);
  CosNaming::Name ourName = charPtrToName(ch);  
  rootContext->rebind(ourName, obj);
  rootContext_mutex.unlock();
}


CORBA::Object_ptr lookup(CORBA::ORB_ptr orb, char *ch) 
  throw (lookupFailureException) {

  CORBA::Object_var tmpobj;

  rootContext_mutex.lock();
  getRootContext(orb);
  rootContext_mutex.unlock();

  CosNaming::Name ourName = charPtrToName(ch);  

  try {
    tmpobj = rootContext->resolve(ourName);            
  }  
  catch (CORBA::COMM_FAILURE& ex) {
    debug::log("unable to contact name service for factory lookup", debug::name);
    throw lookupFailureException();
  }
  catch (...) {
    debug::log("Caught a system exception while using the naming service.", debug::name);
    throw lookupFailureException();
  }      
  return CORBA::Object::_duplicate(tmpobj);
}

