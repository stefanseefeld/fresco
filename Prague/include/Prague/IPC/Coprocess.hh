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
#ifndef _Coprocess_hh
#define _Coprocess_hh

#include <Prague/Sys/Signal.hh>
#include <Prague/Sys/Timer.hh>
#include <Prague/Sys/Thread.hh>
#include <Prague/IPC/Agent.hh>
#include <string>
#include <vector>

namespace Prague
{

class Coprocess : public Agent
{
  typedef vector<Coprocess *> plist_t;
//   class Timeout;
  struct Reaper : Signal::Notifier { virtual void notify(int);};
  friend struct Reaper;
//   struct Timeout : Timer::Notifier
//   {
//     Timeout(Coprocess *p) : process(p) {}
//     virtual void notify() { process->timeout();}
//     Coprocess *process;
//   };
//   friend class Timeout;
public:
  struct IONotifier
  {
    virtual ~IONotifier(){}
    virtual bool notify(iomask_t) = 0;
  };
  struct EOFNotifier
  {
    virtual ~EOFNotifier(){}
    virtual void notify(iomask_t) = 0;
  };
  enum state_t {ready, running, exited, signaled};
  Coprocess(const string &, IONotifier *, EOFNotifier * = 0);
  virtual      ~Coprocess();
  virtual void start();
  virtual void stop();
  const string &command() const { return path;}
  pid_t         pid() const { MutexGuard guard(mutex); return id;}
  state_t       state() const { MutexGuard guard(mutex); return _state;}
  virtual ipcbuf *ibuf() { return inbuf;}
  virtual ipcbuf *obuf() { return outbuf;}
  virtual ipcbuf *ebuf() { return errbuf;}
protected:
  virtual bool processIO(int, iomask_t);
  virtual void notifyStateChange(int) = 0;
//   int          &terminateTimeOut()	 { return termTout; }
//   int          &hangupTimeOut()	         { return hupTout; }
//   int          &killTimeOut()		 { return killTout; }
//   int           terminateTimeOut() const { return termTout; }
//   int           hangupTimeOut()	const    { return hupTout; }
//   int           killTimeOut()	const	 { return killTout; }

  void  terminate(bool flag = false);
  void  shutdown(short);  
//   virtual void  abort();
//   virtual void  wait();
//   virtual bool  pending();

  
protected:
//   virtual void  NewStatus(int);
//   void          initTimer() { if (!timer) timer = new Timer(&tnotifier);}
  string       path;
  IONotifier  *ioNotifier;
  EOFNotifier *eofNotifier;
  pid_t        id;
  state_t      _state;
  ipcbuf      *inbuf;
  ipcbuf      *outbuf;
  ipcbuf      *errbuf;
//   bool running();
//   void Error(const string &msg, bool flag)         {};//{ Notify(Signal::panic, msg); if (flag) running();}
//   void Warning(const string &msg, bool flag)       {};//{ Notify(Signal::strange, msg); if (flag) running();}
//   void SystemError(const string &msg, bool flag)   {};//{ Notify(Signal::panic, msg + ": " + strerror(errno)); if (flag) running();}
//   void SystemWarning(const string &msg, bool flag) {};//{ Notify(Signal::strange, msg + ": " + strerror(errno)); if (flag) running();}
private:
  Coprocess(const Coprocess &);
  Coprocess &operator = (const Coprocess &);
//   void  DefaultHandler(const char *);
  void  timeout();
//   bool  beingTerminated : 1;
//   int   timermode       : 3;
//   int   termTout; 	// terminate TimeOut (in s)
//   int   hupTout;    	// hangup TimeOut (in s)
//   int   killTout;      	// kill TimeOut (in s)
//   void  waitToTerminate();
//   virtual void  outputEOF();
//   virtual void  errorEOF();
  
  void kill(int);
private:
  static plist_t processes;
  static Reaper  reaper;
  static Mutex   mutex;
//   Timeout tout;
//   Timer timer;
};

};

#endif /* _Coprocess_hh */
