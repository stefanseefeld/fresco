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
dnl FRESCO_OPENGL_CHECK
dnl
AC_DEFUN([FRESCO_OPENGL_CHECK],
  [AC_ARG_WITH(opengl-prefix,
	       AC_HELP_STRING([--with-opengl-prefix],[Prefix for openGL]),
               [opengl_prefix="$withval"])

   dnl Check for opengl includes
   if test x$opengl_prefix != x ; then
     GL_CPPFLAGS=-I$opengl_prefix/include
   fi
   save_CPPFLAGS="$CPPFLAGS"
   CPPFLAGS="$GL_CPPFLAGS $CPPFLAGS"
   AC_CHECK_HEADER(GL/gl.h,,no_gl=yes)
   AC_CHECK_HEADER(GL/glu.h,,no_gl=yes)
   CPPFLAGS="$save_CPPFLAGS"
   
   dnl Check for opengl libs
   if test "x$no_gl" = x ; then
   
     if test x$opengl_prefix != x ; then
       GL_LIBS=-L$opengl_prefix/lib
     fi
     save_LDFLAGS="$LDFLAGS"
     LDFLAGS="$GL_LIBS $LDFLAGS"
     AC_CHECK_LIB(GL, glLoadIdentity, :, no_gl=yes)
     AC_CHECK_LIB(GLU, gluNewTess, :, no_gl=yes, [-lGL])
     LDFLAGS="$save_LDFLAGS"
   fi
   
   if test "x$no_gl" = xyes ; then
   
     AC_SUBST(HAVE_GL, 0)
   else
     AC_SUBST(HAVE_GL, 1)
     AC_SUBST(GL_CPPFLAGS, "$GL_CPPFLAGS")
     AC_SUBST(GL_LIBS, "$GL_LIBS -lGL -lGLU")
   fi
])
