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
#include <Command/VisualTextBufferImpl.hh>
#include <iostream>

using namespace Prague;
using namespace Warsaw;

TextBufferImpl::TextBufferImpl() : _visual(0) {
  Prague::Trace trace("TextBufferImpl::TextBufferImpl()");
}
TextBufferImpl::~TextBufferImpl() {
  Prague::Trace trace("TextBufferImpl::~TextBufferImpl()");
}

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
  Warsaw::TextBuffer::Change ch;
  {
      Prague::Guard<Mutex> guard(_mutex);
      if (p < 0 || p > _buffer.size()) return;
      _buffer.position(p);
      ch.pos = _buffer.position();
  }
  ch.len = 0;
  ch.type = Warsaw::TextBuffer::cursor;
  ch.visual = 0;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::forward()
{
  Prague::Trace trace("TextBufferImpl::forward()");
  Warsaw::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (_buffer.position() >= _buffer.size()) return;
    _buffer.forward();
    ch.pos = _buffer.position();
  }
  ch.len = 0;
  ch.type = Warsaw::TextBuffer::cursor;
  ch.visual = 0;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::backward()
{
  Prague::Trace trace("TextBufferImpl::backward()");
  Warsaw::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    if (_buffer.position() <= 0) return;
    _buffer.backward();
    ch.pos = _buffer.position();
  }
  ch.len = 0;
  ch.type = Warsaw::TextBuffer::cursor;
  ch.visual = 0;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::shift(CORBA::Long d)
{
  Prague::Trace trace("TextBufferImpl::size()");
  Warsaw::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    _buffer.shift(d);
    ch.pos = _buffer.position();
  }
  ch.len = 0;
  ch.type = Warsaw::TextBuffer::cursor;
  ch.visual = 0;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::insert_char(Unichar u)
{
  Prague::Trace trace("TextBufferImpl::insert_char(...)");
  Warsaw::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    ch.pos = _buffer.position();
    _buffer.insert(u);
  }
  ch.len = 1;
  ch.type = Warsaw::TextBuffer::insert;
  ch.visual = 0;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::insert_string(const Unistring &s)
{
  Prague::Trace trace("TextBufferImpl::insert_string(...)");
  if (s.length() == 0) return;

  Warsaw::TextBuffer::Change ch;  
  ch.len = s.length();
  Unichar u[ch.len];
  for (long i = 0; i < ch.len; i++) u[i] = s[i];

  {
    Prague::Guard<Mutex> guard(_mutex);
    ch.pos = _buffer.position();
    _buffer.insert(u,ch.len);
  }

  ch.type = Warsaw::TextBuffer::insert;
  ch.visual = 0;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::remove_backward(CORBA::ULong n)
{
  Prague::Trace trace("TextBufferImpl::remove_backward(...)");
  Warsaw::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    ch.pos = _buffer.position();
    n = std::min(n, ch.pos);
    if (n == 0) return;
    _buffer.remove_backward(n);
  }
  ch.len = -n;
  ch.type = Warsaw::TextBuffer::remove;
  ch.visual = 0;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::remove_forward(CORBA::ULong n)
{
  Prague::Trace trace("TextBufferImpl::remove_forward(...)");
  Warsaw::TextBuffer::Change ch;  
  {
    Prague::Guard<Mutex> guard(_mutex);
    ch.pos = _buffer.position();
    n = std::min(n, _buffer.size() - ch.pos);
    if (n == 0) return;
    _buffer.remove_forward(n);
  }
  ch.len = n;
  ch.type = Warsaw::TextBuffer::remove;
  ch.visual = 0;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

void TextBufferImpl::clear() {
  Prague::Trace trace("TextBufferImpl::clear()");
  Warsaw::TextBuffer::Change ch;
  ch.type = Warsaw::TextBuffer::remove;
  {
      Prague::Guard<Mutex> guard(_mutex);
      ch.len = _buffer.size();
      ch.pos = 0;
      _buffer.clear_buffer();
  }
  ch.visual = 0;

  CORBA::Any any;
  any <<= ch;
  notify(any);
}

Warsaw::TextBuffer::StringOrder TextBufferImpl::order() {
  Prague::Trace trace("TextBufferImpl::order()");
  return Warsaw::TextBuffer::memory_order;
}


TextBuffer_ptr TextBufferImpl::get_memory_buffer() {
  Prague::Trace trace("TextBufferImpl::get_memory_buffer()");
  return _this();
}

TextBuffer_ptr TextBufferImpl::get_visual_buffer() {
  Prague::Trace trace("TextBufferImpl::get_visualbuffer()");
  if (!_visual) {
      VisualTextBufferImpl * visual = new VisualTextBufferImpl(this);
      Prague::Guard<Mutex> guard(_mutex);
      _visual = visual;
      activate(_visual);
  }
  return _visual->_this();
}
