dnl $Id$
dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

AC_INIT(LICENSE.Berlin)
AC_SET_PATHS(.)

AC_DIVERT_PUSH(AC_DIVERSION_INIT)dnl
AC_CONFIG_AUX_DIR(config)
AC_DIVERT_POP()

AC_HEADLINE(dnl
Berlin, The Berlin Windowing System, dnl
[Copyright (c) 2000 The Berlin Project <berlin-design@lists.sourceforge.net>])

dnl ------------------------------------------------------------------
dnl Options controlling what to build
dnl ------------------------------------------------------------------

dnl The enable_PACKAGE vars might be set in config.param, so set them
dnl only if they don't exist, or if they are specified by the user.
AC_ARG_ENABLE(prague,
        [  --disable-prague        Don't build libPrague],[
        enable_prague="$enableval"],[
        if test ".$enable_prague" = . ; then
                enable_prague=yes
        fi])
AC_ARG_ENABLE(babylon,
	[ --disable-babylon	   Don't build libBabylon],[
	enable_babylon="$enableval"],[
	if test ".$enable_babylon" = . ; then
		enable_babylon=yes
	fi])
AC_ARG_ENABLE(warsaw,
	[  --disable-warsaw        Don't build libWarsaw],[
	enable_warsaw="$enableval"],[
	if test ".$enable_warsaw" = . ; then
		enable_warsaw=yes
	fi])
AC_ARG_ENABLE(server,
	[  --disable-server        Don't build the server],[
	enable_server="$enableval"],[
	enable_server=yes])
AC_ARG_ENABLE(cxx-clients,
	[  --disable-cxx-clients   Don't build the C++ clients],[
	enable_cxx_clients="$enableval"],[
	enable_cxx_clients=yes])
AC_ARG_ENABLE(py-clients,
        [  --disable-py-clients    Don't build the Python clients],[
        enable_python_clients="$enableval"],[
        enable_python_clients=yes])
AC_ARG_ENABLE(perl-clients,
	[  --enable-perl-clients   Build the Perl clients],[
	enable_perl_clients="$enableval"],[
	enable_perl_clients=no])
AC_ARG_ENABLE(docs,
	[  --enable-docs           Build the documentation],[
	enable_docs="$enableval"],[
	enable_docs=yes])
AC_ARG_ENABLE(complete-deps,
	[  --disable-complete-deps Use a faster, but less correct, dependency generator],[
	enable_complete_deps="$enableval"],[
	enable_complete_deps=yes])

dnl ------------------------------------------------------------------
dnl For all enable_PACKAGE=yes, check if it is in the source tree
dnl ------------------------------------------------------------------
enable_clients=
if test ".$enable_prague" = .yes ; then
        if test -d $srcdir/src/Prague ; then
                enable_prague=yes
        else
                enable_prague=no
        fi
fi
if test ".$enable_babylon" = .yes ; then
	if test -d $srcdir/src/Babylon ; then
		enable_babylon=yes
	else
		enable_babylon=no
	fi
fi
if test ".$enable_warsaw" = .yes ; then
	if test -d $srcdir/src/Warsaw ; then
		enable_warsaw=yes
	else
                enable_warsaw=no
        fi
fi
if test ".$enable_server" = .yes ; then
	if test -d $srcdir/server ; then
		enable_server=yes
	else
		enable_server=no
	fi
fi
if test ".$enable_cxx_clients" = .yes ; then
	if test -d $srcdir/clients/C++ ; then
		enable_cxx_clients=yes
		enable_clients="$enable_clients C++"
	else
		enable_cxx_clients=no
	fi
fi
if test ".$enable_python_clients" = .yes ; then
        if test -d $srcdir/clients/python ; then
                enable_python_clients=yes
		enable_clients="$enable_clients Python"
        else
                enable_python_clients=no
        fi
fi
if test ".$enable_perl_clients" = .yes ; then
	if test -d $srcdir/clients/perl ; then
		enable_perl_clients=yes
		enable_clients="$enable_clients Perl"
	else
		enable_perl_clients=no
	fi
fi
if test ".$enable_docs" = .yes ; then
	if test -d $srcdir/doc ; then
		enable_docs=yes
	else
		enable_docs=no
	fi
fi

dnl ------------------------------------------------------------------
dnl Build tools
dnl ------------------------------------------------------------------
AC_MSG_PART(Build Tools)

AC_PROG_MAKE_SET
AC_PROG_CC_CXX
AC_PROG_INSTALL
BERLIN_FLAG_SO

AC_CHECK_DEBUGGING
AC_CHECK_OPTIMIZE

DEPFLAGS=
if test ".$enable_complete_deps" = .yes ; then
	DEPFLAGS=-M
else
	DEPFLAGS=-MM
fi
AC_SUBST(DEPFLAGS)

dnl ------------------------------------------------------------------
dnl Decisions
dnl ------------------------------------------------------------------

dnl Figure out the packages to configure and build
ac_subdirs=
if test ".$enable_prague" = .yes;
	then
		mkdir -p config/Prague
		ac_subdirs="$ac_subdirs config/Prague"
	fi
if test ".$enable_babylon" = .yes;
	then
		mkdir -p config/Babylon
		ac_subdirs="$ac_subdirs config/Babylon"
	fi
if test ".$enable_warsaw" = .yes ;
	then
		mkdir -p config/Warsaw
		ac_subdirs="$ac_subdirs config/Warsaw"
	fi
if test ".$enable_server" = .yes ;
	then
		mkdir -p config/Server
		ac_subdirs="$ac_subdirs config/Server"
	fi
if test ".$enable_cxx_clients" = .yes ;
	then
		mkdir -p config/Clients-C++
		ac_subdirs="$ac_subdirs config/Clients-C++"
	fi
if test ".$enable_python_clients" = .yes ;
	then
		mkdir -p config/Clients-Python
		ac_subdirs="$ac_subdirs config/Clients-Python"
	fi
if test ".$enable_perl_clients" = .yes ;
	then
		echo "strangely, I'm here !!!!!!"
		mkdir -p config/Clients-Perl
		ac_subdirs="$ac_subdirs config/Clients-Perl"
	fi
if test ".$enable_docs" = .yes ;
	then
		mkdir -p config/Docs
		ac_subdirs="$ac_subdirs config/Docs"
	fi
AC_CONFIG_SUBDIRS($ac_subdirs)

dnl ------------------------------------------------------------------
dnl Print a summary of what's going to be configured
dnl ------------------------------------------------------------------
AC_MSG_PART(Summary)
AC_MSG_RESULT([Configure Prague:          $enable_prague])
AC_MSG_RESULT([Configure Babylon:         $enable_babylon])
AC_MSG_RESULT([Configure Warsaw:          $enable_warsaw])
AC_MSG_RESULT([Configure Server:          $enable_server])
AC_MSG_RESULT([Configure Clients:         $enable_clients])
AC_MSG_RESULT([Configure Documentation:   $enable_docs])

dnl ------------------------------------------------------------------
dnl Output substitution
dnl ------------------------------------------------------------------
AC_MSG_PART(Output Substitution)

mkdir -p config

AC_OUTPUT([
	Makefile:Makefile.in
	config/local.mk:config/local.mk.in
])
