/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org>
 * Copyright (C) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 * Copyright (C) 2001 Bastian Blank <bastianb@gmx.de>
 * Copyright (C) 2003 Tobias Hunger <tobias@fresco.org>
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
#include <Prague/IPC/ptybuf.hh>
#include <cerrno>
#include <sstream>
#include <iostream>

using namespace Prague;

#if defined(HAVE__GETPTY) || defined(HAVE_OPENPTY)
#  undef HAVE_DEV_PTMX
#endif

#ifdef HAVE_PTY_H
#  include <pty.h>
#endif
#if defined(HAVE_DEV_PTMX) && defined(HAVE_SYS_STROPTS_H)
#  include <sys/stropts.h>
#endif

#if defined (HAVE_LIBUTIL_H)
#  include <libutil.h>
#endif

#if defined (HAVE_OPENPTY) || defined (BSD4_4)
#elif defined (HAVE__GETPTY)
#elif defined (HAVE_DEV_PTMX)
#elif defined (HAVE_DEV_PTS_AND_PTC)
#else
#  include <fcntl.h>
#endif

inline void throw_runtime_error(const std::string s) throw(std::runtime_error)
{
    throw std::runtime_error(s + ": " + strerror(errno));
}

//inline char ctrl(char c) { return c & 0x1f;}

ptybuf::ptybuf() :
  ipcbuf(std::ios::in | std::ios::out)
{ }

ptybuf::~ptybuf()
{
    if (my_tty != -1)
        close(my_tty);
}

std::streamsize ptybuf::sys_read(char *buf, std::streamsize len) throw(std::runtime_error)
{
    std::streamsize rval = -1;
    do
        rval = ::read(fd(), buf, len);
    while (rval == -1 && errno == EINTR);
    if (rval == -1 && errno == EIO) return 0;
    if (rval == -1 && errno != EAGAIN)
        throw_runtime_error("ptybuf::read failed");
}

int ptybuf::openpty() throw (std::runtime_error)
{
    if (fd() == -1)
      setup();
    return fd();
}

int ptybuf::opentty() throw (std::runtime_error)
{
    if (my_tty == -1)
        setup();
    return my_tty;
}

void ptybuf::setup() throw (std::runtime_error)
{
    int ttyfd;
    int ptyfd;

    std::cerr << "Trying to open PTY/TTY pair..." << std::endl;

#if defined(HAVE_OPENPTY) || defined(BSD4_4)
    // openpty(3) exists in OSF/1 and some other os'es
    std::cerr << "  using openpty." << std::endl;
    int i;

    i = ::openpty(&ptyfd, &ttyfd, NULL, NULL, NULL);
    if (i < 0) throw_runtime_error("Openpty failed");

    fd(ptyfd);
    my_tty = ttyfd;
    my_ptydev = ttyname(ptyfd);
#elif defined(HAVE__GETPTY)
    // _getpty(3) exists in SGI Irix 4.x, 5.x & 6.x -- it generates more
    // pty's automagically when needed
    std::cerr << "  using _getpty." << std::endl;

    char *name = _getpty(&ptyfd, O_RDWR, 0622, 0);
    if (!name) throw_runtime_error("_getpty failed")

    // Open the slave side.
    ttyfd = open(name, O_RDWR | O_NOCTTY);
    if (ttyfd < 0) throw_runtime_error("Failed to open");

    fd(ptyfd);
    my_tty = ttyfd;
    ptydev = name;
#elif defined(HAVE_DEV_PTMX)
    /*
     * This code is used e.g. on Solaris 2.x.  (Note that Solaris 2.3
     * also has bsd-style ptys, but they simply do not work.)
     */
    std::cerr << "  using ptmx." << std::endl;

    mysig_t old_signal;
    char *name;

    ptyfd = open("/dev/ptmx", O_RDWR | O_NOCTTY);
    if (ptyfd < 0) throw_runtime_error("Failed to open /dev/ptmx");

    old_signal = mysignal(SIGCHLD, SIG_DFL);

    if (grantpt(ptyfd) < 0)
    {
        close(ptyfd);
        throw_runtime_error("grantpt failed");
    }

    mysignal(SIGCHLD, old_signal);

    if (unlockpt(ptyfd) < 0)
    {
        close(ptyfd);
        throw_runtime_error("unlockpt failed");
    }

    // Open the slave side.
    ttyfd = open(name, O_RDWR | O_NOCTTY);
    if (ttyfd < 0) throw_runtime_error("Failed to open");

    fd(ptyfd);
    my_tty = ttyfd;
    my_ptydev = std::string(name);
#elif defined(HAVE_DEV_PTS_AND_PTC)
    /* AIX-style pty code. */
    std::cerr << "  using pts/ptc." << std::endl;

    ptyfd = open("/dev/ptc", O_RDWR | O_NOCTTY);
    if (ptyfd < 0) throw_runtime_error("Failed to open /dev/ptc");

    char *name = ttyname(ptyfd);

    ttyfd = open(name, O_RDWR | O_NOCTTY);
    if (ttyfd < 0)
    {
        close(ptyfd);
        throw_runtime_error("Failed to open "+name)
    }

    fd(ptyfd);
    my_tty = ttyfd;
    my_ptydev = name;
#else
    /* BSD-style pty code. */
    std::cerr << "  using BSD-style." << std::endl;

    std::stringstream buf1;
    std::stringstream buf2;
    const std::string ptymajors("pqrstuvwxyzabcdefghijklmnoABCDEFGHIJKLMNOPQRSTUVWXYZ");
    const std::string ptyminors("0123456789abcdef");
    int num_minors = ptyminors.length();
    int num_ptys = ptymajors.length() * num_minors;

    for (size_t i = 0; i < num_ptys; i++)
    {
        buf1.str("/dev/pty");
        buf1 << ptymajors[i / num_minors] << ptyminors[i % num_minors];
        buf2.str("/dev/tty");
        buf2 << ptymajors[i / num_minors] << ptyminors[i % num_minors];

        ptyfd = open(buf1.str().c_str(), O_RDWR | O_NOCTTY);
        if (ptyfd < 0)
        {
            /* Try SCO style naming */
            buf1.str("/dev/ptyp"); buf1 << i;
            buf2.str("/dev/ttyp"); buf2 << i;

            ptyfd = open(buf1.str().c_str(), O_RDWR | O_NOCTTY);
            if (ptyfd < 0) continue;
        }
        break; // found a master, get out of here!
    }

    /* Open the slave side. */
    ttyfd = open(buf2.str().c_str(), O_RDWR | O_NOCTTY);
    if (ttyfd < 0)
    {
        close(ptyfd);
        throw_runtime_error("Failed to open "+buf2.str());
    }

    fd(ptyfd);
    my_tty = ttyfd;
    my_ptydev = buf1.str();
#endif

    std::cerr << "Got TTY/PTY pair." << std::endl;
}
