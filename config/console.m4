dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org>
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

dnl ------------------------------------------------------------------

dnl BERLIN_CONSOLE_CHECK(mandatory-flag)
dnl
dnl Try to find a usable console. If mandatory-flag is "mandatory", abort if
dnl none is found.
AC_DEFUN([BERLIN_CONSOLE_CHECK],[

	AC_BEGIN_DECISION([Console])
	AC_ARG_WITH(console,[  --with-console=NAME         Specify which Console to use],[dnl
		CON_IMPL="$withval"],[dnl
		if test ".$CON_IMPL" = . ; then
			CON_IMPL="auto"
		fi])

	case $CON_IMPL in
		GGI|auto)
			BERLIN_GGI_CHECK
			if test ".$ac_cv_lib_ggi" != .yes; then
				if test ".$1" = .mandatory; then
					AC_MSG_ERROR(No supported Console environment found!)
				else
					CON_IMPL="none"
				fi
			else
				AC_DECIDE(GGICONSOLE, [use GGI])
				CON_IMPL=GGI
				AC_DEFINE(CONSOLE_GGI)
				CON_CFLAGS="$GGI_CFLAGS"
				CON_LIBS="$GGI_LIBS"
			fi				
			;;
                SDL)
                        AM_PATH_SDL_BERLIN(1.1.8, [
				AC_DECIDE(SDLCONSOLE, [use SDL])
                                CON_IMPL=SDL
				AC_DEFINE(CONSOLE_SDL)
				CON_CFLAGS="$SDL_CFLAGS"
				CON_LIBS="$SDL_LIBS"
], [
                                if test ".$1" = .mandatory; then
                                        AC_MSG_ERROR(No supported Console environment found!)
                                else
                                        CON_IMPL="none"
                                fi
])
                        ;;
                CAVELib)
                        BERLIN_CAVELIB_CHECK
                        if test ".$ac_cv_lib_cave" != .yes; then
                                if test ".$1" = .mandatory; then
                                        AC_MSG_ERROR(No supported Console environment found!)
                                else
                                        CON_IMPL="none"
                                fi
                        else
				AC_DECIDE(CAVECONSOLE, [use CAVELib])
                                CON_IMPL=CAVELIB
				AC_DEFINE(CONSOLE_CAVELIB)
                        fi
                        ;;
                GLUT)
                        BERLIN_GLUT_CHECK
                        if test ".$ac_cv_lib_glut" != .yes; then
                                if test ".$1" = .mandatory; then
                                        AC_MSG_ERROR(No supported Console environment found!)
                                else
                                        CON_IMPL="none"
                                fi
                        else
				AC_DECIDE(GLUTCONSOLE, [use GLUT])
                                CON_IMPL=GLUT
				AC_DEFINE(CONSOLE_GLUT)
                        fi
                        ;;
		DirectFB)
			BERLIN_DIRECTFB_CHECK
			if test ".$ac_cv_lib_directfb" != .yes; then
				if test ".$1" = .mandatory; then
					AC_MSG_ERROR(No supported Console environment found!)
				else
					CON_IMPL="none"
				fi
			else
				AC_DECIDE(DIRECTFBCONSOLE, [use DirectFB])
				CON_IMPL=DIRECTFB
				AC_DEFINE(CONSOLE_DIRECTFB)
			fi
			;;
		*)
			if test ".$1" = .mandatory; then
				AC_MSG_ERROR($CON_IMPL is not supported!)
			else
				AC_MSG_WARN($CON_IMPL is not supported!)
			fi
			;;
	esac
	
	AC_END_DECISION
	if test ".$CON_IMPL" != .none ; then
		AC_DEFINE_UNQUOTED(CONSOLE_IMPL, $CON_IMPL)
		AC_SUBST(CON_IMPL)
		AC_SUBST(CON_CFLAGS)
		AC_SUBST(CON_LIBS)
	fi
])
