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
if test -d $srcdir/GGI; then
  AC_CONFIG_SUBDIRS(GGI)
fi
if test -d $srcdir/SDL; then
  AC_CONFIG_SUBDIRS(SDL)
fi
if test -d $srcdir/Clients-C++; then
  AC_CONFIG_SUBDIRS(Clients-C++)
fi
if test -d $srcdir/Clients-Python; then
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
