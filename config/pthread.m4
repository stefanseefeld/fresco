dnl $Id$
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2000 Håvard Skinnemoen <skinnemo@itk.ntnu.no>
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
dnl AC_PTHREAD
dnl
dnl Checks for pthread support. If found, $ac_cv_pthread is set to "yes",
dnl and $pthread_cppflags and $pthread_lib are defined
AC_DEFUN([AC_PTHREAD],[

    dnl This is used on Linux for glibc binary compatibility (Doh!)
    AC_ARG_ENABLE(pthread-sem, [    --enable-pthread-sem  use pthread semaphores [default=yes]],, enable_pthread_sem=yes)
    case "$target" in
        *-*-darwin*)
            pthread_cppflags="-D_THREAD_SAFE"
# causes Carbon.p complaints?
#            pthread_cppflags="-D_REENTRANT -D_THREAD_SAFE"
            ;;
        *-*-freebsd*)
            pthread_cppflags="-D_REENTRANT -D_THREAD_SAFE"
            pthread_lib="-pthread"
            ;;
        *-*-openbsd*)
            pthread_cppflags="-D_REENTRANT"
            pthread_lib="-pthread"
            ;;
        *-*-solaris*)
            pthread_cppflags="-D_REENTRANT"
            pthread_lib="-lpthread -lposix4"
            ;;
        *-*-sysv5*)
            pthread_cppflags="-D_REENTRANT -Kthread"
            pthread_lib=""
            ;;
        *-*-irix*)
            pthread_cppflags="-D_SGI_MP_SOURCE"
            pthread_lib="-lpthread"
            ;;
        *-*-aix*)
            pthread_cppflags="-D_REENTRANT -mthreads"
            pthread_lib="-lpthread"
            ;;
        *-*-osf*)
            pthread_cppflags="-D_REENTRANT"
            pthread_lib="-pthread"
            ;;
        *-*-qnx*)
            pthread_cppflags=""
            pthread_lib=""
            ;;
        *)
            pthread_cppflags="-D_REENTRANT"
            pthread_lib="-lpthread"
            ;;
    esac
    ac_save_cppflags="$CPPFLAGS"
    ac_save_libs="$LIBS"
    CPPFLAGS="$CPPFLAGS $pthread_cppflags"
    LIBS="$LIBS $pthread_lib"
    if test x$enable_pthreads = xyes; then
        use_pthreads=no
        AC_TRY_LINK([
         #include <pthread.h>
        ],[
         pthread_attr_t type;
         pthread_attr_init(&type);
        ],[
        use_pthreads=yes
        ])
	LIBS="$ac_save_libs"
	CPPFLAGS="$ac_save_cppflags"
        if test x$use_pthreads = xyes; then
	    ac_cv_pthread="yes"
	else
	    AC_MSG_ERROR([no pthread support found!])
	fi
    fi
])
