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

#include "Berlin/GenericFactoryImpl.hh"
#include "Berlin/CloneableImpl.hh"
#include "Berlin/Logger.hh"
#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>

#include <stdlib.h>   // getenv()


#define NUMDIRS 3

// LOUSY HACK! we should be getting this from somewhere other than env
#define PLUGINBASE "WARSAW"


GenericFactoryImpl::GenericFactoryImpl() {
//   _rm = ReactorManager::getManager();
}

// this is the method your average factory-finder is going to call from
// god knows where on the network. Its job it to make the object 
// which identifies itself by "key". If "criteria" contains an omniLifecycleObject, we 
// assume the new object is being made in preparation for a move, so we do
// a _set_lifecycle on the new object.


CORBA::Object_ptr 
GenericFactoryImpl::create_object ( const CosLifeCycle::Key & k, 
				    const CosLifeCycle::Criteria & the_criteria) {  
  CloneableImpl *newCloneable = 0;

  try
    {    
      MutexGuard guard(_loader_mutex);
      newCloneable = loadPlugin(k);  
    }
  catch (noSuchPluginException e)
    {
      throw CosLifeCycle::CannotMeetCriteria();
    }

  if (!newCloneable)
    {
      Logger::log(Logger::loader) << "GenericFactoryImpl::create_object loaded NULL pointer in response to "
				  << ((string)(k[0].id)).c_str() << endl;
    }

  
  CORBA::Object_var newObjectPtr;

  // see if we are doing a lifecycle migration here
  omniLifeCycleInfo_ptr li = extractLifeCycleFromCriteria(the_criteria);

  // no lifeCycleInfo detected
  if (CORBA::is_nil(li))
    {
      Logger::log(Logger::loader) << "GenericFactoryImpl::create_object not doing lifecycle copy for "
				  << ((string)(k[0].id)).c_str() << endl;    
      newCloneable->_obj_is_ready(this->_boa());
      newObjectPtr = newCloneable->CloneableImpl::_this();
    
      if (CORBA::is_nil(newObjectPtr))
	{
	  Logger::log(Logger::loader) << "GenericFactoryImpl::create_object returning a nil reference for "
				      << ((string)(k[0].id)).c_str() << endl;    
	}

      // lifeCycleInfo was found!
    }
  else 
    {
      Logger::log(Logger::loader) << "GenericFactoryImpl::create_object doing lifecycle copy for "
				  << ((string)(k[0].id)).c_str() << endl;    
      newCloneable->_set_lifecycle(li);
      newCloneable->_obj_is_ready(this->_boa());
      newObjectPtr = CORBA::Object::_duplicate(newCloneable);
    }
  
  //    newCloneable->registerWithMyManagers();
  //    startThread(CORBA::Object::_duplicate(newObjectPtr));
  return CORBA::Object::_duplicate(newObjectPtr);
}


// this is just a helper function to make the above code a little more readable
// perhaps someone who knows the Any interface a little better can advise me on whether
// this is the proper way to do it?
omniLifeCycleInfo_ptr
GenericFactoryImpl::extractLifeCycleFromCriteria(const CosLifeCycle::Criteria & criteria) {
  omniLifeCycleInfo_ptr li = omniLifeCycleInfo::_nil();
  for(unsigned int i = 0; i < criteria.length(); i++) {
    if (strcmp(criteria[i].name, "NP_omniLifeCycleInfo") == 0) {
      if(criteria[i].value >>= li) break;
    }
  }
  return li;
}


// this method does the dirty work of getting the new C++ object off the
// disk and connected to the BOA. It's not pretty, but that's all it does.

CloneableImpl *GenericFactoryImpl::loadPlugin(const CosLifeCycle::Key &k) 
  throw (noSuchPluginException) {
  
  CloneableImpl *plugin = NULL;

  map<CosLifeCycle::Key, CloneableImpl *(*)(), keyComp>::iterator p = _pluginLoadingFunctionTable.find(k);
  
  if (p == _pluginLoadingFunctionTable.end()) {
    // naughty boy, you should have called supports() first!
    throw noSuchPluginException();
    
  } else {
    plugin = (*(p->second))(); 
    return plugin;
  }
}


