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

DIR_CPPFLAGS := -D_MIT_POSIX_THREADS -D_REENTRANT -D__OSVERSION__=2 -D__OMNIORB2__ -D__x86__
DIR_CXXFLAGS := -fno-rtti -fno-default-inline -fomit-frame-pointer -fnonnull-objects -pthread 
DIR_INCLUDES :=  -I.  
DIR_LDFLAGS  :=  -L. -L$(TOPDIR)/lib \
		-lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC -lstdc++ 

STATIC_INTERFACES := 	BoundedValue.idl BoundedRange.idl   Damage.idl	LayoutKit.idl	Pencil.idl \
			ClientContext.idl  	Drawable.idl	LifeCycle.idl	Transform.idl \
			Cloneable.idl	DrawingKit.idl	FigureKit.idl	Region.idl \
			Graphic.idl	Metrics.idl	Screen.idl \
			CommandKit.idl	Grid.idl Viewport.idl Stage.idl	Naming.idl	Subject.idl \
			Telltale.idl TextBuffer.idl	Traversal.idl	Text.idl		WidgetKit.idl

DYNAMIC_INTERFACES := Message.idl Event.idl Types.idl Style.idl

IDLSRCS := Naming.idl $(STATIC_INTERFACES) $(DYNAMIC_INTERFACES) 

SO_TARGET := libWarsaw.so 
SO_MAJOR_libWarsaw.so := 0
SO_MINOR_libWarsaw.so := 0
SO_PATCH_libWarsaw.so := 1

CXXSRCS := $(STATIC_INTERFACES:.idl=SK.cc) 
CXXSRCS += $(DYNAMIC_INTERFACES:.idl=DynSK.cc) $(DYNAMIC_INTERFACES:.idl=SK.cc)
SO_OBJS_libWarsaw.so := $(CXXSRCS:.cc=.o) 

include $(TOPDIR)/config/rules.mk


