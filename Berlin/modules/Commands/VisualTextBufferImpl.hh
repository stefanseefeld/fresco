/*$Id$
 *
 * This source file is a part of the Berlin Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
 *               2001 Tobias Hunger <tobias@berlin-consortium.org>
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
#ifndef _VisualTextBufferImpl_hh
#define _VisualTextBufferImpl_hh

#include <Warsaw/config.hh>

#include <Warsaw/TextBuffer.hh>
#include <Berlin/SubjectImpl.hh>
#include <Berlin/ObserverImpl.hh>

#include <Prague/Sys/Thread.hh>

#include <Babylon/defs.hh>
#include <Babylon/String.hh>

class TextBufferImpl;

class VisualTextBufferImpl : public virtual POA_Warsaw::TextBuffer,
			     public SubjectImpl {
public:
    VisualTextBufferImpl(TextBufferImpl *);
    virtual ~VisualTextBufferImpl();
    virtual CORBA::ULong size();
    virtual Warsaw::Unistring *value();
    virtual Warsaw::Unistring *get_chars(CORBA::ULong, CORBA::ULong);
    virtual CORBA::ULong position();
    virtual void position(CORBA::ULong);
    virtual void forward();
    virtual void backward();
    virtual void shift(CORBA::Long d);
    virtual void insert_char(Warsaw::Unichar);
    virtual void insert_string(const Warsaw::Unistring &);
    virtual void remove_backward(CORBA::ULong);
    virtual void remove_forward(CORBA::ULong);
    virtual void clear();
    virtual Warsaw::TextBuffer::StringOrder order();
    virtual Warsaw::TextBuffer_ptr get_memory_buffer();
    virtual Warsaw::TextBuffer_ptr get_visual_buffer();
private:
    class Observer;
    friend class Observer;
    Observer * _observer;

    void update(const Warsaw::TextBuffer::ChangeType,
		const CORBA::ULong,
		const CORBA::Long);
    std::vector<Warsaw::TextBuffer::Change> insert(const CORBA::ULong,
						   const CORBA::Long);
    std::vector<Warsaw::TextBuffer::Change> remove(const CORBA::ULong,
						   const CORBA::Long);
    std::vector<Warsaw::TextBuffer::Change> cursor(const CORBA::ULong,
						   const CORBA::Long);
    CORBA::ULong current_position();

    TextBufferImpl * _memory;

    Babylon::Paragraphs _paragraphs;
    Babylon::Char_Mapping _vis2log;

    Prague::Mutex _mutex;
};

#endif
