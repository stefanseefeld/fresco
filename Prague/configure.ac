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

AC_INIT($top/src/Prague/Sys/DLL.cc)
AC_CONFIG_HEADER($top/include/Prague/Sys/config.hh)

dnl Set AC_CONFIG_AUX_DIR to the top-level config directory. I don't know
dnl what the AC_DIVERT_PUSH magic does, but it is needed for AC_HEADLINE to
dnl know what our AUX_DIR is...
AC_DIVERT_PUSH(AC_DIVERSION_NOTICE)dnl
top=../..
cpath=..
AC_CONFIG_AUX_DIR($cpath)
AC_DIVERT_POP()

AC_HEADLINE(dnl
Prague, The Berlin Utility Library, dnl
Berlin_VERSION, $top/include/version.h, dnl
[Copyright (c) 2000 The Berlin Project <berlin-design@lists.sourceforge.net>])

SH_VERSION='\$Revision\$'
AC_SUBST(SH_VERSION)

dnl ------------------------------------------------------------------
dnl General flags
dnl ------------------------------------------------------------------
AC_ARG_ENABLE(tracer,
        [  --enable-tracer        Compile with tracer support],[
        AC_DEFINE(TRACER)])

AC_MSG_PART(platform specific system utilities)
AC_CHECK_FUNCS(strsignal)
AC_NEED_DECLARATION(strsignal)
AC_CHECK_LIB(z, gzsetparams, AC_DEFINE(HAVE_ZLIB), AC_MSG_ERROR(update your zlib, please))

BERLIN_LIB_PTHREAD

dnl ------------------------------------------------------------------
dnl Plugin support
dnl ------------------------------------------------------------------
AC_MSG_PART(Dynamic Loading Implementation)

AC_CHECK_HEADERS(dlfcn.h dl.h)
AC_CHECK_LIB(dl, dlopen)
AC_CHECK_FUNCS(dlopen dlsym dlclose shl_load)
AC_BEGIN_DECISION([plugin method])
AC_IFALLYES(header:dlfcn.h func:dlopen func:dlsym func:dlclose,
	AC_DECIDE(DLFCN, [use dlopen family of functions for plugins]))
AC_IFALLYES(header:dl.h func:shl_load,
	AC_DECIDE(DLAIX, [use AIX shm_load for plugins]))
AC_END_DECISION
if test ".$ac_decision" = ".DLFCN" ; then
	AC_DEFINE(HAVE_DLFCN)
else
	AC_DEFINE(HAVE_DLAIX)
fi

dnl ------------------------------------------------------------------
dnl IPC support
dnl ------------------------------------------------------------------
AC_MSG_PART(IPC Implementation)
BERLIN_LIB_SOCKET

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------
AC_MSG_PART(Output Substitution)

AC_OUTPUT([
	$cpath/Prague/local.mk:$cpath/Prague/local.mk.in
	$cpath/Prague/PragueConf.sh:$cpath/Prague/PragueConf.sh.in
	$cpath/Prague/PragueConf-u.sh:$cpath/Prague/PragueConf-u.sh.in
])
