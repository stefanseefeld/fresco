# This source file is a part of the Berlin Project.
# Copyright (C) 1998 Graydon Hoare <graydon@pobox.com> 
# http:#www.berlin-consortium.org
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public License
# as published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#

TOPDIR=../..
OS_ARCH='Linux'

DIR_CPPFLAGS := -D_MIT_POSIX_THREADS -D_REENTRANT -D__OSVERSION__=2 -D__OMNIORB2__
DIR_CXXFLAGS := -fno-rtti -fno-default-inline -fomit-frame-pointer -fnonnull-objects -pthread -O3 -Os
DIR_INCLUDES :=  -I.  
DIR_LDFLAGS  :=  -L. -L$(TOPDIR)/lib \
		-lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC -lstdc++ 

ALL_SUBTARGETS := 	BoundedValue.idl   Damage.idl	   LayoutKit.idl  Pencil.idl   Telltale.idl \
			ClientContext.idl  Drawable.idl    LifeCycle.idl  Reactor.idl  Transform.idl \
			Cloneable.idl	   DrawingKit.idl  Message.idl	  Region.idl   Traversal.idl \
			Graphic.idl	   Metrics.idl	  Screen.idl   Types.idl	Text.idl \
			CommandKit.idl	   Grid.idl	   Naming.idl	  Subject.idl  WidgetKit.idl  \
			Event.idl

IDLSRCS := Naming.idl $(ALL_SUBTARGETS) 
SO_TARGET := libwarsaw.so 
SO_MAJOR_libwarsaw.so := 0
SO_MINOR_libwarsaw.so := 0
SO_PATCH_libwarsaw.so := 1

CXXSRCS := $(ALL_SUBTARGETS:.idl=SK.cc) 
CXXSRCS += $(ALL_SUBTARGETS:.idl=DynSK.cc)
SO_OBJS_libwarsaw.so := $(CXXSRCS:.cc=.o) 

include $(TOPDIR)/config/rules.mk


