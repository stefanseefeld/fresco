dnl $Id$
dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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
AC_INIT(Fresco, M3, devel@fresco.org)
AC_CONFIG_SRCDIR(LICENSE)
AC_CONFIG_AUX_DIR(config)

echo "The Fresco Windowing System,
Copyright (c) 2000 The Fresco Project <devel@fresco.org>
"

dnl ------------------------------------------------------------------
dnl Options controlling what to build
dnl ------------------------------------------------------------------

AC_ARG_ENABLE(prague,
              AC_HELP_STRING([--disable-prague],[Don't build Prague]),
              [prague_enabled="$enableval"],
              [prague_enabled=yes])

AC_ARG_ENABLE(babylon,
              AC_HELP_STRING([--disable-babylon],[Don't build libBabylon]),
              [babylon_enabled="$enableval"],
              [babylon_enabled=yes])

AC_ARG_ENABLE(fresco,
              AC_HELP_STRING([--disable-fresco],[Don't build libFresco]),
              [fresco_enabled="$enableval"],
              [fresco_enabled=yes])

AC_ARG_ENABLE(berlin,
              AC_HELP_STRING([--disable-berlin],[Don't build the berlin server]),
              [berlin_enabled="$enableval"],
              [berlin_enabled=yes])

AC_ARG_ENABLE(cxx-clients,
              AC_HELP_STRING([--disable-cxx-clients],[Don't build the C++ clients]),
              [cxx_clients_enabled="$enableval"],
              [cxx_clients_enabled=yes])

AC_ARG_ENABLE(py-clients,
              AC_HELP_STRING([--disable-py-clients],[Don't build the Python clients]),
              [python_clients_enabled="$enableval"],
              [python_clients_enabled=yes])

AC_ARG_ENABLE(java-clients,
              AC_HELP_STRING([--disable-java-clients],[Don't build the Java clients]),
              [java_clients_enabled="$enableval"],
              [java_clients_enabled=no])

AC_ARG_ENABLE(perl-clients,
              AC_HELP_STRING([--enable-perl-clients],[Build the Perl clients]),
              [perl_clients_enabled="$enableval"],
              [perl_clients_enabled=no])

enable_clients=
if test ".$cxx_clients_enabled" = .yes ; then
  enable_clients="C++"
fi
if test ".$python_clients_enabled" = .yes ; then
  enable_clients="$enable_clients Python"
fi
if test ".$java_clients_enabled" = .yes ; then
  enable_clients="$enable_clients Java"
fi
if test ".$perl_clients_enabled" = .yes ; then
  enable_clients="$enable_clients Perl"
fi

dnl ------------------------------------------------------------------
dnl Build tools
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Build Tools])

AC_PROG_MAKE_SET

dnl ------------------------------------------------------------------
dnl Print a summary of what's going to be configured
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Summary])
AC_MSG_RESULT([Configure Prague:          $prague_enabled])
AC_MSG_RESULT([Configure Babylon:         $babylon_enabled])
AC_MSG_RESULT([Configure Fresco:          $fresco_enabled])
AC_MSG_RESULT([Configure Berlin:          $berlin_enabled])
AC_MSG_RESULT([Configure clients for:     $enable_clients])

dnl ------------------------------------------------------------------
dnl Decisions
dnl ------------------------------------------------------------------

if test ".$prague_enabled" ; then
  AC_CONFIG_SUBDIRS(Prague)
fi
if test ".$babylon_enabled" ; then
  AC_CONFIG_SUBDIRS(Babylon)
fi
if test ".$fresco_enabled" ; then
  AC_CONFIG_SUBDIRS(Fresco)
fi
if test ".$berlin_enabled" ; then
  AC_CONFIG_SUBDIRS(Berlin)
fi
if test ".$cxx_clients_enabled" ; then
  AC_CONFIG_SUBDIRS(Clients-C++)
fi
if test ".$python_clients_enabled" ; then
  AC_CONFIG_SUBDIRS(Clients-Python)
fi
if test ".$java_clients_enabled" ; then
  AC_CONFIG_SUBDIRS(Clients-Java)
fi
if test ".$perl_clients_enabled" ; then
  AC_CONFIG_SUBDIRS(Clients-Perl)
fi

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Output Substitution])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
