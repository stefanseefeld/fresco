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

dnl AM_PATH_FREETYPE([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl Test for Freetype2, and define FREETYPE_CFLAGS and FREETYPE_LIBS
dnl
AC_DEFUN(AM_PATH_FREETYPE,
[dnl 
dnl Get the cflags and libraries from the freetype-config script
dnl
AC_ARG_WITH(freetype-prefix,[  --with-freetype-prefix=PFX   Prefix where freetype is installed (optional)],
            freetype_prefix="$withval", freetype_prefix="")
AC_ARG_WITH(freetype-exec-prefix,[  --with-freetype-exec-prefix=PFX Exec prefix where freetype is installed (optional)],
            freetype_exec_prefix="$withval", freetype_exec_prefix="")
AC_ARG_ENABLE(freetypetest, [  --disable-freetypetest       Do not try to compile and run a test freetype program],
		    , enable_freetypetest=yes)

  if test x$freetype_exec_prefix != x ; then
     freetype_args="$freetype_args --exec-prefix=$freetype_exec_prefix"
     if test x${FREETYPE_CONFIG+set} != xset ; then
        FREETYPE_CONFIG=$freetype_exec_prefix/bin/freetype-config
     fi
  fi
  if test x$freetype_prefix != x ; then
     freetype_args="$freetype_args --prefix=$freetype_prefix"
     if test x${FREETYPE_CONFIG+set} != xset ; then
        FREETYPE_CONFIG=$freetype_prefix/bin/freetype-config
     fi
  fi

  AC_PATH_PROG(FREETYPE_CONFIG, freetype-config, no)
  min_freetype_version=ifelse([$1], ,6:1:0,$1)
  AC_MSG_CHECKING(for freetype - version >= $min_freetype_version)
  no_freetype=""
  if test "$FREETYPE_CONFIG" = "no" ; then
    no_freetype=yes
  else
    FREETYPE_CFLAGS=`$FREETYPE_CONFIG $freetypeconf_args --cflags`
    FREETYPE_LIBS=`$FREETYPE_CONFIG $freetypeconf_args --libs`
    freetype_major_version=`$FREETYPE_CONFIG $freetype_args --version | \
           sed 's/\([[0-9]]*\):\([[0-9]]*\):\([[0-9]]*\)/\1/'`
    freetype_minor_version=`$FREETYPE_CONFIG $freetype_args --version | \
           sed 's/\([[0-9]]*\):\([[0-9]]*\):\([[0-9]]*\)/\2/'`
    freetype_micro_version=`$FREETYPE_CONFIG $freetype_config_args --version | \
           sed 's/\([[0-9]]*\):\([[0-9]]*\):\([[0-9]]*\)/\3/'`
    if test "x$enable_freetypetest" = "xyes" ; then
      ac_save_CXXFLAGS="$CXXFLAGS"
      ac_save_LIBS="$LIBS"
      CXXFLAGS="$CXXFLAGS $FREETYPE_CFLAGS"
      LIBS="$LIBS $FREETYPE_LIBS"
dnl
dnl Now check if the installed freetype is sufficiently new. (Also sanity
dnl checks the results of freetype-config to some extent
dnl
      rm -f conf.freetypetest
      AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freetype/freetype.h"

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
  int major, minor, micro;
  char *tmp_version;

  /* This hangs on some systems (?)
  system ("touch conf.freetypetest");
  */
  { FILE *fp = fopen("conf.freetypetest", "a"); if ( fp ) fclose(fp); }

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = my_strdup("$min_freetype_version");
  if (sscanf(tmp_version, "%d:%d:%d", &major, &minor, &micro) != 3) {
     printf("%s, bad version string\n", "$min_freetype_version");
     exit(1);
   }

   if (($freetype_major_version > major) ||
      (($freetype_major_version == major) && ($freetype_minor_version > minor)) ||
      (($freetype_major_version == major) && ($freetype_minor_version == minor) && ($freetype_micro_version >= micro)))
    {
      return 0;
    }
  else
    {
      printf("\n*** 'freetype-config --version' returned %d.%d.%d, but the minimum version\n", $freetype_major_version, $freetype_minor_version, $freetype_micro_version);
      printf("*** of freetype required is %d.%d.%d. If freetype-config is correct, then it is\n", major, minor, micro);
      printf("*** best to upgrade to the required version.\n");
      printf("*** If freetype-config was wrong, set the environment variable FREETYPE_CONFIG\n");
      printf("*** to point to the correct copy of freetype-config, and remove the file\n");
      printf("*** config.cache before re-running configure\n");
      return 1;
    }
}

],, no_freetype=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CXXFLAGS="$ac_save_CXXFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_freetype" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$FREETYPE_CONFIG" = "no" ; then
       echo "*** The freetype-config script installed by freetype could not be found"
       echo "*** If freetype was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the FREETYPE_CONFIG environment variable to the"
       echo "*** full path to freetype-config."
     else
       if test -f conf.freetypetest ; then
        :
       else
          echo "*** Could not run freetype test program, checking why..."
          CXXFLAGS="$CXXFLAGS $FREETYPE_CFLAGS"
          LIBS="$LIBS $FREETYPE_LIBS"
          AC_TRY_LINK([
#include <stdio.h>
#include "freetype/freetype.h"
],      [ return 0; ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding freetype or finding the wrong"
          echo "*** version of freetype. If it is not finding freetype, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means freetype was incorrectly installed"
          echo "*** or that you have moved freetype since it was installed. In the latter case, you"
          echo "*** may want to edit the freetype-config script: $FREETYPE_CONFIG" ])
          CXXFLAGS="$ac_save_CXXFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
     FREETYPE_CFLAGS=""
     FREETYPE_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(FREETYPE_CFLAGS)
  AC_SUBST(FREETYPE_LIBS)
  rm -f conf.freetypetest
])

dnl
dnl BERLIN_LIB_FREETYPE
dnl
dnl Checks if FreeType is found.  If it is, $ac_cv_lib_freetype is
dnl set to "yes".

AC_DEFUN([BERLIN_LIB_FREETYPE],[

	AC_LANG_SAVE
	AC_LANG_CPLUSPLUS

	AC_ARG_WITH(freetype-prefix,
		[  --with-freetype-prefix  Prefix for Freetype],[
		freetype_prefix="$withval"])

	dnl Check for Freetype includes.
	if test ".$freetype_prefix" != . ; then
		FREETYPE_CFLAGS=-I$freetype_prefix/include
	fi
	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$FREETYPE_CFLAGS $CPPFLAGS"
	AC_CHECK_HEADER(freetype/freetype.h,,no_freetype=yes)
	CPPFLAGS="$save_CPPFLAGS"

	if test ".$no_freetype" = yes; then
		if test ".$1" = .mandatory; then
			AC_MSG_ERROR(Could not find freetype.h!)
		fi
	fi
	
	dnl Check for Freetype libs
	if test x$no_freetype = x ; then
		    
		if test x$freetype_prefix != x ; then
		        freetype_libs=-L$freetype_prefix/lib
		fi
		freetype_libs="$freetype_libs -lfreetype"

		AC_CACHE_CHECK([for working Freetype environment],
		ac_cv_lib_freetype, [
		
		save_LDFLAGS="$LDFLAGS"
		save_CPPFLAGS="$CPPFLAGS"
		save_LIBS="$LIBS"
		LIBS="$LIBS $freetype_libs"
		LDFLAGS="$LDFLAGS"
		CPPFLAGS="$CPPFLAGS $FREETYPE_CFLAGS"
		
		dnl Check if everything works
		AC_TRY_RUN([
#include <freetype/freetype.h>
#include <iostream>

int main (int argc, char* argv[])
{
  FT_Library library;
  if(FT_Init_FreeType(&library) != 0)
    {
      cerr << "Error: Could not initialize FreeType engine!" << endl;
      return 1;
    }
  return 0;
}
 			    ], ac_cv_lib_freetype=yes,
 			       ac_cv_lib_freetype=no,
 			       ac_cv_lib_freetype=yes)
 
 		CPPFLAGS="$save_CPPFLAGS"
 		LDFLAGS="$save_LDFLAGS"
 		LIBS="$save_LIBS"
 
 		]) dnl End of AC_CACHE_CHECK
 
	fi
 	
	if test x$ac_cv_lib_freetype = xyes ; then
	        FREETYPE_LIBS=$freetype_libs
        else
		if test ".$1" = .mandatory ; then
			AC_MSG_ERROR(Could not find freetype library!)
		fi
	fi
 	
	AC_SUBST(FREETYPE_CFLAGS)
	AC_SUBST(FREETYPE_LIBS)

	AC_LANG_RESTORE
])
