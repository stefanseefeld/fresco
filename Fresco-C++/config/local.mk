# $Id$
#
# This source file is a part of the Berlin Project.
# Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
# http://www.berlin-consortium.org
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
# MA 02139, USA.

# Build tools specific to Warsaw
IDL		= /usr/local/bin/omniidl2

# Compilation and linking flags.
IDLFLAGS	= 
LCIDLFLAGS	= -l
DYNIDLFLAGS	= -a
ORBFLAGS	= __OMNIORB2__
ORBDEFS		= -D__x86__ -D__linux__ -D__OSVERSION__=2
ORBCPPFLAGS	= 
ORBOPTFLAGS	= -fno-default-inline -fomit-frame-pointer -fnonnull-objects
ORBLIBS		=  -lomniORB2 -lomnithread -ltcpwrapGK -lomniLC -lomniDynamic2 -lomniLC -lomniORB2 -lomnithread -ltcpwrapGK
