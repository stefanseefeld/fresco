/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
 * http://www.berlin-consortium.org
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
 * MA 02139, USA.
 */
#ifndef _Dispatcher_h
#define _Dispatcher_h

#include <Prague/Sys/Time.h>
#include <Prague/Sys/FdSet.h>
#include <Prague/Async/Agent.h>
#include <string>
#include <vector>
#include <map>

namespace Prague
{

class Timer;

class Dispatcher
{
  typedef vector<Agent *> List;
  typedef vector<Agent *> ChannelList;
  typedef vector<pair<Agent *, Agent::iomask> > TmpList;
  typedef map<int, Agent *> Dictionary;
  class TimerQueue;
public:
  static Dispatcher *Instance();
  void start();
  void stop();
  void step();
  void bind(Agent *);
  void release(Agent *);
  Agent *search(int pid);
  bool wait();
  void addTimeout(Timer *, const Time &);
  void removeTimeout(const Timer *);
private:
  AsyncManager();
  virtual ~Dispatcher();
  void sigChild(const int &);
  void sigKill(const int &);
  void dispatchStreams(Agent::iomask, Agent *);
  void dispatchTimeouts();
  static Dispatcher *instance;
  FdSet         rfds;
  FdSet         wfds;
  FdSet         xfds;
  List          agents;
  Dictionary    rchannel;
  Dictionary    wchannel;
  Dictionary    echannel;
  TimerQueue   *timers;
  Action<int>  *killhandler;
  Action<int>  *childhandler;
  bool          running;
};

};

#endif /* _Dispatcher_h */

