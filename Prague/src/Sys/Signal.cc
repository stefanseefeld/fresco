/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org>
 * http://www.fresco.org
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
#include "Prague/config.hh"
#include "Prague/Sys/Signal.hh"
#include <cstring>
#include <string>
#include <algorithm>
#include <cstdio>

namespace Prague
{
  typedef void (*sighnd_type) (int);
  void sighandler (int signo)
  {
      /*
       * due to the non conformance of LinuxThreads with
       * POSIX 1003.1c we can't let the signal server thread
       * handle the SIGCHLD signal. 'wait()' would fail.
       * Instead, we have to handle it directly, trusting
       * the event handler that it is reentrant and async safe
       * - stefan
       */
      if (signo == Signal::child) Signal::notify(Signal::type(signo));
      else if (!Thread::id())
      Signal::queue.push(Signal::type(Signal::type(signo)));
  }

} // namespace

using namespace Prague;

Signal::dict_t Signal::notifiers;
Thread::Queue<Signal::type> Signal::queue(32);
Thread Signal::server(&Signal::run, 0);

bool Signal::set(type signum, Signal::Notifier *notifier)
{
    if (server.state() == Thread::READY) server.start();
    if (!notifiers[signum].size())
    {
        struct sigaction sa;
        if (sigaction (signum, 0, &sa) == -1) return false;
        if (sa.sa_handler != sighnd_type (&sighandler))
        {
            sa.sa_handler = sighnd_type (&sighandler);
            if (sigemptyset (&sa.sa_mask) == -1) return false;
            sa.sa_flags = 0;
            if (sigaction (signum, &sa, 0) == -1) return false;
        }
    }
    notifiers[signum].push_back(notifier);
    return true;
}

bool Signal::unset(type signum, Signal::Notifier *notifier)
{
    nlist_t::iterator i = find (notifiers[signum].begin(), notifiers[signum].end(), notifier);
    if (i != notifiers[signum].end())
    {
        notifiers[signum].erase(i);
        if (!notifiers[signum].size()) unset(signum);
        return true;
    }
    return false;
}

void Signal::unset(type signum)
{
    notifiers[signum].erase(notifiers[signum].begin(), notifiers[signum].end());
    struct sigaction sa;
    if (sigaction(int(signum), 0, &sa) == -1) return;
    if (sa.sa_handler == sighnd_type(&sighandler))
    {
        sa.sa_handler = sighnd_type(SIG_DFL);
        if (sigemptyset(&sa.sa_mask) == -1) return;
        sa.sa_flags = 0;
        if (sigaction(int(signum), &sa, 0) == -1) return;
    }
}

void Signal::mask(type signum)
{
    sigset_t s;
    if (sigemptyset(&s) == -1) return;
    if (sigaddset(&s, int(signum)) == -1) return;
    if (sigprocmask(SIG_BLOCK, &s, 0) == -1) return;
}

void Signal::mask (type siga, type sigb)
{
    struct sigaction sa;
    if (sigaction(int(siga), 0, &sa) == -1) return;
    if (sa.sa_handler != sighnd_type(&sighandler))
    {
        sa.sa_handler = sighnd_type(&sighandler);
        if (sigemptyset(&sa.sa_mask) == -1) return;
        sa.sa_flags = 0;
    }
    if (sigaddset(&sa.sa_mask, int(sigb)) == -1) return;
    if (sigaction(int(siga), &sa, 0) == -1) return;
}

void Signal::unmask(type signum)
{
    sigset_t s;
    if (sigemptyset(&s) == -1) return;
    if (sigaddset(&s, int(signum)) == -1) return;
    if (sigprocmask(SIG_UNBLOCK, &s, 0) == -1) return;
}

void Signal::unmask(type siga, type sigb)
{
    struct sigaction sa;
    if (sigaction(int(siga), 0, &sa) == -1) return;
    if (sa.sa_handler != sighnd_type(&sighandler))
    {
        sa.sa_handler = sighnd_type(&sighandler);
        if (sigemptyset(&sa.sa_mask) == -1) return;
        sa.sa_flags = 0;
    }
    else { if (sigdelset(&sa.sa_mask, int(sigb)) == -1) return;}
    if (sigaction(int(siga), &sa, 0) == -1) return;
}

void Signal::sysresume(type signum, bool set)
{
    struct sigaction sa;
    if (sigaction(int(signum), 0, &sa) == -1) return;
    if (sa.sa_handler != sighnd_type(&sighandler))
    {
        sa.sa_handler = sighnd_type(&sighandler);
        if (sigemptyset(&sa.sa_mask) == -1) return;
        sa.sa_flags = 0;
    }
    if (sigaction(int(signum), &sa, 0) == -1) return;
}

sigset_t Signal::pending()
{
    sigset_t s;
    if (sigemptyset(&s) == -1) return s;
    if (sigpending(&s) == -1) return s;
    return s;
}

bool Signal::ispending(type signo) throw(std::runtime_error)
{
    sigset_t s = pending();
    switch (sigismember(&s, type(signo)))
    {
      case  1:
        return true;
      case -1:
        throw std::runtime_error(std::string("Signal::ispending failed: ") +
                                 strerror(errno));
      case  0:
      default:
        return false;
    }
    return false;
}

const char *Signal::name(type signum) { return strsignal(int(signum)); }

struct execute
{
    execute(Signal::type s) : signum(s) { }
    void operator () (Signal::Notifier *notifier) { notifier->notify(signum); }
    Signal::type signum;
};

void Signal::notify(type signum)
{
    nlist_t tmp = notifiers[signum];
    execute e(signum);
    for_each(tmp.begin(), tmp.end(), e);
}

void *Signal::run(void *)
{
    while (true)
    {
        type signo = Signal::queue.top();
        Signal::queue.pop();
        Signal::notify(signo);
        Thread::testcancel();
    }
    return 0;
}
