dnl $Id$
dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) Håvard Skinnemoen <skinnemo@itk.ntnu.no>
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
AC_PREREQ(2.52)
AC_REVISION($Revision$)

AC_INIT(Fresco, 0.3.0, devel@fresco.org)
AC_CONFIG_SRCDIR(../LICENSE)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADER(include/Fresco/acconfig.hh:config/acconfig.hh.in)

AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_CXX
AC_PROG_CXXCPP
AC_LANG_CPLUSPLUS

dnl ------------------------------------------------------------------
dnl ORB
dnl ------------------------------------------------------------------

FRESCO_LIB_ORB(mandatory)
MAKEFILE=
if test ".$ORB" = .omniORB ; then
  MAKEFILE="Makefile.omniorb.in"
elif test ".$ORB" = .TAO ; then
  MAKEFILE="Makefile.tao.in"
fi

dnl ------------------------------------------------------------------
dnl General flags
dnl ------------------------------------------------------------------

FRESCO_PACKAGE(Babylon, $PACKAGE_VERSION)
CPPFLAGS="$CPPFLAGS $Babylon_CPPFLAGS"
LIBS="$LIBS $Babylon_LIBS"

FRESCO_FLAG_SO

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Output Substitution])

AC_CONFIG_FILES([config/local.mk config/synopsis.py Makefile src/Makefile:config/$MAKEFILE])

mkdir -p share
mkdir -p lib
mkdir -p bin

AC_OUTPUT
