dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2000 Niklas Elmqvist <elm@3dwm.org>
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
dnl BERLIN_CAVELIB_CHECK(mandatory-flag)
dnl
dnl Checks if cavelib is found. If it is, $ac_cv_lib_cave is set to "yes".
dnl We want the OpenGL versions of CAVELib (not the default IrisGL)!

AC_DEFUN([BERLIN_CAVELIB_CHECK],[

	AC_LANG_SAVE
	AC_LANG_C

	AC_ARG_WITH(cavelib-prefix,
		[  --with-cavelib-prefix=PFX   Prefix for cavelib (console CAVELib)],[
		cavelib_prefix="$withval"])

	dnl Check for cavelib includes
	if test ".$cavelib_prefix" != . ; then
		CON_INCLUDES="-I$cavelib_prefix/include"
	fi
	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$CON_INCLUDES $CPPFLAGS"
	AC_CHECK_HEADER(cave_ogl.h,:,no_cavelib=yes)
	CPPFLAGS="$save_CPPFLAGS"

	dnl Check for cavelib libs
	if test ".$no_cavelib" = . ; then

		if test ".$cavelib_prefix" != . ; then
			CON_LIBS="-L$cavelib_prefix/lib"
		fi

		save_LDFLAGS="$LDFLAGS"
		LDFLAGS="$CON_LIBS $LDFLAGS"
		AC_CHECK_LIB(cave_ogl, CAVEInit, :, no_cavelib=yes)
		LDFLAGS="$save_LDFLAGS"
	fi

	if test ".$no_cavelib" != . ; then

		ac_cv_lib_cave=no
		dnl Abort or warn?
		ifelse($1, mandatory, AC_MSG_ERROR(CAVELib was not found!))
	else
		ac_cv_lib_cave=yes
		CON_LIBS="$CON_LIBS -lcave_ogl"
	fi

dnl	AC_SUBST(CON_INCLUDES)
dnl	AC_SUBST(CON_LIBS)

	AC_LANG_RESTORE
])
