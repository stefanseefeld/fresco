dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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
dnl BERLIN_GGI_CHECK(mandatory-flag)
dnl
dnl Checks if GGI is found. If it is, $ac_cv_lib_ggi is set to "yes".

AC_DEFUN([BERLIN_GGI_CHECK],[

	AC_ARG_WITH(ggi-prefix,
		[  --with-ggi-prefix=PFX   Prefix for GGI],[
		ggi_prefix="$withval"])

	dnl Check for GGI includes
	if test ".$ggi_prefix" != . ; then
		GGI_CPPFLAGS="-I$ggi_prefix/include"
	fi
	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$GGI_CPPFLAGS $CPPFLAGS"
	AC_CHECK_HEADER(ggi/ggi.h,:,no_ggi=yes)
	CPPFLAGS="$save_CPPFLAGS"

	dnl Check for GGI libs
	if test ".$no_ggi" = . ; then

		if test ".$ggi_prefix" != . ; then
			GGI_LIBS="-L$ggi_prefix/lib"
		fi

		save_LDFLAGS="$LDFLAGS"
		LDFLAGS="$GGI_LIBS $LDFLAGS"
		AC_CHECK_LIB(ggi, ggiInit, :, no_ggi=yes)
		LDFLAGS="$save_LDFLAGS"
	fi

	if test ".$no_ggi" != . ; then

		ac_cv_lib_ggi=no
		dnl Abort or warn?
		ifelse($1,mandatory,AC_MSG_ERROR(GGI library was not found!))
	else
		ac_cv_lib_ggi=yes
		GGI_LIBS="$GGI_LIBS -lggi"
	fi
])
