/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
 * http://www.fresco.org
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
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/Tracer.hh>
#include "daVinci/RefCountBase.hh"

using namespace Prague;
using namespace Fresco;

static Mutex mutex;

namespace daVinci
{

RefCountBase::RefCountBase() : refcount(1) {}
RefCountBase::~RefCountBase() { Trace trace("RefCountBase::~RefCountBase");}
void RefCountBase::increment()
{
  Trace trace("RefCountBase::increment");
  Guard<Mutex> guard(mutex);
  refcount++;
}

void RefCountBase::decrement()
{
  Trace trace("RefCountBaseImpl::decrement");
  Guard<Mutex> guard(mutex);
  if (!--refcount) deactivate();
}
};
