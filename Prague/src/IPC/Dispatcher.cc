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

#include "Prague/Sys/Signal.hh"
#include "Prague/IPC/Dispatcher.hh"
#include <queue>
#include <algorithm>
#include <ctime>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>

using namespace Prague;

Dispatcher *Dispatcher::dispatcher = 0;
Dispatcher::Cleaner Dispatcher::cleaner;
Mutex Dispatcher::singletonMutex;

struct SignalNotifier : Signal::Notifier
{
  virtual void notify(int signum)
  {
    cerr << Signal::name(signum) << endl;
    exit(1);
  }
};

void Dispatcher::Handler::process()
{
  switch (mask)
    {
    case Agent::inready:  agent->processInput(); break;
    case Agent::outready: agent->processOutput(); break;
    case Agent::errready: agent->processError(); break;
    case Agent::inexc:    agent->processInputException(); break;
    case Agent::outexc:   agent->processOutputException(); break;
    case Agent::errexc:   agent->processErrorException(); break;
    default: break;
    }
};

Dispatcher::Cleaner::~Cleaner() { delete Dispatcher::dispatcher;}

Dispatcher *Dispatcher::instance()
{
  MutexGuard guard(singletonMutex);
  if (!dispatcher) dispatcher = new Dispatcher;
  return dispatcher;
}

Dispatcher::Dispatcher()
  //. create a queue of up to 64 tasks 
  //. and a thread pool with 16 threads
  : notifier(new SignalNotifier),
    tasks(64),
    workers(tasks, acceptor, 16),
    server(&Dispatcher::dispatch, this)
{
  Signal::mask(Signal::pipe);
  Signal::set(Signal::hangup, notifier);
  Signal::set(Signal::interrupt, notifier);
  Signal::set(Signal::quit, notifier);
  Signal::set(Signal::illegal, notifier);
  Signal::set(Signal::abort, notifier);
  Signal::set(Signal::fpe, notifier);
  Signal::set(Signal::bus, notifier);
  //  Signal::set(Signal::segv, notifier);
  Signal::set(Signal::iotrap, notifier);
  Signal::set(Signal::terminate, notifier);
}

Dispatcher::~Dispatcher()
{
//   for (alist_t::iterator i = agents.begin(); i != agents.end(); i++) (*i)->kill();
}

void Dispatcher::bind(int fd, Agent *agent, Agent::iomask_t mask)
{
  if (server.state() != Thread::running) server.start();
  Signal::Guard sguard(Signal::child);
  MutexGuard guard(mutex);
  if (find(agents.begin(), agents.end(), agent) == agents.end())
    agents.push_back(agent);
  if (mask & Agent::in)
    {
      if (mask & Agent::inready) wfds.set(fd);
      if (mask & Agent::inexc) xfds.set(fd);
      if (wchannel.find(fd) == wchannel.end()) wchannel[fd] = agent;
      else { cerr << "Dispatcher::bind() : Error : file descriptor already in use" << endl; return;}
    }
  if (mask & Agent::out)
    {
      if (mask & Agent::outready) rfds.set(fd);
      if (mask & Agent::outexc) xfds.set(fd);
      if (rchannel.find(fd) == rchannel.end()) rchannel[fd] = agent;
      else { cerr << "Dispatcher::bind() : Error : file descriptor already in use" << endl; return;}
    }
  if (mask & Agent::err)
    {
      if (mask & Agent::errready) rfds.set(fd);
      if (mask & Agent::errexc) xfds.set(fd);
      if (echannel.find(fd) == echannel.end()) echannel[fd] = agent;
      else { cerr << "Dispatcher::bind() : Error : file descriptor already in use" << endl; return;}
    }
}

void Dispatcher::release(int fd)
{
  MutexGuard guard(mutex);
  dictionary_t::iterator c;
  if ((c = rchannel.find(fd)) != rchannel.end())
    {
      rchannel.erase(c);
      rfds.clear(fd);
      xfds.clear(fd);
    }
  else if ((c = wchannel.find(fd)) != wchannel.end())
    {
      wchannel.erase(c);
      wfds.clear(fd);
      xfds.clear(fd);
    }
  else if ((c = echannel.find(fd)) != echannel.end())
    {
      echannel.erase(c);
      rfds.clear(fd);
      xfds.clear(fd);
    }
}

void Dispatcher::release(Agent *agent)
{
  Signal::Guard guard(Signal::child);
  alist_t::iterator i = find(agents.begin(), agents.end(), agent);
  if (i != agents.end()) agents.erase(i);
}

void *Dispatcher::dispatch(void *X)
{
  Dispatcher *dispatcher = reinterpret_cast<Dispatcher *>(X);
  dispatcher->workers.start();
  do dispatcher->wait();
  while (true);
  return 0;
};

void Dispatcher::wait()
{
  FdSet tmprfds = rfds;
  FdSet tmpwfds = wfds;
  FdSet tmpxfds = xfds;
  unsigned int fdsize = max(max(tmprfds.max(), tmpwfds.max()), tmpxfds.max()) + 1;
  int nsel = select(fdsize, tmprfds, tmpwfds, tmpxfds, 0);
  if (nsel == -1)
    {
      if (errno == EINTR || errno == EAGAIN) errno = 0;
      /*
       * signal or being canceled...
       */
    }
  else if (nsel > 0 && fdsize)
    {
      tlist_t t;
      for (dictionary_t::iterator i = rchannel.begin(); i != rchannel.end(); i++)
	{
	  if (tmprfds.isset((*i).first))
	    {
	      (*i).second->ibuf()->underflow();
	      t.push_back(task((*i).second, Agent::outready));
	    }
	  if (tmpxfds.isset((*i).first)) t.push_back(task((*i).second, Agent::outexc));
	}
      for (dictionary_t::iterator i = wchannel.begin(); i != wchannel.end(); i++)
	{
	  if (tmpwfds.isset((*i).first)) t.push_back(task((*i).second, Agent::inready));
	  if (tmpxfds.isset((*i).first)) t.push_back(task((*i).second, Agent::inexc));
	}
      for (dictionary_t::iterator i = echannel.begin(); i != echannel.end(); i++)
	{
	  if (tmprfds.isset((*i).first)) t.push_back(task((*i).second, Agent::errready));
	  if (tmpxfds.isset((*i).first)) t.push_back(task((*i).second, Agent::errexc));
	}
      for (tlist_t::const_iterator i = t.begin(); i != t.end(); i++)
	tasks.push(*i);
    }
};
