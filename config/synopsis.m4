dnl $Id$
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

dnl
dnl SYNOPSIS_CHECK
dnl
dnl Check for synopsis
AC_DEFUN([SYNOPSIS_CHECK],[
    MIN_SYN_VERSION="$1"
    MIN_SYN_VERSION=`echo $MIN_SYN_VERSION |\
        sed -e "s/^\([0-9]\+\.[0-9]\+\).*$/\1/"`

    AC_PATH_PROG([SYNOPSIS], [synopsis])

    if test "$SYNOPSIS." != "." -a "$MIN_SYN_VERSION." != "." ; then
        AC_MSG_CHECKING([Checking version of synopsis (min. $MIN_SYN_VERSION)])

        MIN_SYN_MAYOR=`echo $MIN_SYN_VERSION | cut -d"." -f 1`
        MIN_SYN_MINOR=`echo $MIN_SYN_VERSION | cut -d"." -f 2`
        SYN_VERSION=`$SYNOPSIS --version | sed -e "s/synopsis version //"`
        SYN_MAYOR=`echo $SYN_VERSION | cut -d"." -f 1`
        SYN_MINOR=`echo $SYN_VERSION | cut -d"." -f 2`

        if test $MIN_SYN_MAYOR -lt $SYN_MAYOR -o \
                \( $MIN_SYN_MAYOR -eq $SYN_MAYOR -a \
                   $MIN_SYN_MINOR -le $SYN_MINOR \) ; then
            AC_MSG_RESULT([yes])
        else
            SYNOPSIS=""
            AC_MSG_RESULT([no])
        fi
    fi       
])
