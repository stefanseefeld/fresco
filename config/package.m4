dnl $Id$
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
dnl

dnl FRESCO_PACKAGE(PACKAGE[, MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl
AC_DEFUN(FRESCO_PACKAGE,
[dnl 
dnl Get the cppflags and libraries from the package-config script
dnl

dnl
dnl if the distribution ships the requested package, all is simple:
dnl we know where to find it (${top_srcdir}/$1) and we don't need any
dnl additional tests
dnl
dnl if not search elsewhere...
dnl

  dnl now test for the <package>-build-config script to be used
  dnl to retrieve the flags for the build process itself
  dnl
  dnl if this test fails, it means the specified package is not
  dnl part of the distribution, so we use the flags determined
  dnl by <package>-config
  dnl
  AC_PATH_PROG($1_BUILD_CONFIG, $1-config, no, ../$1/bin)
  AC_PATH_PROG($1_CONFIG, $1-config, no, ../$1/config)
  no_$1=""
  if test "$$1_BUILD_CONFIG" != "no" ; then
    $1_CPPFLAGS="`$$1_CONFIG --cppflags`"
    $1_LIBS="`$$1_CONFIG --libs`"
    $1_BUILD_CPPFLAGS="`$$1_BUILD_CONFIG --cppflags`"
    $1_BUILD_LIBS="`$$1_BUILD_CONFIG --libs`"
    $1_prefix="`$$1_BUILD_CONFIG $ac_$1_args --prefix`"
  else
    AC_ARG_WITH($1-prefix, AC_HELP_STRING([--with-$1-prefix],
                                          [Prefix where $1 is installed]),
                $1_prefix="$withval", $1_prefix="")
    AC_ARG_WITH($1-exec-prefix, AC_HELP_STRING([--with-$1-exec-prefix],
                                               [Exec prefix where $1 is installed]),
                $1_exec_prefix="$withval", $1_exec_prefix="")

    if test x$$1_exec_prefix != x ; then
      ac_$1_args="$ac_$1_args --exec-prefix=$$1_exec_prefix"
      if test x${$1_CONFIG+set} != xset ; then
        $1_CONFIG=$$1_exec_prefix/bin/$1-config
      fi
    fi
    if test x$$1_prefix != x ; then
      ac_$1_args="$ac_$1_args --prefix=$$1_prefix"
      if test x${$1_CONFIG+set} != xset ; then
        $1_CONFIG=$$1_prefix/bin/$1-config
      fi
    fi

    dnl Work around some strange quoting issue:
    AC_PATH_PROG($1_CONFIG, $1-config, no, $PATH$PATH_SEPARATOR$prefix/bin)
    min_$1_version=ifelse([$2], ,1.0.0,$2)
    AC_MSG_CHECKING([for $1 - version >= $min_$1_version])
    no_$1=""
    if test "$$1_CONFIG" = "no" ; then
      no_$1=yes
    else
      $1_CPPFLAGS="`$$1_CONFIG $ac_$1_args --cppflags`"
      $1_LIBS="`$$1_CONFIG $ac_$1_args --libs`"
      $1_prefix="`$$1_CONFIG $ac_$1_args --prefix`"

      $1_major_version=`$$1_CONFIG $ac_$1_args --version | \
             sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
      $1_minor_version=`$$1_CONFIG $ac_$1_args --version | \
             sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
      $1_patch_level=`$$1_CONFIG $ac_$1_args --version | \
             sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
      if test "x$enable_$1test" = "xyes" ; then
        ac_save_CPPFLAGS="$CPPFLAGS"
        ac_save_LIBS="$LIBS"
        CPPFLAGS="$CPPFLAGS $$1_CPPFLAGS"
        LIBS="$LIBS $$1_LIBS"
        dnl
        dnl Now check if the installed PACKAGE is sufficiently new.
        dnl
        rm -f conf.$1test
        AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char*
my_strdup (char *str)
{
  char *new_str;
  
  if (str)
    {
      new_str = (char *)malloc ((strlen (str) + 1) * sizeof(char));
      strcpy (new_str, str);
    }
  else
    new_str = NULL;
  
  return new_str;
}

int main (int argc, char *argv[])
{
  int major, minor, patch;
  char *tmp_version;

  /* This hangs on some systems (?)
  system ("touch conf.$1test");
  */
  { FILE *fp = fopen("conf.$1test", "a"); if ( fp ) fclose(fp); }

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = my_strdup("$min_$1_version");
  if (sscanf(tmp_version, "%d.%d.%d", &major, &minor, &patch) != 3) {
     printf("%s, bad version string\n", "$min_$1_version");
     exit(1);
   }

   if (($$1_major_version > major) ||
      (($$1_major_version == major) && ($$1_minor_version > minor)) ||
      (($$1_major_version == major) && ($$1_minor_version == minor) && ($$1_patch_level >= patch)))
    {
      return 0;
    }
  else
    {
      printf("\n*** '$1-config --version' returned %d.%d.%d, but the minimum version\n", $$1_major_version, $$1_minor_version, $$1_patch_level);
      printf("*** of $1 required is %d.%d.%d. If $1-config is correct, then it is\n", major, minor, micro);
      printf("*** best to upgrade to the required version.\n");
      printf("*** If $1-config was wrong, set the environment variable $1_CONFIG\n");
      printf("*** to point to the correct copy of $1-config, and remove the file\n");
      printf("*** config.cache before re-running configure\n");
      return 1;
    }
}

],, no_$1=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
        CPPFLAGS="$ac_save_CPPFLAGS"
        LIBS="$ac_save_LIBS"
      fi
    fi
    if test "x$no_$1" = x ; then
      AC_MSG_RESULT(yes)
      AC_SUBST($1_prefix)
      ifelse([$3], , :, [$3])     
    else
      AC_MSG_RESULT(no)
      if test "$$1_CONFIG" = "no" ; then
        echo "*** The $1-config script installed by $1 could not be found"
        echo "*** If $1 was installed in PREFIX, make sure PREFIX/bin is in"
        echo "*** your path, or set the $1_CONFIG environment variable to the"
        echo "*** full path to $1-config."
      fi
      $1_CPPFLAGS=""
      $1_LIBS=""
      ifelse([$4], , :, [$4])
    fi
    rm -f conf.$1test
  fi
])
