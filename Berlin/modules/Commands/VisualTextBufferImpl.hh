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
#ifndef _VisualTextBufferImpl_hh
#define _VisualTextBufferImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Babylon/defs.hh>
#include <Babylon/String.hh>
#include <Fresco/config.hh>
#include <Fresco/TextBuffer.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/ObserverImpl.hh>

class TextBufferImpl;

class VisualTextBufferImpl : public virtual POA_Fresco::TextBuffer,
			     public SubjectImpl {
public:
    VisualTextBufferImpl(TextBufferImpl *);
    virtual ~VisualTextBufferImpl();
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
    class Observer;
    friend class Observer;
    Observer * _observer;

    void update(const Fresco::TextBuffer::ChangeType,
		const CORBA::ULong,
		const CORBA::Long);
    std::vector<Fresco::TextBuffer::Change> insert(const CORBA::ULong,
						   const CORBA::Long);
    std::vector<Fresco::TextBuffer::Change> remove(const CORBA::ULong,
						   const CORBA::Long);
    std::vector<Fresco::TextBuffer::Change> cursor(const CORBA::ULong,
						   const CORBA::Long);
    CORBA::ULong current_position();

    TextBufferImpl * _memory;

    Babylon::Paragraphs _paragraphs;
    Babylon::Char_Mapping _vis2log;

    Prague::Mutex _mutex;
};

#endif
