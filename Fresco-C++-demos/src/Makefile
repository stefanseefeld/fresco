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

SHELL	= /bin/sh

top	= ../..
cpath	= $(top)/config
ipath	= $(top)/include
lpath	= $(top)/lib
mpath	= $(top)/modules
dpath	= dep
opath	= obj
gpath	= gdb
ppath	= prf
rpath	= $(lpath)

include $(cpath)/local.mk

# Compilation and linking flags.
CPPFLAGS= -I$(ipath) -I$(ipath)/Warsaw $(ORBCPPFLAGS)
CXXFLAGS= -pthread -Wall $(OPTFLAGS)
LDFLAGS	= -L$(lpath)
LIBS	= -lWarsaw -lBerlin -lPrague -lpthread
DEMO =	  Application.cc LayoutDemo.cc TextDemo.cc EditTextDemo.cc RasterDemo.cc TransformDemo.cc LogoDemo.cc \
	  FocusDemo.cc ViewportDemo.cc DocDemo.cc TermDemo.cc demo.cc
DEP	= $(patsubst %.cc, $(dpath)/%.d, $(DEMO))
OBJ	= $(patsubst %.cc, $(opath)/%.o, $(DEMO))

TARGET	=  demo

world:		$(TARGET)

ldlibpath = LD_LIBRARY_PATH=$(lpath)

demo:		$(OBJ)
		$(ldlibpath) $(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

install:	world
		for i in $(TARGET); do \
		  install -m755 $$i $(bindir); \
		done

clean:	
		rm -f *.o $(opath)/*.o $(dpath)/*.d *~ bb.out gmon.out

distclean:	clean
		rm -f $(TARGET)
		rm -rf $(opath) $(gpath) $(ppath) $(dpath)

$(dpath)/%.d:	%.cc %.hh
		@echo making dependencies for $<
		-@if [ ! -d $(dpath) ]; then mkdir $(dpath); fi
		@$(SHELL) -ec '$(CXX) -MM $(CPPFLAGS) $< \
		| sed "s/$*\\.o[ :]*/$(dpath)\/$*\\.d $(opath)\/$*\\.o : /g" > $@'
$(opath)/%.o:	%.cc
		-@if [ ! -d $(opath) ]; then mkdir $(opath); fi
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

trafo:		trafo.o
		g++ -L../../lib -o trafo trafo.o -lBerlin -lWarsaw

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean) 
-include $(DEP)
endif 
endif
