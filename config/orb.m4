dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 2000 Håvard Skinnemoen <skinnemo@itk.ntnu.no>
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

dnl ------------------------------------------------------------------

dnl FRESCO_LIB_ORB(mandatory-flag)
dnl
dnl Try to find a usable ORB. If mandatory-flag is "mandatory", abort if
dnl none is found.
dnl For now, omniORB and TAO are supported.
dnl This macro doesn't check anything by itself. It just delegates it to
dnl secondary macros, which checks if the specific ORB is available and
dnl sets ORB_LIBS, ORB_CPPFLAGS, IDLCXX, IDLCXXFLAGS, IDLDYNFLAGS and
dnl IDLTIEFLAGS. Those variables are AC_SUBSTed here.

AC_DEFUN([FRESCO_LIB_ORB],[

	AC_MSG_NOTICE(ORB)
	AC_ARG_WITH(orb,
		[  --with-orb=NAME         Specify which ORB to use],[dnl
		ORB="$withval"],[dnl
		if test ".$ORB" = "." ; then
			ORB="auto"
		fi])

	case "$ORB" in
		omniORB|auto)
			FRESCO_LIB_OMNIORB
			if test ".$fresco_cv_lib_omniORB" != ".yes"; then
				ifelse($1,mandatory,AC_MSG_ERROR(No supported CORBA environment found!),ORB="none")
			else
				ORB=omniORB
			fi		
			;;
		TAO)
			FRESCO_LIB_TAO
			if test ".$fresco_cv_lib_TAO" != ".yes"; then
				ifelse($1,mandatory,AC_MSG_ERROR(No supported CORBA environment found!),ORB="none")
			else
				ORB=TAO
			fi		
			;;
 		*)
 			msg="$ORB is not supported (yet)."
 			ifelse($1,mandatory,AC_MSG_ERROR($msg),
 				AC_MSG_WARN($msg))
 			ORB=none
 			;;
	esac
	
	case $ORB in
		omniORB)
			AC_MSG_RESULT([use omniORB])
			AC_DEFINE(ORB_omniORB, 1, [Define if omniORB is used.])
			;;
		TAO)
			AC_MSG_RESULT([use TAO])
			AC_DEFINE(ORB_TAO, 1, [Define if TAO is used.])
			;;
		none)
			AC_MSG_RESULT([none found])
			;;
	esac
	AC_SUBST(ORB)
	AC_SUBST(CPPFLAGS)
	AC_SUBST(LIBS)
	AC_SUBST(IDLCXX)
])
