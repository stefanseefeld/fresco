/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
#include <Prague/Sys/Tracer.hh>
#include <Prague/Sys/File.hh>
#include <Prague/Sys/GetOpt.hh>
#include <Prague/IPC/Acceptor.hh>
#include <string>
#include <unistd.h>

using namespace Prague;
bool running;

class Connection : public SocketAgent
{
public:
  Connection(sockbuf *socket) : SocketAgent(socket)
  {
    Trace trace("Connection::Connection");
  }
  ~Connection() { Trace trace("Connection::~Connection"); running = false;}
private:
  virtual bool process(int, iomask_t)
  {
    Trace trace("Connection::process");
    istream is(obuf());
    string line;
    getline(is, line);
    ostream os(ibuf());
    os << "welcome !" << endl;
    return false;
  }
};

int main (int argc, char **argv)
{
  GetOpt getopt(argv[0], "an async (unix) socket client");
  getopt.add('t', "trace", GetOpt::novalue, "switch tracing on");
  getopt.parse(argc, argv);
  string value;
  getopt.get("trace", &value);
  if (value == "true") Tracer::logging(true);
  sockunixbuf *socket = new sockunixbuf(sockbuf::sock_stream);
  string name = File::tmp();
  socket->bind(name);
  Agent *acceptor = new Acceptor<Connection>(socket);
  running = true;
  acceptor->start();
  acceptor->remove_ref();
  cout << "server is accepting connection requests at " << name << endl;
  while (running) sleep(1);
}
