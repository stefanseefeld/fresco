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
#ifndef _Signal_hh
#define _Signal_hh

#include <signal.h>
#include <vector>
#include <map>

namespace Prague
{

class sigerr {};

/* @Class{Signal}
 *
 * @Description{a wrapper for the (POSIX) signal handling functions}
 */
class Signal 
{
public:
  class Notifier
    {
    public:
      virtual ~Notifier() {}
      virtual void notify(int) = 0;
    };
  enum type { hangup = SIGHUP, interrupt = SIGINT, quit = SIGQUIT, illegal = SIGILL,
	      trap = SIGTRAP, abort = SIGABRT, iotrap = SIGIOT, bus = SIGBUS, fpe = SIGFPE,
	      segv = SIGSEGV,
	      usr1 = SIGUSR1, usr2 = SIGUSR2, alarm = SIGALRM, terminate = SIGTERM, child = SIGCLD, io = SIGIO,
	      pipe = SIGPIPE, kill = SIGKILL};
  static bool set (int, Notifier *);
  static bool unset (int, Notifier *);
  static void unset (int);
  static void mask (int);
  static void mask (int, int);
  static void unmask (int);
  static void unmask (int, int);
  static bool ispending (int);
  static sigset_t pending ();
  static void sysresume (int, bool);
  static void notify (int);
  static char *Name(int);

  class Guard
  {
  public:
    Guard(int s) : signo(s) { mask(signo);}
    ~Guard() { unmask(signo);}
  private:
    int signo;
  };
private:
  friend void sighandler (int signo);
  typedef vector<Notifier *> NotifierList;
  typedef map<int, NotifierList *> Dictionary;
  static Dictionary notifiers;
};

};

#endif /* _Signal_hh */
