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
#include <algorithm>
#include <cstdio>

namespace Prague
{
typedef void (*sighnd_type) (...);
void sighandler (int signo) { Signal::notify (signo);}
};

using namespace Prague;

Signal::Dictionary Signal::notifiers;

extern "C" char *strsignal(int signo);

/* @Method{bool Signal::set(int signum, Notifier *notifier)}
 *
 * Description{add @var{A} to the list of actions executed whenever the signal @var{signum} is catched}
 */
bool Signal::set (int signum, Signal::Notifier *notifier)
{
  if (!notifiers[signum])
    {
      notifiers[signum] = new NotifierList;
      struct sigaction sa;
      if (sigaction (signum, 0, &sa) == -1) return false;
      if (sa.sa_handler != sighnd_type (&sighandler))
	{
	  // setting for the first time
	  sa.sa_handler = sighnd_type (&sighandler);
	  if (sigemptyset (&sa.sa_mask) == -1) return false;
	  sa.sa_flags = 0;
	  if (sigaction (signum, &sa, 0) == -1) return false;
	}
    }
  notifiers[signum]->push_back(notifier);
  return true;
}

/* @Method{bool Signal::unset(int signum, const Action<int> &A)}
 *
 * @Description{removes @var{A} from the action list for @var{signum}}
 */
bool Signal::unset (int signum, Signal::Notifier *notifier)
{
  NotifierList *L = notifiers[signum];
  if (!L) return false;
  NotifierList::iterator i = find (L->begin(), L->end(), notifier);
  if (i != L->end ())
    {
      L->erase (i);
      /*
       * if this was the only installed handler, call unset(signo) to reinstall the system's default handler
       */
      if (!L->size()) { delete L; unset(signum);}
      return true;
    }
  return false;
}

/* @Method{void Signal::unset(int signum)}
 *
 * @Description{remove all actions for the signal @var{signum} and reinstall the system's default handler}
 */
void Signal::unset (int signum)
{
  NotifierList *L = notifiers[signum];
  if (L) L->erase (L->begin(), L->end());
  struct sigaction sa;
  if (sigaction (signum, 0, &sa) == -1) return;
  if (sa.sa_handler == sighnd_type (&sighandler))
    {
      sa.sa_handler = sighnd_type (SIG_DFL);
      if (sigemptyset (&sa.sa_mask) == -1) return;
      sa.sa_flags = 0;
      if (sigaction (signum, &sa, 0) == -1) return;
    }
}

/* @Method{void Signal::mask(int signum)}
 *
 * @Description{ignore the specified signal}
 */
void Signal::mask (int signum)
{
  sigset_t s;
  if (sigemptyset (&s) == -1) return;
  if (sigaddset (&s, signum) == -1) return;
  if (sigprocmask (SIG_BLOCK, &s, 0) == -1) return;
}

/* @Method{void Signal::unmask (int signum)}
 *
 * @Description{don't ignore the specified signal any more}
 */
void Signal::unmask (int signum)
{
  sigset_t s;
  if (sigemptyset (&s) == -1) return;
  if (sigaddset (&s, signum) == -1) return;
  if (sigprocmask (SIG_UNBLOCK, &s, 0) == -1) return;
}

/* @Method{void Signal::mask(int siga, int sigb)}
 *
 * @Description{block @var{sigb} while @var{siga} is handled}
 */
void Signal::mask (int siga, int sigb)
{
  struct sigaction sa;
  if (sigaction (siga, 0, &sa) == -1) return;
  if (sa.sa_handler != sighnd_type (&sighandler))
    {
      sa.sa_handler = sighnd_type (&sighandler);
      if (sigemptyset (&sa.sa_mask) == -1) return;
      sa.sa_flags = 0;
    }
  if (sigaddset (&sa.sa_mask, sigb) == -1) return;
  if (sigaction (siga, &sa, 0) == -1) return;
}

void Signal::unmask (int siga, int sigb)
{
  struct sigaction sa;
  if (sigaction (siga, 0, &sa) == -1) return;
  if (sa.sa_handler != sighnd_type (&sighandler))
    {
      sa.sa_handler = sighnd_type (&sighandler);
      if (sigemptyset (&sa.sa_mask) == -1) return;
      sa.sa_flags = 0;
    }
  else { if (sigdelset (&sa.sa_mask, sigb) == -1) return;}
  if (sigaction (siga, &sa, 0) == -1) return;
}

void Signal::sysresume (int signum, bool set)
{
  struct sigaction sa;
  if (sigaction (signum, 0, &sa) == -1) return;
  if (sa.sa_handler != sighnd_type (&sighandler))
    {
      sa.sa_handler = sighnd_type (&sighandler);
      if (sigemptyset (&sa.sa_mask) == -1) return;
      sa.sa_flags = 0;
    }
  if (sigaction (signum, &sa, 0) == -1) return;
}

struct execute
{
  execute(int s) : signum(s) {}
  void operator () (Signal::Notifier *notifier) { notifier->notify(signum);}
  int signum;
};

/* @Method{void Signal::notify (int signum)}
 *
 * @Description{call the observers}
 */
void Signal::notify (int signum)
{
  NotifierList *L = notifiers[signum];
  execute e(signum);
  if (L) for_each (L->begin(), L->end(), e);
}

/* @Method{sigset_t Signal::pending()}
 *
 * @Description{is there any pending signal (while being blocked)}
 */
sigset_t Signal::pending ()
{
  sigset_t s;
  if (sigemptyset (&s) == -1) return s;
  if (sigpending (&s) == -1) return s;
  return s;
}

/* @Method{bool Signal::ispending(int signum)}
 *
 * @Description{is there a pending signal of type @var{signum} (while being blocked)}
 */
bool Signal::ispending (int signo)
{
  sigset_t s = pending();
  switch (sigismember (&s, signo))
    {
    case  1: return true;
    case -1: perror("Signal::ispending: ");
    case  0:
    default: return false;
    }
  return false;
}

/* @Method{char *Signal::Name(int signum)}
 *
 * @Description{returns the signal name of @var{signum} if nonzero or of the last signal beeing catched}
 */
char *Signal::Name(int signum)
{
  return strsignal(signum);
}
