dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
dnl http://www.fresco.org
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
dnl FRESCO_GGIMESA_CHECK(mandatory-flag)
dnl
dnl Checks if GGIMesa is found. If it is, $ac_cv_lib_GGIMesa is set to "yes".

AC_DEFUN([FRESCO_GGIMESA_CHECK],
  [AC_ARG_WITH(ggimesa-prefix,
	       AC_HELP_STRING([--with-ggimesa-prefix],[Prefix for GGIMesa]),
               [ggimesa_prefix="$withval"])

	dnl Check for GGIMesa includes
	if test x$ggimesa_prefix != x ; then
	  GGIMESA_CPPFLAGS=-I$ggimesa_prefix/include
	fi
	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$GGIMESA_CPPFLAGS $CPPFLAGS"
	AC_CHECK_HEADER(GL/ggimesa.h,,no_ggigl=yes)
	CPPFLAGS="$save_CPPFLAGS"

	dnl Check for GGIMesa libs
	if test x$no_ggigl = x ; then

	  if test x$ggimesa_prefix != x ; then
	    GGIMESA_LIBS="-L$ggimesa_prefix/lib -lgii"
	  fi
	  save_LDFLAGS="$LDFLAGS"
	  LDFLAGS="$GGIMESA_LIBS $LDFLAGS"
	  AC_CHECK_LIB(GL, GGIMesaCreateContext, :, no_ggigl=yes)
	  LDFLAGS="$save_LDFLAGS"
	fi

	if test x$no_ggigl != x ; then

	  ac_cv_lib_GGIMesa=no		
	  AC_MSG_WARN(GGI OpenGL library was not found!)
	else
	  ac_cv_lib_GGIMesa=yes
	  AC_SUBST(HAVE_GGIMESA, 1)
	  GGIMESA_LIBS="$GGIMESA_LIBS -lGL -lGLU"
	fi

	AC_SUBST(GGIMESA_CPPFLAGS)
	AC_SUBST(GGIMESA_LIBS)
])
