dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
dnl http://www.berlin-consortium.org
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
dnl BERLIN_OMNIORB_HOOK(script-if-omniorb-found, version, failflag)
dnl
dnl If failflag is "failure", it aborts if omniORB is not found.
dnl `version' should be 2 or 3. For more specific version checking, we
dnl might check the variable omniORB_x_y in omniInternal.h, where x is
dnl major and y is minor version number.
dnl

AC_DEFUN([BERLIN_OMNIORB_HOOK],[

	AC_LANG_SAVE
	AC_LANG_CPLUSPLUS

	omniorb_version=$2

	AC_ARG_WITH(orb-prefix,
		[  --with-orb-prefix=PFX   Prefix for omniORB],[
		omniorb_prefix="$withval"])
	AC_ARG_WITH(orb-eprefix,
		[  --with-orb-eprefix=PFX  Exec prefix for omniORB],[
		omniorb_eprefix="$withval"],[
		omniorb_eprefix=$omniorb_prefix])

	dnl Check for omniidl<omniorb_version>
	if test x$omniorb_eprefix != x ; then
		omniorb_path=$omniorb_eprefix/bin:$PATH
	else
		omniorb_path=$PATH
	fi
	AC_PATH_PROG(OMNIIDL, omniidl$omniorb_version, no, $omniorb_path)

	dnl Get system information we pass in CPPFLAGS
	dnl This is according to "The omniORB2 version 2.8.0 User's Guide"
	dnl TODO: Check if everything is correct.
	dnl I don't have access to anything other that x86/linux, so this is
	dnl based on looking at config.guess
	case $host_cpu in
		sparc)
			omniorb_defs=-D__sparc__
			;;
		i*86)
			omniorb_defs=-D__x86__
			;;
		alpha*)
			omniorb_defs=-D__alpha__
			;;
		hppa*)
			omniorb_defs=-D__hppa__
			;;
		powerpc)
			omniorb_defs=-D__powerpc__
			;;
		vax)
			omniorb_defs=-D__vax__
			;;
		mips*)
			omniorb_defs=-D__mips__
			;;
		arm)
			omniorb_defs=-D__arm__
			;;
		m68k)
			omniorb_defs=-D__m68k__
			;;
		*)
			AC_MSG_WARN(Unknown CPU type $host_cpu.)
			AC_MSG_WARN(Please check the omniORB documentation to see if your CPU type is supported,)
			AC_MSG_WARN(and update macros/omniorb.m4)
			;;
	esac

	case $host_os in
		linux*)
			omniorb_defs="$omniorb_defs -D__linux__"
			;;
		solaris*)
			dnl Some of these definitions should probably be moved
			dnl somewhere else...
			omniorb_defs="-DUsePthread -D_REENTRANT $omniorb_defs -D__sunos__"
			;;
		osf1)
			omniorb_defs="$omniorb_defs -D__osf1__"
			;;
		hpux*)
			omniorb_defs="$omniorb_defs -D__hpux__"
			;;
		aix*)
			omniorb_defs="$omniorb_defs -D__aix__"
			;;
		winnt*)
			dnl Seems like Windows uses winnt*, cygwin32
			dnl or mingw32. Don't know which is which...
			omniorb_defs="$omniorb_defs -D__NT__ -D__WIN32__"
			;;
		irix*)
			omniorb_defs="$omniorb_defs -D__irix__"
			;;
		nextstep*)
			omniorb_defs="$omniorb_defs -D__nextstep__"
			;;
		sysv4.2uw*)
			omniorb_defs="$omniorb_defs -D__uw7__"
			;;
		*)
			AC_MSG_WARN(Unknown OS $host_os.)
			AC_MSG_WARN(Please check the omniORB documentation to see if you OS is supported,)
			AC_MSG_WARN(and update macros/omniorb.m4.)
			;;
	esac

	dnl Don't know if this is portable...
	os_major_version=[`uname -r | cut -d '.' -f 1`]
dnl	os_major_version=2
	omniorb_defs="$omniorb_defs -D__OSVERSION__=$os_major_version"

	dnl Check for omniORB includes
	if test x$omniorb_prefix != x ; then
		omniorb_includes=-I$omniorb_prefix/include
	fi
	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$omniorb_defs $omniorb_includes $CPPFLAGS"
	AC_CHECK_HEADER(omniORB$omniorb_version/CORBA.h,,no_omniorb=yes)
	CPPFLAGS="$save_CPPFLAGS"

	dnl Check for omniORB libs
	if test x$no_omniorb = x ; then
		
		if test x$omniorb_eprefix != x ; then
			omniorb_libs=-L$omniorb_eprefix/lib
		fi
		omniorb_libs="$omniorb_libs -lomniORB2 -lomnithread"
		omniorb_libs="$omniorb_libs -ltcpwrapGK -lomniLC"
		case $host_os in
			solaris2.6)
				omniorb_libs="$omniorb_libs -lomniDynamic2 -lpthread -lposix4 -lsocket -lnsl"
				;;
		esac

		AC_CACHE_CHECK([for working omniORB environment],
		berlin_cv_omniorb_found, [

		save_LDFLAGS="$LDFLAGS"
		save_CPPFLAGS="$CPPFLAGS"
		LDFLAGS="$omniorb_libs $LDFLAGS"
		CPPFLAGS="$omniorb_defs $omniorb_includes $CPPFLAGS"
		
		dnl Check if everything works
		AC_TRY_RUN([
#include <omniORB$omniorb_version/CORBA.h>

int
main (int argc, char* argv[])
{
	try {
		CORBA::ORB_ptr orb
			= CORBA::ORB_init (argc, argv, "omniORB$omniorb_version");
	} catch (...) {
		return 1;
	}

	return 0;
}
			], , no_omniorb=yes)

		CPPFLAGS="$save_CPPFLAGS"
		LDFLAGS="$save_LDFLAGS"

		if test x$no_omniorb = x ; then
			berlin_cv_omniorb_found=yes
		else
			berlin_cv_omniorb_found=no
		fi
		]) dnl End of AC_CACHE_CHECK

	fi

	if test x$no_omniorb = xyes ; then
		
		dnl Abort or warn?
		if test x$3 = xfailure ; then
			AC_MSG_ERROR(No working omniORB environment found!)
		else
			AC_MSG_WARN(No working omniORB environment found!)
		fi
	else
		ORBCPPFLAGS="$omniorb_defs $omniorb_includes"
		ORBLIBS="$omniorb_libs"
		ifelse($1,,:,$1)
	fi

	AC_LANG_RESTORE
])

AC_DEFUN([BERLIN_OMNIORB_CHECK], [
	BERLIN_OMNIORB_HOOK([],2,failure)
])
