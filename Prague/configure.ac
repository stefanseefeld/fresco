dnl $Id$
dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2000 Håvard Skinnemoen <skinnemo@itk.ntnu.no>
dnl Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

AC_INIT(subdirs.mk.in)
AC_VERSION(0, 2, 2, 0, 0)
AC_SET_PATHS(../..)
AC_CONFIG_HEADER($builddir/include/Prague/config.hh:config/Prague/config.hh.in)

AC_DIVERT_PUSH(AC_DIVERSION_INIT)dnl
AC_CONFIG_AUX_DIR(config)
AC_DIVERT_POP()

AC_HEADLINE(dnl
Prague, The Berlin Utility Library, dnl
[Copyright (c) 2000 The Berlin Project <berlin-design@lists.sourceforge.net>],
VERSION)

AC_LANG_CPLUSPLUS
dnl ------------------------------------------------------------------
dnl General flags
dnl ------------------------------------------------------------------
AC_ARG_ENABLE(tracer,
        [  --enable-tracer        Compile with tracer support],[
        AC_DEFINE(TRACER)])

AC_ARG_ENABLE(unicode-blocks,
	[  --enable-unicode-blocks complete or latin unicode support],[
	UNICODE_BLOCKS="$enableval"],[
	UNICODE_BLOCKS=complete])

AC_SUBST(UNICODE_BLOCKS)

AC_MSG_PART(platform specific system utilities)
AC_CHECK_FUNCS(strsignal)
AC_CHECK_HEADERS(string.h)
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

mkdir -p $builddir/bin
mkdir -p $builddir/lib
mkdir -p $builddir/config/Prague
mkdir -p $builddir/include/Prague
mkdir -p $builddir/src/Prague
dnl mkdir -p $builddir/src/Prague/SAX/expat
mkdir -p $builddir/src/Prague/Examples/Sys
mkdir -p $builddir/src/Prague/Examples/Thread
mkdir -p $builddir/src/Prague/Examples/IPC
mkdir -p $builddir/src/Prague/Examples/Filter
mkdir -p $builddir/src/Prague/Examples/Network
mkdir -p $builddir/src/Prague/Examples/bin

AC_OUTPUT([
	$builddir/bin/Prague-config:config/package-config.in
	$builddir/config/Prague/subdirs.mk:config/Prague/subdirs.mk.in
	$builddir/src/Prague/Makefile:src/Prague/Makefile.in
dnl $builddir/src/Prague/SAX/expat/Makefile:src/Prague/SAX/expat/Makefile.in
	$builddir/src/Prague/Examples/Makefile:src/Prague/Examples/Makefile.in
	$builddir/src/Prague/Examples/Sys/Makefile:src/Prague/Examples/Sys/Makefile.in
	$builddir/src/Prague/Examples/Thread/Makefile:src/Prague/Examples/Thread/Makefile.in
	$builddir/src/Prague/Examples/IPC/Makefile:src/Prague/Examples/IPC/Makefile.in
	$builddir/src/Prague/Examples/Filter/Makefile:src/Prague/Examples/Filter/Makefile.in
	$builddir/src/Prague/Examples/Network/Makefile:src/Prague/Examples/Network/Makefile.in
],[
	chmod +x $builddir/bin/Prague-config
],[
	builddir=$builddir
])
