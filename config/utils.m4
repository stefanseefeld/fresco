dnl $Id$
dnl
dnl This source file is a part of the Berlin Project.
dnl Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
dnl Copyright (C) 2000 Håvard Skinnemoen <skinnemo@itk.ntnu.no>
dnl http://www.berlin-consortium.org/
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

divert(-1)

dnl ##
dnl ##  Display Configuration Headers
dnl ##
dnl ##  configure.in:
dnl ##    AC_MSG_PART(<text>)
dnl ##

define(AC_MSG_PART,[dnl
if test ".$enable_subdir" != .yes; then
    AC_MSG_RESULT()
    AC_MSG_RESULT(${TB}$1:${TN})
fi
])dnl

dnl ##
dnl ##  Display a message under --verbose
dnl ##
dnl ##  configure.in:
dnl ##    AC_MSG_VERBOSE(<text>)
dnl ##

define(AC_MSG_VERBOSE,[dnl
if test ".$verbose" = .yes; then
    AC_MSG_RESULT([  $1])
fi
])

dnl ##
dnl ##  Do not display message for a command
dnl ##
dnl ##  configure.in:
dnl ##    AC_MSG_SILENT(...)
dnl ##

define(AC_FD_TMP, 9)
define(AC_MSG_SILENT,[dnl
exec AC_FD_TMP>&AC_FD_MSG AC_FD_MSG>/dev/null
$1
exec AC_FD_MSG>&AC_FD_TMP AC_FD_TMP>&-
])

dnl ##
dnl ##  Perform something only once
dnl ##
dnl ##  configure.in:
dnl ##    AC_ONCE(<action>)
dnl ##

define(AC_ONCE,[
ifelse(ac_once_$1, already_done, ,[
    define(ac_once_$1, already_done)
    $2
])dnl
])

dnl ##
dnl ##  Support for $(S)
dnl ##
dnl ##  configure.in:
dnl ##    AC_SRCDIR_PREFIX(<varname>)
dnl ##

AC_DEFUN(AC_SRCDIR_PREFIX,[
ac_prog=[$]0
changequote(, )dnl
ac_srcdir=`echo $ac_prog | sed -e 's%/[^/][^/]*$%%' -e 's%\([^/]\)/*$%\1%'`
changequote([, ])dnl
if test ".$ac_srcdir" = ".$ac_prog"; then
    ac_srcdir=""
elif test "x$ac_srcdir" = "x."; then
    ac_srcdir=""
else
    if test ".$CFLAGS" = .; then
        CFLAGS="-I$ac_srcdir"
    else
        CFLAGS="$CFLAGS -I$ac_srcdir"
    fi
    ac_srcdir="$ac_srcdir/"
fi
$1="$ac_srcdir"
AC_SUBST($1)
])dnl

dnl ##
dnl ##  Set paths srcdir and builddir to point to
dnl ##  the respective top level directories.
dnl ##  This macro assumes that both trees are identically
dnl ##  structured, i.e. the given <offset> parameter is
dnl ##  subtracted from both, `pwd` as well as <srcdir>
dnl ##
dnl ##  configure.in:
dnl ##    AC_SET_PATHS(<offset>)
dnl ##

AC_DEFUN(AC_SET_PATHS,[
AC_DIVERT_PUSH(AC_DIVERSION_INIT)dnl
changequote(, )dnl
dnl builddir=`pwd | sed -e 's%$1$%%'`
builddir=`pwd`/$1
dnl srcdir=`echo $srcdir | sed -e 's%$1$%%'`
srcdir="${srcdir}/$1"
topdir="${srcdir}"
changequote([, ])dnl
AC_DIVERT_POP()
AC_SUBST(topdir)
AC_SUBST(builddir)
])dnl

dnl ##
dnl ##  Support for --enable-subdir (for use with pth.m4)
dnl ##
dnl ##  configure.in:
dnl ##    AC_ENABLESUBDIR
dnl ##

AC_DEFUN(AC_ENABLESUBDIR,[
AC_ARG_ENABLE(subdir,dnl
[  --enable-subdir         enable local building as subdirectory (default=no)],[dnl
],[dnl
enable_subdir=no
])dnl
if test ".$enable_subdir" = .yes; then
    enable_batch=yes
    enable_shared=no
fi
])dnl

