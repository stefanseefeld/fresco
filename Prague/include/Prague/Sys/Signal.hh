/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org>
 * Copyright (C) 2003 Tobias Hunger <tobias@fresco.org>
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
#ifndef _Prague_Signal_hh
#define _Prague_Signal_hh

#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/ThreadQueue.hh>
#include <signal.h>
#include <vector>
#include <map>

namespace Prague
{

  //. A wrapper for the POSIX signal handling functions.
  class Signal
  {
    public:
      //. This class defines the interface all Notifiers will have to use.
      //. A notifier is a objectified callback function that can get bound to
      //. a signal.
      class Notifier
      {
        public:
          virtual ~Notifier() { }
          virtual void notify(int) = 0;
      };

      //. Types of signals as defined in the single unix specification version 3.
      //. (see http://www.unix.org/version3/)
      enum type
      {
          none = 0, //.< All is well, move along...
          abort = SIGABRT, //.< Process abort signal. (default: abort process)
          alarm = SIGALRM, //.< Alarm clock. (default: terminate process)
          bus = SIGBUS, //.< Access to an undefined portion of a memory object. (default: abort process)
          child = SIGCHLD, //.< Child process terminated, stopped, or continued. (default: ignore signal)
          continue_execution = SIGCONT, //.< Continue executing, if stopped. (default: continue process)
          floating_point= SIGFPE, //.< Erroneous arithmetic operation. (default: abort process)
          hangup = SIGHUP, //.< Hangup. (default: terminate process)
          illegal = SIGILL, //.< Illegal instruction. (default: abort process)
          interrupt = SIGINT, //.< Terminal interrupt signal. (default: terminate process)
          kill = SIGKILL, //.< Kill (cannot be caught or ignored). (default: terminate process)
          pipe = SIGPIPE, //.< Write on a pipe with no one to read it. (default: terminate process)
          quit = SIGQUIT, //.< Terminal quit signal. (default: abort process)
          segfault = SIGSEGV, //.< Invalid memory reference. (default: abort process)
          stop = SIGSTOP, //.< Stop executing (cannot be caught or ignored). (default: stop process)
          terminate = SIGTERM, //.< Termination signal. (default: terminate process)
          terminal_stop = SIGTSTP, //.< Terminal stop signal. (default: stop process)
          background_read = SIGTTIN, //.< Background process attempting read. (default: stop process)
          background_write = SIGTTOU, //.< Background process attempting write. (default: stop process)
          user1 = SIGUSR1, //.< User-defined signal 1. (default: terminate process)
          user2 = SIGUSR2, //.< User-defined signal 2. (default: terminate process)
#ifdef __FreeBSD__
          poll = SIGIO, //.< Pollable event. (default: terminate process)
#else
          poll = SIGPOLL, //.< Pollable event. (default: terminate process)
#endif

          profiling = SIGPROF, //.< Profiling timer expired. (default: terminate process)
          system = SIGSYS, //.< Bad system call. (default: abort process)
          trap = SIGTRAP, //.< Trace/breakpoint trap. (default: abort process)
          urgent = SIGURG, //.< High bandwidth data is available at a socket. (default: ignore signal)
          virtual_timer = SIGVTALRM, //.< Virtual timer expired. (default: terminate process)
          cpu_time = SIGXCPU, //.< CPU time limit exceeded. (default: abort process)
          fs_size = SIGXFSZ //.< File size limit exceeded. (default: abort process)
      };

      //. add a notifier to be executed whenever the given signal is catched
      static bool set(type, Notifier *);
      //. removes a notifier from the list for signum
      static bool unset(type, Notifier *);
      //. remove all notifiers for the signal and reinstall the system's default handler
      static void unset(type);
      //. ignore the specified signal
      static void mask(type);
      //. block sigb while siga is handled
      static void mask(type, type);
      //. don't ignore the specified signal any more
      static void unmask(type);
      //. don't ignore the specified signal any more
      static void unmask(type, type);
      //. is there a pending signal of type signum (while being blocked)
      static bool ispending(type) throw(std::runtime_error);
      //. is there any pending signal (while being blocked)
      static sigset_t pending();
      static void sysresume(type, bool);
      //. returns the signal name of signum if nonzero or of the last signal beeing catched
      static const char *name(type);

      //. a Signal Guard, that masks a given signal over its lifetime.
      class Guard
      {
        public:
          Guard(type s) : signo(s) { mask(signo); }
          ~Guard() { unmask(signo); }
        private:
          type signo;
      };
    private:
      typedef std::vector<Notifier *> nlist_t;
      typedef std::map<int, nlist_t> dict_t;

      static void notify(type);
      friend void sighandler (int signo);
      static void *run(void *);
      static dict_t notifiers;
      static Thread::Queue<type> queue;
      static Thread server;
  };

} // namespace

#endif
