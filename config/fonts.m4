dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 2003 Tobias Hunger <tobias@fresco.org>
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

dnl BERLIN_FONTS
dnl
dnl Find some directory containing some ttf or pfb files.

AC_DEFUN([BERLIN_FONTS],
    [
        AC_ARG_WITH(fontpath,
		AC_HELP_STRING([--with-fontpath=PATH], [set fontpath]),
                [ BERLIN_FONTPATH="$withval" ],
                [
		    if test ".$BERLIN_FONTPATH" = "." ; then
		        BERLIN_FONTPATH="auto"
		    fi
                ])

	known_font_suffixes=".ttf .pfb"

	known_font_locations="/usr/share/fonts/truetype \
                              /usr/share/fonts/type1 \
                              /usr/lib/X11/fonts/TrueTyoe \
                              /usr/lib/X11/fonts/Type1 \
                              /usr/X/lib/X11/fonts/TrueType \
                              /usr/X/lib/X11/fonts/Type1"

        findargs=""
        for i in $known_font_suffixes; do
            findargs="$findargs -name *$i -o"
        done

	AC_MSG_CHECKING([for a directory with fonts])
        if test ".$BERLIN_FONTPATH" = ".auto" ; then
            for i in $known_font_locations ; do
                if test -d $i ; then
                    if test ".`find $i -mindepth 1 -maxdepth 1 $findargs -false`" != "." ; then
                      BERLIN_FONTPATH=$i
                      break
                    fi
                fi
            done

            if test ".$BERLIN_FONTPATH" = ".auto" ; then
                AC_MSG_RESULT([none found.])
                AC_MSG_ERROR([Please provide a fontpath manually (using --with-fontpath=PATH)])
            else
                AC_MSG_RESULT([using '$BERLIN_FONTPATH'])
            fi
        else
            AC_MSG_RESULT([using '$BERLIN_FONTPATH' (forced)])
        fi

	AC_SUBST(BERLIN_FONTPATH)
])