dnl ##
dnl ##  Support for Configuration Headers
dnl ##
dnl ##  configure.in:
dnl ##    AC_HEADLINE(<short-name>, <long-name>, <copyright>[, <version>])
dnl ##
dnl ##
dnl ##  Modified to look for shtool in ./config too
dnl ##  Warning: $ac_aux_dir isn't documented.

AC_DEFUN(AC_HEADLINE,[dnl
AC_DIVERT_PUSH(AC_DIVERSION_INIT)dnl
#   configuration header
if test ".`echo dummy [$]@ | grep enable-subdir`" != .; then
    enable_subdir=yes
fi
if test ".`echo dummy [$]@ | grep help`" = .; then
    #   bootstrapping shtool
    ac_prog=[$]0
changequote(, )dnl
    ac_srcdir=`echo $ac_prog | sed -e 's%/[^/][^/]*$%%' -e 's%\([^/]\)/*$%\1%'`
changequote([, ])dnl
    test ".$ac_srcdir" = ".$ac_prog" && ac_srcdir=.
    if test -x "$ac_srcdir/shtool" ; then
        ac_shtool="$ac_srcdir/shtool"
    elif test -x "$ac_aux_dir/shtool" ; then
	ac_shtool="$ac_aux_dir/shtool"
    else
	AC_MSG_ERROR(Unable to locate shtool!)
    fi

    #   find out terminal sequences
    if test ".$enable_subdir" != .yes; then
        TB=`$ac_shtool echo -n -e %B 2>/dev/null`
        TN=`$ac_shtool echo -n -e %b 2>/dev/null`
    else
        TB=''
        TN=''
    fi

    #   friendly header ;)
    ifelse([$4], , [
	echo "Configuring ${TB}$1${TN} ($2)"], [
	echo "Configuring ${TB}$1${TN} ($2), Version ${TB}${$4}${TN}"
	])
    echo "$3"
fi
AC_DIVERT_POP()
])dnl

dnl ##
dnl ##  Support for Version numbers
dnl ##
dnl ##  configure.in:
dnl ##    AC_VERSION(<major, <minor>, <patch>, <interface>, <binary>)
dnl ##
dnl ## Making releases:
dnl ##
dnl ##   <interface> += 1;
dnl ##   <binary> += 1;
dnl ## if any functions have been added, set <interface> to 0.
dnl ## if backwards compatibility has been broken,
dnl ## set <binary> and <interface> to 0.
dnl ##

AC_DEFUN(AC_VERSION,[
AC_DIVERT_PUSH(AC_DIVERSION_NOTICE)dnl
MAJOR_VERSION=$1
MINOR_VERSION=$2
PATCH_LEVEL=$3
INTERFACE_AGE=$4
BINARY_AGE=$5
VERSION=$MAJOR_VERSION.$MINOR_VERSION.$PATCH_LEVEL

AC_SUBST(MAJOR_VERSION)
AC_SUBST(MINOR_VERSION)
AC_SUBST(PATCH_LEVEL)
AC_SUBST(INTERFACE_AGE)
AC_SUBST(BINARY_AGE)
AC_SUBST(VERSION)
AC_DIVERT_POP()
])dnl

dnl ##
dnl ##  Support for Platform IDs
dnl ##
dnl ##  configure.in:
dnl ##    AC_PLATFORM(<variable>)
dnl ##

AC_DEFUN(AC_PLATFORM,[
dnl #   Autoconf has set $nonopt
case ".$nonopt" in
    .NONE ) $1=`${CONFIG_SHELL-/bin/sh} $srcdir/config.guess` ;;
    *     ) $1="$nonopt" ;;
esac
$1=`${CONFIG_SHELL-/bin/sh} $srcdir/config.sub $$1`
AC_SUBST($1)
if test ".$enable_subdir" != .yes; then
    echo "Platform: ${TB}${$1}${TN}"
fi
])dnl

dnl ##
dnl ##  Support for config.param files
dnl ##
dnl ##  configure.in:
dnl ##    AC_CONFIG_PARAM(<file>)
dnl ##

