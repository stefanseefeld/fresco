dnl $Id$
dnl This source file is a part of the Fersco Project.
dnl Copyright (c) 1999 Ralf S. Engelschall <rse@engelschall.com>
dnl Copyright (c) 2000 Momchil Velikov <velco@fadata.bg>
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

AC_DEFUN(FRESCO_PROG_CC_CXX, [
	user_g_CFLAGS=""
	user_O_CFLAGS=""
	user_g_CXXFLAGS=""
	user_O_CXXFLAGS=""

	for flag in $CFLAGS ; do
		case $flag in
			( *-g* ) user_g_CFLAGS="$user_g_CFLAGS $flag" ;;
			( *-O*|*-f* ) user_O_CFLAGS="$user_O_CFLAGS $flag" ;;
		esac
	done
	for flag in $CXXFLAGS ; do
		case $flag in
			( *-g* ) user_g_CXXFLAGS="$user_g_CXXFLAGS $flag" ;;
			( *-O*|*-f* ) user_O_CXXFLAGS="$user_O_CXXFLAGS $flag" ;;
		esac
	done

	AC_PROG_CC
	AC_PROG_CXX

	CFLAGS=`echo "$CFLAGS" | \
		sed -e "s/ -g / /g" -e "s/ -g$//" \
		    -e "s/^-g //g" -e "s/^-g$//"`
	CXXFLAGS=`echo "$CXXFLAGS" | \
		sed -e "s/ -g / /g" -e "s/ -g$//" \
		    -e "s/^-g //g" -e "s/^-g$//"`

	changequote(<<, >>)
	CFLAGS=`echo "$CFLAGS" | \
		sed -e "s/ -O[0-9]* / /g" -e "s/ -O[0-9]*$//" \
		    -e "s/^-O[0-9]*//g" -e "s/^-O[0-9]*$//"`
	CXXFLAGS=`echo "$CXXFLAGS" | \
		sed -e "s/ -O[0-9]* / /g" -e "s/ -O[0-9]*$//" \
		    -e "s/^-O[0-9]*//g" -e "s/^-O[0-9]*$//"`
	changequote([, ])

	if test ".$ac_cv_prog_gcc" = ".yes" ; then
		AC_MSG_CHECKING([Checking GCC version >= 3.0])
		if test `$CXX -dumpversion | cut -d. -f1` -lt 3 ; then
			AC_MSG_ERROR([GCC is too old])
		else
			AC_MSG_RESULT([ok])
		fi
		for flag in "-pipe" ; do
			case "$CFLAGS" in
				( *${flag}* ) ;;
				( *) CFLAGS="$CFLAGS $flag" ;;
			esac
			case "$CXXFLAGS" in
				( *${flag}* ) ;;
				( *) CXXFLAGS="$CXXFLAGS $flag" ;;
			esac
		done
	fi
])

AC_DEFUN(FRESCO_COMPILER_OPTION, [
	AC_CACHE_CHECK([whether compiler option(s) $2 work],
		[fresco_cv_stat_compiler_option_$1],
		[
			SAVE_CFLAGS="$CFLAGS"
			SAVE_CXXFLAGS="$CXXFLAGS"
			CFLAGS="$CFLAGS $3"
			CXXFLAGS="$CXXFLAGS $3"
			AC_TRY_COMPILE([],[], fresco_cv_stat_compiler_option_$1=yes, fresco_cv_stat_compiler_option_$1=no)
			CFLAGS="$SAVE_CFLAGS"
			CXXFLAGS="$SAVE_CXXFLAGS"
		])
	if test ".$fresco_cv_stat_compiler_option_$1" = .yes; then
		[$4]
	fi
])
	
