dnl $Id$
dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 2000 Håvard Skinnemoen <skinnemo@itk.ntnu.no>
dnl Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
dnl Copyright (C) 2000 Tobias Hunger <tobias@fresco.org>
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

AC_INIT(Babylon, M1, devel@fresco.org)
AC_CONFIG_SRCDIR(LICENSE)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADER(include/Babylon/acconfig.hh:config/acconfig.hh.in)

AC_CANONICAL_SYSTEM

AC_PROG_MAKE_SET
AC_LANG(C++)

dnl ------------------------------------------------------------------
dnl Prague
dnl ------------------------------------------------------------------

FRESCO_PACKAGE(Prague, Prague, $PACKAGE_VERSION, ..)
INSTALL_CPPFLAGS="$CPPFLAGS $Prague_CPPFLAGS"
INSTALL_LIBS="$Prague_LIBS $LIBS"
CPPFLAGS="$CPPFLAGS $Prague_BUILD_CPPFLAGS"
LIBS="$Prague_BUILD_LIBS $LIBS"

AC_SUBST(INSTALL_CPPFLAGS)
AC_SUBST(INSTALL_LIBS)

dnl ------------------------------------------------------------------
dnl General flags
dnl ------------------------------------------------------------------

AC_ARG_ENABLE(unicode-blocks,
              AC_HELP_STRING([--enable-unicode-blocks],[complete or latin unicode support]),
              [AC_SUBST(UNICODE_BLOCKS,"$enableval")],
              [AC_SUBST(UNICODE_BLOCKS,complete)])

FRESCO_FLAG_SO

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Output Substitution])

AC_CONFIG_FILES([config/local.mk config/synopsis.py])
AC_CONFIG_FILES([config/Babylon.spec])
AC_CONFIG_FILES([config/Babylon-config], [chmod +x config/Babylon-config])
AC_CONFIG_FILES([bin/Babylon-config:config/Babylon-build-config.in], [chmod +x bin/Babylon-config])
AC_CONFIG_FILES([Makefile src/Makefile modules/Makefile])

mkdir -p lib
mkdir -p modules
mkdir -p bin

AC_OUTPUT