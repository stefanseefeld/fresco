dnl Process this file with autoconf to produce a configure script.
dnl
dnl This script should now detect your ORB and your system correctly.
dnl It will only detect omniORB2 right now, but more ORBs can be added
dnl later on.
dnl
dnl ======================================================================
dnl Initialize automake and autoconf

AC_PREREQ(2.12)
AC_INIT(src/WHAT-IS-THIS)
AC_CONFIG_AUX_DIR(${srcdir}/config/autoconf)
AC_CANONICAL_SYSTEM

dnl Set this define to make fixes w/o breaking anything else.
AC_DEFINE(USE_AUTOCONF)

dnl ======================================================================
dnl These are all the variables we can set. I note them here because
dnl it will be easier to sort it out later.

dnl These are ORB specific
ORB_CFLAGS=""
ORB_INCLUDE_PATH=""
ORB_LIBRARY_PATH=""
ORB_LDFLAGS=""
ORB_IDL_FLAGS=""

dnl Various shared library options
DLL_SUFFIX="so"
MKSHLIB=""
DSO_LDOPTS=""
DSO_CFLAGS=""

dnl Specific compiler flags we may or may not want
DEFINES=""
CFLAGS=""
CXXFLAGS=""
LDFLAGS=""
INCLUDE_PATH=""
LIBRARY_PATH=""
RTTI_FLAGS=""
OPT_FLAGS="-O"
DEBUG_FLAGS=""
DEBUG="0"

dnl ======================================================================
dnl Check for programs and compatibility

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CC_C_O
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_AWK
AC_PROG_RANLIB
AC_ISC_POSIX

GNU_CC=
GNU_CXX=
if test "$GCC" = "yes"; then
    GNU_CC=1
fi
if test "$GXX" = "yes"; then
    GNU_CXX=1
fi

AC_SUBST(GNU_CC)
AC_SUBST(GNU_CXX)

dnl ======================================================================
dnl Check for libraries

dnl Required for just about everything.
AC_CHECK_LIB(pthread, pthread_attr_init,
	[LDFLAGS="-lpthread $LDFLAGS"
	DEFINES="-D_REENTRANT=1 $DEFINES"],
        [AC_MSG_ERROR("Unable to find POSIX threads")])

dnl Sooner or later we are going to support multiple ORBs.. 
_ORB_FOUND="0"

dnl OmniORB2 has no standard install path (sigh)
AC_ARG_WITH(omniORB2,
[  --with-omniORB2=PREFIX  Use libomniORB2 in PREFIX],
	[OMNIORB2_DIR=$withval
	ORB_CFLAGS="-D__OMNIORB2__"
	case "$target" in
	i*86-*-linux*)
		ORB_CFLAGS="-D__x86__=1 -D__linux__ -D__OSVERSION__=2 $ORB_CFLAGS"
		;;
	alpha-*-linux*)
		ORB_CFLAGS="-D__alpha__=1 -D__linux__ -D__OSVERSION__=2 $ORB_CFLAGS"
		;;
	esac
	if test "$OMNIORB2_DIR" = "yes"; then
		ORB_INCLUDE_PATH=""
		ORB_LIBRARY_PATH=""
	else
		ORB_INCLUDE_PATH="-I$OMNIORB2_DIR/include"
		ORB_LIBRARY_PATH="-L$OMNIORB2_DIR/lib"
	fi
	ORB_LDFLAGS="-lomniORB2 -lomniLC -lomnithread -ltcpwrapGK"
	ORB_IDL_FLAGS="-l -a"
	_ORB_FOUND="1"
])

dnl Checks for other ORBs would go here...

if test "$_ORB_FOUND" = "0"; then
	AC_MSG_ERROR([Unable to find ORB - specify one])
fi


dnl ======================================================================
dnl Check for headers

dnl ========================================================================
dnl Checks for typedefs, structures, and compiler characteristics.

if test "$GNU_CC"; then
    MKSHLIB='$(CXX) $(DSO_LDOPTS)'
    MKSHLIB_FORCE_ALL='-Wl,--whole-archive'
    MKSHLIB_UNFORCE_ALL='-Wl,--no-whole-archive'
    DSO_LDOPTS='-shared -Wl,-h -Wl,$(@:$(OBJDIR)/%.$(DLL_SUFFIX)=%.$(DLL_SUFFIX))'
    DSO_CFLAGS='-fPIC'
else
    AC_MSG_ERROR("This will not compile without GCC or EGCS")
fi

dnl turn rtti off
if test "$GNU_CXX"; then
    RTTI_FLAGS="-fno-rtti"
else
    AC_MSG_ERROR("This will not compile without G++ or EGCS")
fi

AC_ARG_ENABLE(debug,
[  --enable-debug          Enable debugging build],
  [DEBUG="1"
   DEBUG_FLAGS="-g"
   OPT_FLAGS=""
  ]
)

dnl ======================================================================
dnl Output makefiles and configuration

AC_SUBST(MKSHLIB)
AC_SUBST(MKSHLIB_FORCE_ALL)
AC_SUBST(MKSHLIB_UNFORCE_ALL)
AC_SUBST(DSO_CFLAGS)
AC_SUBST(DSO_LDOPTS)
AC_SUBST(DLL_SUFFIX)

AC_SUBST(ORB_CFLAGS)
AC_SUBST(ORB_INCLUDE_PATH)
AC_SUBST(ORB_LIBRARY_PATH)
AC_SUBST(ORB_LDFLAGS)
AC_SUBST(ORB_IDL_FLAGS)

AC_SUBST(DEFINES)
AC_SUBST(CFLAGS)
AC_SUBST(CXXFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(INCLUDE_PATH)
AC_SUBST(LIBRARY_PATH)

AC_SUBST(RTTI_FLAGS)
AC_SUBST(OPT_FLAGS)
AC_SUBST(DEBUG_FLAGS)
AC_SUBST(DEBUG)

AC_CONFIG_HEADER(include/autoconf.h)
AC_OUTPUT([config/autoconf.mk])
