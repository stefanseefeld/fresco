dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2000 Håvard Skinnemoen <skinnemo@users.sourceforge.net>
dnl http://berlin.benham.net/
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

dnl BERLIN_ORB_CHECK(mandatory-flag)
dnl
dnl Try to find a usable ORB. If mandatory-flag is "mandatory", abort if
dnl none is found.
dnl For now, only omniORB2 is supported.

AC_DEFUN([BERLIN_ORB_CHECK],[

	AC_ARG_WITH(orb,[  --with-orb=NAME         Specify which ORB to use],[dnl
		ORB="$withval"],[dnl
		if test ".$ORB" = . ; then
			ORB="auto"
		fi])
	AC_REGISTER_PARAM(ORB)

	case $ORB in
		omniORB2|auto)
			BERLIN_OMNIORB2_CHECK
			if test ".$ac_cv_lib_omniORB2" != .yes; then
				if test ".$1" = .mandatory; then
					AC_MSG_ERROR(No supported CORBA environment found!)
				else
					ORB="none"
				fi
			else
				ORB=omniORB2
			fi				
			;;
		*)
			if test ".$1" = .mandatory; then
				AC_MSG_ERROR($ORB is not supported!)
			else
				AC_MSG_WARN($ORB is not supported!)
			fi
			;;
	esac
	
	case $ORB in
		omniORB2)
			IDL="$OMNIIDL2"
			IDLFLAGS=""
			LCIDLFLAGS="-l"
			DYNIDLFLAGS="-a"
			ORBFLAGS="__OMNIORB2__"
		;;
	esac

	AC_SUBST(ORB)
	if test ".$ORB" != .none ; then
		AC_SUBST(IDL)
		AC_SUBST(IDLFLAGS)
		AC_SUBST(LCIDLFLAGS)
		AC_SUBST(DYNIDLFLAGS)
		AC_DEFINE_UNQUOTED(ORBFLAGS, $ORBFLAGS)
		AC_SUBST(ORBFLAGS)
		AC_SUBST(ORBDEFS)
		AC_SUBST(ORBCPPFLAGS)
		AC_SUBST(ORBLIBS)
	fi
])
