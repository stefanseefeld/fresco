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
dnl BERLIN_LIBART_CHECK(mandatory-flag)
dnl
dnl Checks if libArt is found. If it is, $ac_cv_lib_libArt is set to "yes"

AC_DEFUN([BERLIN_LIBART_CHECK],[

	AC_LANG_SAVE
	AC_LANG_C

	dnl First, try to pull everything out of gnome-config
	BERLIN_PROG_GNOME_CONFIG
	if test ".$GNOME_CONFIG" != . ; then
		LIBART_INCLUDES=`$GNOME_CONFIG --cflags libart`
		LIBART_LIBS=`$GNOME_CONFIG --libs libart`
	fi

	AC_ARG_WITH(art-prefix,
		[  --with-art-prefix=PFX   Prefix for libArt],[
		art_prefix="$withval"])

	dnl Check for header files if gnome-config failed
	if test ".$LIBART_INCLUDES" = . -a ".$art_prefix" != . ; then
			LIBART_INCLUDES=-I$art_prefix/include
			LIBART_LIBS=-L$art_prefix/lib
	fi
	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$LIBART_INCLUDES $CPPFLAGS"
	AC_CHECK_HEADER(art_pixbuf.h,:,
		AC_CHECK_HEADER(libart_lgpl/art_pixbuf.h,[
			if test ".$LIBART_INCLUDES" = . ; then
				LIBART_INCLUDES=/usr/include/libart_lgpl
			else
				LIBART_INCLUDES="$LIBART_INCLUDES/libart_lgpl"
			fi ],no_libart=yes))
	CPPFLAGS="$save_CPPFLAGS"

	dnl Assuming it's okay if the header was found
	if test ".$no_libart" != yes ; then
		ac_cv_lib_libArt=yes
		AC_SUBST(LIBART_INCLUDES)
		AC_SUBST(LIBART_LIBS)
	else
		ifelse($1,mandatory,AC_MSG_ERROR(libArt could not be found!))
		ac_cv_lib_libArt=no
	fi
])