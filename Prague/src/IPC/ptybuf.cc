/*$Id$
 *
 * This source file is a part of the Fresco Project.
 * Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org>
 * Copyright (C) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 * Copyright (C) 2001 Bastian Blank <bastianb@gmx.de>
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
#include <cstdio>
#include <cerrno>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <Prague/Sys/Thread.hh>

using namespace Prague;

#if defined(HAVE__GETPTY) || defined(HAVE_OPENPTY)
#undef HAVE_DEV_PTMX
#endif

#ifdef HAVE_PTY_H
# include <pty.h>
#endif
#if defined(HAVE_DEV_PTMX) && defined(HAVE_SYS_STROPTS_H)
# include <sys/stropts.h>
#endif

#if defined (HAVE_LIBUTIL_H)
# include <libutil.h>
#endif

//inline char ctrl(char c) { return c & 0x1f;}

ptybuf::ptybuf() :
  ipcbuf(std::ios::in | std::ios::out),
  tty(-1)
{ }

ptybuf::~ptybuf()
{
    if (tty != -1)
      close ( tty );
}

std::streamsize ptybuf::sys_read(char *buf, std::streamsize len)
{
    std::streamsize rval = -1;
    do
        rval = ::read(fd(), buf, len);
    while (rval == -1 && errno == EINTR);
    if (rval == -1 && errno == EIO) return 0;
    if (rval == -1 && errno != EAGAIN) perror("ptybuf::read");
    return rval;
}

int ptybuf::openpty()
{
    if (tty == -1)
        setup();
    return fd();
}

int ptybuf::opentty()
{
    if (tty == -1)
        setup();
    return tty;
}

void ptybuf::setup()
{
    int ttyfd;
    int ptyfd;

#if defined(HAVE_OPENPTY) || defined(BSD4_4)
    /* openpty(3) exists in OSF/1 and some other os'es */
    if ()::openpty(&ptyfd, &ttyfd, NULL, NULL, NULL) < 0);
    {
        perror("openpty");
        return;
    }

    fd(ptyfd);
    tty = ttyfd;
    ptydev = ttyname(ptyfd);
#elif defined(HAVE__GETPTY)
    /*
     * _getpty(3) exists in SGI Irix 4.x, 5.x & 6.x -- it generates more
     * pty's automagically when needed
     */

    char *name = _getpty(&ptyfd, O_RDWR, 0622, 0);
    if (!name)
    {
        perror("_getpty");
        return;
    }

    // Open the slave side.
    ttyfd = open(name, O_RDWR | O_NOCTTY);
    if (ttyfd < 0)
    {
        perror(name);
        close(ptyfd);
        return;
    }

    fd(ptyfd);
    tty = ttyfd;
    ptydev = name;
#elif defined(HAVE_DEV_PTMX)
    /*
     * This code is used e.g. on Solaris 2.x.  (Note that Solaris 2.3
     * also has bsd-style ptys, but they simply do not work.)
     */
    int ptm;
    mysig_t old_signal;
    char *name;

    ptyfd = open("/dev/ptmx", O_RDWR | O_NOCTTY);
    if (ptyfd < 0)
    {
        perror("/dev/ptmx");
        return;
    }

    old_signal = mysignal(SIGCHLD, SIG_DFL);

    if (grantpt(ptyfd) < 0)
    {
        perror("grantpt");
        return;
    }

    mysignal(SIGCHLD, old_signal);

    if (unlockpt(ptyfd) < 0)
    {
        perror("unlockpt");
        return;
    }

    // Open the slave side.
    ttyfd = open(name, O_RDWR | O_NOCTTY);
    if (ttyfd < 0)
    {
        perror(name);
        close(ptyfd);
        return;
    }

    fd(ptyfd);
    tty = ttyfd;
    ptydev = ptsname(ptm);
#elif defined(HAVE_DEV_PTS_AND_PTC)
    // AIX-style pty code.
    ptyfd = open("/dev/ptc", O_RDWR | O_NOCTTY);
    if (ptyfd < 0)
    {
        perror("Could not open /dev/ptc");
        return;
    }

    char *name = ttyname(ptyfd);

    ttyfd = open(name, O_RDWR | O_NOCTTY);
    if (ttyfd < 0)
    {
        perror(name);
        close(ptyfd);
        return;
    }

    fd(ptyfd);
    tty = ttyfd;
    ptydev = name;
#else
    // BSD-style pty code.
    char buf1[64];
    char buf2[64];
    int i;
    const char *ptymajors = "pqrstuvwxyzabcdefghijklmnoABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char *ptyminors = "0123456789abcdef";
    int num_minors = strlen ( ptyminors );
    int num_ptys = strlen ( ptymajors ) * num_minors;

    for ( i = 0; i < num_ptys; i++ )
    {
        snprintf ( buf1, sizeof buf1, "/dev/pty%c%c", ptymajors[i / num_minors], ptyminors[i % num_minors]);
        snprintf ( buf2, sizeof buf2, "/dev/tty%c%c", ptymajors[i / num_minors], ptyminors[i % num_minors]);

        ptyfd = open ( buf1, O_RDWR | O_NOCTTY );

        if ( ptyfd < 0 )
        {
            /* Try SCO style naming */
            snprintf ( buf1, sizeof buf1, "/dev/ptyp%d", i );
            snprintf ( buf2, sizeof buf2, "/dev/ttyp%d", i );

            ptyfd = open ( buf1, O_RDWR | O_NOCTTY );
            if ( ptyfd < 0 ) continue;
        }

        /* Open the slave side. */
        ttyfd = open ( buf2, O_RDWR | O_NOCTTY );
        if ( ttyfd < 0 )
        {
            perror ( buf2 );
            close ( ptyfd );
            return;
        }

        fd(ptyfd);
        tty = ttyfd;
        ptydev = buf1;
    }
#endif
}
