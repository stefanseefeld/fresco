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
dnl BERLIN_LIB_CORE(name)
dnl
dnl Checks for the Berlin Core library `name', eg. Warsaw or Prague
AC_DEFUN([BERLIN_LIB_CORE],[

	AC_LANG_SAVE
	AC_LANG_CPLUSPLUS

	dnl First, locate berlin-config
	AC_REQUIRE([BERLIN_PROG_BERLIN_CONFIG])

	AC_MSG_CHECKING(for lib$1)
	dnl Check for warsaw -- uninstalled first
	if $BERLIN_CONFIG --cpath=$cpath $1 --modversion &>/dev/null ; then
		tmp="`$BERLIN_CONFIG --cpath=$cpath $1 --cflags`"
		translit($1, 'a-z', 'A-Z')_CPPFLAGS="$tmp"
		tmp="`$BERLIN_CONFIG --cpath=$cpath $1 --libs`"
		translit($1, 'a-z', 'A-Z')_LIBS="$tmp"
		AC_MSG_RESULT([yes, not installed])
	else
		if $BERLIN_CONFIG $1 --modversion &>/dev/null; then
			tmp="`$BERLIN_CONFIG $1 --cflags`"
			translit($1, 'a-z', 'A-Z')_CPPFLAGS="$tmp"
			tmp="`$BERLIN_CONFIG $1 --libs`"
			translit($1, 'a-z', 'A-Z')_LIBS="$tmp"
			AC_MSG_RESULT([yes, installed])
		else
			AC_MSG_RESULT(no)
			AC_MSG_ERROR(lib$1 was not found)
		fi
	fi

	AC_SUBST(translit($1, 'a-z', 'A-Z')_CPPFLAGS)
	AC_SUBST(translit($1, 'a-z', 'A-Z')_LIBS)
])
