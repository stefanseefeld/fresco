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

#include <Command/TextBufferImpl.hh>
#include <iostream>

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

Unistring *TextBufferImpl::getChars(CORBA::ULong pos, CORBA::ULong len)
{
  MutexGuard guard(mutex);
  CORBA::ULong fin = buffer.size();
  CORBA::ULong start = pos > fin ? fin : pos;
  CORBA::ULong end = start + len > fin ? fin : start + len;
  Unistring *us = new Unistring(end-start, end-start, const_cast<Unichar *>(buffer.get() + start), false);
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
  TextBuffer::Change ch;  
  {
    MutexGuard guard(mutex);
    buffer.forward();
    ch.pos = buffer.position();
  }
  ch.len = 0;
  ch.type = cursor;
  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::backward()
{
  TextBuffer::Change ch;  
  {
    MutexGuard guard(mutex);
    buffer.backward();
    ch.pos = buffer.position();
  }
  ch.len = 0;
  ch.type = cursor;
  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::shift(CORBA::Long d)
{
  TextBuffer::Change ch;  
  {
    MutexGuard guard(mutex);
    buffer.shift(d);
    ch.pos = buffer.position();
  }
  ch.len = 0;
  ch.type = cursor;
  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::insertChar(Unichar u)
{
  TextBuffer::Change ch;  
  {
    MutexGuard guard(mutex);
    ch.pos = buffer.position();
    buffer.insert(u);
  }
  ch.len = 1;
  ch.type = insert;
  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::insertString(const Unistring &s)
{
  TextBuffer::Change ch;  
  ch.len = s.length();
  Unichar u[ch.len];
  for (long i = 0; i < ch.len; i++) u[i] = s[i];

  {
    MutexGuard guard(mutex);
    ch.pos = buffer.position();
    buffer.insert(u,ch.len);
  }

  ch.type = insert;
  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::removeBackward(CORBA::Long n)
{
  TextBuffer::Change ch;  
  ch.len = -n;

  {
    MutexGuard guard(mutex);
    ch.pos = buffer.position();
    buffer.removeBackward(n);
  }

  ch.type = remove;
  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::removeForward(CORBA::Long n)
{
  TextBuffer::Change ch;  
  ch.len = n;

  {
    MutexGuard guard(mutex);
    ch.pos = buffer.position();
    buffer.removeForward(n);
  }
  ch.type = remove;
  CORBA::Any any;
  any <<= ch;
  notify(any);
}
