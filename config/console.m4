dnl
dnl This source file is a part of the Berlin Project.
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

dnl ------------------------------------------------------------------

dnl BERLIN_CONSOLE_CHECK(mandatory-flag)
dnl
dnl Try to find a usable console.
AC_DEFUN([BERLIN_CONSOLE_CHECK],[

	AC_ARG_ENABLE(consoles,
		[  --enable-consoles=LIST         Specify which Consoles to build],
		[if test ".$enableval" = .yes ; then
			enable_consoles=all
		 else
			enable_consoles="$enableval"
		 fi],[
		 if test ".$enable_consoles" = . ; then
			enable_consoles=all
		 fi])
	if test ".$enable_consoles" = .all ; then
		enable_consoles="GGI SDL DFB"
	elif test ".$enable_consoles" = .no ; then
		enable_consoles=
	else
		dnl Handle comma-separated lists, too
		enable_consoles=["`echo $enable_consoles | sed 's/[, ]\+/ /g'`"]
	fi
	for con in $enable_consoles ; do
		if test -d $srcdir/src/Console/$con ; then
			eval enable_$con=yes
		else
			eval enable_$con=no
		fi
	done
	tested_consoles=
	if test ".$enable_GGI" = .yes ; then
		BERLIN_GGI_CHECK
		if test ".$ac_cv_lib_ggi" = .yes ; then
			tested_consoles="$tested_consoles Console/GGI"
			BERLIN_LIB_GGIMESA
			HAS_GGIMESA=
			if test ".$ac_cv_lib_GGIMesa" = .yes ; then
				HAS_GGIMESA=1
			else
				HAS_GGIMESA=0
			fi
			GGI_CPPFLAGS="$GGI_CPPFLAGS"
			GGI_LIBS="$GGI_LIBS"
			AC_SUBST(GGI_CPPFLAGS)
			AC_SUBST(GGI_LIBS)
			AC_SUBST(HAS_GGIMESA)
		fi
	fi
	if test ".$enable_SDL" = .yes ; then
		AM_PATH_SDL_BERLIN(1.1.8, [
			SDL_CPPFLAGS="$SDL_CPPFLAGS"
			SDL_LIBS="$SDL_LIBS"
			AC_SUBST(SDL_CPPFLAGS)
			AC_SUBST(SDL_LIBS)
			tested_consoles="$tested_consoles Console/SDL"])
	fi
	if test ".$enable_DFB" = .yes ; then
		BERLIN_DIRECTFB_CHECK
		DFB_CPPFLAGS="$DFB_CPPFLAGS"
		DFB_LIBS="$DFB_LIBS"
		AC_SUBST(DFB_CPPFLAGS)
		AC_SUBST(DFB_LIBS)
		if test ".$ac_cv_lib_DFB" = .yes ; then
			tested_consoles="$tested_consoles Console/DFB"
		fi
	fi
])
