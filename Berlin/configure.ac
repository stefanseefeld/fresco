dnl $Id$
dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
dnl http://www.fresco.org/
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
dnl Process this file with autoconf to produce a configure script.

dnl ------------------------------------------------------------------
dnl Autoconf initialization
dnl ------------------------------------------------------------------

AC_PREREQ(2.12)
AC_REVISION($Revision$)

AC_INIT(Berlin, 0.3.0, devel@fresco.org)
AC_CONFIG_SRCDIR(../LICENSE)
AC_CONFIG_HEADER(include/Berlin/acconfig.hh:config/acconfig.hh.in)
AC_CONFIG_AUX_DIR(config)

dnl AC_HEADLINE(dnl
dnl Berlin Server, The Berlin Server, dnl
dnl [Copyright (c) 2000 The Berlin Project <berlin-design@lists.sourceforge.net>],
dnl VERSION)

AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_LANG_CPLUSPLUS

dnl ------------------------------------------------------------------
dnl General flags
dnl ------------------------------------------------------------------

FRESCO_FLAG_SO

dnl ------------------------------------------------------------------
dnl Text rendering
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Text Rendering])

FRESCO_FREETYPE_CHECK(6.1.0,,[AC_MSG_ERROR([can't compile Server without freetype])])
AC_CHECK_HEADERS(png.h)
AC_CHECK_LIB(png, png_read_info,,[AC_MSG_ERROR([can't compile libBerlin without libpng])])

dnl ------------------------------------------------------------------
dnl Graphics environment
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Graphics Environment])

enabled_drawing_kits=

FRESCO_LIBART_CHECK
if test ".$HAVE_LIBART" = .1 ; then
  enabled_drawing_kits="$enabled_drawing_kits Drawing/libArt"
fi

FRESCO_OPENGL_CHECK
if test ".$HAVE_GL" = .1 ; then
  enabled_drawing_kits="$enabled_drawing_kits Drawing/openGL"
fi

dnl ------------------------------------------------------------------
dnl Prague and Warsaw
dnl ------------------------------------------------------------------

FRESCO_PACKAGE(Prague, $PACKAGE_VERSION)
CPPFLAGS="$CPPFLAGS $Prague_CPPFLAGS"
LIBS="$Prague_LIBS $LIBS"
FRESCO_PACKAGE(Babylon, $PACKAGE_VERSION)
CPPFLAGS="$CPPFLAGS $Babylon_CPPFLAGS"
LIBS="$Babylon_LIBS $LIBS"
FRESCO_PACKAGE(Fresco, $PACKAGE_VERSION)
CPPFLAGS="$CPPFLAGS $Fresco_CPPFLAGS"
LIBS="$Fresco_LIBS $LIBS"

dnl ------------------------------------------------------------------
dnl some helper utils
dnl ------------------------------------------------------------------

AC_ARG_ENABLE(jprof, 
              AC_HELP_STRING([--enable-jprof],[enable profiling with the jprof tool]),
              [AC_DEFINE(JPROF, 1, [Define if jprof support should be compiled in.])])
AC_ARG_ENABLE(lclog, AC_HELP_STRING([--enable-lclog],[enable lifecycle logging]),
              [AC_DEFINE(LCLOG, 1, [Define if lifecycle debugging should be enabled.])])
AC_ARG_ENABLE(rmdebug, 
              AC_HELP_STRING([--enable-rmdebug],[enable region management debugging]),
              [AC_DEFINE(RMDEBUG, 1, [Define if region management debugging should be enabled.])])

dnl ------------------------------------------------------------------
dnl Decisions
dnl ------------------------------------------------------------------

dnl ------------------------------------------------------------------
dnl Print a summary of what's going to be built
dnl ------------------------------------------------------------------

AC_MSG_NOTICE(Summary)
AC_MSG_RESULT([Build DrawingKits:                      $enabled_drawing_kits])
AC_MSG_RESULT([Add profiling support:                   $jprof])
AC_MSG_RESULT([Add lifecycle log support:               $lclog])
AC_MSG_RESULT([Add region management debugging support: $rmdebug])

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Output Substitution])

for kit in Drawing/PostScript $enabled_drawing_kits Layout Commands Tools Images Figures Primitives Text Widgets/Motif Gadgets Desktop Unidraw ; do
  mkdir -p modules/$kit
  AC_CONFIG_FILES([modules/$kit/Makefile])
done

AC_CONFIG_FILES([config/local.mk config/module.mk config/synopsis.py])
AC_CONFIG_FILES([Makefile src/Makefile modules/Makefile server/Makefile])

mkdir -p lib
mkdir -p etc
mkdir -p bin

AC_OUTPUT
