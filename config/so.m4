dnl $Id$
dnl This source file is a part of the Fresco Project.
dnl Copyright (C) 2000 Håvard Skinnemoen <skinnemo@itk.ntnu.no>
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
dnl FRESCO_FLAG_SO
dnl
dnl Check for compiler and linker flags needed to make shared libraries
AC_DEFUN([FRESCO_FLAG_SO],[

	dnl TODO: Add checks to set the right flag for all compilers
	SO_CXXFLAGS="-fPIC"
	SO_LDFLAGS="-shared"

	AC_SUBST(SO_CXXFLAGS)
	AC_SUBST(SO_LDFLAGS)
])
