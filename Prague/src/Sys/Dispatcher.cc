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

#include "Prague/Sys/Time.h"
#include "Prague/Sys/Signal.h"
#include "Prague/Sys/Observer.h"
#include "Prague/Sys/Dispatcher.h"
#include "Prague/Sys/Timer.h"
#include "Prague/Sys/Agent.h"
#include <queue>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

namespace Prague
{

class Compare
{
public:
  typedef pair<Time, Timer *> value_type;
  typedef size_t size_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  bool operator () (const pair<Time, Timer *> &A, const pair<Time, Timer *> &B) { return A.first > B.first;}
};

class Dispatcher::TimerQueue : public priority_queue<pair<Time, Timer *>, vector<pair<Time, Timer *> >, Compare>
{
  class sender_is
  {
  public:
    sender_is(const Timer *TT) : T(TT) {}
    bool operator () (const pair<Time, Timer *> &P) { return T == P.second;}
  private:
    const Timer *T;
  };
 public:
  void remove(const Timer *T)
    {
      vector<pair<Time, Timer *> >::iterator end = remove_if(c.begin(), c.end(), sender_is(T));
      c.erase(end, c.end());
    }
};

};

using namespace Prague;

Dispatcher *Dispatcher::instance = 0;

Dispatcher *Dispatcher::Instance()
{
  if (!instance) instance = new Dispatcher;
  return instance;
}

Dispatcher::Dispatcher()
  : running(false)
{
  killhandler = new Observer<Dispatcher, int> (this, &sigKill);
  childhandler = new Observer<Dispatcher, int> (this, &sigChild);
  Sys::Signal::mask(Sys::Signal::pipe);
  Sys::Signal::set(Sys::Signal::child, childhandler);
  Sys::Signal::set(Sys::Signal::hangup, killhandler);
  Sys::Signal::set(Sys::Signal::interrupt, killhandler);
  Sys::Signal::set(Sys::Signal::quit, killhandler);
  Sys::Signal::set(Sys::Signal::illegal, killhandler);
  Sys::Signal::set(Sys::Signal::abort, killhandler);
  Sys::Signal::set(Sys::Signal::fpe, killhandler);
  Sys::Signal::set(Sys::Signal::bus, killhandler);
  //  Sys::Signal::set(Sys::Signal::segv, killhandler);
  Sys::Signal::set(Sys::Signal::iotrap, killhandler);
  Sys::Signal::set(Sys::Signal::terminate, killhandler);
  timers    = new TimerQueue;
}

/* @Method{Dispatcher::~Dispatcher()}
 *
 * @Description{}
 */
Dispatcher::~Dispatcher()
{
#ifdef GDB
  cout << "Dispatcher::~Dispatcher" << endl;
#endif
  delete timers;
  for (List::iterator i = agents.begin(); i != agents.end(); i++) (*i)->kill();  
#ifdef GDB
  cout << "leaving Dispatcher::~Dispatcher" << endl;
#endif
}

/* @Method{void Dispatcher::start()}
 *
 * @Description{starts the event loop}
 */
void Dispatcher::start()
{
  running = true;
  do
    {
      dispatchTimeouts();
      wait();
    }
  while (running);
}

/* @Method{void Dispatcher::stop()}
 *
 * @Description{stops the event loop}
 */
void Dispatcher::stop()
{
  running = false;
}

/* @Method{void Dispatcher::step()}
 *
 * @Description{handles all pending input and returns immediately}
 */
void Dispatcher::step()
{
#ifdef GDB
  cout << "Dispatcher::step " << endl;
#endif
  running = false;
  do
    {
      dispatchTimeouts();
    }
  while (wait());
}

/* @Method{void Dispatcher::bind(Agent *A)}
 *
 * @Description{add @var{A} to the agent list}
 */
