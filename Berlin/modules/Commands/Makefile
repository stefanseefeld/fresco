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

cpath	= ../../config
ipath	= ../../include
lpath	= ../../lib
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

SRC	= 

DEP	= $(patsubst %.cc, $(dpath)/%.d, $(SRC))
OBJ	= $(patsubst %.cc, $(opath)/%.o, $(SRC))
GDB	= $(patsubst %.cc, $(gpath)/%.o, $(SRC))
PRF	= $(patsubst %.cc, $(ppath)/%.o, $(SRC))
TARGET	= $(lpath)/libCommand.so

vpath %.d $(dpath)
vpath %.hh  $(ipath)/Warsaw $(ipath)/Berlin $(ipath)/Command

world:	$(TARGET)

$(TARGET):	$(OBJ)
		$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

$(dpath)/%.d:	%.cc $(ipath)/Command/%.hh
		@echo making dependencies for $<
		@if [ ! -d $(dpath) ]; then mkdir $(dpath); fi
		@$(SHELL) -ec '$(CXX) -MM $(CXXFLAGS) $< \
		| sed "s/$*\\.o[ :]*/$(dpath)\/$*\\.d $(opath)\/$*\\.o $(gpath)\/$*\\.o $(ppath)\/$*\\.o : /g" > $@'
$(opath)/%.o:	%.cc
		@if [ ! -d $(opath) ]; then mkdir $(opath); fi
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(SOFLAGS) -c $< -o $@
$(gpath)/%.o:	%.cc
		@if [ ! -d $(gpath) ]; then mkdir $(gpath); fi
		$(CXX) $(CXXFLAGS) $(GDBFLAGS) -c $< -o $@
$(ppath)/%.o:	%.cc
		@if [ ! -d $(ppath) ]; then mkdir $(ppath); fi
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(SOFLAGS) $(PRFFLAGS) -c $< -o $@

clean:	
		rm -f $(opath)/*.o $(gpath)/*.o $(ppath)/*.o $(dpath)/*.d
		rm -f *~ $(ipath)/Command/*~

distclean:	clean
		rm -f $(TARGET)
		rm -rf $(opath) $(gpath) $(ppath) $(dpath)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean) 
-include $(DEP)
endif 
endif 
