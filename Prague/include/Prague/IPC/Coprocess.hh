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

#include <Prague/Sys/Timer.hh>
#include <Prague/IPC/Agent.hh>
#include <string>

namespace Prague
{

class Coprocess : public Agent
{
  struct Timeout : public Timer::Notifier
  {
    Timeout(Coprocess *a) : agent(a) {}
    virtual void notify() { agent->timeout();}
    Coprocess *agent;
  };
  friend class Timeout;
public:
  Coprocess(Notifier *, const string &);
  Coprocess(const Coprocess &);
  virtual        ~Coprocess();
  virtual pid_t   PID() const { return pid;}
  const string   &command() const { return path;} 
  virtual ipcbuf *ibuf() { return inbuf;}
  virtual ipcbuf *obuf() { return outbuf;}
  virtual ipcbuf *ebuf() { return errbuf;}
  virtual int     IFD() const { return inbuf ? inbuf->fd() : -1;}
  virtual int     OFD() const { return outbuf ? outbuf->fd() : -1;}
  virtual int     EFD() const { return errbuf ? errbuf->fd() : -1;}

  int          &terminateTimeOut()	 { return termTout; }
  int          &hangupTimeOut()	         { return hupTout; }
  int          &killTimeOut()		 { return killTout; }
  int           terminateTimeOut() const { return termTout; }
  int           hangupTimeOut()	const    { return hupTout; }
  int           killTimeOut()	const	 { return killTout; }
  int           Status() const	         { return status; }

  virtual void  terminate(bool flag = false);
  virtual void  abort();
  virtual void  wait();
  virtual bool  pending();
  virtual void  dispatchpending();
protected:
  virtual void  NewStatus(int);
  void          initTimer() { if (!timer) timer = new Timer(&tnotifier);}
  pid_t         pid;
  const string  path;
  ipcbuf       *inbuf;
  ipcbuf       *outbuf;
  ipcbuf       *errbuf;
  bool running();
  void Error(const string &msg, bool flag)         {};//{ Notify(Signal::panic, msg); if (flag) running();}
  void Warning(const string &msg, bool flag)       {};//{ Notify(Signal::strange, msg); if (flag) running();}
  void SystemError(const string &msg, bool flag)   {};//{ Notify(Signal::panic, msg + ": " + strerror(errno)); if (flag) running();}
  void SystemWarning(const string &msg, bool flag) {};//{ Notify(Signal::strange, msg + ": " + strerror(errno)); if (flag) running();}
private:
//   void  DefaultHandler(const char *);
  void  timeout();
  bool  beingTerminated : 1;
  int   timermode       : 3;
  int   termTout; 	// terminate TimeOut (in s)
  int   hupTout;    	// hangup TimeOut (in s)
  int   killTout;      	// kill TimeOut (in s)
  void  waitToTerminate();
  void  shutdown(short);  
  virtual void  outputEOF();
  virtual void  errorEOF();
  
  void kill(int);
private:
  Timer *timer;
  Timeout tnotifier;
};

};

#endif /* _Coprocess_hh */
