dnl $Id$
dnl
dnl This source file is a part of the Fresco Project.
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

AC_ARG_ENABLE(ggi,
              AC_HELP_STRING([--enable-ggi],[Configure with ggi support]),
              [config_ggi="$enableval"],[config_ggi="yes"])
AC_ARG_ENABLE(sdl,
              AC_HELP_STRING([--enable-sdl],[Configure with sdl support]),
              [config_sdl="$enableval"],[config_sdl="yes"])
AC_ARG_ENABLE(clients-c++,
              AC_HELP_STRING([--enable-clients-c++],[Configure c++ clients support]),
              [config_clients_cxx="$enableval"],[config_clients_cxx="yes"])
AC_ARG_ENABLE(clients-python,
              AC_HELP_STRING([--enable-clients-py],[Configure python clients support]),
              [config_clients_py="$enableval"],[config_clients_py="yes"])

if test -d $srcdir/Prague; then
  AC_CONFIG_SUBDIRS(Prague)
fi
if test -d $srcdir/Babylon; then
  AC_CONFIG_SUBDIRS(Babylon)
fi
if test -d $srcdir/Fresco; then
  AC_CONFIG_SUBDIRS(Fresco)
fi
if test -d $srcdir/Berlin; then
  AC_CONFIG_SUBDIRS(Berlin)
fi
if test -d $srcdir/GGI -a ".$config_ggi" = ".yes"; then
  AC_CONFIG_SUBDIRS(GGI)
fi
if test -d $srcdir/SDL -a ".$config_sdl" = ".yes"; then
  AC_CONFIG_SUBDIRS(SDL)
fi
if test -d $srcdir/Clients-C++ -a ".$config_clients_cxx" = ".yes"; then
  AC_CONFIG_SUBDIRS(Clients-C++)
fi
if test -d $srcdir/Clients-Python -a ".$config_clients_py" = ".yes"; then
  AC_CONFIG_SUBDIRS(Clients-Python)
fi
if test -d $srcdir/Clients-Java; then
  AC_CONFIG_SUBDIRS(Clients-Java)
fi
if test -d $srcdir/Clients-Perl; then
  AC_CONFIG_SUBDIRS(Clients-Perl)
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
