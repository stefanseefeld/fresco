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

#include "StreamBufferImpl.hh"

using namespace Prague;
using namespace Fresco;

CORBA::Long Berlin::CommandKit::StreamBufferImpl::size()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_length;
}

CORBA::Long Berlin::CommandKit::StreamBufferImpl::available()
{
    Prague::Guard<Mutex> guard(my_mutex);
    return my_buffer.size();
}

void Berlin::CommandKit::StreamBufferImpl::write(const Fresco::StreamBuffer::Data &data)
{
    bool overflow = false;
    {
	Prague::Guard<Mutex> guard(my_mutex);
	CORBA::ULong l = data.length();
	CORBA::ULong s = my_buffer.size();
	if (s + l > my_buffer.capacity()) my_buffer.reserve(s + l);
	for (unsigned long i = 0; i != l; ++i)
	    my_buffer.push_back(data[i]);
	if (my_buffer.size() >= my_length) overflow = true;
    }
    if (overflow)
    {
	CORBA::Any any;
	notify(any);
    }
}

void Berlin::CommandKit::StreamBufferImpl::flush()
{
    bool overflow = false;
    {
	Prague::Guard<Mutex> guard(my_mutex);
	if (my_buffer.size()) overflow = true;
    }
    if (overflow)
    {
	CORBA::Any any;
	notify(any);
    }
}

Fresco::StreamBuffer::Data * Berlin::CommandKit::StreamBufferImpl::read()
{
    Guard<Mutex> guard(my_mutex);
    Fresco::StreamBuffer::Data_var data = new Fresco::StreamBuffer::Data;
    data->length(my_buffer.size());
    for (unsigned long i = 0; i != my_buffer.size(); ++i)
	data[i] = my_buffer[i];
    my_buffer.erase(my_buffer.begin(), my_buffer.end());
    my_buffer.reserve(my_length);
    return data._retn();
}
