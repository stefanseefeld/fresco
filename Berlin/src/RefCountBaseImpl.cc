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
#include <Prague/Sys/Thread.hh>
#include <Prague/Sys/Tracer.hh>
#include <Berlin/config.hh>
#include <Berlin/Logger.hh>
#include "Berlin/RefCountBaseImpl.hh"
#include <typeinfo>

using namespace Prague;
using namespace Warsaw;

namespace
{
  Mutex mutex;
};

RefCountBaseImpl::RefCountBaseImpl() : _refcount(1)
{
#ifdef LCLOG
  Logger::log(Logger::lifecycle) << "RefCountBaseImpl::RefCountBaseImpl: " << this << " constructed" << std::endl;
#endif
}

RefCountBaseImpl::~RefCountBaseImpl()
{
  Trace trace("RefCountBaseImpl::~RefCountBaseImpl");
#ifdef LCLOG
  Logger::log(Logger::lifecycle) << "RefCountBaseImpl::~RefCountBaseImpl: " << this << " destructed" << std::endl;
#endif
}

void RefCountBaseImpl::increment()
{
  Trace trace("RefCountBaseImpl::increment");
  Prague::Guard<Mutex> guard(mutex);
  ++_refcount;
#ifdef LCLOG
  Logger::log(Logger::lifecycle) << "RefCountBaseImpl::increment on " << this << " (" << typeid(*this).name() << "): new count is " << _refcount << std::endl;
#endif
}

void RefCountBaseImpl::decrement()
{
  Trace trace("RefCountBaseImpl::decrement");
  bool done;
  {
    Prague::Guard<Mutex> guard(mutex);
    done = --_refcount;
#ifdef LCLOG
    Logger::log(Logger::lifecycle) << "RefCountBaseImpl::decrement on " << this << " (" << typeid(*this).name() << "): new count is " << _refcount << std::endl;
#endif
  }
  if (done) return;
  else
    {
#ifdef LCLOG
      Logger::log(Logger::lifecycle) << "deactivating " << this << std::endl;
#endif
      deactivate();
    }
}

