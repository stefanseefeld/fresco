dnl $Id$
dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2000 Håvard Skinnemoen <skinnemo@itk.ntnu.no>
dnl http://www.berlin-consortium.org/
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

AC_INIT(../../clients/python/Makefile)
dnl AC_CONFIG_HEADER($top/include/Berlin/config.hh)

dnl Set AC_CONFIG_AUX_DIR to the top-level config directory. I don't know
dnl what the AC_DIVERT_PUSH magic does, but it is needed for AC_HEADLINE to
dnl know what our AUX_DIR is...
AC_DIVERT_PUSH(AC_DIVERSION_NOTICE)dnl
top=../..
cpath=..
spath=$top/src
AC_CONFIG_AUX_DIR($cpath)
AC_DIVERT_POP()

AC_HEADLINE(dnl
Berlin Clients Python, Berlin python clients, dnl
Berlin_VERSION, $top/include/version.h, dnl
[Copyright (c) 2000 The Berlin Project <berlin-design@lists.sourceforge.net>])

dnl ------------------------------------------------------------------
dnl CORBA environment
dnl ------------------------------------------------------------------
AC_MSG_PART(CORBA Environment)
BERLIN_OMNIORBPY_CHECK

dnl ------------------------------------------------------------------
dnl Decisions
dnl ------------------------------------------------------------------

dnl Decide whether we are ready to build
PYTHON=
if test ".$berlin_cv_sys_omniidl_py" = .yes ; then
	PYTHON="clients/python"
fi
AC_SUBST(PYTHON)

dnl ------------------------------------------------------------------
dnl Print a summary of what's going to be built
dnl ------------------------------------------------------------------
AC_MSG_PART(Summary)
AC_MSG_RESULT([Build Python runtime:          $ac_cv_lib_omniORBpy])

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------
AC_MSG_PART(Output Substitution)

AC_OUTPUT($cpath/Clients-Python/local.mk:$cpath/Clients-Python/local.mk.in $cpath/Clients-Python/clients-python.mk:$cpath/Clients-Python/clients-python.mk.in)
