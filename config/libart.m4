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
dnl FRESCO_LIBART_CHECK(mandatory-flag)
dnl
dnl Checks if libArt is found. If it is, $ac_cv_lib_libArt is set to "yes"

AC_DEFUN([FRESCO_LIBART_CHECK],[
   AC_ARG_WITH(libart-prefix,
               AC_HELP_STRING([--with-art-prefix],[Prefix for libArt]),
               [libart_prefix="$withval"])

   if test ".$libart_prefix" != . ; then
      libart_config_prefix="$libart_prefix/bin:" ;
   fi

   dnl First, try to pull everything out of libart-config
   AC_PATH_PROG([LIBART_CONFIG],[libart2-config],,[$libart_config_prefix$PATH])
   if test ".$LIBART_CONFIG" != . ; then
     LIBART_CPPFLAGS=`$LIBART_CONFIG --cflags`
     LIBART_LIBS=`$LIBART_CONFIG --libs`
   else
     dnl Second, try to pull everything out of gnome-config
     AC_PATH_PROG([GNOME_CONFIG],[gnome-config],,[$libart_config_prefix$PATH])
     if test ".$GNOME_CONFIG" != . ; then
       LIBART_CPPFLAGS=`$GNOME_CONFIG --cflags libart`
       LIBART_LIBS=`$GNOME_CONFIG --libs libart`
     fi
   fi

   dnl Check for header files if above checks failed
   if test ".$LIBART_LIBS" = . -a ".$libart_prefix" != . ; then
   		LIBART_CPPFLAGS=-I$libart_prefix/include
   		LIBART_LIBS=-L$libart_prefix/lib
   fi
   save_CPPFLAGS="$CPPFLAGS"
   CPPFLAGS="$LIBART_CPPFLAGS $CPPFLAGS"
   AC_CHECK_HEADER(art_pixbuf.h, , [AC_CHECK_HEADER(libart_lgpl/art_pixbuf.h, , [no_libart=yes])])
   CPPFLAGS="$save_CPPFLAGS"
   
   dnl Assuming it's okay if the header was found
   if test ".$no_libart" != .yes ; then
     AC_SUBST(HAVE_LIBART, 1)
     AC_SUBST(LIBART_CPPFLAGS)
     AC_SUBST(LIBART_LIBS)
   else
     AC_SUBST(HAVE_LIBART, 0)
     ifelse($1,mandatory,AC_MSG_ERROR(libArt could not be found!))
   fi
])
