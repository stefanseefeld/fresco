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

AC_INIT(Berlin-GGI, M1, devel@fresco.org)
AC_CONFIG_SRCDIR(LICENSE)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADER(include/Fresco/acconfig.hh:config/acconfig.hh.in)

AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_LANG_CPLUSPLUS

dnl ------------------------------------------------------------------
dnl ORB
dnl ------------------------------------------------------------------

AC_SEARCH_LIBS(recv, resolv, [LIBS="$LIBS -lresolv"])

FRESCO_ORB
MAKEFILE=
if test ".$ORB" = .omniORB ; then
  MAKEFILE="Makefile.omniorb.in"
elif test ".$ORB" = .TAO ; then
  MAKEFILE="Makefile.tao.in"
fi

FRESCO_IDL_PATH

AC_SUBST(Fresco_IDL_prefix)

dnl ------------------------------------------------------------------
dnl General flags
dnl ------------------------------------------------------------------

FRESCO_FLAG_SO

dnl ------------------------------------------------------------------
dnl Graphics environment
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Graphics Environment])

FRESCO_GGI_CHECK
if test ".$HAVE_GGI" = .1 ; then
  FRESCO_GGIMESA_CHECK
else
  AC_MSG_ERROR([this package needs GGI to compile and run])
fi

FRESCO_PACKAGE(Fresco-C++, FRESCO_CXX, $PACKAGE_VERSION)
AC_SUBST(Fresco_CXX_prefix)

FRESCO_PACKAGE(Berlin, Berlin, $PACKAGE_VERSION)
CPPFLAGS="$CPPFLAGS $Berlin_BUILD_CPPFLAGS"
LIBS="$Berlin_BUILD_LIBS $LIBS"

dnl ------------------------------------------------------------------
dnl Decisions
dnl ------------------------------------------------------------------

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Output Substitution])

AC_CONFIG_FILES(config/local.mk)
AC_CONFIG_FILES([config/GGI.spec])
AC_CONFIG_FILES([Makefile src/Makefile demos/Makefile])
AC_CONFIG_FILES([GGIKit/Makefile:config/$MAKEFILE])

mkdir -p lib/Fresco/Console
mkdir -p bin

AC_OUTPUT
