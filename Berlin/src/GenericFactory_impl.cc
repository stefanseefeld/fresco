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

// genericFactory is a dynamic linking facility conforming to the
// corba COS Lifecycle specification. It produces objects based on
// their interface names. It also handles assigning lifecycle info
// tags to the objects, so that they may migrate from one server to
// another.

#include "berlin/cos/GenericFactory_impl.hh"
#include "berlin/cloneable_impl.hh"
#include "sys/types.h"
#include "dirent.h"
#include "dlfcn.h"
#include "berlin/graphics/graphic_impl.hh"

#include <stdlib.h>   // getenv()
#include "berlin/debug.hh"


#define NUMDIRS 3

// LOUSY HACK! we should be getting this from somewhere other than env
#define PLUGINBASE "WARSAW"


GenericFactory_impl::GenericFactory_impl() {
  _rm = reactorManager::getManager();
}

// this is the method your average factory-finder is going to call from
// god knows where on the network. Its job it to make the object 
// which identifies itself by "key". If "criteria" contains an omniLifecycleObject, we 
// assume the new object is being made in preparation for a move, so we do
// a _set_lifecycle on the new object.


CORBA::Object_ptr 
GenericFactory_impl::create_object ( const CosLifeCycle::Key & k, 
				     const CosLifeCycle::Criteria & the_criteria) {  
  cloneable_impl *newCloneable = NULL;

  try {    
    _loader_mutex.lock();
    newCloneable = loadPlugin(k);  
    _loader_mutex.unlock();

  } catch (noSuchPluginException e) {
    _loader_mutex.unlock();
    throw CosLifeCycle::CannotMeetCriteria();
  }

  if (newCloneable == NULL) {
    debug::log((string)"!!WOAH THERE!! trying to work with a NULL pointer -->" + (string)k[0].id, debug::loader);    
  }

  
  CORBA::Object_var newObjectPtr;

  // see if we are doing a lifecycle migration here
  omniLifeCycleInfo_ptr li = extractLifeCycleFromCriteria(the_criteria);

  // no lifeCycleInfo detected
  if (CORBA::is_nil(li)) {

    debug::log((string)"not doing lifecycle copy -->" + (string)k[0].id, debug::loader);    
    newCloneable->_obj_is_ready(this->_boa());
    newObjectPtr = newCloneable->cloneable_impl::_this();
    
    if (CORBA::is_nil(newObjectPtr)) {
      debug::log((string)"!!WOAH THERE!! returning a nil reference from factory -->" + (string)k[0].id, debug::loader);    
    }

    // lifeCycleInfo was found!
  } else {

    debug::log((string)"doing lifecycle copy -->" + (string)k[0].id, debug::loader);    
    newCloneable->_set_lifecycle(li);
    newCloneable->_obj_is_ready(this->_boa());
    newObjectPtr = CORBA::Object::_duplicate(newCloneable);
  }
  
  newCloneable->registerWithMyManagers();
  startThread(CORBA::Object::_duplicate(newObjectPtr));
  return CORBA::Object::_duplicate(newObjectPtr);
}


// this is just a helper function to make the above code a little more readable
// perhaps someone who knows the Any interface a little better can advise me on whether
// this is the proper way to do it?
omniLifeCycleInfo_ptr
GenericFactory_impl::extractLifeCycleFromCriteria(
						  const CosLifeCycle::Criteria & criteria) {
  omniLifeCycleInfo_ptr li = omniLifeCycleInfo::_nil();
  for(int i = 0; i < criteria.length(); i++) {
    if (strcmp(criteria[i].name, "NP_omniLifeCycleInfo") == 0) {
      if(criteria[i].value >>= li) break;
    }
  }
  return li;
}


// this method does the dirty work of getting the new C++ object off the
// disk and connected to the BOA. It's not pretty, but that's all it does.

cloneable_impl *GenericFactory_impl::loadPlugin(const CosLifeCycle::Key &k) 
  throw (noSuchPluginException) {
  
  cloneable_impl *plugin = NULL;

  map<CosLifeCycle::Key, cloneable_impl *(*)(), keyComp>::iterator p = _pluginLoadingFunctionTable.find(k);
  
  if (p == _pluginLoadingFunctionTable.end()) {
    // naughty boy, you should have called supports() first!
    throw noSuchPluginException();
    
  } else {
    plugin = (*(p->second))(); 
    return plugin;
  }
}


// you can call this is you're curious about creation support in the factory.
CORBA::Boolean  GenericFactory_impl::supports ( const CosLifeCycle::Key & k ) {
  map<CosLifeCycle::Key, cloneable_impl *(*)(), keyComp>::iterator p = _pluginLoadingFunctionTable.find(k);

  if (p == _pluginLoadingFunctionTable.end()) {
    debug::log((string)"Sadly, we do not support" + (string)k[0].id, debug::loader);    
    debug::log((string)"Here's a list of what's on the menu at chez GenericFactory: ", debug::loader);    
    for(p = _pluginLoadingFunctionTable.begin(); p != _pluginLoadingFunctionTable.end(); p++) {
      debug::log((string)(p->first[0].id), debug::loader);    
    }
    return false;
  } else {
    return true;
  }

}


