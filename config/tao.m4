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

dnl TAO uses $ACE_ROOT and $TAO_ROOT, so let's just rely on it for now...
dnl
dnl Checks if TAO is found. If it
dnl is, $fresco_cv_lib_TAO is set to "yes". Also, the
dnl variables IDLCXX, ORB_LIBS
dnl and ORB_CPPFLAGS are set, and necessary definitions are added.

AC_DEFUN([FRESCO_LIB_TAO],[

	AC_REQUIRE([AC_CANONICAL_SYSTEM])
	AC_REQUIRE([AC_PROG_CC])
	AC_REQUIRE([AC_PROG_CXX])
	AC_REQUIRE([AC_PROG_CPP])
	AC_REQUIRE([AC_PROG_CXXCPP])

	use_tao=
	if test ".$ACE_ROOT" = "." -a ".$TAO_ROOT" = "." ; then
		use_tao="yes"
	fi

	dnl Check for tao_idl
	if test ".$TAO_ROOT" != "." ; then
		tao_idl_path="$TAO_ROOT/TAO_IDL:$PATH"
		ORB_LIBS="-L$ACE_ROOT/ace -L$TAO_ROOT/tao"
		ORB_CPPFLAGS="-I$ACE_ROOT -I$TAO_ROOT"
	else
		tao_idl_path="$PATH"
	fi
	AC_PATH_PROG(IDLCXX, tao_idl, no, $tao_idl_path)
	if test ".$IDLCXX" = ".no" ; then
		no_tao="yes"
	fi
	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS $ORB_CPPFLAGS"
	dnl Check for TAO libraries
	if test ".$no_tao" = "." ; then
		ORB_LIBS="$ORB_LIBS -lACE"
		FRESCO_CHECK_LIB(ORB_LIBS, TAO, [CORBA::ORB_var orb;],
				tao/ORB.h)
		if test ".$fresco_cv_lib_tao" = ".no" \
			-a ".$fresco_cv_lib_tao" = ".no" ; then
			no_tao="yes"
		fi
		LIBS="$ORB_LIBS $LIBS"
	fi

dnl	CPPFLAGS="$save_CPPFLAGS"

	if test ".$no_tao" = "." ; then
		fresco_cv_lib_tao="yes"
	fi

])
