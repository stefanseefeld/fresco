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

AC_INIT(../../src/Berlin/Makefile)
dnl AC_CONFIG_HEADER($top/include/Berlin/config.hh)

dnl Set AC_CONFIG_AUX_DIR to the top-level config directory. I don't know
dnl what the AC_DIVERT_PUSH magic does, but it is needed for AC_HEADLINE to
dnl know what our AUX_DIR is...
AC_DIVERT_PUSH(AC_DIVERSION_NOTICE)dnl
top=.
cpath=..
spath=../../src
AC_CONFIG_AUX_DIR($cpath)
AC_DIVERT_POP()

AC_HEADLINE(dnl
Berlin Server, The Berlin Server, dnl
Berlin_VERSION, $top/include/version.h, dnl
[Copyright (c) 2000 The Berlin Project <berlin-design@lists.sourceforge.net>])

dnl Load the global options first, then the local ones. The local options
dnl will then override the global.
AC_CONFIG_LOAD($cpath/config.param)
AC_CONFIG_LOAD($cpath/Server/config.param)

dnl Required to determine host CPU and OS in BERLIN_OMNIORB2_CHECK
AC_CANONICAL_SYSTEM

dnl ------------------------------------------------------------------
dnl CORBA environment
dnl ------------------------------------------------------------------
AC_MSG_PART(CORBA Environment)

BERLIN_ORB_CHECK(mandatory)

dnl ------------------------------------------------------------------
dnl Options controlling what to build
dnl ------------------------------------------------------------------

dnl The enable_PACKAGE vars might be set in config.param, so set them
dnl only if they don't exist, or if they are specified by the user.
AC_ARG_ENABLE(berlin,
	[  --disable-berlin        Don't build libBerlin],[
	enable_berlin="$enableval"],[
	if test ".$enable_berlin" = . ; then
		enable_berlin=yes
	fi])
AC_REGISTER_PARAM(enable_berlin)
AC_ARG_ENABLE(kits,
	[  --enable-kits=LIST      Specify which kits to build (default: all)],
[	if test ".$enableval" = .yes ; then
		enable_kits=all
	else
		enable_kits="$enableval"
	fi],[
	if test ".$enable_kits" = . ; then	
		enable_kits=all
	fi])
AC_REGISTER_PARAM(enable_kits)
AC_ARG_ENABLE(drawing,
	[  --enable-drawing=LIST   Specify which DrawingKits to build (default: all)], [
	if test ".$enableval" = .yes ; then
		enable_drawing_kits=all
	else
		enable_drawing_kits="$enableval"
	fi],[
	if test ".$enable_drawing_kits" = . ; then
		enable_drawing_kits=all
	fi])
AC_REGISTER_PARAM(enable_drawing_kits)
AC_ARG_ENABLE(server,
	[  --disable-server        Don't build the server],[
	enable_server="$enableval"],[
	enable_server=yes])
AC_REGISTER_PARAM(enable_server)

dnl ------------------------------------------------------------------
dnl For all enable_PACKAGE=yes, check if it is in the source tree
dnl ------------------------------------------------------------------
dnl if test ".$enable_berlin" = .yes ; then
dnl 	if test -d $spath/Berlin ; then
dnl 		enable_berlin=yes
dnl 	else
dnl 		enable_berlin=no
dnl 	fi
dnl fi

dnl ------------------------------------------------------------------
dnl Graphics environment
dnl ------------------------------------------------------------------
AC_MSG_PART(Graphics Environment)

BERLIN_GGI_CHECK(mandatory)

if test ".$enable_drawing_kits" = .all ; then
	enable_drawing_kits="libArt openGL"
elif test ".$enable_drawing_kits" = .no ; then
	enable_drawing_kits=
else
	dnl Handle comma-separated lists, too
	enable_drawing_kits=["`echo $enable_drawing_kits | sed 's/[, ]\+/ /g'`"]
fi

for kit in $enable_drawing_kits ; do
	if test -d $spath/Drawing/$kit ; then
		eval enable_$kit=yes
	else
		eval enable_$kit=no
	fi
done

tested_drawing_kits=
if test ".$enable_libArt" = .yes ; then
	BERLIN_LIBART_CHECK
	if test ".$ac_cv_lib_libArt" = .yes ; then
		tested_drawing_kits="$tested_drawing_kits Drawing/libArt"
	fi
fi
if test ".$enable_openGL" = .yes ; then
	BERLIN_GGIMESA_CHECK
	if test ".$ac_cv_lib_GGIMesa" = .yes ; then
		tested_drawing_kits="$tested_drawing_kits Drawing/openGL"
	fi
fi

dnl ------------------------------------------------------------------
dnl other kits to build
dnl ------------------------------------------------------------------

dnl Enable all Kits present if $enable_kits == all (the default)
if test ".$enable_kits" = .all ; then
	enable_kits=
	for kit in Layout Command Tool Image Figure Text Widget Gadget Desktop
	do
		if test -d $spath/$kit ; then
			enable_kits="$enable_kits $kit"
		fi
	done
	enable_kits=["`echo $enable_kits | sed 's/^ //'`"]
elif test ".$enable_kits" = .no ; then
	enable_kits=
else
	dnl Handle comma-separated lists, too
	enable_kits=["`echo $enable_kits | sed 's/[, ]\+/ /g'`"]
fi



dnl ------------------------------------------------------------------
dnl Decisions
dnl ------------------------------------------------------------------

dnl Decide which additional subdirectories are needed
BERLIN=
if test ".$enable_berlin" = .yes ; then
	BERLIN="src/Berlin"
fi
AC_SUBST(BERLIN)
for kit in $tested_drawing_kits $enable_kits
do
	KITS="$KITS src/$kit"
done
AC_SUBST(KITS)

SERVER="server"
AC_SUBST(SERVER)

dnl ------------------------------------------------------------------
dnl Print a summary of what's going to be built
dnl ------------------------------------------------------------------
AC_MSG_PART(Summary)
AC_MSG_RESULT([Build libBerlin:          $enable_berlin])
AC_MSG_RESULT([Build Kits:               $tested_drawing_kits $enable_kits])

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------
AC_MSG_PART(Output Substitution)

AC_MSG_RESULT(Storing configuration in $cpath/Server/config.param...)
AC_CONFIG_STORE($cpath/Server/config.param)

AC_OUTPUT($cpath/Server/local.mk:$cpath/Server/local.mk.in $cpath/Server/server.mk:$cpath/Server/server.mk.in)
