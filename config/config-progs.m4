dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
dnl http://www.berlin-consortium.org
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

dnl This file just contains macros to find various <whatever>-config scripts

AC_DEFUN([BERLIN_PROG_GNOME_CONFIG],[
	AC_PATH_PROG(GNOME_CONFIG, gnome-config)
])

dnl
dnl BERLIN_PROG_BERLIN_CONFIG(cpath)
dnl
dnl Checks for berlin-config, first in cpath, if given, then in
dnl $BERLIN_ROOT/bin:$PATH
AC_DEFUN([BERLIN_PROG_BERLIN_CONFIG],[

	if ! test ".$cpath" = "." ; then
		AC_PATH_PROG(BERLIN_CONFIG, berlin-config, "not found", $cpath)
	fi
	if test ".$BERLIN_CONFIG" = ".not found" ; then
		if test ".$BERLIN_ROOT" = "." ; then
			bcpath="$PATH"
		else
			bcpath="$BERLIN_ROOT/bin:$PATH"
		fi
		AC_PATH_PROG(BERLIN_CONFIG, berlin-config, "not found", $bcpath)
	fi
	if test ".$BERLIN_CONFIG" = ".not found" ; then
		AC_MSG_ERROR(berlin-config was not found)
	fi
])
