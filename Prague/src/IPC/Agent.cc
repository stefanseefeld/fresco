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
#include "Prague/IPC/Agent.hh"
#include "Prague/IPC/Dispatcher.hh"

using namespace Prague;

Agent::Agent()
  : iomask(none), running(false)
{}


Agent::~Agent()
{
  if (running)
    Dispatcher::instance()->release(this);
  running = false;
}

void Agent::start()
{
  running = true;
  if (iomask & in && ibuf()) Dispatcher::instance()->bind(this, ibuf()->fd(), in);
  if (iomask & out && obuf()) Dispatcher::instance()->bind(this, obuf()->fd(), out);
  if (iomask & err && ebuf()) Dispatcher::instance()->bind(this, ebuf()->fd(), err);
}

void Agent::mask(short m)
{
  if (iomask == m) return;
  if (running)
    {
      if ((iomask ^ m) & in)
	if (iomask & in && ibuf()) Dispatcher::instance()->release(this, ibuf()->fd());
	else  Dispatcher::instance()->bind(this, ibuf()->fd(), in);
      if ((iomask ^ m) & out)
	if (iomask & out && obuf()) Dispatcher::instance()->release(this, obuf()->fd());
	else  Dispatcher::instance()->bind(this, obuf()->fd(), out);
      if ((iomask ^ m) & err)
	if (iomask & err && ebuf()) Dispatcher::instance()->release(this, ebuf()->fd());
	else  Dispatcher::instance()->bind(this, ebuf()->fd(), err);
    }
  iomask = m;
}

void Agent::stop()
{
  mask(none);
  Dispatcher::instance()->release(this);
  running = false;
}
