dnl $Id$
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2000 Håvard Skinnemoen <skinnemo@itk.ntnu.no>
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

dnl
dnl BERLIN_LIB_PTHREAD
dnl
dnl Checks for libpthread and adds the necessary flags to LIBS
dnl and CPPFLAGS
AC_DEFUN([BERLIN_LIB_PTHREAD],[

	AC_LANG_SAVE
	AC_LANG_C

	AC_CACHE_CHECK([for pthread flags to the preprocessor],
		berlin_cv_cppflag_pthread,[
		save_CPPFLAGS="$CPPFLAGS"
		CPPFLAGS="$CPPFLAGS -pthread"
		AC_TRY_CPP([
#include <unistd.h>
], berlin_cv_cppflag_pthread=-pthread, berlin_cv_cppflags_pthread="")

		CPPFLAGS="$save_CPPFLAGS"
		if test ! ".$berlin_cv_cppflag_pthread" = ".-pthread" ; then
			berlin_cv_cppflag_pthread="none"

			dnl TODO: Check which flags are needed for
			dnl various systems
			AC_DEFINE(_REENTRANT)
			case $host_os in
				solaris*)
					AC_DEFINE(UsePthread)
				;;
				freebsd*)
					AC_DEFINE(_THREAD_SAFE)
				;;
			esac
		fi
	])

	if test ! ".$berlin_cv_cppflag_pthread" = ".none" ; then
		CPPFLAGS="$CPPFLAGS $berlin_cv_cppflag_pthread"
	fi

	dnl Then, check for libraries
	AC_CACHE_CHECK([for pthread flags to the linker],
		berlin_cv_lib_pthread,[
		
		save_LIBS="$LIBS"
		LIBS="$LIBS -pthread"
		AC_TRY_LINK([
#include <pthread.h>
],[
void *
thread_test (void *arg)
{
	return NULL;
}

int main (int argc, char *argv[])
{
	pthread_t thread;
	return pthread_create (&thread, NULL, thread_test, NULL);
}
],berlin_cv_lib_pthread="-pthread", berlin_cv_lib_pthread="none")

	])
	LIBS="$save_LIBS"

	if test ".$berlin_cv_lib_pthread" = ".none" ; then
		AC_CHECK_LIB(posix4, main)
		AC_CHECK_LIB(pthread, pthread_create)
	else
		LIBS="$LIBS $berlin_cv_lib_pthread"
	fi

	AC_LANG_RESTORE
])
