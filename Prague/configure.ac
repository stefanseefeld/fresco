dnl $Id$
dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
dnl http://www.fresco.org/
dnl
dnl This library is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Library General Public
dnl License as published by the Free Software Foundation; either
dnl version 2 of the License, or (at your option) any later version.
dnl
dnl This library is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
dnl Library General Public License for more details.
dnl
dnl You should have received a copy of the GNU Library General Public
dnl License along with this library; if not, write to the
dnl Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
dnl MA 02139, USA.
dnl
dnl Process this file with autoconf to produce a configure script.

dnl ------------------------------------------------------------------
dnl Autoconf initialization
dnl ------------------------------------------------------------------
AC_PREREQ(2.53)
AC_REVISION($Revision$)
AC_INIT(Prague, M1, devel@fresco.org)
AC_CONFIG_SRCDIR(LICENSE)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADER(include/Prague/acconfig.hh:config/acconfig.hh.in)

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AC_PROG_MAKE_SET
AC_PROG_INSTALL

dnl ------------------------------------------------------------------
dnl Environment (this needs to go before AC_LANG(C++)
dnl ------------------------------------------------------------------

AC_HEADER_STDC
AC_CHECK_FUNCS(getenv putenv setenv unsetenv)

AC_LANG(C++)

dnl ------------------------------------------------------------------
dnl General flags
dnl ------------------------------------------------------------------

AC_ARG_ENABLE(tracer,
              AC_HELP_STRING([--enable-tracer],[Compile with tracer support]),
              [AC_DEFINE(TRACER, 1, [Define if you want tracer support.])])

AC_MSG_NOTICE([platform specific system utilities])
AC_CHECK_FUNCS(strsignal)
AC_CHECK_HEADERS(string.h)
AC_NEED_DECLARATION(strsignal)
AC_HEADER_SYS_WAIT
AC_CHECK_LIB(z, gzsetparams, AC_DEFINE(HAVE_ZLIB, 1, [Define if you have the zlib library.]), [AC_MSG_ERROR([update your zlib, please])])

FRESCO_FLAG_SO

dnl ------------------------------------------------------------------
dnl Thread support
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Thread Implementation])
FRESCO_THREAD

dnl ------------------------------------------------------------------
dnl Plugin support
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Dynamic Loading Implementation])
AC_CHECK_HEADERS(dlfcn.h dl.h)
AC_CHECK_LIB(dl, dlopen)
AC_LANG(C)
AC_CHECK_FUNCS(dlopen dlsym dlclose shl_load)
AC_LANG(C++)

AC_MSG_NOTICE([plugin method :])

AC_IFALLYES([header:dlfcn.h func:dlopen func:dlsym func:dlclose],
  [AC_DEFINE(HAVE_DLFCN, 1, [Define if you have the dlfcn family of functions.]) AC_MSG_RESULT([use dlopen family of functions for plugins])])
AC_IFALLYES([header:dl.h func:shl_load],
  [AC_DEFINE(HAVE_DLAIX, 1, [Define if you have the AIX family of functions.]) AC_MSG_RESULT([use AIX shm_load for plugins])])

dnl ------------------------------------------------------------------
dnl IPC support
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([IPC Implementation])
FRESCO_LIB_SOCKET
AC_CHECK_LIB(util, login, LIBS="$LIBS -lutil")
AC_CHECK_HEADERS([pty.h sys/stropts.h])
AC_LANG(C)
AC_CHECK_FUNCS([openpty _getpty])
AC_LANG(C++)

dnl won't work without AC_CANONICAL_HOST
dnl 
dnl case "$host" in
dnl *-*-linux*)
dnl 	no_dev_ptmx=1
dnl 	;;
dnl *-*-sco3.2v4*)
dnl 	no_dev_ptmx=1
dnl 	;;
dnl *-*-sco3.2v5*)
dnl 	no_dev_ptmx=1
dnl 	;;
dnl esac
dnl 
dnl complete disable
no_dev_ptmx=1

if test -z "$no_dev_ptmx" ; then
  AC_CHECK_FILE("/dev/ptmx", [AC_DEFINE(HAVE_DEV_PTMX, 1, [Define if you have /dev/ptmx.]) have_dev_ptmx=1])
fi
AC_CHECK_FILE("/dev/ptc", [AC_DEFINE(HAVE_DEV_PTS_AND_PTC, 1, [Define if you have /dev/ptc.]) have_dev_ptc=1])

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Output Substitution])

AC_CONFIG_FILES([config/local.mk config/synopsis.py])
AC_CONFIG_FILES([config/Prague-config], [chmod +x config/Prague-config])
AC_CONFIG_FILES([config/Prague.spec])
AC_CONFIG_FILES([bin/Prague-config:config/Prague-build-config.in], [chmod +x bin/Prague-config])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_CONFIG_FILES([demo/Makefile demo/Sys/Makefile demo/Thread/Makefile demo/IPC/Makefile
                 demo/Filter/Makefile demo/Network/Makefile])

mkdir -p lib
mkdir -p bin

AC_OUTPUT
