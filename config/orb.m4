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

dnl FRESCO_ORB
dnl
dnl Try to find a usable ORB. If mandatory-flag is "mandatory", abort if
dnl none is found.
dnl For now, omniORB and TAO are supported.
dnl This macro doesn't check anything by itself. It just delegates it to
dnl secondary macros, which checks if the specific ORB is available and
dnl sets ORB_LIBS, ORB_CPPFLAGS, IDLCXX, IDLCXXFLAGS, IDLDYNFLAGS and
dnl IDLTIEFLAGS. Those variables are AC_SUBSTed here.

AC_DEFUN([FRESCO_ORB],[

	AC_MSG_NOTICE(checking for CORBA environment.)
	AC_ARG_WITH(orb,
		[  --with-orb=NAME         Specify which ORB to use],[dnl
		ORB="$withval"],[dnl
		if test ".$ORB" = "." ; then
			ORB="auto"
		fi])

        supported_orb_found="none"
        checked_orbs=""

        dnl Test for omniORB
        if test \( ".$ORB" = ".omniORB" -o ".$ORB" = ".auto" \) -a \
                \( ".$supported_orb_found" = ".none" \) ; then
            AC_MSG_NOTICE(... omniORB)
            checked_orbs="${checked_orbs}${checked_orbs:+, }omniORB"
            FRESCO_OMNIORB
            if test ".$fresco_cv_lib_omniORB" = ".yes"; then
                supported_orb_found="omniORB"
            fi
        fi

        dnl Test for TAO
        if test \( ".$ORB" = ".TAO" -o ".$ORB" = ".auto" \) -a \
                \( ".$supported_orb_found" = ".none" \) ; then
            AC_MSG_NOTICE(... TAO)
            checked_orbs="${checked_orbs}${checked_orbs:+, }TAO"
            FRESCO_TAO
            if test ".$fresco_cv_lib_TAO" = ".yes"; then
                supported_orb_found="TAO"
            fi
        fi

        dnl Invald ORB passed in via configure setting.
        if test \( ".$ORB" != ".auto" \) -a \
                \( ".$checked_orbs" = "." \) ; then
            AC_MSG_ERROR([$ORB is not a supported CORBA environment (yet).])
        fi

	AC_MSG_CHECKING(for CORBA environment done)
	case $supported_orb_found in
		omniORB)
		  AC_MSG_RESULT([using omniORB])
		  AC_DEFINE(ORB_omniORB, 1, [Define if omniORB is used.])
		;;
		TAO)
		  AC_MSG_RESULT([using TAO])
	  	  AC_DEFINE(ORB_TAO, 1, [Define if TAO is used.])
		;;
		none)
		  AC_MSG_RESULT([none found (I checked for '$checked_orbs')])
                  AC_MSG_ERROR([No supported CORBA environment found, stopping.])
		;;
	esac
	AC_SUBST(ORB)
	AC_SUBST(CPPFLAGS)
	AC_SUBST(LIBS)
	AC_SUBST(IDLCXX)
])
