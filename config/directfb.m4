dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2000 Tobias Hunger <Tobias@berlin-consortium.org>
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
dnl BERLIN_DIRECTFB_CHECK(mandatory-flag)
dnl
dnl Checks if directfb is found. If it is, $ac_cv_lib_directfb is set to "yes".

AC_DEFUN([BERLIN_DIRECTFB_CHECK],[

	AC_ARG_WITH(directfb-prefix,
		[  --with-directfb-prefix=PFX   Prefix for DirectFb (console DirectFB)],[
		directfb_prefix="$withval"])

	dnl Check for directFB includes
	if test ".$directfb_prefix" != . ; then
		DFB_CPPFLAGS="-I$directfb_prefix/include"
	fi
	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$DFB_CPPFLAGS $CPPFLAGS"
	AC_CHECK_HEADER(directfb.h,:,no_directfb=yes)
	CPPFLAGS="$save_CPPFLAGS"

	dnl Check for directfb libs
	if test ".$no_directfb" = . ; then

		if test ".$directfb_prefix" != . ; then
			DFB_LIBS="-L$directfb_prefix/lib"
		fi

		save_LDFLAGS="$LDFLAGS"
		LDFLAGS="$DFB_LIBS $LDFLAGS"
		AC_CHECK_LIB(directfb, DirectFBCreate, :, no_directfb=yes)
		LDFLAGS="$save_LDFLAGS"
	fi

	if test ".$no_directfb" != . ; then

		ac_cv_directfb=no
		dnl Abort or warn?
		ifelse($1, mandatory, AC_MSG_ERROR(DirectFB was not found!))
	else
		ac_cv_lib_directfb=yes
		DFB_LIBS="$DFB_LIBS -ldirectfb"
	fi

])
