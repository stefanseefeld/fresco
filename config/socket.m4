dnl $Id$
dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org>
dnl http://www.berlin-consortium.org/
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

dnl ------------------------------------------------------------------

dnl BERLIN_LIB_SOCKET
dnl
dnl Check for a suitable socket implementation and add any needed
dnl libraries to LIBS.

AC_DEFUN(BERLIN_LIB_SOCKET,[
cv_inet_sockets=no
cv_unix_sockets=no
cv_lib_socket="c"
SOCKET_LIBS=""
AC_CHECK_HEADERS(sys/socket.h select.h sys/select.h netinet/in_systm.h netinet/ip.h)
AC_CHECK_HEADERS(arpa/inet.h, cv_inet_sockets=yes)
AC_CHECK_HEADERS(sys/un.h, cv_unix_sockets=yes)
AC_CHECK_TYPEDEF(socklen_t, sys/socket.h)
AC_CHECK_LIB(socket, socket, [cv_lib_socket="socket" LIBS="$LIBS -lsocket"])
if test $cv_inet_sockets = yes ; then
	AC_DEFINE(HAVE_INET_SOCKETS)
	AC_CHECK_LIB($cv_lib_socket, inet_aton,[AC_DEFINE(HAVE_INET_ATON)])
fi

if test $cv_unix_sockets = yes ; then
	AC_DEFINE(HAVE_UNIX_SOCKETS)
fi
])
