dnl $Id$
dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) Håvard Skinnemoen <skinnemo@itk.ntnu.no>
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

AC_INIT($top/src/Warsaw/Makefile)
AC_CONFIG_HEADER($top/include/Warsaw/config.hh)

dnl Set AC_CONFIG_AUX_DIR to the top-level config directory. I don't know
dnl what the AC_DIVERT_PUSH magic does, but it is needed for AC_HEADLINE to
dnl know what our AUX_DIR is...
AC_DIVERT_PUSH(AC_DIVERSION_NOTICE)dnl
top=../..
cpath=..
AC_CONFIG_AUX_DIR($cpath)
AC_DIVERT_POP()

AC_HEADLINE(dnl
Warsaw, The Berlin Protocol, dnl
Berlin_VERSION, $top/include/version.h, dnl
[Copyright (c) 2000 The Berlin Project <berlin-design@lists.sourceforge.net>])

SH_VERSION='\$Revision\$'
AC_SUBST(SH_VERSION)

dnl ------------------------------------------------------------------

dnl TODO: Do this better
AC_MSG_CHECKING("for C++ optimization flags")
CXXFLAGS="-O2 -fno-default-inline -fomit-frame-pointer -fnonnull-objects"
AC_MSG_RESULT($CXXFLAGS)

BERLIN_LIB_ORB

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------
AC_MSG_PART(Output Substitution)

AC_OUTPUT([
$cpath/Warsaw/local.mk:$cpath/Warsaw/local.mk.in
$cpath/Warsaw/WarsawConf.sh:$cpath/Warsaw/WarsawConf.sh.in
$cpath/Warsaw/WarsawConf-u.sh:$cpath/Warsaw/WarsawConf-u.sh.in
])
