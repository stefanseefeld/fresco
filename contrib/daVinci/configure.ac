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

AC_PREREQ(2.53)
AC_REVISION($Revision$)

AC_INIT(daVinci, M1, devel@fresco.org)
AC_CONFIG_SRCDIR(LICENSE)
AC_CONFIG_HEADER(include/daVinci/acconfig.hh:config/acconfig.hh.in)
AC_CONFIG_AUX_DIR(config)

AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_LANG(C++)

dnl ------------------------------------------------------------------
dnl General flags
dnl ------------------------------------------------------------------

FRESCO_FLAG_SO

dnl ------------------------------------------------------------------
dnl Prague, Babylon, and Fresco
dnl ------------------------------------------------------------------

FRESCO_PACKAGE(Prague, Prague, $PACKAGE_VERSION, ../..)
CPPFLAGS="$CPPFLAGS $Prague_BUILD_CPPFLAGS"
LIBS="$LIBS $Prague_BUILD_LIBS"

FRESCO_PACKAGE(Babylon, Babylon, $PACKAGE_VERSION, ../..)
CPPFLAGS="$CPPFLAGS $Babylon_BUILD_CPPFLAGS"
LIBS="$LIBS $Babylon_BUILD_LIBS"

FRESCO_PACKAGE(Fresco-C++, Fresco_CXX, $PACKAGE_VERSION, ../..)
CPPFLAGS="$CPPFLAGS $Fresco_CXX_BUILD_CPPFLAGS"
LIBS="$LIBS $Fresco_CXX_BUILD_LIBS"

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Output Substitution])

AC_CONFIG_FILES([config/local.mk config/synopsis.py])
AC_CONFIG_FILES([Makefile src/Makefile])

mkdir -p lib
mkdir -p bin

AC_OUTPUT
