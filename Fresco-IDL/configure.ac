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
AC_PREREQ(2.53)
AC_REVISION($Revision$)

AC_INIT(Fresco-IDL, M1, devel@fresco.org)
AC_CONFIG_SRCDIR(LICENSE)
AC_CONFIG_AUX_DIR(config)

AC_PROG_MAKE_SET

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

AC_MSG_NOTICE([Output Substitution])

AC_CONFIG_FILES([config/synopsis.py])
AC_CONFIG_FILES([config/Fresco-IDL.spec])
AC_CONFIG_FILES([Makefile])
if test "$srcdir" != .; then
  AC_CONFIG_LINKS([share/idl:share/idl])
fi

mkdir -p lib

AC_OUTPUT
