dnl $Id$
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2004 Tobias Hunger <tobias@fresco.org>
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
dnl FRESCO_ICONV
dnl
dnl Checks for iconv support. If found, $ac_cv_iconv is set to "yes",
dnl and $iconv_cppflags and $iconv_lib are defined
AC_DEFUN([FRESCO_ICONV],[

    AC_ARG_WITH([iconv-prefix],
                AC_HELP_STRING([--with-iconv-prefix=PRF],
                               [search for iconv library in prefix]),
                [
                    if test -d $withval/include ; then
                        ICONV_CPPFLAGS="$CPPFLAGS -I$withval/include"
                    fi
                    if test -d $withval/lib ; then
                        ICONV_LIBS="$LIBS -L$withval/lib"
                    fi
                ]
    )

    am_cv_iconv="no"

    saved_LIBS="$LIBS"
    saved_CPPFLAGS="$CPPFLAGS"

    LIBS="$ICONV_LIBS"
    CPPFLAGS="$ICONV_CPPFLAGS"

    AC_MSG_CHECKING([whether -liconv is needed])

    AC_TRY_LINK([#include <stdlib.h>
#include <iconv.h>],
                [
                    iconv_t cd = iconv_open("", "");
                    iconv(cd, NULL, NULL, NULL, NULL);
                    iconv_close(cd);
                ],
                [
                     AC_MSG_RESULT([not needed])
                     am_cv_iconv="yes"
                ]
    )

    if test ".$am_cv_iconv" != ".yes"; then
        ICONV_LIBS="$ICONV_LIBS -liconv"
    
        LIBS="$ICONV_LIBS"

        AC_TRY_LINK([#include <stdlib.h>
#include <iconv.h>],
                    [
                        iconv_t cd = iconv_open("", "");
                        iconv(cd, NULL, NULL, NULL, NULL);
                        iconv_close(cd);
                    ],
                    [
                         AC_MSG_RESULT([needed])
                         am_cv_iconv="yes"
                    ],
                    [
                        AC_MSG_RESULT([iconv not found!])
                    ]
         )
    fi

    LIBS="$saved_LIBS"
    CPPFLAGS="$saved_CPPFLAGS"

    if test ".$am_cv_iconv" != ".yes"; then
        AC_ERROR([iconv not found: Try installing GNU libiconv.]);
    else
        AC_DEFINE(HAVE_ICONV, 1, [Define if you have iconv() function.])
        AC_SUBST(ICONV_CPPFLAGS)
        AC_SUBST(ICONV_LIBS)
    fi

])
