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
#include "Prague/IPC/Coprocess.hh"
#include "Prague/Sys/Signal.hh"

#include <fstream>

#include <cstdio>
#include <cerrno>
#include <wait.h>
#include <unistd.h>

using namespace Prague;

Coprocess::plist_t  Coprocess::processes;
Coprocess::Cleaner *Coprocess::cleaner = 0;

Coprocess::Cleaner::Cleaner()
{
  Signal::set(Signal::child, this);
}

void Coprocess::Cleaner::notify(int signum)
{
  for (plist_t::iterator i = processes.begin(); i != processes.end(); i++)
    {
      pid_t id = (*i)->pid();
      int status;
      if (id > 0 && waitpid(id, &status, WNOHANG | WUNTRACED) == id)
	{
	  if (WIFEXITED(status))
	    {
	      (*i)->_state = exited;
	      if ((*i)->exitNotifier) (*i)->exitNotifier->notify(WEXITSTATUS(status));
	    }
	  else if (WIFSIGNALED(status))
	    {
	      (*i)->_state = signaled;
	      if ((*i)->signalNotifier) (*i)->signalNotifier->notify(WTERMSIG(status));
	    }
	  else if (WIFSTOPPED(status))
	    {
	      if ((*i)->stopNotifier) (*i)->stopNotifier->notify(WSTOPSIG(status));
	    }
	}
    }
}

Coprocess::Coprocess(const string &cmd, Notifier *e, Notifier *si, Notifier *st)
  : path(cmd), id(0), _state(ready), inbuf(0), outbuf(0), errbuf(0),
//     beingTerminated(false), termTout(10), hupTout(5), killTout(15),
    tout(this), timer(&tout),
    exitNotifier(e), signalNotifier(si), stopNotifier(st)
{
  if (!cleaner) cleaner = new Cleaner;
};

Coprocess::~Coprocess()
{
//   terminate();
};

void Coprocess::start()
{
  MutexGuard guard(mutex);
  _state = running;
  Agent::start();
}

void Coprocess::stop()
{
  Agent::stop();
}

void Coprocess::timeout()
{
// /*
//  * delayed status update
//  * 2 : terminate timeout
//  * 3 : hangup timeout
//  * 4 : kill timeout
//  */
//   switch (timermode)
//     {
//     case 1: if (WIFEXITED(stat) || WIFSIGNALED(stat)) abort(); break;
//     case 2:
//       timermode = 3;
//       kill(Signal::terminate);
//       timer->start((hupTout-termTout)*1000);
//       break;
//     case 3:
//       timermode = 4;
//       kill(Signal::hangup);
//       timer->start((killTout-hupTout)*1000);
//       break;
//     case 4:
//       timermode = 0;
//       kill(Signal::kill);
//       break;
//     default: break;
//     }
}

// void Coprocess::NewStatus(int s)
// {
//   status = s;
// //   notify(Agent::newstatus);
//   /*
//    * if we run in asyncronous mode, update our status with some delay
//    */
//   if (bound) { timermode = 1; timer->start(1000);}
// }

void Coprocess::terminate(bool flag)
{
//   /*
//    * We're exiting: call only the default handlers
//    */
//   if (flag) mask = panic|died;
//   if (!running()) return;
//   beingTerminated = true;
//   if (flag) Coprocess::abort();
//   else abort();
//   beingTerminated = false;
//   if (!bound || (pid >= 0 && flag)) waitToTerminate();
//   if (active) active = false, notify(stopped);
//   if (bound && pid > 0)
//     {
//       /*
//        * Kill asynchronously.  We don't want to wait until the
//        * process dies, so we just send out some signals and pretend
//        * the process has terminated gracefully.
//        */
//       if (termTout) timermode = 2, timer->start(termTout*1000);
//       abort();
//       notify(died);
//     }
}

// void Coprocess::abort()
// {
//   /*
//    * close pipes
//    * we deliberately ignore any error messages here
//    */
//   if (bound)
//     {
// //       AsyncManager *manager = AsyncManager::Instance();
// //       manager->release(this);
//     }
//   shutdown(in|out|err);
//   if (!beingTerminated) if (active) active = false, notify(stopped); // declare agent as "not running"
//   if (status >= 0) notify(died), status = -1;
// }

// void Coprocess::wait()
// {
//   while (running())
//     {
//       int s;
//       pid_t ret = waitpid(pid, &s, 0);
//       if (ret > 0)
// 	{
// 	  //	  assert(ret == pid);
// 	  stat = s;
// 	  if (WIFEXITED(stat) || WIFSIGNALED(stat)) abort();
// 	}
//     }
// }

// bool Coprocess::pending()
// {
//   return (outbuf && outbuf->in_avail()) || (errbuf && errbuf->in_avail());
// }

// bool Coprocess::running()
// {
//   if (active && pid >= 0)
//     {
//       /*
//        * Ignore interrupts for a while
//        */
//       Signal::Guard _g1(Signal::interrupt);
//       Signal::Guard _g2(Signal::quit);
//       Signal::Guard _g3(Signal::hangup);
//       /*
//        * Query current process state
//        */
// 	int s;
// 	pid_t r = waitpid(PID(), &s, WNOHANG);
// 	if (r > 0)
// 	  {
// 	    /*
// 	     * Coprocess stopped or terminated
// 	     */
// 	    //	    assert(r == pid);
// 	    stat = s;
// 	    if (WIFEXITED(stat) || WIFSIGNALED(stat)) abort();
// 	  }
// 	else if (r < 0)
// 	  {
// 	    if (errno == ECHILD) abort();	// No such child: agent is not running
// 	    else SystemError("wait failed", false);
// 	  }
//     }
//   return active;
// }

// void Coprocess::waitToTerminate()
// {
//   int sig = 0;
//   for (int seconds = 0; running(); seconds++)
//     {
//       sig = 0;
//       if (seconds == termTout) sig = SIGTERM;
//       if (seconds == hupTout)  sig = SIGHUP;
//       if (seconds == killTout) sig = SIGKILL;
//       if (sig)	     kill(sig);
//       if (running()) sleep(1);
//     }
//   if (sig)
//     {
//       string msg = string("Coprocess wouldn't die (") + strsignal(sig) + ")";
//       Error(msg.c_str(), true);
//     }
// }

void Coprocess::shutdown(short m)
{
  m = mask() | ~m;
  mask(m);
  if (m ^ inready)
    {
      delete inbuf;
      inbuf = 0;
    }
  else if (m ^ outready)
    {
      delete outbuf;
      outbuf = 0;
    }
  else if (m ^ errready)
    {
      delete errbuf;
      errbuf = 0;
    }
}

// void Coprocess::outputEOF()
// {
//   running();
//   shutdown(out);
// }

// void Coprocess::errorEOF()
// {
//   running();
//   shutdown(err);
// }

// void Coprocess::kill(int sig)
// {
//   if (running() && pid >= 0)
//     if (::kill(pid, sig) < 0) SystemError("Could not kill", true);
// }