AC_DEFUN(AC_CONFIG_PARAM,[
AC_DIVERT_PUSH(-1)
AC_ARG_WITH(param,[  --with-param=ID[,ID,..] load parameters from $1])
AC_DIVERT_POP()
AC_DIVERT_PUSH(AC_DIVERSION_NOTICE)
ac_prev=""
ac_param=""
if test -f $1; then
    ac_param="$1:common"
fi
for ac_option
do
    if test ".$ac_prev" != .; then
        eval "$ac_prev=\$ac_option"
        ac_prev=""
        continue
    fi
    case "$ac_option" in
        -*=*) ac_optarg=`echo "$ac_option" | sed 's/[[-_a-zA-Z0-9]]*=//'` ;;
           *) ac_optarg="" ;;
    esac
    case "$ac_option" in
        --with-param=* ) 
            case $ac_optarg in
                *:* ) 
                    ac_from=`echo $ac_optarg | sed -e 's/:.*//'`
                    ac_what=`echo $ac_optarg | sed -e 's/.*://'`
                    ;;
                * ) 
                    ac_from="$1"
                    ac_what="$ac_optarg"
                    ;;
            esac
            if test ".$ac_param" = .; then
                ac_param="$ac_from:$ac_what"
            else
                ac_param="$ac_param,$ac_from:$ac_what"
            fi
            ;;
    esac
done
if test ".$ac_param" != .; then
    # echo "loading parameters"
    OIFS="$IFS"
    IFS=","
    pconf="/tmp/autoconf.$$"
    echo "ac_options=''" >$pconf
    ac_from="$1"
    for ac_section in $ac_param; do
        changequote(, )
        case $ac_section in
            *:* ) 
                ac_from=`echo "$ac_section" | sed -e 's/:.*//'`
                ac_section=`echo "$ac_section" | sed -e 's/.*://'`
                ;;
        esac
        sed -e "1,/[ 	]*[ 	]*${ac_section}[ 	]*{[ 	]*/d" \
            -e '/[ 	]*}[ 	]*/,$d' \
            -e ':join' -e '/\\[ 	]*$/N' -e 's/\\[ 	]*\n[ 	]*//' -e 'tjoin' \
            -e 's/^[ 	]*//g' \
            -e 's/^\(--.*=.*\)$/ac_options="$ac_options \1"/' \
            -e 's/^\(--.*\)$/ac_options="$ac_options \1"/' \
            $ac_from >>$pconf
        changequote([, ])
    done
    IFS="$OIFS"
    . $pconf
    rm -f $pconf >/dev/null 2>&1
    if test ".[$]*" = .; then
        set -- $ac_options
    else
        set -- "[$]@" $ac_options
    fi
fi
AC_DIVERT_POP()
])dnl

dnl ##
dnl ##  Check whether compiler option works
dnl ##
dnl ##  configure.in:
dnl ##    AC_COMPILER_OPTION(<name>, <display>, <option>, 
dnl ##                       <action-success>, <action-failure>)
dnl ##

AC_DEFUN(AC_COMPILER_OPTION,[dnl
AC_MSG_CHECKING(whether compiler option(s) $2 work)
AC_CACHE_VAL(ac_cv_compiler_option_$1,[
SAVE_CFLAGS="$CFLAGS"
CFLAGS="$CFLAGS $3"
AC_TRY_COMPILE([],[], ac_cv_compiler_option_$1=yes, ac_cv_compiler_option_$1=no)
CFLAGS="$SAVE_CFLAGS"
])dnl
if test ".$ac_cv_compiler_option_$1" = .yes; then
    ifelse([$4], , :, [$4])
else
    ifelse([$5], , :, [$5])
fi
AC_MSG_RESULT([$ac_cv_compiler_option_$1])
])dnl

dnl ##
dnl ##  Profiling Support  
dnl ##
dnl ##  configure.in:
dnl ##    AC_CHECK_PROFILING
dnl ##

AC_DEFUN(AC_CHECK_PROFILING,[dnl
AC_MSG_CHECKING(for compilation profile mode)
AC_ARG_ENABLE(profile,dnl
[  --enable-profile        build for profiling (default=no)],
[dnl
if test ".$ac_cv_prog_gcc" = ".no"; then
    AC_MSG_ERROR([profiling requires gcc and gprof])
fi
CFLAGS=`echo "$CFLAGS" | sed -e 's/-O3//g'`
CFLAGS="$CFLAGS -O0 -pg"
LDFLAGS="$LDFLAGS -pg"
AC_DEFINE(profile)
msg="enabled"
],[
msg="disabled"
])dnl
AC_MSG_RESULT([$msg])
if test ".$msg" = .enabled; then
    enable_shared=no
fi
])

