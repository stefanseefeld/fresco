dnl $Id$
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 2001 Stefan Seefeld <stefan@fresco.org>
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
dnl FRESCO_THREAD
dnl
dnl Try to find a usable thread library.
dnl Add the necessary stuff to LIBS and CPPFLAGS
AC_DEFUN([FRESCO_THREAD],
  [AC_MSG_NOTICE([Threading])
   AC_ARG_ENABLE(pthreads,
     [  --enable-pthreads       use POSIX threads for multi-threading (default: yes)],
     [  enable_pthreads="$enableval"])
   if test ".$enable_pthreads" = . ; then
     enable_pthreads=yes
   fi
   if test ".$enable_pthreads" = .yes ; then
     FRESCO_PTHREAD
     if test ".$ac_cv_pthread" != .yes; then
       AC_MSG_ERROR([No supported thread API found!])
     else
       AC_MSG_RESULT([use pthreads])
       CPPFLAGS="$CPPFLAGS $pthread_cppflags"
       LIBS="$LIBS $pthread_lib"
     fi
   fi
])