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

AC_PREREQ(2.52)
AC_REVISION($Revision$)
AC_INIT(Berlin, M1, devel@fresco.org)
AC_CONFIG_AUX_DIR(config)

dnl ------------------------------------------------------------------
dnl CORBA environment
dnl ------------------------------------------------------------------

dnl AC_MSG_PART(CORBA Environment)
FRESCO_OMNIORBPY

FRESCO_IDL_PATH

AC_SUBST(Fresco_IDL_prefix)

AC_PATH_PROGS([python_program], [python python1.6 python2.1 python2.2])
if test ".$python_program" == "." ; then
  AC_MSG_ERROR([can't install Python bindings without interpreter])
fi

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------

dnl AC_MSG_PART(Output Substitution)

AC_CONFIG_FILES([setup.py], [chmod +x setup.py])
AC_CONFIG_FILES([config/local.mk])
AC_CONFIG_FILES([Makefile Fresco/Makefile:config/Makefile.omniorb.in])
if test "$srcdir" != .; then
  AC_CONFIG_LINKS([Fresco/__init__.py:Fresco/__init__.py])
fi

AC_OUTPUT
