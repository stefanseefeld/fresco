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
#include <Prague/IPC/Connector.hh>
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
    ostream os(ibuf());
    os << "hi there" << endl;
  }
  ~Connection() { Trace trace("Connection::~Connection"); running = false;}
private:
  virtual bool process(int, iomask)
  {
    Trace trace("Connection::process");
    istream is(obuf());
    string line;
    getline(is, line);
    cout << "server replied: " << line << endl;
    stop();
    return false;
  }
};

int main (int argc, char **argv)
{
  GetOpt getopt(argv[0], "an async (unix) socket client");
  getopt.add('h', "help", GetOpt::novalue, "help message");
  getopt.add('t', "trace", GetOpt::novalue, "switch tracing on");
  getopt.add('a', "address", GetOpt::mandatory, "peer address (path)");
  getopt.parse(argc, argv);
  string value;
  getopt.get("help", &value);
  if (value == "true")
    {
      getopt.usage();
      return 0;
    }
  value = "";
  getopt.get("trace", &value);
  if (value == "true") Tracer::logging(true);
  value = "";
  getopt.get("address", &value);
  if (value == "")
    {
      getopt.usage();
      return 1;
    }
  sockunixbuf *socket = new sockunixbuf(sockbuf::sock_stream);
  Agent *connector = new Connector<Connection, sockunixbuf>(socket, sockunixaddr(value));
  running = true;
  try
    {
      connector->start();
    }
  catch (const sockerr &e)
    {
      cerr << "error starting the Connector: " << e.errstr() << endl;
      running = false;
    }
  connector->remove_ref();
  while (running) sleep(1);
}
