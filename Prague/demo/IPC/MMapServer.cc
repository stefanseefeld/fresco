/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

#include <Prague/Sys/File.hh>
#include <Prague/Sys/Process.hh>
#include <Prague/Sys/User.hh>
#include <Prague/IPC/mmapbuf.hh>
#include <unistd.h>

using namespace Prague;

int main (int argc, char **argv)
{
  File file = File::tmp();
  string name = file.long_name();
  streambuf *mbuf = new mmapbuf(name, 1024*1024, ios::out);
  ostream os(mbuf);
  os << "hi there ! from process " << Process::id() << '\n';
  cout << "tmp file : " << name << endl;
  sleep(10);
  delete mbuf;
  file.rm();
}
