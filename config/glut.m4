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
dnl BERLIN_GLUT_CHECK(mandatory-flag)
dnl
dnl Checks if GLUT is found. If it is, $ac_cv_lib_glut is set to "yes".

AC_DEFUN([BERLIN_GLUT_CHECK],[

	AC_ARG_WITH(glut-prefix,
		[  --with-glut-prefix=PFX   Prefix for GLUT],[
		glut_prefix="$withval"])

	dnl Check for GLUT includes
	if test ".$glut_prefix" != . ; then
		CON_INCLUDES="-I$glut_prefix/include"
	fi
	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$CON_INCLUDES $CPPFLAGS"
	AC_CHECK_HEADER(GL/glut.h,:,no_glut=yes)
	CPPFLAGS="$save_CPPFLAGS"

	if test ".$glut_prefix" != . ; then
		CON_LIBS="-L$glut_prefix/lib"
	fi
	
	if test ".$no_glut" != . ; then

		ac_cv_lib_glut=no
		dnl Abort or warn?
		ifelse($1,mandatory,AC_MSG_ERROR(GLUT library was not found!))
	else
		# @@@ Fix this to something more cross-platform!
		ac_cv_lib_glut=yes
		CON_LIBS="$CON_LIBS -lglut -lGL -lGLU"
	fi

])
