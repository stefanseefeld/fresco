dnl Process this file with autoconf to produce a configure script.
AC_INIT()
AM_INIT_AUTOMAKE(berlin, 0.0.1)
AM_CONFIG_HEADER(config.h)

dnl Check for programs and compatibility
AC_PROG_CC
AC_ISC_POSIX

dnl Check for headers
AC_HEADER_STDC
AC_HAVE_HEADERS(omnithread.h omniORB2/omniORB.h)

dnl Check for libraries
AD_HAVE_LIB(omniorb)

dnl Output makefiles and configuration
AC_OUTPUT([Makefile src/Makefile src/berlin/Makefile src/libwarsaw/Makefile \
	src/demos/Makefile])
