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
#include <Prague/IPC/PipeAgent.hh>
#include <string>

using namespace Prague;

Agent *agent;

class Output : public Coprocess::IONotifier
{
public:
  virtual bool notify(Agent::iomask_t mask)
  {
    if (mask != Agent::outready) return false;
#if 0
    istream is(agent->obuf());
    char c;
    cout << "output : '";
    while (is.get(c)) cout.put(c);
    cout << '\'' << endl;
#else
    int c;
    cout << "output : '";
    while ((c = agent->obuf()->uflow()) != EOF) cout.put(c);
    cout << '\'' << endl;
#endif
    return true;
  }
};

class ConnectionClosed : public Coprocess::EOFNotifier
{
public:
  virtual void notify(Agent::iomask_t mask)
  {
    if (mask == Agent::outready)
      cout << "output : connection closed";
  }
};

int main (int argc, char **argv)
{
  Output *out = new Output;
  ConnectionClosed *eof = new ConnectionClosed;
  agent = new PipeAgent("./echo", out, eof);
  agent->start();
  ostream os(agent->ibuf());
  while (cin)
    {
      Thread::delay(500);
      string line;
      cout << "input :";
      getline(cin, line);
      os << line << endl;
    }
  delete agent;
  delete eof;
  delete out;
}