dnl ##
dnl ##  Build Parameters
dnl ##
dnl ##  configure.in:
dnl ##    AC_CHECK_BUILDPARAM
dnl ##

AC_DEFUN(AC_CHECK_BUILDPARAM,[dnl
dnl #   determine build mode
AC_MSG_CHECKING(whether to activate batch build mode)
AC_ARG_ENABLE(batch,dnl
[  --enable-batch          enable batch build mode (default=no)],[dnl
],[dnl
enable_batch=no
])dnl
if test ".$silent" = .yes; then
    enable_batch=yes
fi
AC_MSG_RESULT([$enable_batch])
BATCH="$enable_batch"
AC_SUBST(BATCH)
dnl #   determine build targets
TARGET_ALL='$(TARGET_PREQ) $(TARGET_LIBS)'
AC_MSG_CHECKING(whether to activate maintainer build targets)
AC_ARG_ENABLE(maintainer,dnl
[  --enable-maintainer     enable maintainer build targets (default=no)],[dnl
],[dnl
enable_maintainer=no
])dnl
AC_MSG_RESULT([$enable_maintainer])
if test ".$enable_maintainer" = .yes; then
    TARGET_ALL="$TARGET_ALL \$(TARGET_MANS)"
fi
AC_MSG_CHECKING(whether to activate test build targets)
AC_ARG_ENABLE(tests,dnl
[  --enable-tests          enable test build targets (default=yes)],[dnl
],[dnl
enable_tests=yes
])dnl
AC_MSG_RESULT([$enable_tests])
if test ".$enable_tests" = .yes; then
    TARGET_ALL="$TARGET_ALL \$(TARGET_TEST)"
fi
AC_SUBST(TARGET_ALL)
])

dnl ##
dnl ##  Check for a pre-processor define in a header
dnl ##
dnl ##  configure.in:
dnl ##    AC_CHECK_DEFINE(<define>, <header>)
dnl ##  acconfig.h:
dnl ##    #undef HAVE_<define>
dnl ##

AC_DEFUN(AC_CHECK_DEFINE,[dnl
AC_MSG_CHECKING(for define $1 in $2)
AC_CACHE_VAL(ac_cv_define_$1,
[AC_EGREP_CPP([YES_IS_DEFINED], [
#include <$2>
#ifdef $1
YES_IS_DEFINED
#endif
], ac_cv_define_$1=yes, ac_cv_define_$1=no)])dnl
AC_MSG_RESULT($ac_cv_define_$1)
if test $ac_cv_define_$1 = yes; then
    AC_DEFINE(HAVE_[]translit($1, [a-z], [A-Z]))
fi
])

dnl ##
dnl ##  Check for an ANSI C typedef in a header
dnl ##
dnl ##  configure.in:
dnl ##    AC_CHECK_TYPEDEF(<typedef>, <header>)
dnl ##  acconfig.h:
dnl ##    #undef HAVE_<typedef>
dnl ##

AC_DEFUN(AC_CHECK_TYPEDEF,[dnl
AC_REQUIRE([AC_HEADER_STDC])dnl
AC_MSG_CHECKING(for typedef $1)
AC_CACHE_VAL(ac_cv_typedef_$1,
[AC_EGREP_CPP(dnl
changequote(<<,>>)dnl
<<(^|[^a-zA-Z_0-9])$1[^a-zA-Z_0-9]>>dnl
changequote([,]), [
#include <$2>
], ac_cv_typedef_$1=yes, ac_cv_typedef_$1=no)])dnl
AC_MSG_RESULT($ac_cv_typedef_$1)
if test $ac_cv_typedef_$1 = yes; then
    AC_DEFINE(HAVE_[]translit($1, [a-z], [A-Z]))
fi
])

dnl ##
dnl ##  Check for an ANSI C struct attribute in a structure defined in a header
dnl ##
dnl ##  configure.in:
dnl ##    AC_CHECK_STRUCTATTR(<attr>, <struct>, <header>)
dnl ##  acconfig.h:
dnl ##    #undef HAVE_<attr>
dnl ##

