/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org>
 * http://www.fresco.org
 *
 * this file defines a C++ interface to zlib
 * written by Kevin Ruland <kevin@rodin.wustl.edu>
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
#include "Prague/Filter/gzbuf.hh"
#include <memory.h>
#include <cstdio>

using namespace Prague;

gzbuf::gzbuf() : _file(0), _mode(0), _owner(false), _buf(new char[BUFSIZ]) { }
gzbuf::~gzbuf()
{
    sync();
    delete _buf;
    if (_owner) close();
}

gzbuf *gzbuf::open(const char *name, int io_mode)
{
    if (is_open()) return 0;
    char char_mode[10];
    char *p;
    memset(char_mode, '\0', 10);
    p = char_mode;
    if (io_mode & std::ios::in)
    {
        _mode = std::ios::in;
        *p++ = 'r';
    }
    else if (io_mode & std::ios::app)
    {
        _mode = std::ios::app;
        *p++ = 'a';
    }
    else
    {
        _mode = std::ios::out;
        *p++ = 'w';
    }
    if (io_mode & std::ios::binary)
    {
        _mode |= std::ios::binary;
        *p++ = 'b';
    }
    // Hard code the compression level
    if (io_mode & (std::ios::out|std::ios::app))
        *p++ = '9';
    if ((_file = gzopen(name, char_mode)) == 0) return 0;
    _owner = true;
    return this;
}

gzbuf *gzbuf::attach(int fd, int io_mode)
{
    if (is_open()) return 0;
    char char_mode[10];
    char *p;
    memset(char_mode,'\0',10);
    p = char_mode;
    if (io_mode & std::ios::in)
    {
        _mode = std::ios::in;
        *p++ = 'r';
    }
    else if (io_mode & std::ios::app)
    {
        _mode = std::ios::app;
        *p++ = 'a';
    }
    else
    {
        _mode = std::ios::out;
        *p++ = 'w';
    }
    if (io_mode & std::ios::binary)
    {
        _mode |= std::ios::binary;
        *p++ = 'b';
    }
    // Hard code the compression level
    if (io_mode & (std::ios::out|std::ios::app))
        *p++ = '9';
    if ((_file = gzdopen(fd, char_mode)) == 0) return 0;
    _owner = false;
    return this;
}

gzbuf *gzbuf::close()
{
    if (is_open())
    {
        sync();
        gzclose(_file);
        _file = 0;
    }
    return this;
}

int gzbuf::setcompressionlevel(short comp_level)
{ return gzsetparams(_file, comp_level, -2); }

int gzbuf::setcompressionstrategy(short comp_strategy)
{ return gzsetparams(_file, -2, comp_strategy); }

std::streampos gzbuf::seekoff(std::streamoff off, std::ios::seekdir dir, int which)
{ return std::streampos(EOF); }

int gzbuf::underflow()
{
    // If the file hasn't been opened for reading, error.
    if (!is_open() || !(_mode & std::ios::in)) return EOF;
    // if a buffer doesn't exists, allocate one.
    if (in_avail()) return (unsigned char) *gptr();
    // Attempt to fill the buffer.
    int result = fillbuf();
    if (result == EOF)
    {
        // disable get area
        setg(0,0,0);
        return EOF;
    }
    return (unsigned char) *gptr();
}

int gzbuf::overflow(int c)
{
    if (!is_open() || !(_mode & std::ios::out)) return EOF;
    if (pptr() - pbase())
    {
        if (flushbuf() == EOF) return EOF;
    }
    setp(_buf, _buf + BUFSIZ);
    if (c != EOF)
    {
        *pptr() = c;
        pbump(1);
    }
    return 0;
}

int gzbuf::sync()
{
    if (!is_open()) return EOF;
    if (pptr() - pbase()) return flushbuf();
    return 0;
}

int gzbuf::flushbuf()
{
    int n;
    char *q;
    q = pbase();
    n = pptr() - q;
    if (gzwrite(_file, q, n) < n) return EOF;
    setp(0, 0);
    return 0;
}

int gzbuf::fillbuf()
{
    int t = gzread(_file, _buf, BUFSIZ);
    if (t <= 0) return EOF;
    setg(_buf, _buf, _buf + t);
    return t;
}
