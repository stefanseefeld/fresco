dnl Process this file with autoconf to produce a configure script.
dnl ======================================================================
dnl Initialize automake and autoconf

AC_INIT(include/berlin/reactor_impl.hh)
AM_INIT_AUTOMAKE(berlin,0.0.1,-)

AM_DISABLE_STATIC

dnl ======================================================================
dnl Check for programs and compatibility

AC_PROG_CC
AC_ISC_POSIX
AM_PROG_CXX
AM_PROG_LIBTOOL
AC_PROG_INSTALL

dnl ======================================================================
dnl Check for libraries
AD_HAVE_LIB(omniorb)

dnl ======================================================================
dnl Check for headers
AC_HEADER_STDC
AC_HAVE_HEADERS(omnithread.h omniORB2/omniORB.h)

dnl ========================================================================
dnl Checks for typedefs, structures, and compiler characteristics.

dnl ======================================================================
dnl Output makefiles and configuration

AM_CONFIG_HEADER(include/config.h)
AC_OUTPUT([Makefile src/Makefile src/berlin/Makefile src/libwarsaw/Makefile \
	src/demos/Makefile])