// init builds the table of function pointers from which we construct new objects.
// if you ever want to re-scan the directory for new plugins, well, we could use stat
// records or something, or you could just call init again. That would probably do OK.

void GenericFactory_impl::init() {

  _pluginLoadingFunctionTable.clear();
  _loader_mutex.lock();

  // !!FIXME!! this is probably unwise. It's just for now. yeah yeah.
  // Perhaps this can be a query to the registrar?
  char *dirNames[NUMDIRS] = {"messages", "commands", "widgets"};

  char *pluginBase;
  char pluginDir[256];
  char pluginName[256];
  
  pluginBase = getenv(PLUGINBASE);
  
  if ( pluginBase == NULL ) {
    
  } else {
    
    for (int i = 0; i < NUMDIRS; i++) {
      
      strcpy(pluginDir, pluginBase);
      // Bad hack! Need to ensure a seperating / - Jonas
      strcat(pluginDir, "/");
      strcat(pluginDir, dirNames[i]);

      DIR *dirHandle = opendir(pluginDir);
      char *error;
      
      if (dirHandle != NULL) {
	
	struct dirent *pluginEntry;
	debug::log((string)"Scanning plugin dir: " + (string)pluginDir, debug::loader);
	
	while((pluginEntry = readdir(dirHandle))) {
	  if (strstr(pluginEntry->d_name, ".so") != NULL) {
	    
	    strcpy(pluginName, pluginDir);
	    // Once again the infamous / - Jonas
	    strcat(pluginName, "/");
	    strcat(pluginName, pluginEntry->d_name);
	    
	    // now we actually map the file into our address space
	    void *handle = dlopen (pluginName, RTLD_NOW);
	    	    
	    if (!handle) {
	      debug::log((string)"Failed to load: " + (string)pluginName, debug::loader);
	      debug::log((string)"Reason: " + (string)dlerror(), debug::loader);
	      continue;
	    }
	    
	    // ask it if it's a plugin, or just some random .so...
	    char *(*nameGetter)();
	    nameGetter = (char *(*)())dlsym(handle, "getName");
	    
	    // check for erorrs in symbol lookup
	    error = dlerror();
	    if (error != NULL)  {
	      debug::log((string)"can't locate symbol in plugin: " + (string)error, debug::loader);
	      continue;
	    }
	    
	    // ask it what plugin it provides
	    char *nameInFile = (*nameGetter)();
	    CosLifeCycle::Key prototypeName;
	    prototypeName.length(1);
	    prototypeName[0].id   = (const char*) nameInFile;    // string copied
	    prototypeName[0].kind = (const char*) "Object"; // string copied    

	    map<CosLifeCycle::Key, cloneable_impl *(*)(), keyComp>::iterator p = 
	      _pluginLoadingFunctionTable.find(prototypeName);

	    if (p != _pluginLoadingFunctionTable.end())
	      debug::log((string)"Warning: multiple definitions for plugin" + (string)nameInFile, debug::loader);

	    // believe it or not, this is a "standard C" variable declaration
	    cloneable_impl *(*pluginGetter)();

	    // and this monster here is a cast of a pointer returned by dlsym. 
	    pluginGetter = (cloneable_impl *(*)())dlsym(handle, "getPlugin");
	    
	    // if all is well and good, we have a function pointer we can call to get the plugin
	    char *error = dlerror();
	    if (error != NULL)  {
	      debug::log((string)"Failed to load plugin function: " + ((string)nameInFile), debug::loader);
	      debug::log((string)"Reason: " + (string)error, debug::loader);
	    }
	    	    
	    // stash the function pointer for loading new object in the future
	    _pluginLoadingFunctionTable[prototypeName] = pluginGetter;
	    debug::log((string)"Plugin: " + (string)nameInFile, debug::loader);		       
	  }
	}
      }
      closedir(dirHandle);
    }
  }
  _loader_mutex.unlock();
}


// this is just a helper which tries to activate the threads on objects which happen
// to be subclasses of threads. If they aren't, oh well, life's like that.
void GenericFactory_impl::startThread(CORBA::Object_ptr o) {
  reactor_var r = reactor::_narrow(o);
  if (CORBA::is_nil(r)) {
    return; // no sweat, it's not a reactor!
  }

  try {
    reactor_impl *impl = _rm->getReactor(r);
    debug::log((string)"Starting Reactor", debug::loader);
    impl->start();
  } catch (noSuchReactorException &nsre) {
    // this reactor is not present in our registry. How odd!
    debug::log((string)"tried to start non-local reactor!", debug::loader);
  }
}  


bool keyComp::operator()(const CosLifeCycle::Key &a, const CosLifeCycle::Key &b) {
  // Blast C-style strings! see pg 468 of Stroustrup 3rd ed.
  return( strcmp(a[0].id, b[0].id) < 0);
};
