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

dnl
dnl AC_SYNOPSIS
dnl
dnl Checks if synopsis is installed. If it is, $ac_cv_synopsis is
dnl set to "yes".

AC_DEFUN([AC_SYNOPSIS],[

	synopsis_path="$PATH"
	AC_ARG_WITH(synopsis-prefix, [  --with-synopsis-prefix  Prefix for synopsis],[ synopsis_prefix="$withval"])
	if test ".$synopsis_prefix" != "." ; then
		synopsis_path="$synopsis_prefix:$synopsis_path"
	fi
	AC_PATH_PROG(SYNOPSIS, synopsis,, $synopsis_path)
])
