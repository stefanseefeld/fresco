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
#ifndef _Prague_Connector_hh
#define _Prague_Connector_hh

#include <Prague/IPC/SocketAgent.hh>

namespace Prague
{

/*
 * a Connector is an Agent that connects to
 * a specified sockaddr asynchronously
 */
template <typename Connection, typename Socket>
class Connector : public SocketAgent
{
public:
  Connector(Socket *socket, const typename Socket::address_type &peer)
    : SocketAgent(socket), _peer(peer) {}
  virtual Socket *ibuf() { return static_cast<Socket *>(SocketAgent::ibuf());}
  virtual Socket *obuf() { return static_cast<Socket *>(SocketAgent::obuf());}
  virtual void start();
private:
  virtual bool process(int, iomask_t);
  typename Socket::address_type _peer;
};

template <typename Connection, typename Socket>
void Connector<Connection, Socket>::start()
{
  Trace trace("Connector::start");
  mask(in);
  ibuf()->connect(_peer);
  SocketAgent::start();
}

template <typename Connection, typename Socket>
bool Connector<Connection, Socket>::process(int, iomask_t)
{
  Trace trace("Connector::process");
  int error = ibuf()->clearerror();
  if (!error)
    {
      Connection *connection = new Connection(new Socket(*ibuf()));
      connection->start();
      connection->remove_ref();
    }
  else clog << "connect: " << strerror(error) << endl;
  return false;
}

};

#endif
