dnl $Id$
dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 2000 Stefan Seefeld <stefan@fresco.org> 
dnl Copyright (C) 2000 Håvard Skinnemoen <skinnemo@itk.ntnu.no>
dnl http://www.fresco.org/
dnl
dnl part of this code is from Ralph S. Engelschall
dnl Copyright (c) 1999 Ralf S. Engelschall <rse@engelschall.com>
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

dnl ##
dnl ##  Decision Hierachy
dnl ##

define(AC_IFALLYES,[dnl
ac_rc=yes
for ac_spec in $1; do
    ac_type=`echo "$ac_spec" | sed -e 's/:.*$//'`
    ac_item=`echo "$ac_spec" | sed -e 's/^.*://'`
    case $ac_type in
        header [)]
            ac_item=`echo "$ac_item" | sed 'y%./+-%__p_%'`
            ac_var="ac_cv_header_$ac_item"
            ;;
        file [)]
            ac_item=`echo "$ac_item" | sed 'y%./+-%__p_%'`
            ac_var="ac_cv_file_$ac_item"
            ;;
        func    [)] ac_var="ac_cv_func_$ac_item"   ;;
        lib     [)] ac_var="ac_cv_lib_$ac_item"    ;;
        define  [)] ac_var="ac_cv_define_$ac_item" ;;
        typedef [)] ac_var="ac_cv_typedef_$ac_item" ;;
        custom  [)] ac_var="$ac_item" ;;
    esac
    eval "ac_val=\$$ac_var"
    if test ".$ac_val" != .yes; then
        ac_rc=no
        break
    fi
done
if test ".$ac_rc" = .yes; then
    :
    $2
else
    :
    $3
fi
])

dnl See whether we need a declaration for a function.
dnl AC_NEED_DECLARATION(FUNCTION [, EXTRA-HEADER-FILES])
AC_DEFUN([AC_NEED_DECLARATION],
[AC_MSG_CHECKING([whether $1 must be declared])
AC_CACHE_VAL(ac_cv_decl_needed_$1,
[AC_TRY_COMPILE([
#include <stdio.h>
#ifdef STRING_WITH_STRINGS
# include <string.h>
# include <strings.h>
#else
# ifdef HAVE_STRING_H
#  include <string.h>
# else
#  ifdef HAVE_STRINGS_H
#   include <strings.h>
#  endif
# endif
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifndef HAVE_RINDEX
#define rindex strrchr
#endif
#ifndef HAVE_INDEX
#define index strchr
#endif
$2],
[char *(*pfn) = (char *(*)) $1],
eval "ac_cv_decl_needed_$1=no", eval "ac_cv_decl_needed_$1=yes")])
if eval "test \"`echo '$ac_cv_decl_needed_'$1`\" = yes"; then
  AC_MSG_RESULT(yes)
  AC_DEFINE_UNQUOTED(NEED_DECLARATION_$1, 1, [Define if you need to declare $1])
else
  AC_MSG_RESULT(no)
fi
])dnl

dnl
dnl FRESCO_CHECK_LIB(variable, library, func_call, include_files)
dnl
dnl Checks if library is found by doing func_call. Include include_files
dnl to avoid compilation errors, and add library to variable if successful.
dnl variable is also used to specify additional libraries or paths.
dnl
dnl This functions is meant to address some of the severe limitations of
dnl autoconf when it comes to handling C++.
AC_DEFUN([FRESCO_CHECK_LIB],[

	save_LIBS="$LIBS"
	LIBS="$LIBS -l$2 $$1"
	changequote(`, ')
	includes="patsubst(`$4', `\(\w\|\.\|/\)+', `#include <\&>
')"
	changequote([, ])
	AC_CACHE_CHECK(for -l$2,
		fresco_cv_lib_$2,
		AC_TRY_LINK($includes,
			$3, fresco_cv_lib_$2="yes", fresco_cv_lib_$2="no"))

	LIBS="$save_LIBS"
	if test ".$fresco_cv_lib_$2" = ".yes" ; then
		$1="$$1 -l$2"
	fi
])
