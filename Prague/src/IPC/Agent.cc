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
#include "Prague/IPC/Agent.hh"
#include <string>

using namespace Prague;

/* @Method{Agent::Agent(Agent::Notifier *n)}
 *
 * @Description{}
 */
Agent::Agent(Agent::Notifier *n)
  : notifier(n), mask(panic|strange|died), active(false), bound(false)
{
};

/* @Method{Agent::Agent(const Agent &A)}
 *
 * @Description{}
 */
Agent::Agent(const Agent &A)
  : notifier(A.notifier), mask(panic|strange|died), active(true), bound(false)
{
  notify(started);
};

/* @Method{Agent::~Agent()}
 *
 * Description{}
 */
Agent::~Agent()
{
  if (bound)
    {
//       AsyncManager *manager = AsyncManager::Instance();
//       manager->release(this);
    }
};

/* @Method{void Agent::setMask(short mask)}
 *
 * @Description{}
 */
void Agent::setMask(short m)
{
//   AsyncManager *manager = 0;
  bool b = bound;
  if (b)
    {
//       manager = AsyncManager::Instance();
//       manager->release(this);
    }
  mask = m;
//   if (b) manager->bind(this);
};

/* @Method{void Agent::notify(short msg)}
 *
 * @Description{call the specific Notify handler, if the signal passes the filter mask}
 */
void Agent::notify(short signal)
{
  signal &= mask;
  if (signal && notifier) notifier->notify(signal);
};
