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

dnl ------------------------------------------------------------------

dnl PRAGUE_SOCKET_CHECK
dnl

AC_DEFUN(PRAGUE_SOCKET_CHECK,[
cv_inet_sockets=no
cv_unix_sockets=no
cv_lib_socket="c"
cv_have_inet_aton=no
SOCKET_LIBS=""
AC_CHECK_HEADERS(sys/socket.h select.h sys/select.h netinet/in_systm.h netinet/ip.h)
AC_CHECK_HEADERS(arpa/inet.h, cv_inet_sockets=yes)
AC_CHECK_HEADERS(sys/un.h, cv_unix_sockets=yes)
AC_CHECK_TYPEDEF(socklen_t, sys/socket.h)
AC_CHECK_LIB(socket, socket, [LIBS="$LIBS -lsocket" AC_DEFINE(HAVE_INET_SOCKETS, 1,[Define if you have inet sockets.])])
AC_CHECK_LIB(socket, inet_aton,[cv_have_inet_aton=yes])
AC_CHECK_LIB(resolv, inet_aton,[LIBS="$LIBS -lresolv" cv_have_inet_aton=yes])

if test $cv_have_inet_aton = yes ; then
	AC_DEFINE(HAVE_INET_ATON, 1, [Define if you have the inet_aton function.])
fi

if test $cv_unix_sockets = yes ; then
	AC_DEFINE(HAVE_UNIX_SOCKETS, 1, [Define if you have unix sockets.])
fi
AC_SUBST(SOCKET_LIBS)
])
