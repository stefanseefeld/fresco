# $Id$
#
# This source file is a part of the Berlin Project.
# Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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

SHELL	= /bin/sh

top	= ../../..
cpath	= $(top)/config

include $(cpath)/local.mk
include $(cpath)/Server/local.mk

hpath	= $(ipath)/Drawing/libArt

# Compilation and linking flags.
CPPFLAGS= -I$(ipath) -I$(ipath)/Warsaw $(LIBART_INCLUDES) -I/usr/local/include/libart_lgpl $(ORBCPPFLAGS)
LDFLAGS	= -shared -rdynamic -L$(lpath)
LIBS	= -lPrague -lBerlin $(LIBART_LIBS) -lfreetype

SRC	= LibArtDrawingKit.cc LibArtUnifont.cc LibArtFTFont.cc LibArtRaster.cc  
TARGET	= $(mpath)/libArtDrawing.so

vpath %.d $(dpath)
vpath %.hh  $(ipath)/Warsaw $(ipath)/Berlin $(ipath)/Drawing/libArt

include $(cpath)/module.mk
