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
dnl BERLIN_FREETYPE_CHECK
dnl
dnl Checks if FreeType is found.  If it is, $ac_cv_lib_freetype is
dnl set to "yes".

AC_DEFUN([BERLIN_FREETYPE_CHECK],[

	AC_LANG_SAVE
	AC_LANG_CPLUSPLUS

	AC_ARG_WITH(freetype-prefix,
		[  --with-freetype-prefix  Prefix for Freetype],[
		freetype_prefix="$withval"])
	AC_REGISTER_PARAM(freetype_prefix)

	dnl Check for Freetype includes.
	if test ".$freetype_prefix" != . ; then
		FREETYPE_INCLUDES=-I$freetype_prefix/include
	fi
	save_CPPFLAGS="$CPPFLAGS"
	CPPFLAGS="$FREETYPE_INCLUDES $CPPFLAGS"
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
		CPPFLAGS="$CPPFLAGS $FREETYPE_INCLUDES"
		
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
 	
	AC_SUBST(FREETYPE_LIBS)
	AC_SUBST(FREETYPE_INCLUDES)

	AC_LANG_RESTORE
])