void Dispatcher::bind (Agent *A)
{
  Sys::Signal::mask(Sys::Signal::child);
  agents.push_back(A);
  A->bound = true;
  A->start();
  int fd;
  short mask = A->Mask() & Agent::asyncio;
  if (mask & Agent::out)
    {
      fd = A->OFD();
#ifdef GDB
      cout << "Dispatcher::bind " << fd << endl;
#endif
      if (mask & Agent::outready) rfds.set(fd);
      if (mask & Agent::outexc) xfds.set(fd);
      if (rchannel.find(fd) == rchannel.end()) rchannel[fd] = A;
      else { cerr << "Dispatcher::bind() : Error : file descriptor already in use" << endl; return;}
    }
  if (mask & Agent::in)
    {
      fd = A->IFD();
#ifdef GDB
      cout << "Dispatcher::bind " << fd << endl;
#endif
      if (mask & Agent::inready) wfds.set(fd);
      if (mask & Agent::inexc) xfds.set(fd);
      if (wchannel.find(fd) == wchannel.end()) wchannel[fd] = A;
      else { cerr << "Dispatcher::bind() : Error : file descriptor already in use" << endl; return;}
    }
  if (mask & Agent::err)
    {
      fd = A->EFD();
#ifdef GDB
      cout << "Dispatcher::bind " << fd << endl;
#endif
      if (mask & Agent::errready) rfds.set(fd);
      if (mask & Agent::errexc) xfds.set(fd);
      if (echannel.find(fd) == echannel.end()) echannel[fd] = A;
      else { cerr << "Dispatcher::bind() : Error : file descriptor already in use" << endl; return;}
    }
  Sys::Signal::unmask(Sys::Signal::child);
}

/* @Method{void Dispatcher::release(Agent *A)}
 *
 * @Description{remove @var{A}}
 */
void Dispatcher::release (Agent *A)
{
#ifdef GDB
  cout << "Dispatcher::release" << endl;
#endif
  Sys::Signal::mask(Sys::Signal::child);
  A->bound = false;
  int fd;
  Dictionary::iterator c;
  fd = A->OFD();
  if ((c = rchannel.find(fd)) != rchannel.end())
    {
      rchannel.erase(c);
      rfds.clear(fd);
      xfds.clear(fd);
    }
  fd = A->IFD();
  if ((c = wchannel.find(fd)) != wchannel.end())
    {
      wchannel.erase(c);
      wfds.clear(fd);
      xfds.clear(fd);
    }
  fd = A->EFD();
  if ((c = echannel.find(fd)) != echannel.end())
    {
      echannel.erase(c);
      rfds.clear(fd);
      xfds.clear(fd);
    }
  for (List::iterator i = agents.begin(); i != agents.end(); i++) if (A == *i) { agents.erase(i); break;}
  Sys::Signal::unmask(Sys::Signal::child);
#ifdef GDB
  cout << "leave Dispatcher::release" << endl;
#endif
}

/* @Method{Agent *Dispatcher::search(int pid)}
 *
 * @Description{search for an agent in terms of the @var{pid} of the corresponding subprocess}
 */
Agent *Dispatcher::search(int pid)
{
  for (List::iterator i = agents.begin(); i != agents.end(); i++) if (pid == (*i)->PID()) return *i;
  return 0;
}

/* @Method{void Dispatcher::sigChild(const int &signum)}
 *
 * @Description{process status changes of children: prevent children from becoming zombies. Return true if signal was handled}
 */
void Dispatcher::sigChild(const int &)
{
#ifdef GDB
  cout << " got sigChild" << endl;
#endif
  for (List::iterator i = agents.begin(); i != agents.end(); i++)
    {
      pid_t pid = (*i)->PID();
      int status;
      if (pid > 0 && waitpid(pid, &status, WNOHANG) == pid) (*i)->NewStatus(status);
    }
  // this is not necessary for POSIX...
  //  Sys::Signal::set(Sys::Signal::child, childhandler);
}

/* @Method{void Dispatcher::sigKill(const int &signum)}
 *
 * @Description{we got a terminate signal (or hangup or kill or ...); call @code{exit()} to make sure all global destructors are called
 and all children get killed}
 */
void Dispatcher::sigKill(const int &signum)
{
  cerr << Sys::Signal::Name(signum) << endl;
#if 1
  delete this;
#endif
  exit(1);
}

/* @Method{void Dispatcher::dispatchStreams()}
 *
 * @Description{}
 */
