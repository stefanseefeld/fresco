/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
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

#include "TextBufferImpl.hh"
#include <iostream>

using namespace Prague;
using namespace Fresco;

TextBufferImpl::TextBufferImpl() { }
TextBufferImpl::~TextBufferImpl() { }

CORBA::ULong TextBufferImpl::size()
{
  Prague::Trace trace("TextBufferImpl::size()");
  Prague::Guard<Mutex> guard(_mutex);
  return _buffer.size();
}

Unistring *TextBufferImpl::value()
{
  Prague::Trace trace("TextBufferImpl::value()");
  Prague::Guard<Mutex> guard(_mutex);
  Unistring *us = new Unistring(_buffer.size(), _buffer.size(), const_cast<Unichar *>(_buffer.get()), false);
  return us;
}

Unistring *TextBufferImpl::get_chars(CORBA::ULong pos, CORBA::ULong len)
{
  Prague::Trace trace("TextBufferImpl::get_chars(...)");
  Prague::Guard<Mutex> guard(_mutex);
  CORBA::ULong fin = _buffer.size();
  CORBA::ULong start = pos > fin ? fin : pos;
  CORBA::ULong end = start + len > fin ? fin : start + len;
  Unistring *us = new Unistring(end-start, end-start, const_cast<Unichar *>(_buffer.get() + start), false);
  return us;
}


CORBA::ULong TextBufferImpl::position()
{
  Prague::Trace trace("TextBufferImpl::position()");
  Prague::Guard<Mutex> guard(_mutex);
  return _buffer.position();
}

void TextBufferImpl::position(CORBA::ULong p)
{
  Prague::Trace trace("TextBufferImpl::position(...)");
  Fresco::TextBuffer::Change ch;
  {
      Prague::Guard<Mutex> guard(_mutex);
      if (p < 0 || p > _buffer.size()) return;
      _buffer.position(p);
      ch.pos = _buffer.position();
  }
  ch.len = 0;
  ch.type = Fresco::TextBuffer::cursor;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::forward()
{
  Prague::Trace trace("TextBufferImpl::forward()");
  Fresco::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (_buffer.position() >= _buffer.size()) return;
    _buffer.forward();
    ch.pos = _buffer.position();
  }
  ch.len = 0;
  ch.type = Fresco::TextBuffer::cursor;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::backward()
{
  Prague::Trace trace("TextBufferImpl::backward()");
  Fresco::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (_buffer.position() <= 0) return;
    _buffer.backward();
    ch.pos = _buffer.position();
  }
  ch.len = 0;
  ch.type = Fresco::TextBuffer::cursor;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::shift(CORBA::Long d)
{
  Prague::Trace trace("TextBufferImpl::size()");
  Fresco::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    _buffer.shift(d);
    ch.pos = _buffer.position();
  }
  ch.len = 0;
  ch.type = Fresco::TextBuffer::cursor;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::insert_char(Unichar u)
{
  Prague::Trace trace("TextBufferImpl::insert_char(...)");
  Fresco::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    ch.pos = _buffer.position();
    _buffer.insert(u);
  }
  ch.len = 1;
  ch.type = Fresco::TextBuffer::insert;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::insert_string(const Unistring &s)
{
  Prague::Trace trace("TextBufferImpl::insert_string(...)");
  if (s.length() == 0) return;

  Fresco::TextBuffer::Change ch;  
  ch.len = s.length();
  Unichar u[ch.len];
  for (long i = 0; i < ch.len; i++) u[i] = s[i];

  {
    Prague::Guard<Mutex> guard(_mutex);
    ch.pos = _buffer.position();
    _buffer.insert(u,ch.len);
  }

  ch.type = Fresco::TextBuffer::insert;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::remove_backward(CORBA::ULong n)
{
  Prague::Trace trace("TextBufferImpl::remove_backward(...)");
  Fresco::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    ch.pos = _buffer.position();
    n = std::min(n, ch.pos);
    if (n == 0) return;
    _buffer.remove_backward(n);
  }
  ch.len = -n;
  ch.type = Fresco::TextBuffer::remove;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::remove_forward(CORBA::ULong n)
{
  Prague::Trace trace("TextBufferImpl::remove_forward(...)");
  Fresco::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    ch.pos = _buffer.position();
    n = std::min(n, _buffer.size() - ch.pos);
    if (n == 0) return;
    _buffer.remove_forward(n);
  }
  ch.len = n;
  ch.type = Fresco::TextBuffer::remove;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::clear() {
  Prague::Trace trace("TextBufferImpl::clear()");
  Fresco::TextBuffer::Change ch;
  ch.type = Fresco::TextBuffer::remove;
  {
      Prague::Guard<Mutex> guard(_mutex);
      ch.len = _buffer.size();
      ch.pos = 0;
      _buffer.clear_buffer();
  }

  CORBA::Any any;
  any <<= ch;
  notify(any);
}