AC_DEFUN(AC_CHECK_STRUCTATTR,[dnl
AC_REQUIRE([AC_HEADER_STDC])dnl
AC_MSG_CHECKING(for attribute $1 in struct $2 from $3)
AC_CACHE_VAL(ac_cv_structattr_$1,[dnl

AC_TRY_LINK([
#include <sys/types.h>
#include <$3>
],[
struct $2 *sp1;
struct $2 *sp2;
sp1->$1 = sp2->$1;
], ac_cv_structattr_$1=yes, ac_cv_structattr_$1=no)])dnl
AC_MSG_RESULT($ac_cv_structattr_$1)
if test $ac_cv_structattr_$1 = yes; then
    AC_DEFINE(HAVE_[]translit($1, [a-z], [A-Z]))
fi
])

dnl ##
dnl ##  Check for argument type of a function
dnl ##
dnl ##  configure.in:
dnl ##    AC_CHECK_ARGTYPE(<header> [...], <func>, <arg-number>,
dnl ##                     <max-arg-number>, <action-with-${ac_type}>)
dnl ##

AC_DEFUN(AC_CHECK_ARGTYPE,[dnl
AC_REQUIRE_CPP()dnl
AC_MSG_CHECKING([for type of argument $3 for $2()])
AC_CACHE_VAL([ac_cv_argtype_$2$3],[
cat >conftest.$ac_ext <<EOF
[#]line __oline__ "configure"
#include "confdefs.h"
EOF
for ifile in $1; do
    echo "#include <$ifile>" >>conftest.$ac_ext
done
gpat=''
spat=''
i=1
changequote(, )dnl
while test $i -le $4; do
    gpat="$gpat[^,]*"
    if test $i -eq $3; then
        spat="$spat\\([^,]*\\)"
    else
        spat="$spat[^,]*"
    fi
    if test $i -lt $4; then
        gpat="$gpat,"
        spat="$spat,"
    fi
    i=`expr $i + 1`
done
(eval "$ac_cpp conftest.$ac_ext") 2>&AC_FD_CC |\
sed -e ':join' \
    -e '/,[ 	]*$/N' \
    -e 's/,[ 	]*\n[ 	]*/, /' \
    -e 'tjoin' |\
egrep "[^a-zA-Z0-9_]$2[ 	]*\\($gpat\\)" | head -1 |\
sed -e "s/.*[^a-zA-Z0-9_]$2[ 	]*($spat).*/\\1/" \
    -e 's/(\*[a-zA-Z_][a-zA-Z_0-9]*)/(*)/' \
    -e 's/^[ 	]*//' -e 's/[ 	]*$//' \
    -e 's/^/arg:/' \
    -e 's/^arg:\([^ 	]*\)$/type:\1/' \
    -e 's/^arg:\(.*_t\)*$/type:\1/' \
    -e 's/^arg:\(.*\*\)$/type:\1/' \
    -e 's/^arg:\(.*[ 	]\*\)[_a-zA-Z][_a-zA-Z0-9]*$/type:\1/' \
    -e 's/^arg:\(.*[ 	]char\)$/type:\1/' \
    -e 's/^arg:\(.*[ 	]short\)$/type:\1/' \
    -e 's/^arg:\(.*[ 	]int\)$/type:\1/' \
    -e 's/^arg:\(.*[ 	]long\)$/type:\1/' \
    -e 's/^arg:\(.*[ 	]float\)$/type:\1/' \
    -e 's/^arg:\(.*[ 	]double\)$/type:\1/' \
    -e 's/^arg:\(.*[ 	]unsigned\)$/type:\1/' \
    -e 's/^arg:\(.*[ 	]signed\)$/type:\1/' \
    -e 's/^arg:\(.*struct[ 	][_a-zA-Z][_a-zA-Z0-9]*\)$/type:\1/' \
    -e 's/^arg:\(.*\)[ 	]_[_a-zA-Z0-9]*$/type:\1/' \
    -e 's/^arg:\(.*\)[ 	]\([^ 	]*\)$/type:\1/' \
    -e 's/^type://' >conftest.output
ac_cv_argtype_$2$3=`cat conftest.output`
changequote([, ])dnl
rm -f conftest*
])
AC_MSG_RESULT([$ac_cv_argtype_$2$3])
ac_type="$ac_cv_argtype_$2$3"
[$5]
])

dnl ##
dnl ##  Check for existance of a function
dnl ##
dnl ##  configure.in:
dnl ##     AC_CHECK_FUNCTION(<function> [, <action-if-found> [, <action-if-not-found>]])
dnl ##     AC_CHECK_FUNCTIONS(<function> [...] [, <action-if-found> [, <action-if-not-found>]])
dnl ##

AC_DEFUN(AC_CHECK_FUNCTIONS,[dnl
for ac_func in $1; do
    AC_CHECK_FUNCTION($ac_func, 
        [changequote(, )dnl
        ac_tr_func=HAVE_`echo $ac_func | tr 'abcdefghijklmnopqrstuvwxyz' 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'`
        changequote([, ])dnl
        AC_DEFINE_UNQUOTED($ac_tr_func) $2], $3)dnl
done
])

AC_DEFUN(AC_CHECK_FUNCTION, [dnl
AC_MSG_CHECKING([for function $1])
AC_CACHE_VAL(ac_cv_func_$1, [dnl
AC_TRY_LINK([
/* System header to define __stub macros and hopefully few prototypes,
   which can conflict with char $1(); below. */
#include <assert.h>
#ifdef __cplusplus
extern "C"
#endif
/* We use char because int might match the return type of a gcc2
   builtin and then its argument prototype would still apply. */
char $1();
char (*f)();
], [
/* The GNU C library defines this for functions which it implements
   to always fail with ENOSYS.  Some functions are actually named
   something starting with __ and the normal name is an alias. */
#if defined (__stub_$1) || defined (__stub___$1)
choke me
#else
f = $1;
#endif
], eval "ac_cv_func_$1=yes", eval "ac_cv_func_$1=no")])
if eval "test \"`echo '$ac_cv_func_'$1`\" = yes"; then
  AC_MSG_RESULT(yes)
  ifelse([$2], , :, [$2])
else
  AC_MSG_RESULT(no)
ifelse([$3], , , [$3
])dnl
fi
])

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

define(AC_BEGIN_DECISION,[dnl
ac_decision_item='$1'
ac_decision_msg='FAILED'
ac_decision=''
])

define(AC_DECIDE,[dnl
ac_decision='$1'
ac_decision_msg='$2'
ac_decision_$1=yes
ac_decision_$1_msg='$2'
])

define(AC_DECISION_OVERRIDE,[dnl
    ac_decision=''
    for ac_item in $1; do
         eval "ac_decision_this=\$ac_decision_${ac_item}"
         if test ".$ac_decision_this" = .yes; then
             ac_decision=$ac_item
             eval "ac_decision_msg=\$ac_decision_${ac_item}_msg"
         fi
    done
])

define(AC_DECISION_FORCE,[dnl
ac_decision="$1"
eval "ac_decision_msg=\"\$ac_decision_${ac_decision}_msg\""
])

define(AC_END_DECISION,[dnl
if test ".$ac_decision" = .; then
    echo "[$]0:Error: decision on $ac_decision_item failed." 1>&2
    echo "[$]0:Hint: see config.log for more details!" 1>&2
    exit 1
else
    if test ".$ac_decision_msg" = .; then
        ac_decision_msg="$ac_decision"
    fi
    AC_MSG_RESULT([decision on $ac_decision_item... ${TB}$ac_decision_msg${TN}])
fi
])

dnl ##
dnl ##  Check for existance of a file
dnl ##
dnl ##  configure.in:
dnl ##    AC_TEST_FILE(<file>, <success-action>, <failure-action>)
dnl ##

AC_DEFUN(AC_TEST_FILE, [
ac_safe=`echo "$1" | sed 'y%./+-%__p_%'`
AC_MSG_CHECKING([for $1])
AC_CACHE_VAL(ac_cv_file_$ac_safe, [
if test -r $1; then
    eval "ac_cv_file_$ac_safe=yes"
else
    eval "ac_cv_file_$ac_safe=no"
fi
])dnl
if eval "test \"`echo '$ac_cv_file_'$ac_safe`\" = yes"; then
    AC_MSG_RESULT(yes)
    ifelse([$2], , :, [$2])
else
    AC_MSG_RESULT(no)
    ifelse([$3], , :, [$3])
fi
])

dnl ##
dnl ##  Check for an external/extension library.
dnl ##  - is aware of <libname>-config style scripts
dnl ##  - searches under standard paths include, lib, etc.
dnl ##  - searches under subareas like .libs, etc.
dnl ##
dnl ##  configure.in:
dnl ##      AC_CHECK_EXTLIB(<realname>, <libname>, <func>, <header>,
dnl ##                      [<success-action> [, <fail-action>]])
dnl ##  Makefile.in:
dnl ##      CFLAGS  = @CFLAGS@
dnl ##      LDFLAGS = @LDFLAGS@
dnl ##      LIBS    = @LIBS@
dnl ##  shell:
dnl ##      $ ./configure --with-<libname>[=DIR]
dnl ##

AC_DEFUN(AC_CHECK_EXTLIB,[dnl
AC_ARG_WITH($2,dnl
[  --with-]substr([$2[[=DIR]]                 ], 0, 19)[build against $1 library (default=no)],
    if test ".$with_$2" = .yes; then
        #   via config script
        $2_version=`($2-config --version) 2>/dev/null`
        if test ".$$2_version" != .; then
            CPPFLAGS="$CPPFLAGS `$2-config --cflags`"
            CFLAGS="$CFLAGS `$2-config --cflags`"
            LDFLAGS="$LDFLAGS `$2-config --ldflags`"
        fi
    else
        if test -d "$with_$2"; then
            found=0
            #   via config script
            for dir in $with_$2/bin $with_$2; do
                if test -f "$dir/$2-config"; then
                    $2_version=`($dir/$2-config --version) 2>/dev/null`
                    if test ".$$2_version" != .; then
                        CPPFLAGS="$CPPFLAGS `$dir/$2-config --cflags`"
                        CFLAGS="$CFLAGS `$dir/$2-config --cflags`"
                        LDFLAGS="$LDFLAGS `$dir/$2-config --ldflags`"
                        found=1
                        break
                    fi
                fi
            done
            #   via standard paths
            if test ".$found" = .0; then
                for dir in $with_$2/include/$2 $with_$2/include $with_$2; do
                    if test -f "$dir/$4"; then
                        CPPFLAGS="$CPPFLAGS -I$dir"
                        CFLAGS="$CFLAGS -I$dir"
                        found=1
                        break
                    fi
                done
                for dir in $with_$2/lib/$2 $with_$2/lib $with_$2; do
                    if test -f "$dir/lib$2.a" -o -f "$dir/lib$2.so"; then
                        LDFLAGS="$LDFLAGS -L$dir"
                        found=1
                        break
                    fi
                done
            fi
            #   in any subarea
            if test ".$found" = .0; then
changequote(, )dnl
                for file in x `find $with_$2 -name "$4" -type f -print`; do
                    test .$file = .x && continue
                    dir=`echo $file | sed -e 's;[[^/]]*$;;' -e 's;\(.\)/$;\1;'`
                    CPPFLAGS="$CPPFLAGS -I$dir"
                    CFLAGS="$CFLAGS -I$dir"
                done
                for file in x `find $with_$2 -name "lib$2.[[aso]]" -type f -print`; do
                    test .$file = .x && continue
                    dir=`echo $file | sed -e 's;[[^/]]*$;;' -e 's;\(.\)/$;\1;'`
                    LDFLAGS="$LDFLAGS -L$dir"
                done
changequote([, ])dnl
            fi
        fi
    fi
    AC_HAVE_HEADERS($4)
    AC_CHECK_LIB($2, $3)
    AC_IFALLYES(header:$4 lib:$2_$3, with_$2=yes, with_$2=no)
    if test ".$with_$2" = .no; then
        AC_ERROR([Unable to find $1 library])
    fi
,
if test ".$with_$2" = .; then
    with_$2=no
fi
)dnl
AC_MSG_CHECKING(whether to build against $1 library)
if test ".$with_$2" = .yes; then
    ifelse([$5], , :, [$5])
else
    ifelse([$6], , :, [$6])
fi
AC_MSG_RESULT([$with_$2])
])dnl


dnl See whether we need a declaration for a function.
dnl AC_NEED_DECLARATION(FUNCTION [, EXTRA-HEADER-FILES])
AC_DEFUN(AC_NEED_DECLARATION,
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
  ac_tr_decl=NEED_DECLARATION_`echo $1 | tr 'abcdefghijklmnopqrstuvwxyz' 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'`
  AC_DEFINE_UNQUOTED($ac_tr_decl)
else
  AC_MSG_RESULT(no)
fi
])dnl

divert

