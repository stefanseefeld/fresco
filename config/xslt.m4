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
dnl AC_XSLT
dnl
dnl Checks if an xslt processor. If it is found, define XSLT
dnl as of now, only check for 4xslt. Add other processors later...
AC_DEFUN([AC_XSLT],[

	xslt_path="$PATH"
	AC_ARG_WITH(xslt-prefix,
          AC_HELP_STRING([--with-xslt-prefix=PRF],
                         [Prefix for xslt processor]),
          [xslt_prefix="$withval"])
	if test ".$xslt_prefix" != "." ; then
		xslt_path="$xslt_prefix:$xslt_path"
	fi
	AC_PATH_PROG(XSLT, 4xslt,, $xslt_path)
])
