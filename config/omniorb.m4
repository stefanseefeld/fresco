dnl $Id$
dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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
dnl BERLIN_CHECK_LIB(variable, library, func_call, include_files)
dnl
dnl Checks if library is found by doing func_call. Include include_files
dnl to avoid compilation errors, and add library to variable if successful.
dnl variable is also used to specify additional libraries or paths.
dnl
dnl This functions is meant to address some of the severe limitations of
dnl autoconf when it comes to handling C++.
AC_DEFUN([BERLIN_CHECK_LIB],[

	save_LIBS="$LIBS"
	LIBS="$LIBS $$1 -l$2"
	changequote(`, ')
	includes="patsubst(`$4', `\(\w\|\.\|/\)+', `#include <\&>
')"
	changequote([, ])
	AC_CACHE_CHECK("for -l$2",
		berlin_cv_lib_$2,
		AC_TRY_LINK($includes,
			$3, berlin_cv_lib_$2="yes", berlin_cv_lib_$2="no"))

	LIBS="$save_LIBS"
	if test ".$berlin_cv_lib_$2" = ".yes" ; then
		$1="$$1 -l$2"
	fi
])

dnl dnl BERLIN_LIB_OMNIORB dnl dnl Checks if omniORB is found. If it
dnl is, $berlin_cv_lib_omniORB is set to "yes". Also, the
dnl variables IDLCXX, IDLCXXFLAGS, IDLDYNFLAGS, IDLTIEFLAGS, ORB_LIBS
dnl and ORB_CPPFLAGS are set, and necessary definitions are added.

AC_DEFUN([BERLIN_LIB_OMNIORB],[

	AC_REQUIRE([AC_CANONICAL_SYSTEM])
	AC_REQUIRE([AC_PROG_CC])
	AC_REQUIRE([AC_PROG_CXX])
	AC_REQUIRE([AC_PROG_CPP])
	AC_REQUIRE([AC_PROG_CXXCPP])
	AC_REQUIRE([BERLIN_LIB_SOCKET])
dnl 	AC_noREQUIRE(BERLIN_LIB_NSL)

	AC_LANG_SAVE
	AC_LANG_CPLUSPLUS

	AC_ARG_WITH(omniorb-prefix,
		[  --with-omniorb-prefix  Prefix for omniORB],[
		omniorb_prefix="$withval"])

	dnl Check for omniidl.
	if test ".$omniorb_prefix" != "." ; then
		omniorb_path="$omniorb_prefix/bin:$PATH"
		ORB_LIBS="-L$omniorb_prefix/lib"
		ORB_CPPFLAGS="-I$omniorb_prefix/include"
	else
		omniorb_path="$PATH"
	fi
	AC_PATH_PROG(IDLCXX, omniidl, no, $omniorb_path)
	if test ".$IDLCXX" = ".no" ; then
		no_omniorb="yes"
	fi

	save_CPPFLAGS="$CPPFLAGS"
	if test ".$no_omniorb" = "." ; then
		dnl Get system information we pass in CPPFLAGS
		dnl This is according to
		dnl "The omniORB2 version 2.8.0 User's Guide"
		dnl TODO: Check if everything is correct.
		dnl I don't have access to anything other that
		dnl x86/linux, so this is based on looking at
		dnl config.guess
		case $host_cpu in
		sparc)
			AC_DEFINE(__sparc__)
			;;
		i*86)
			AC_DEFINE(__x86__)
			;;
		alpha*)
			AC_DEFINE(__alpha__)
			;;
		hppa*)
			AC_DEFINE(__hppa__)
			;;
		powerpc)
			AC_DEFINE(__powerpc__)
			;;
		vax)
			AC_DEFINE(__vax__)
			;;
		mips*)
			AC_DEFINE(__mips__)
			;;
		arm)
			AC_DEFINE(__arm__)
			;;
		m68k)
			AC_DEFINE(__m68k__)
			;;
		*)
			AC_MSG_WARN(Unknown CPU type $host_cpu.)
			AC_MSG_WARN(Please check the omniORB documentation to see if your CPU type is supported,)
			AC_MSG_WARN(and update config/Warsaw/macros/omniorb.m4)
			;;
		esac

		case $host_os in
		linux*)
			AC_DEFINE(__linux__)
			;;
		solaris*)
			AC_DEFINE(__sunos__)
			;;
		osf1)
			AC_DEFINE(__osf1__)
			;;
		hpux*)
			AC_DEFINE(__hpux__)
			;;
		aix*)
			AC_DEFINE(__aix__)
			;;
		winnt*)
			dnl Seems like Windows uses winnt*, cygwin32
			dnl or mingw32. Don't know which is which...
			AC_DEFINE(__NT__)
			AC_DEFINE(__WIN32__)
			;;
		irix*)
			AC_DEFINE(__irix__)
			;;
		nextstep*)
			AC_DEFINE(__nextstep__)
			;;
		sysv4.2uw*)
			AC_DEFINE(__uw7__)
			;;
		freebsd*)
			AC_DEFINE(__freebsd__)
			;;
		*)
			AC_MSG_WARN(Unknown OS $host_os.)
			AC_MSG_WARN(Please check the omniORB documentation to see if you OS is supported,)
			AC_MSG_WARN(and update macros/omniorb.m4.)
			;;
		esac

		dnl Don't know if this is portable...
		os_major_version=[`uname -r | cut -d '.' -f 1`]
		AC_DEFINE_UNQUOTED(__OSVERSION__, $os_major_version)

		dnl Check for omniORB includes
		CPPFLAGS="$CPPFLAGS $ORB_CPPFLAGS"
		AC_CHECK_HEADER(omniORB3/CORBA.h,,no_omniorb=yes)
	fi

	dnl Check for omniORB libraries
	if test ".$no_omniorb" = "." ; then
dnl		BERLIN_CHECK_LIB(ORB_LIBS, omnithread, [omni_mutex my_mutex],
dnl			omnithread.h)
		dnl Hard to check the GateKeeper lib because of circular
		dnl dependency between it and libomniORB3
		ORB_LIBS="$ORB_LIBS -ltcpwrapGK"
		BERLIN_CHECK_LIB(ORB_LIBS, omniDynamic3, [CORBA::Any_var any;],
			omniORB3/CORBA.h)
		BERLIN_CHECK_LIB(ORB_LIBS, omniORB3, [CORBA::ORB_var orb],
			omniORB3/CORBA.h)
		if test ".$berlin_cv_lib_omniORB3" = ".no" \
			-a ".$berlin_cv_lib_omniDynamic3" = ".no" \
			-a ".$berlin_cv_lib_omnithread" = ".no" ; then
			no_omniorb="yes"
		fi
		LIBS="$ORB_LIBS $LIBS"
	fi

dnl CPPFLAGS="$save_CPPFLAGS"

	if test ".$no_omniorb" = "." ; then
		berlin_cv_lib_omniORB="yes"
	fi

	AC_LANG_RESTORE
])
