/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
 *               2001 Tobias Hunger <tobias@fresco.org>
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
#ifndef _TextBufferImpl_hh
#define _TextBufferImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/TextBuffer.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/GapBuffer.hh>

class VisualTextBufferImpl;

class TextBufferImpl : public virtual POA_Fresco::TextBuffer,
		       public SubjectImpl
{
public:
    friend class VisualTextBufferImpl;

    TextBufferImpl();
    virtual ~TextBufferImpl();
    virtual CORBA::ULong size();
    virtual Fresco::Unistring *value();
    virtual Fresco::Unistring *get_chars(CORBA::ULong, CORBA::ULong);
    virtual CORBA::ULong position();
    virtual void position(CORBA::ULong);
    virtual void forward();
    virtual void backward();
    virtual void shift(CORBA::Long d);
    virtual void insert_char(Fresco::Unichar);
    virtual void insert_string(const Fresco::Unistring &);
    virtual void remove_backward(CORBA::ULong);
    virtual void remove_forward(CORBA::ULong);
    virtual void clear();
    virtual Fresco::TextBuffer::StringOrder order();
    virtual Fresco::TextBuffer_ptr get_memory_buffer();
    virtual Fresco::TextBuffer_ptr get_visual_buffer();
private:
    GapBuffer<Fresco::Unichar, 32> _buffer;
    Prague::Mutex _mutex;
    VisualTextBufferImpl * _visual;
};

#endif
