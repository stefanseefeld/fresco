dnl $Id$
dnl This source file is a part of the Berlin Project.
dnl Copyright (c) 1999 Ralf S. Engelschall <rse@engelschall.com>
dnl Copyright (c) 2000 Momchil Velikov <velco@fadata.bg>
dnl http://www.berlin-consortium.org/
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

AC_DEFUN(AC_PROG_CC_CXX,[dnl

	user_g_CFLAGS=""
	user_O_CFLAGS=""
	user_g_CXXFLAGS=""
	user_O_CXXFLAGS=""

	for flag in $CFLAGS ; do
		case $flag in
			*-g* ) user_g_CFLAGS="$user_g_CFLAGS $flag" ;;
			*-O*|*-f* ) user_O_CFLAGS="$user_O_CFLAGS $flag" ;;
		esac
	done
	for flag in $CXXFLAGS ; do
		case $flag in
			*-g* ) user_g_CXXFLAGS="$user_g_CXXFLAGS $flag" ;;
			*-O*|*-f* ) user_O_CXXFLAGS="$user_O_CXXFLAGS $flag" ;;
		esac
	done

	AC_PROG_CC
	AC_PROG_CXX

	CFLAGS=`echo "$CFLAGS" \
        	| sed -e 's/ -g / /g' -e 's/ -g$//' -e 's/^-g //g' -e 's/^-g$//'`
	CXXFLAGS=`echo "$CXXFLAGS" \
        	| sed -e 's/ -g / /g' -e 's/ -g$//' -e 's/^-g //g' -e 's/^-g$//'`
	changequote(<<, >>)
	CFLAGS=`echo $CFLAGS \
        	| sed -e "s/ -O[0-9]* / /g" -e "s/ -O[0-9]*$//" \
			-e "s/^-O[0-9]* //g" -e "s/^-O[0-9]*$//"`
	CXXFLAGS=`echo $CXXFLAGS \
        	| sed -e "s/ -O[0-9]* / /g" -e "s/ -O[0-9]*$//" \
			-e "s/^-O[0-9]* //g" -e "s/^-O[0-9]*$//"`
	changequote([, ])

	if test ".$ac_cv_prog_gcc" = ".yes" ; then
		for flag in "-pipe" ; do
			case "$CFLAGS" in
				*${flag}* ) ;;
				*) CFLAGS="$CFLAGS $flag" ;;
			esac
			case "$CXXFLAGS" in
				*${flag}* ) ;;
				*) CXXFLAGS="$CXXFLAGS $flag" ;;
			esac
		done
	fi
])
	
AC_DEFUN(AC_CHECK_DEBUGGING,[dnl

	AC_ARG_ENABLE(debug,dnl
[  --enable-debug          build for debugging (default=no)],
	[dnl
		if test ".$enableval" = ".yes" ; then
			if test ".$user_g_CFLAGS" != . ; then
				CFLAGS="$CFLAGS $user_g_CFLAGS"
			else
				CFLAGS="$CFLAGS -g"
				if test ".$ac_cv_prog_gcc" = ".yes" ; then
				         AC_COMPILER_OPTION(cggdb3, -ggdb3, -ggdb3,
						CFLAGS="$CFLAGS -ggdb3")
				fi
			fi

			if test ."$user_g_CXXFLAGS" != . ; then
				CXXFLAGS="$CXXFLAGS $user_g_CXXFLAGS"
			else
				CXXFLAGS="$CXXFLAGS -g"
				if test ."$ac_cv_prog_gcc" = ."yes" ; then
					AC_LANG_SAVE
					AC_LANG_CPLUSPLUS
					AC_COMPILER_OPTION(cxxggdb3, -ggdb3, -ggdb3,
						CXXFLAGS="$CXXFLAGS -ggdb3")
					AC_LANG_RESTORE
				fi
			fi
			msg=enabled
			AC_DEFINE(DEBUG)
		else
			msg=disabled
		fi
		AC_MSG_CHECKING(for compilation debug mode)
		AC_MSG_RESULT($msg)
	],[dnl
		CFLAGS="$CFLAGS $user_g_CFLAGS"
		CXXFLAGS="$CXXFLAGS $user_g_CXXFLAGS"
		AC_MSG_CHECKING(for compilation debug mode)
		AC_MSG_RESULT(default)
	])
])

AC_DEFUN(AC_CHECK_OPTIMIZE,[dnl

	AC_REQUIRE([AC_CANONICAL_HOST])

	AC_ARG_ENABLE(optimize,dnl
[  --enable-optmize          build with optimization (default=no)],
	[dnl
		if test ".$enableval" = ".yes" ; then
			if test ".$user_O_CFLAGS" != "." ; then
				CFLAGS="$CFLAGS $user_O_CFLAGS"
			else
				if test ".$ac_cv_prog_gcc" = ".yes" ; then
					OPT_CFLAGS='-O3 -funroll-loops -fstrength-reduce -fomit-frame-pointer -ffast-math'
					AC_COMPILER_OPTION(coptimize_std,
						[-f<xxx> for C],
						$OPT_CFLAGS,
						CFLAGS="$CFLAGS $OPT_CFLAGS")
					case $host_cpu in
					i?86*|?86*)
						OPT_CFLAGS='-malign-functions=4 -malign-jumps=4 -malign-loops=4' 
						AC_COMPILER_OPTION(coptimize_x86,
							[-f<xxx> for x86 CPU],
							$OPT_CFLAGS,
							CFLAGS="$CFLAGS $OPT_CFLAGS")
							;;
					esac
				else
					CFLAGS="$CFLAGS -O"
				fi
			fi

			if test ".$user_O_CXXFLAGS" != "." ; then
				CXXFLAGS="$CXXFLAGS $user_O_CXXFLAGS"
			else
				if test ."$ac_cv_prog_gcc" = ."yes" ; then
					OPT_CXXFLAGS='-O3 -funroll-loops -fstrength-reduce -ffast-math'
					AC_COMPILER_OPTION(cxxoptimize_std,
						[-f<xxx> for C++],
						$OPT_CXXFLAGS,
						CXXFLAGS="$CXXFLAGS $OPT_CXXFLAGS")
					case $host_cpu in
					i?86*|?86*)
						OPT_CXXFLAGS='-malign-functions=4 -malign-jumps=4 -malign-loops=4' 
						AC_COMPILER_OPTION(cxxoptimize_x86,
							[-f<xxx> for x86 CPU],
							$OPT_CXXFLAGS,
							CXXFLAGS="$CXXFLAGS $OPT_CXXFLAGS")
							;;
					esac
				else
					CXXFLAGS="$CXXFLAGS -O"
				fi
			fi
			msg=enabled
		else
			msg=disabled
		fi

		AC_MSG_CHECKING(for compilation optimize mode)
		AC_MSG_RESULT(msg)
	],[dnl
		CFLAGS="$CFLAGS $user_O_CFLAGS"
		CXXFLAGS="$CXXFLAGS $user_O_CXXFLAGS"
		AC_MSG_CHECKING(for compilation optimize mode)
		AC_MSG_RESULT(default)
	])
])
