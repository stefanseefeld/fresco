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

top     = ../..
cpath   = $(top)/config
hpath   = $(top)/include/Berlin

#cpath	= ../../config
#ipath	= ../../include
#lpath	= ../../lib
dpath	= dep
opath	= obj
gpath	= gdb
ppath	= prf
rpath	= $(lpath)

include $(cpath)/local.mk

# Compilation and linking flags.
CPPFLAGS= -I$(ipath) -I$(ipath)/Warsaw
LDFLAGS	= -shared -rdynamic -L$(lpath)
LIBS	= -lPrague -lBerlin $(ORBLIBS)

SRC	= TextKitImpl.cc TextChunk.cc FontChange.cc

DEP	= $(patsubst %.cc, $(dpath)/%.d, $(SRC))
OBJ	= $(patsubst %.cc, $(opath)/%.o, $(SRC))
GDB	= $(patsubst %.cc, $(gpath)/%.o, $(SRC))
PRF	= $(patsubst %.cc, $(ppath)/%.o, $(SRC))

TARGET	= $(lpath)/libText.so

vpath %.d $(dpath)
vpath %.hh  $(ipath)/Warsaw $(ipath)/Berlin $(ipath)/Text

world:	$(TARGET)

$(TARGET):	$(OBJ)
		$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

clean:	
		rm -f $(opath)/*.o $(gpath)/*.o $(ppath)/*.o $(dpath)/*.d
		rm -f *~ $(ipath)/Text/*~

distclean:	clean
		rm -f $(TARGET)
		rm -rf $(opath) $(gpath) $(ppath) $(dpath)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean) 
-include $(DEP)
endif 
endif 
 
include $(cpath)/plugin.mk
