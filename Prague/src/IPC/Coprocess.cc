/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include "Prague/IPC/Coprocess.hh"
#include "Prague/Sys/Signal.hh"
#include "Prague/Sys/Tracer.hh"

#include <fstream>

#include <cstdio>
#include <cerrno>
#include <unistd.h>

#define PRAGUE_INCL_FOR_WAITPID
#include "Prague/Sys/includes.hh"

using namespace Prague;

Coprocess::plist_t  Coprocess::processes;
Coprocess::Reaper   Coprocess::reaper;
Mutex               Coprocess::singletonMutex;
/*
 * we can't set the Signal::child handler within the Reapers constructor 
 * since Signals are possibly not initialized
 * do it in the first Coprocess' constructor instead
 * - stefan
 */
static bool init = false;

void Coprocess::Reaper::notify(int)
{
  Trace trace("Coprocess::Reaper::notify");
  MutexGuard guard(singletonMutex);
  for (plist_t::iterator i = processes.begin(); i != processes.end(); i++)
    {
      int status;
      pid_t id = (*i)->pid();
      if (id > 0 && waitpid(id, &status, 0) == id)
	{
	  if (WIFEXITED(status))
	    {
	      MutexGuard guard((*i)->mutex);
	      (*i)->id     = 0;
	      (*i)->_state = exited;
	      (*i)->_value = WEXITSTATUS(status);
	    }
	  else if (WIFSIGNALED(status))
	    {
	      MutexGuard guard((*i)->mutex);
	      (*i)->id     = 0;
	      (*i)->_state = signaled;
	      (*i)->_value = WTERMSIG(status);
	    }
	  processes.erase(i);
	  break;
	}
    }
}

Coprocess::Coprocess(const string &cmd, IONotifier *n, EOFNotifier *e)
  : path(cmd), ioNotifier(n), eofNotifier(e), id(0), _state(ready), inbuf(0), outbuf(0), errbuf(0)
{
  if (!init) Signal::set(Signal::child, &reaper);
  init = true;
  _timeout.hangup    = 5;
  _timeout.terminate = 10;
  _timeout.kill      = 15;
};

Coprocess::~Coprocess()
{
  stop();
  terminate();
};

void Coprocess::start()
{
  MutexGuard guard(mutex);
  processes.push_back(this);
  _state = running;
  Agent::start();
}

void Coprocess::stop()
{
  Agent::stop();
}

bool Coprocess::process(int, iomask_t m)
{
  Trace trace("Coprocess::process");
  MutexGuard guard(mutex);
  /*
   * let the client process the IO
   */
  bool flag = ioNotifier ? ioNotifier->notify(m) : false;
  flag &= (id != 0);
  /*
   * see whether the channel is still open
   */
  switch (m)
    {
    case Agent::inready:
    case Agent::inexc:
      if (ibuf()->eof())
	{
	  if (eofNotifier) eofNotifier->notify(Agent::in);
	  flag = false;
	}
      break;
    case Agent::outready:
    case Agent::outexc:
      if (obuf()->eof()) 
	{
	  if (eofNotifier) eofNotifier->notify(Agent::out);
	  flag = false;
	}
      break;
    case Agent::errready: 
    case Agent::errexc:
      if (ebuf()->eof())
	{
	  if (eofNotifier) eofNotifier->notify(Agent::err);
	  flag = false;
	}
      break;
    default: break;
    }
  return flag;
}

void Coprocess::done(int, iomask_t m)
{
  Trace trace("Coprocess::done");
  MutexGuard guard(mutex);
  switch (m)
    {
    case Agent::inready:
    case Agent::inexc: shutdown(in); break;
    case Agent::outready:
    case Agent::outexc: shutdown(out); break;
    case Agent::errready:
    case Agent::errexc: shutdown(err); break;
    default: break;
    }
}

void Coprocess::terminate()
{
  int sig = 0;
  for (long ms = 0; pid(); ms++)
    {
      sig = 0;
      if (ms == _timeout.terminate) sig = Signal::terminate;
      if (ms == _timeout.hangup)  sig = Signal::hangup;
      if (ms == _timeout.kill) sig = Signal::kill;
      if (sig)	     kill(sig);
      Thread::delay(1);
    }
  Thread::delay(10);
  if (pid()) cerr << "Coprocess " << pid() << " wouldn't die (" << Signal::name(sig) << ')' << endl;
}

void Coprocess::shutdown(short m)
{
  short om = mask();
  m &= om;
  mask(om & ~m);
  if (m & in)
    {
      delete inbuf;
      inbuf = 0;
    }
  if (m & out)
    {
      delete outbuf;
      outbuf = 0;
    }
  if (m & err)
    {
      delete errbuf;
      errbuf = 0;
    }
}

void Coprocess::kill(int signum)
{
  if (id > 0 && ::kill(id, signum) < 0) perror("Coprocess::kill");
}
