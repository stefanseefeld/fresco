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
#include <unistd.h>

using namespace Prague;

struct Notifier : Coprocess::Notifier
{
  Notifier(const char *pre) : prefix(pre) {}
  virtual void notify(int i) { cout << prefix << ' ' << i << endl;}
  const char *prefix;
};

int main (int argc, char **argv)
{
  if (argc != 2)
    {
      cerr << "Usage : " << argv[0] << " <cmd>\n";
      exit(-1);
    }
  Notifier *exit = new Notifier("exit");
  Notifier *signal = new Notifier("signal");
  Notifier *stop = new Notifier("stop");
  PipeAgent *pipe = new PipeAgent(argv[1], exit, signal, stop);
  pipe->start();
  sleep(3);
//   Thread::delay(5000);
}
