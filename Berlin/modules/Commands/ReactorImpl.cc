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

// Reactors are basically 2 different kinds of typesafe dispatch
// tables async ones have their own thread and message queue, sync
// ones do not.

#include "Command/ReactorImpl.hh"
#include <strstream>
#include <algorithm>

// this lets you toggle the run state of the Reactor.
void ReactorImpl::active(CORBA::Boolean r) {
    // we have to lock on something.. might as well use this
    map_mutex.lock();
    if (r) {
      if (amRunning) {
	// do nothing, already running
      } else {
	amRunning = true;
      }
    } else {
      if (amRunning) {
	amRunning = false;
      } else {
	// do nothing, already stopped
      }
    }
    map_mutex.unlock();
}

CORBA::Boolean ReactorImpl::active() {
  map_mutex.lock();
  CORBA::Boolean tmp = (CORBA::Boolean)amRunning;
  map_mutex.unlock();
  return tmp;
}



void ReactorImpl::accept(const message &m) {
  
  if (amRunning) {
    // store a method-local command vector to avoid deadlocking if a command
    // tries to modify react_map. this happens more than you'd think.
    vector<command_var> commands_to_execute;
    
    // select the commands which match this message
    map_mutex.lock();            
    commands_to_execute = react_map[m.payload.type()];
    map_mutex.unlock();      
    
    // execute each command, unbinding on exception
    typedef vector<command_var>::iterator CI; 
    for(CI i = commands_to_execute.begin(); i != commands_to_execute.end(); i++) {
      try {
	debug::log("running command for type " + (string)(m.payload.type()->id()), debug::reactor);
	(*i)->execute(m);
      } catch (...) {
	debug::log("command failed, unbinding for " + (string)(m.payload.type()->id()), debug::reactor);
	this->unbind(m.payload.type(), *i);
      }
    }
  }
}


// this lets you toggle the run state of the Reactor.
void AsyncReactorImpl::active(CORBA::Boolean r) {
  // we have to lock on something.. might as well use this
  queue_mutex.lock();
  if (r) {
    if (amRunning) {
      // do nothing, already running
    } else {
      this->start();
      amRunning = true;
    }
  } else {
    if (amRunning) {
      amRunning = false;
    } else {
      // do nothing, already stopped
    }
  }
  queue_mutex.unlock();
  queue_mutex.signal();
}

CORBA::Boolean AsyncReactorImpl::active() {
    queue_mutex.lock();
    CORBA::Boolean tmp = (CORBA::Boolean)amRunning;
    queue_mutex.unlock();
    return tmp;
}

// this just slots a message into the queue and wakes up the local thread.
void AsyncReactorImpl::accept(const message &m) {
    queue_mutex.lock();
    identifyAndLog("received message of type" + (string)(m.payload.type()->id()));
    react_queue.push(m);
    queue_mutex.unlock();
    queue_cond.signal();
}


void AsyncReactorImpl::run(void *arg) {
  while(true) { // thread lives in here.        
    identifyAndLog("sleeping on message queue");
    
    queue_cond.wait(); // this unlocks the queue atomically while it sleeps
    while(!react_queue.empty() && amRunning) { // when it wakes up, the queue is re-locked
      
      const message m = react_queue.top();
      CORBA::TypeCode_var ty = m.payload.type();
      identifyAndLog("processing a new message of type " + (string)(ty->id())); 
      react_queue.pop();      
      queue_mutex.unlock();
      
      this->ReactorImpl::accept(m);
    }
  }
}

// this is just a log-message helper
void AsyncReactorImpl::identifyAndLog(const char *c) {
    ostrstream ost;
    ost << "[asyncReactor " << this->id() << "] " << c;
    debug::log(ost.str(), debug::reactor);
}

// this is just a log-message helper
void AsyncReactorImpl::identifyAndLog(string &s) {
    ostrstream ost;
    ost << "[asyncReactor " << this->id() << "] " << s;
    debug::log(ost.str(), debug::reactor);
}


// this constructor is necessary to initialize the queue condition variable
// (which allows thread sleep/wakeup) with a reference to the queue mutex
// (which the cond variable manages locking/unlocking)
AsyncReactorImpl::AsyncReactorImpl() : queue_mutex(), queue_cond(&queue_mutex) {} 


// bind will not duplicate bindings. specifically, for 1 typecode
// and 1 command reference, a binding can be made at most once.

void ReactorImpl::bind(CORBA::TypeCode_ptr ty, command_ptr c) {  
  map_mutex.lock();
  debug::log("binding new command to type " + (string)(ty->id()), debug::reactor);
  CORBA::TypeCode_var newTy = ty;
  command_var com = c;
  vector<command_var>::iterator i = find(react_map[newTy].begin(), 
					 react_map[ty].end(), com); 
  if (i != react_map[ty].end()) {
    react_map[newTy].push_back(command::_duplicate(com));
  }
  map_mutex.unlock();
}


// this unbinds the 1 (and only) association between a typecode
// and a command_ptr in this reactor. it happens automatically
// when the command goes null and/or throws an exception

void ReactorImpl::unbind(CORBA::TypeCode_ptr ty, command_ptr c){
  map_mutex.lock();
  command_var cmd = c;
  debug::log("unbinding command from type " + (string)(ty->id()), debug::reactor);
  std::remove(react_map[ty].begin(), react_map[ty].end(), cmd);
  // remove the vector altogether if it's empty. 
  typedef map< CORBA::TypeCode_var, vector<command_var> >::iterator MI;      
  MI i = react_map.find(ty);
  if (i->second.begin() == i->second.end()) {
    react_map.erase(i);
  }
  map_mutex.unlock();
}  


void ReactorImpl::copy_react_map_to(reactor_ptr r) {
  map_mutex.lock();
  typedef map< CORBA::TypeCode_var, vector<command_var> >::iterator MI;      
  typedef vector<command_var>::iterator VI;
  for(MI i = react_map.begin(); i != react_map.end(); i++) {
    for(VI j = i->second.begin(); j != i->second.end(); j++) { 
      r->bind(CORBA::TypeCode::_duplicate(i->first), command::_duplicate(*j));  
    }
  }
  map_mutex.unlock();
}

