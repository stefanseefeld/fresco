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

CORBA::Long TextBufferImpl::size()
{
  MutexGuard guard(myMutex);
  return buffer.size();
}

CORBA::Long TextBufferImpl::position()
{
  MutexGuard guard(myMutex);
  return buffer.position();
}

void TextBufferImpl::position(CORBA::Long p)
{
  MutexGuard guard(myMutex);
  buffer.position(p);
}

void TextBufferImpl::forward()
{
  MutexGuard guard(myMutex);
  buffer.forward();
}

void TextBufferImpl::backward()
{
  MutexGuard guard(myMutex);
  buffer.backward();
}

void TextBufferImpl::shift(CORBA::Long d)
{
  MutexGuard guard(myMutex);
  buffer.shift(d);
}

void TextBufferImpl::insertChar(Unichar u)
{
  MutexGuard guard(myMutex);
  buffer.insert(u);
  notify();
}

void TextBufferImpl::insertString(const Unistring &s)
{
  MutexGuard guard(myMutex);
//   buffer.insert(s);
  notify();
}

void TextBufferImpl::removeLeft(CORBA::Long n)
{
  MutexGuard guard(myMutex);
  buffer.removeLeft(n);
  notify();
}

void TextBufferImpl::removeRight(CORBA::Long n)
{
  MutexGuard guard(myMutex);
  buffer.removeRight(n);
  notify();
}