AC_DEFUN(FRESCO_CHECK_DEBUGGING, [
	AC_REQUIRE([AC_CANONICAL_HOST])

	AC_ARG_ENABLE(debugging, AC_HELP_STRING([--enable-debugging], [build for debugging (default=no)]),
	[
		if test ".$enableval" = ".yes" ; then
			msg="enabled";
			if test ".$user_g_CFLAGS" != . ; then
				CFLAGS="$CFLAGS $user_g_CFLAGS"
				msg="$msg, using specified CFLAGS"
			else
				if test ".$ac_cv_prog_gcc" = ".yes" ; then
					 AC_LANG_SAVE
					 AC_LANG(C)
				         FRESCO_COMPILER_OPTION(cggdb3, [-ggdb3 for C], -ggdb3,
						CFLAGS="$CFLAGS -ggdb3")
					 AC_LANG_RESTORE
				else
					 CFLAGS="$CFLAGS -g"
				fi
			fi

			if test ."$user_g_CXXFLAGS" != . ; then
				CXXFLAGS="$CXXFLAGS $user_g_CXXFLAGS"
				msg="$msg, using specified CXXFLAGS"
			else
				if test ."$ac_cv_prog_gcc" = ."yes" ; then
					AC_LANG_SAVE
					AC_LANG(C++)
                                        FRESCO_COMPILER_OPTION(cxxggdb3, [-ggdb3 for C++], -ggdb3,
						CXXFLAGS="$CXXFLAGS -ggdb3")
					AC_LANG_RESTORE
				else
					CXXFLAGS="$CXXFLAGS -g"
				fi
			fi
			AC_DEFINE(DEBUG, [], [Enable debugging code?])
			AC_SUBST(DEBUG)
			AC_MSG_CHECKING(for compilation debug mode)
			AC_MSG_RESULT([$msg])
		else
			AC_MSG_CHECKING(for compilation debug mode)
			AC_MSG_RESULT(disabled, ignoring CFLAGS and CXXFLAGS)
		fi
	],[
		msg="Setting none of my own"
		if test ."$user_g_CFLAGS" != . ; then
			CFLAGS="$CFLAGS $user_g_CFLAGS"
			msg="$msg, using specified CFLAGS";
		fi
		if test ."$user_g_CXXFLAGS" != . ; then
			CXXFLAGS="$CXXFLAGS $user_g_CXXFLAGS"
			msg="$msg, using specified CXXFLAGS";
		fi
		AC_MSG_CHECKING(for compilation debug mode)
		AC_MSG_RESULT([$msg])
	])
])

AC_DEFUN(FRESCO_CHECK_OPTIMIZE, [
	AC_REQUIRE([AC_CANONICAL_HOST])

	AC_ARG_ENABLE(optimization, AC_HELP_STRING([--enable-optimization], [build with optimization (default=no)]),
	[
		if test ".$enableval" = ".yes" ; then
			msg="enabled"
			if test ".$user_O_CFLAGS" != "." ; then
				CFLAGS="$CFLAGS $user_O_CFLAGS"
				msg="$msg, using specified CFLAGS"
			else
				if test ".$ac_cv_prog_gcc" = ".yes" ; then
					OPT_CFLAGS='-O3 -funroll-loops -fstrength-reduce -fomit-frame-pointer -ffast-math'
					AC_LANG_SAVE
					AC_LANG(C)
					FRESCO_COMPILER_OPTION(coptimize_std,
						[-f<xxx> for C],
						$OPT_CFLAGS,
						CFLAGS="$CFLAGS $OPT_CFLAGS")
					case $host_cpu in
					i?86*|?86*)
						OPT_CFLAGS='-falign-functions=4 -falign-jumps=4 -falign-loops=4' 
						FRESCO_COMPILER_OPTION(coptimize_x86,
							[-f<xxx> for x86 CPU],
							$OPT_CFLAGS,
							CFLAGS="$CFLAGS $OPT_CFLAGS")
							;;
					esac
					AC_LANG_RESTORE
				else
					CFLAGS="$CFLAGS -O"
				fi
			fi

			if test ".$user_O_CXXFLAGS" != "." ; then
				CXXFLAGS="$CXXFLAGS $user_O_CXXFLAGS"
				msg="$msg, using specified CXXFLAGS"
			else
				if test ."$ac_cv_prog_gcc" = ."yes" ; then
					OPT_CXXFLAGS='-O3 -funroll-loops -fstrength-reduce -ffast-math'
					AC_LANG_SAVE
					AC_LANG(C++)
					FRESCO_COMPILER_OPTION(cxxoptimize_std,
						[-f<xxx> for C++],
						$OPT_CXXFLAGS,
						CXXFLAGS="$CXXFLAGS $OPT_CXXFLAGS")
					case $host_cpu in
					i?86*|?86*)
						OPT_CXXFLAGS='-falign-functions=4 -falign-jumps=4 -falign-loops=4' 
						FRESCO_COMPILER_OPTION(cxxoptimize_x86,
							[-f<xxx> for x86 CPU],
							$OPT_CXXFLAGS,
							CXXFLAGS="$CXXFLAGS $OPT_CXXFLAGS")
							;;
					esac
					AC_LANG_RESTORE
				else
					CXXFLAGS="$CXXFLAGS -O"
				fi
			fi
			AC_MSG_CHECKING(for compilation optimize mode)
			AC_MSG_RESULT([$msg])
		else
			AC_MSG_CHECKING(for compilation optimize mode)
			AC_MSG_RESULT([disabled, ignoring specified CFLAGS and CXXFLAGS])
		fi
	],[
		msg="Setting none of my own"
		if test ."$user_O_CFLAGS" != . ; then
			CFLAGS="$CFLAGS $user_O_CFLAGS"
			msg="$msg, using specified CFLAGS";
		fi
		if test ."$user_O_CXXFLAGS" != . ; then
			CXXFLAGS="$CXXFLAGS $user_O_CXXFLAGS"
			msg="$mesgm using specified CXXFLAGS";
		fi
		AC_MSG_CHECKING(for compilation optimize  mode)
		AC_MSG_RESULT([$msg])
	])
])
