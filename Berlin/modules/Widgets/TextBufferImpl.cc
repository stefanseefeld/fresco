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

#include <Widget/TextBufferImpl.hh>

using namespace Prague;

TextBufferImpl::TextBufferImpl() {}
TextBufferImpl::~TextBufferImpl() {}

CORBA::Long TextBufferImpl::size()
{
  MutexGuard guard(mutex);
  return buffer.size();
}

Unistring *TextBufferImpl::value()
{
  MutexGuard guard(mutex);
  Unistring *us = new Unistring(buffer.size(), buffer.size(), const_cast<Unichar *>(buffer.get()), false);
  return us;
}

CORBA::Long TextBufferImpl::position()
{
  MutexGuard guard(mutex);
  return buffer.position();
}

void TextBufferImpl::position(CORBA::Long p)
{
  MutexGuard guard(mutex);
  buffer.position(p);
}

void TextBufferImpl::forward()
{
  MutexGuard guard(mutex);
  buffer.forward();
}

void TextBufferImpl::backward()
{
  MutexGuard guard(mutex);
  buffer.backward();
}

void TextBufferImpl::shift(CORBA::Long d)
{
  MutexGuard guard(mutex);
  buffer.shift(d);
}

void TextBufferImpl::insertChar(Unichar u)
{
  {
    MutexGuard guard(mutex);
    buffer.insert(u);
  }
  CORBA::Any any;
  notify(any);
}

void TextBufferImpl::insertString(const Unistring &s)
{
  {
    MutexGuard guard(mutex);
    //   buffer.insert(s);
  }
  CORBA::Any any;
  notify(any);
}

void TextBufferImpl::removeBackward(CORBA::Long n)
{
  {
    MutexGuard guard(mutex);
    buffer.removeBackward(n);
  }
  CORBA::Any any;
  notify(any);
}

void TextBufferImpl::removeForward(CORBA::Long n)
{
  {
    MutexGuard guard(mutex);
    buffer.removeForward(n);
  }
  CORBA::Any any;
  notify(any);
}
