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
#ifndef _CommandKit_StreamBufferImpl_hh
#define _CommandKit_StreamBufferImpl_hh

#include <Prague/Sys/Thread.hh>
#include <Fresco/config.hh>
#include <Fresco/StreamBuffer.hh>
#include <Berlin/SubjectImpl.hh>
#include <vector>

namespace Berlin
{
  namespace CommandKit
  {
    class StreamBufferImpl : public virtual POA_Fresco::StreamBuffer,
                             public SubjectImpl
    {
      public:
        StreamBufferImpl(long l) : my_length(l)
    { my_buffer.reserve(my_length); }
        virtual ~StreamBufferImpl() { }
        virtual CORBA::Long size();
        virtual CORBA::Long available();
        virtual Fresco::StreamBuffer::Data *read();
        virtual void write(const Fresco::StreamBuffer::Data &);
        virtual void flush();
      private:
        size_t my_length;
        std::vector<CORBA::Octet> my_buffer;
        Prague::Mutex my_mutex;
    };

  } // namespace
} // namespace

#endif
