/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#ifndef _Prague_SocketAgent_hh
#define _Prague_SocketAgent_hh

#include <Prague/IPC/Agent.hh>
#include <Prague/IPC/sockbuf.hh>

namespace Prague
{

class SocketAgent : public Agent
{
public:
  SocketAgent(sockbuf *);
  virtual         ~SocketAgent();
  virtual sockbuf *ibuf() { return _socket;}
  virtual sockbuf *obuf() { return _socket;}
  virtual sockbuf *ebuf() { return 0;}
private:
  virtual void done(int, iomask_t) { stop();}
  sockbuf *_socket;
};

};

#endif
