dnl $Id$
dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 1999, 2000 Stefan Seefeld <stefan@fresco.org> 
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

dnl dnl FRESCO_OMNIORB dnl dnl Checks if omniORB is found. If it
dnl is, $fresco_cv_lib_omniORB is set to "yes". Also, the
dnl variables IDLCXX, IDLCXXFLAGS, IDLDYNFLAGS, IDLTIEFLAGS, ORB_LIBS
dnl and ORB_CPPFLAGS are set, and necessary definitions are added.

AC_DEFUN([FRESCO_OMNIORB],
[

  AC_REQUIRE([AC_CANONICAL_SYSTEM])
  AC_REQUIRE([AC_PROG_CC])
  AC_REQUIRE([AC_PROG_CXX])
  AC_REQUIRE([AC_PROG_CPP])
  AC_REQUIRE([AC_PROG_CXXCPP])
  AC_REQUIRE([FRESCO_PTHREAD])

  AC_ARG_WITH(omniorb-prefix,
    [  --with-omniorb-prefix  Prefix for omniORB],
    [  omniorb_prefix="$withval"])
  AC_ARG_WITH(omniorb-version,
    [  --with-omniorb-version  omniORB version (3 and 4 supported)],
    [  omniorb_version="$withval"])
  if test ".$omniorb_version" = ".4" ; then
    AC_ARG_WITH(colocation-optimization,
      [  --with-colocation-optimization  switch on ORB specific optimizations],
      [  omniorb_shortcut="$withval"])
    SHORTCUT="$omniorb_shortcut"
    AC_SUBST(SHORTCUT)
    AC_DEFINE(COLOCATION_OPTIMIZATION, 1, 
              [Define whether special colocation optimizations are supported])
  fi

  AC_SEARCH_LIBS(recv, [socket resolv])

  dnl Check for omniidl.
  if test ".$omniorb_prefix" != "." ; then
    omniorb_path="$omniorb_prefix/bin:$PATH"
    ORB_LIBS="-L$omniorb_prefix/lib"
    ORB_CPPFLAGS="-I$omniorb_prefix/include"
  else
    omniorb_path="$PATH"
  fi
  AC_PATH_PROG(IDLCXX, omniidl, no, $omniorb_path)
  if test ".$IDLCXX" = ".no" ; then
    no_omniorb="yes"
  fi

  save_CPPFLAGS="$CPPFLAGS"
  if test ".$no_omniorb" = "." ; then
    case $host_cpu in
    sparc)
      AC_DEFINE(__sparc__, 1, [what cpu])
      ;;
    i*86)
      AC_DEFINE(__x86__, 1, [what cpu])
      ;;
    alpha*)
      AC_DEFINE(__alpha__, 1, [what cpu])
      ;;
    hppa*)
      AC_DEFINE(__hppa__, 1, [what cpu])
      ;;
    powerpc)
      AC_DEFINE(__powerpc__, 1, [what cpu])
      ;;
    vax)
      AC_DEFINE(__vax__, 1, [what cpu])
      ;;
    mips*)
      AC_DEFINE(__mips__, 1, [what cpu])
      ;;
    arm)
      AC_DEFINE(__arm__, 1, [what cpu])
      ;;
    m68k)
      AC_DEFINE(__m68k__, 1, [what cpu])
      ;;
    *)
      AC_MSG_WARN([Unknown CPU type $host_cpu.])
      AC_MSG_WARN([Please check the omniORB documentation to see if your CPU type is supported,])
      AC_MSG_WARN([and update config/omniorb.m4])
      ;;
    esac
  
    case $host_os in
    linux*)
      AC_DEFINE(__linux__, 1, [what os])
      ;;
    solaris*)
      AC_DEFINE(__sunos__, 1, [what os])
      ;;
    osf1)
      AC_DEFINE(__osf1__, 1, [what os])
      ;;
    hpux*)
      AC_DEFINE(__hpux__, 1, [what os])
      ;;
    aix*)
      AC_DEFINE(__aix__, 1, [what os])
      ;;
    winnt*)
      dnl Seems like Windows uses winnt*, cygwin32
      dnl or mingw32. Don't know which is which...
      AC_DEFINE(__NT__, 1, [what os])
      AC_DEFINE(__WIN32__, 1, [what os])
      ;;
    irix*)
      AC_DEFINE(__irix__, 1, [what os])
      ;;
    nextstep*)
      AC_DEFINE(__nextstep__, 1, [what os])
      ;;
    sysv4.2uw*)
      AC_DEFINE(__uw7__, 1, [what os])
      ;;
    freebsd*)
      AC_DEFINE(__freebsd__, 1, [what os])
      ;;
    darwin*)
      AC_DEFINE(__darwin__, 1, [what os])
      ;;
    *)
      AC_MSG_WARN(Unknown OS $host_os.)
      AC_MSG_WARN(Please check the omniORB documentation to see if you OS is supported,)
      AC_MSG_WARN(and update config/omniorb.m4.)
      ;;
    esac
  
    dnl Don't know if this is portable...
    os_major_version=[`uname -r | cut -d '.' -f 1`]
    AC_DEFINE_UNQUOTED(__OSVERSION__, $os_major_version, [Define the os version.])
  
    dnl Check for omniORB includes
    CPPFLAGS="$CPPFLAGS $ORB_CPPFLAGS"
    if test ".$omniorb_version" = ".4" \
       -o ".$omniorb_version" = "." ; then
      AC_CHECK_HEADER(omniORB4/CORBA.h, omniorb_version=4, no_omniorb=yes)
    fi
    if test ".$omniorb_version" = ".3" || \
       test ".$omniorb_version" = "." -a ".$no_omniorb" = ".yes" ; then
      AC_CHECK_HEADER(omniORB3/CORBA.h, omniorb_version=3 no_omniorb=, no_omniorb=yes)
    fi
  fi

  dnl Check for omniORB libraries
  if test ".$no_omniorb" = "." ; then
    FRESCO_CHECK_LIB(ORB_LIBS, omnithread, [omni_mutex my_mutex], omnithread.h)
    dnl Hard to check the GateKeeper lib because of circular
    dnl dependency between it and libomniORB3
    if test ".$omniorb_version" = ".4" ; then
      FRESCO_CHECK_LIB(ORB_LIBS, omniORB4, [CORBA::ORB_var orb], omniORB4/CORBA.h)
      FRESCO_CHECK_LIB(ORB_LIBS, omniDynamic4, [CORBA::Any_var any;], omniORB4/CORBA.h)
      if test ".$fresco_cv_lib_omniORB4" = ".no" \
        -a ".$fresco_cv_lib_omniDynamic4" = ".no" \
        -a ".$fresco_cv_lib_omnithread" = ".no" ; then
        no_omniorb="yes"
      fi
      LIBS="$ORB_LIBS $LIBS"
    else
      ORB_LIBS="$ORB_LIBS -ltcpwrapGK"
      FRESCO_CHECK_LIB(ORB_LIBS, omniORB3, [CORBA::ORB_var orb], omniORB3/CORBA.h)
      FRESCO_CHECK_LIB(ORB_LIBS, omniDynamic3, [CORBA::Any_var any;], omniORB3/CORBA.h)
      if test ".$fresco_cv_lib_omniORB3" = ".no" \
      	-a ".$fresco_cv_lib_omniDynamic3" = ".no" \
      	-a ".$fresco_cv_lib_omnithread" = ".no" ; then
      	no_omniorb="yes"
      fi
      LIBS="$ORB_LIBS $LIBS"
    fi
  fi

  if test ".$no_omniorb" = "." ; then
    fresco_cv_lib_omniORB="yes"
  fi
])
