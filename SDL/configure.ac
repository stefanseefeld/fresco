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

AC_INIT(SDL, 0.3.0, devel@fresco.org)
AC_CONFIG_SRCDIR(../LICENSE)
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

AC_ARG_ENABLE(complete-deps,
              AC_HELP_STRING([--disable-complete-deps],[Use a faster, but less correct, dependency generator]),
              [complete_deps_enabled="$enableval"],
              [complete_deps_enabled=yes])

DEPFLAGS=
if test ".$complete_deps_enabled" = .yes ; then
  AC_SUBST(DEPFLAGS,-M)
else
  AC_SUBST(DEPFLAGS,-MM)
fi

FRESCO_FLAG_SO

dnl ------------------------------------------------------------------
dnl Graphics environment
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Graphics Environment])

FRESCO_SDL_CHECK
if test ".$HAVE_SDL" != .1 ; then
  AC_MSG_ERROR([this package needs SDL to compile and run])
fi

FRESCO_OPENGL_CHECK

FRESCO_PACKAGE(Fresco, $PACKAGE_VERSION)
CPPFLAGS="$CPPFLAGS $Fresco_CPPFLAGS"
LIBS="$LIBS -lFresco $Fresco_LIBS"
FRESCO_PACKAGE(Berlin, $PACKAGE_VERSION)
CPPFLAGS="$CPPFLAGS $Berlin_CPPFLAGS"
LIBS="$LIBS -lBabylon $Berlin_LIBS"

dnl ------------------------------------------------------------------
dnl Decisions
dnl ------------------------------------------------------------------

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Output Substitution])

AC_CONFIG_FILES(config/local.mk)
AC_CONFIG_FILES([Makefile src/Makefile])

mkdir -p lib/Fresco/Console

AC_OUTPUT