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
#ifndef _Agent_hh
#define _Agent_hh

#include <Prague/Sys/Thread.hh>
#include <Prague/IPC/ipcbuf.hh>
#include <sys/types.h>

namespace Prague
{

/* @Class {Agent}
 *
 * @Description {the interface to the client part of an ipc connection}
 */
class Agent// : public Thread
{
public:
  struct Notifier { virtual ~Notifier(){}; virtual void notify(short) = 0;};
  enum signal {panic = 0x0100, strange = 0x0200, started = 0x0400, stopped = 0x0800,
	       outputeof = 0x1000, erroreof = 0x2000, died = 0x4000, newstatus = 0x8000};    
  enum iomask {outready = 0x01, inready = 0x02, errready = 0x04,
	       outexc = 0x10, inexc = 0x20, errexc = 0x40,
	       out = 0x11, in = 0x22, err = 0x44,
	       asyncio = 0xff};
  Agent(Notifier *);
  Agent(const Agent &);
  virtual        ~Agent();
  void            setMask(short);
  short           Mask() const { return mask;}
  virtual pid_t   PID() const { return -2;}
  virtual int     IFD() const = 0;
  virtual int     OFD() const = 0;
  virtual int     EFD() const = 0;
  virtual ipcbuf *ibuf() = 0;
  virtual ipcbuf *obuf() = 0;
  virtual ipcbuf *ebuf() = 0;

  virtual void  start() = 0;
  virtual bool  pending() = 0;
  virtual void  dispatchpending() = 0;
protected:
  void          notify(short);
  virtual void  notifyWhenIdle(short s) { notify(s);} // delayed Notify

//   virtual void  InputNotify() { notify(Message(this, inready));}
//   virtual void  OutputNotify() { notify(Message(this, outready));}
//   virtual void  ErrorNotify() { notify(Message(this, errready));}
//   virtual void  UrgentInputNotify() { notify(Message(this, inexc));}
//   virtual void  UrgentOutputNotify() { notify(Message(this, outexc));}
//   virtual void  UrgentErrorNotify() { notify(Message(this, errexc));}

  virtual void  NewStatus(int) {}
  bool          isactive() const { return active;}
  void          setactive() { if (!active) {active = true; notify(started);}}
  bool          isbound() const { return bound;}
  void          setbound() { bound = true;}
  void          kill(int) {}
  Notifier *notifier;
  short mask;
  bool  active          : 1;
  bool  bound           : 1;
  int   status;
private:
};

};

#endif /* _Agent_hh */
