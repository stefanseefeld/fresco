//
// $Id$
//
// This source file is a part of the Berlin Project.
// Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
// Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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
#include "Prague/Sys/DLL.hh"
#include "Prague/Sys/Directory.hh"

class Plugin : private DLL
{
public:
  Plugin(const string &name) : DLL(name), id(0), loader(0)
    {
      char *(*getName)() = (char *(*)()) resolve("getName");
      if (!getName)
	{
	  Logger::log(Logger::loader) << "Plugin " << DLL::name() << " failed to load (reason: " << DLL::error() << ')' << endl;
	  return;
	}
      id = getName();
      loader = (CloneableImpl *(*)()) resolve("getPlugin");
    }
  ~Plugin() {}
  bool ok() { return loader != 0;}
  const char *name() { return id;}
  CloneableImpl *load() { return loader ? loader() : 0;}
private:
  const char *id;
  CloneableImpl *(*loader)();
};


GenericFactoryImpl::GenericFactoryImpl() {}
GenericFactoryImpl::~GenericFactoryImpl() { clear();}

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
      MutexGuard guard(mutex);
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
  throw (noSuchPluginException)
{
  map<CosLifeCycle::Key, Plugin *, keyComp>::iterator p = plugins.find(k);
  if (p == plugins.end())
    {
      // naughty boy, you should have called supports() first!
      throw noSuchPluginException();
    }
  else return (*p).second->load(); 
}


// you can call this is you're curious about creation support in the factory.
CORBA::Boolean  GenericFactoryImpl::supports ( const CosLifeCycle::Key & k )
{
  map<CosLifeCycle::Key, Plugin *, keyComp>::iterator p = plugins.find(k);

  if (p == plugins.end())
    {
      Logger::log(Logger::loader) << "GenericFactoryImpl::supports does not support " << ((string)(k[0].id)).c_str() << endl;    
      Logger::log(Logger::loader) << "GenericFactoryImpl::supports interface listing follows: " << endl;
      for(p = plugins.begin(); p != plugins.end(); p++)
	Logger::log(Logger::loader) << p->first[0].id << endl;
      return false;
    }
  else return true;
}


// init builds the table of function pointers from which we construct new objects.
// if you ever want to re-scan the directory for new plugins, well, we could use stat
// records or something, or you could just call init again. That would probably do OK.

void GenericFactoryImpl::scan(const char *name)
{
  MutexGuard guard(mutex);
  /*
   * load all files in <name> according to the regexp '\\.so'
   */
  Directory directory(name, Directory::alpha, "\\.so");
  Logger::log(Logger::loader) << "GenericFactoryImpl::init scanning plugin dir " << name << endl;
  for (Directory::iterator i = directory.begin(); i != directory.end(); i++)
    {
      Plugin *plugin = new Plugin((*i)->LongName());
      /*
       * if this is not a plugin, skip over it
       */
      if (!plugin->ok()) continue;
      CosLifeCycle::Key prototypeName;
      prototypeName.length(1);
      prototypeName[0].id   = (const char*) plugin->name();    // string copied
      prototypeName[0].kind = (const char*) "Object";          // string copied    
      
      map<CosLifeCycle::Key, Plugin *, keyComp>::iterator p = plugins.find(prototypeName);
      if (p != plugins.end())
	Logger::log(Logger::loader) << "GenericFactoryImpl::init warning: multiple definitions for plugin "
				    << plugin->name() << endl;
      
      // stash the function pointer for loading new object in the future
      plugins[prototypeName] = plugin;
      Logger::log(Logger::loader) << "GenericFactoryImpl::init loaded plugin " << plugin->name() << endl;
    }
}

void GenericFactoryImpl::clear()
{
  MutexGuard guard(mutex);
  for (plist_t::iterator i = plugins.begin(); i != plugins.end(); i++) delete (*i).second;
  plugins.erase(plugins.begin(), plugins.end());
}

bool keyComp::operator()(const CosLifeCycle::Key &a, const CosLifeCycle::Key &b) {
  // Blast C-style strings! see pg 468 of Stroustrup 3rd ed.
  return( strcmp(a[0].id, b[0].id) < 0);
};
