# $Id$
#
# This source file is a part of the Berlin Project.
# Copyright (C) 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

top		= ../..
cpath		= $(top)/config

include $(cpath)/local.mk
include $(cpath)/Clients-C++/local.mk

# Compilation and linking flags.
CXXFLAGS	+= -Wall $(OPTFLAGS)
LIBS		+= -lBerlin -lPrague

TARGETS		= demo canvas # trafo -- doesn't work here. Anyone?
demo_SRC	= \
		  Application.cc LayoutDemo.cc TextDemo.cc \
		  EditTextDemo.cc RasterDemo.cc TransformDemo.cc \
		  ColorDemo.cc LogoDemo.cc FocusDemo.cc \
		  ViewportDemo.cc DocDemo.cc TermDemo.cc demo.cc
canvas_SRC	= canvas.cc

trafo_SRC	= trafo.cc

all: world

include $(cpath)/binary.mk
