dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org>
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

dnl FRESCO_CONSOLE_CHECK(mandatory-flag)
dnl
AC_DEFUN([FRESCO_CONSOLE_CHECK],
  [AC_ARG_ENABLE(consoles,
                 AC_HELP_STRING([--enable-consoles],[Specify which Consoles to build]),
		 [if test ".$enableval" = .yes ; then
		    enabled_consoles=all
		  else
		    enabled_consoles="$enableval"
		  fi],
		 [enabled_consoles=all])

   if test ".$enabled_consoles" = .all ; then
     enabled_consoles="GGI SDL DFB"
   elif test ".$enabled_consoles" = .no ; then
     enabled_consoles=
   else
     dnl Handle comma-separated lists, too
     enabled_consoles=["`echo $enabled_consoles | sed 's/[, ]\+/ /g'`"]
   fi
   for con in $enabled_consoles ; do
     eval ${con}_enabled=yes
   done
   tested_consoles=
   if test ".$GGI_enabled" = .yes ; then
     FRESCO_GGI_CHECK
     if test ".$HAVE_GGI" = .1 ; then
       tested_consoles="$tested_consoles GGI"
       FRESCO_GGIMESA_CHECK
     fi
   fi
   if test ".$SDL_enabled" = .yes ; then
     FRESCO_SDL_CHECK(1.1.8)
     if test ".$HAVE_SDL" = .1 ; then
       tested_consoles="$tested_consoles SDL"
     fi
   fi
   if test ".$DFB_enabled" = .yes ; then
     FRESCO_DIRECTFB_CHECK
     if test ".$HAVE_DFB" = .1 ; then
       tested_consoles="$tested_consoles DFB"
     fi
   fi
])
