dnl
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 1999 Stefan Seefeld <stefan@fresco.org> 
dnl http://www.fresco.org
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
dnl FRESCO_OMNIORBPY_CHECK
dnl
dnl Checks if omniORBpy is found. If it is, $berlin_cv_lib_omniORBpy is
dnl set to "yes". Also, the variable IDLPY is defined.

AC_DEFUN([FRESCO_OMNIORBPY_CHECK],
  [AC_ARG_WITH(omniorbpy-prefix,
	       AC_HELP_STRING([--with-omniorbpy-prefix],[Prefix for omniORBpy]),
               [omniorbpy_prefix="$withval"])

    dnl Check for omniidl. Should we check in
    dnl $omniorb_prefix/bin/<arch>, too?
    if test x$omniorb_prefix != x ; then
      omniorb_path=$omniorb_prefix/bin:$PATH
    else
      omniorb_path=$PATH
    fi
    AC_PATH_PROG(IDLPY, omniidl, no, $omniorb_path)
    
    dnl Test whether omniidl knows about the python backend
    AC_CACHE_CHECK([whether omniidl supports Python],
    berlin_cv_sys_omniidl_py, [
    
    cat > conftest.idl <<EOF
dnl	#line __oline__ configure
    interface foo {};
EOF
    if $IDLPY -bpython conftest.idl; then
    dnl Don't remove the temporary files here, so they can be examined.
      ifelse([$2], , , [$2])
      berlin_cv_sys_omniidl_py=yes
    else
dnl  	  echo "configure: failed program was:" >&AC_FD_CC
dnl  	  cat conftest.$ac_ext >&AC_FD_CC
      ifelse([$3], , , [  rm -fr conftest*
      	$3])
      berlin_cv_sys_omniidl_py=no
    fi
    rm -fr conftest*
    rm -fr _GlobalIDL _GlobalIDL__POA])
    AC_SUBST(IDLPY)
])
