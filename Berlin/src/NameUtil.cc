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

#include "Warsaw/config.hh"
#include "Berlin/NameUtil.hh"
#include "Berlin/Debug.hh"

static CosNaming::NamingContext_var rootContext;
static Mutex rootContext_mutex;

// this verifies that we have a root context reference. there's really
// no point in trying to catch these. If you have no name service,
// you're sunk.
static void getRootContext(CORBA::ORB_ptr orb) {
  try {
    if (CORBA::is_nil(rootContext)) {  
	Debug::log(Debug::corba, "getRootContext: looking up root corba name context");
	CORBA::Object_var initServ;
	initServ = orb->resolve_initial_references("NameService");
	rootContext = CosNaming::NamingContext::_narrow(initServ);
    }
  } catch(CORBA::ORB::InvalidName& ex) {
      Debug::log(Debug::corba, "getRootContext: Service required is invalid [does not exist].");
      throw ex;
  } catch(CosNaming::NamingContext::NotFound& ex) {
      Debug::log(Debug::corba, "getRootContext: Root Name Context not found.");
    throw ex;
  } catch (CORBA::COMM_FAILURE& ex) { 
      Debug::log(Debug::corba, "getRootContext: had a COMM_FAILURE during root name service lookup");
      throw ex;
  } catch (...) { 
      Debug::log(Debug::corba, "getRootContext: unknown exception during root name service lookup");
      throw CosNaming::NamingContext::NotFound();
  }
  
  // can't throw an exception if you are in a try {} block :)
  if (CORBA::is_nil(rootContext)) {
      Debug::log(Debug::corba, "getRootContext: root name context is nil");
    throw CORBA::ORB::InvalidName();
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
  MutexGuard guard(rootContext_mutex);
  getRootContext(orb);
  CosNaming::Name ourName = charPtrToName(ch);  
  rootContext->rebind(ourName, obj);
}


CORBA::Object_ptr lookup(CORBA::ORB_ptr orb, char *ch) 
  throw (lookupFailureException) {

  CORBA::Object_var tmpobj;

  {
    MutexGuard guard(rootContext_mutex);
    getRootContext(orb);
  }
  CosNaming::Name ourName = charPtrToName(ch);  

  try {
    tmpobj = rootContext->resolve(ourName);            
  }  
  catch (CORBA::COMM_FAILURE& ex) {
    Debug::log(Debug::corba, "unable to contact name service for factory lookup");
    throw lookupFailureException();
  }
  catch (...) {
    Debug::log(Debug::corba, "Caught a system exception while using the naming service.");
    throw lookupFailureException();
  }      
  return CORBA::Object::_duplicate(tmpobj);
}