void Dispatcher::dispatchStreams(Agent::iomask m, Agent *A)
{
#ifdef GDB
  cout << "Dispatcher::dispatchStreams" << endl;
#endif
  switch (m)
    {
    case Agent::inready:  (A)->InputNotify(); break;
    case Agent::outready: (A)->OutputNotify(); break;
    case Agent::errready: (A)->ErrorNotify(); break;
    case Agent::inexc:    (A)->UrgentInputNotify(); break;
    case Agent::outexc:   (A)->UrgentOutputNotify(); break;
    case Agent::errexc:   (A)->UrgentErrorNotify(); break;
    default: break;
    }
#ifdef GDB
  cout << "leaving Dispatcher::dispatchStreams" << endl;
#endif
};

/* @Method{void Dispatcher::dispatchTimeouts()}
 *
 * @Description{Timer::timeout() should simply broadcast a signal, since it doesn't take too long, all timeouts might be catched with the same currentTime() value}
 */
void Dispatcher::dispatchTimeouts()
{
  Time current = Time::currentTime();
  while (timers->size() && timers->top().first <= current)
    {
      Timer *timer = timers->top().second;
      timers->pop();
      timer->timeout();
    }
};

/* @Method{bool Dispatcher::wait()}
 *
 * @Description{returns if there is input to be processed or a timout has elapsed. For every selected file descriptor call the apropriate Agent...}
 */
bool Dispatcher::wait()
{
  for (List::iterator i = agents.begin(); i != agents.end(); i++)
    if ((*i)->pending()) { (*i)->dispatchpending(); return true;}
  if (!running) return false;
  FdSet tmprfds = rfds;
  FdSet tmpwfds = wfds;
  FdSet tmpxfds = xfds;
  Time T = timers->size() ? timers->top().first - Time::currentTime() : Time(0);
  unsigned int fdsize = max(max(tmprfds.max(), tmpwfds.max()), tmpxfds.max()) + 1;
  int nsel = select(fdsize, tmprfds, tmpwfds, tmpxfds, T ? &T : 0);
  if (nsel == -1)
    {
      if (errno == EINTR || errno == EAGAIN) errno = 0;
      /*
       * did we catch a signal ???
       */
#ifdef GDB
      cout << " I got probably a nonblocked signal" << endl;
#endif
    }
  else if (nsel > 0 && fdsize)
    {
      /*
       * we maintain a temporal lists of agents to be notified;
       * since Agents might remove themselves from the Dictionaries while being notified
       * the notification can't be done in a loop over the main Dictionary
       */
      TmpList channels;
      for (Dictionary::iterator i = rchannel.begin(); i != rchannel.end(); i++)
	{
	  if (tmprfds.isset((*i).first)) channels.push_back(pair<Agent *, Agent::iomask>((*i).second, Agent::outready));
	  if (tmpxfds.isset((*i).first)) channels.push_back(pair<Agent *, Agent::iomask>((*i).second, Agent::outexc));
	}
      for (Dictionary::iterator i = wchannel.begin(); i != wchannel.end(); i++)
	{
	  if (tmpwfds.isset((*i).first)) channels.push_back(pair<Agent *, Agent::iomask>((*i).second, Agent::inready));
	  if (tmpxfds.isset((*i).first)) channels.push_back(pair<Agent *, Agent::iomask>((*i).second, Agent::inexc));
	}
      for (Dictionary::iterator i = echannel.begin(); i != echannel.end(); i++)
	{
	  if (tmprfds.isset((*i).first)) channels.push_back(pair<Agent *, Agent::iomask>((*i).second, Agent::errready));
	  if (tmpxfds.isset((*i).first)) channels.push_back(pair<Agent *, Agent::iomask>((*i).second, Agent::errexc));
	}
      for(TmpList::iterator i = channels.begin(); i != channels.end(); i++) dispatchStreams((*i).second, (*i).first);
    }
#ifdef GDB
  cout << "leaving Dispatcher::wait" << endl;
#endif
  return true;
};

/* @Method{void Dispatcher::addTimeout(Timer *TO, const Time &T)}
 *
 * @Description{}
 */
void Dispatcher::addTimeout(Timer *TO, const Time &T)
{
  timers->push(pair<Time, Timer *> (T, TO));
};

/* @Method{void Dispatcher::removeTimeout(Timer *T)}
 *
 * @Description{}
 */
void Dispatcher::removeTimeout(const Timer *TO)
{
  timers->remove(TO);
};