// you can call this is you're curious about creation support in the factory.
CORBA::Boolean  GenericFactoryImpl::supports ( const CosLifeCycle::Key & k ) {
  map<CosLifeCycle::Key, CloneableImpl *(*)(), keyComp>::iterator p = _pluginLoadingFunctionTable.find(k);

  if (p == _pluginLoadingFunctionTable.end())
    {
      Logger::log(Logger::loader) << "GenericFactoryImpl::supports does not support " << ((string)(k[0].id)).c_str() << endl;    
      Logger::log(Logger::loader) << "GenericFactoryImpl::supports interface listing follows: " << endl;
      for(p = _pluginLoadingFunctionTable.begin(); p != _pluginLoadingFunctionTable.end(); p++)
	Logger::log(Logger::loader) << p->first[0].id << endl;
      return false;
    }
  else return true;
}


// init builds the table of function pointers from which we construct new objects.
// if you ever want to re-scan the directory for new plugins, well, we could use stat
// records or something, or you could just call init again. That would probably do OK.

void GenericFactoryImpl::init()
{
  _pluginLoadingFunctionTable.clear();
  MutexGuard guard(_loader_mutex);
  char *pluginDir;
  char pluginName[256];
  
  pluginDir = getenv(PLUGINBASE);
  
  if (!pluginDir)  {}
  else
    {  
      DIR *dirHandle = opendir(pluginDir);
      char *error;
      
      if (dirHandle)
	{
	  struct dirent *pluginEntry;
	  Logger::log(Logger::loader) << "GenericFactoryImpl::init scanning plugin dir " << pluginDir << endl;
	
	  while((pluginEntry = readdir(dirHandle)))
	    {
	      if (strstr(pluginEntry->d_name, ".so") != 0)
		{
		  strcpy(pluginName, pluginDir);
		  // Once again the infamous / - Jonas
		  strcat(pluginName, "/");
		  strcat(pluginName, pluginEntry->d_name);
	    
		  // now we actually map the file into our address space
		  void *handle = dlopen (pluginName, RTLD_NOW);
		  if (!handle)
		    {
		      Logger::log(Logger::loader) << "GenericFactoryImpl::init failed to load "
						  << pluginName << " (reason: " << dlerror() << ')' << endl;
		      continue;
		    }
	    
		  // ask it if it's a plugin, or just some random .so...
		  char *(*nameGetter)();
		  nameGetter = (char *(*)())dlsym(handle, "getName");
	    
		  // check for erorrs in symbol lookup
		  error = dlerror();
		  if (error != 0)
		    {
		      Logger::log(Logger::loader) << "GenericFactoryImpl::init can't locate symbol in plugin: " << error << endl;
		      continue;
		    }
	    
		  // ask it what plugin it provides
		  char *nameInFile = (*nameGetter)();
		  CosLifeCycle::Key prototypeName;
		  prototypeName.length(1);
		  prototypeName[0].id   = (const char*) nameInFile;    // string copied
		  prototypeName[0].kind = (const char*) "Object"; // string copied    
	    
		  map<CosLifeCycle::Key, CloneableImpl *(*)(), keyComp>::iterator p = 
		    _pluginLoadingFunctionTable.find(prototypeName);
	    
		  if (p != _pluginLoadingFunctionTable.end())
		    Logger::log(Logger::loader) << "GenericFactoryImpl::init warning: multiple definitions for plugin "
						<< nameInFile << endl;
	    
		  // believe it or not, this is a "standard C" variable declaration
		  CloneableImpl *(*pluginGetter)();
	    
		  // and this monster here is a cast of a pointer returned by dlsym. 
		  pluginGetter = (CloneableImpl *(*)())dlsym(handle, "getPlugin");
	    
		  // if all is well and good, we have a function pointer we can call to get the plugin
		  char *error = dlerror();
		  if (error != 0)
		    Logger::log(Logger::loader) << "GenericFactoryImpl::init failed to load plugin function: "
						<< nameInFile << " (reason: " << error << ')' << endl;
		  // stash the function pointer for loading new object in the future
		  _pluginLoadingFunctionTable[prototypeName] = pluginGetter;
		  Logger::log(Logger::loader) << "GenericFactoryImpl::init loaded plugin " << nameInFile << endl;		       
		}
	    }
	}
      closedir(dirHandle);
    }
}

bool keyComp::operator()(const CosLifeCycle::Key &a, const CosLifeCycle::Key &b) {
  // Blast C-style strings! see pg 468 of Stroustrup 3rd ed.
  return( strcmp(a[0].id, b[0].id) < 0);
};
