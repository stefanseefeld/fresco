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

top	= ../../..
cpath	= $(top)/config
ipath	= $(top)/include
hpath	= $(top)/include/Berlin
dpath	= dep
opath	= obj

include $(cpath)/local.mk

# Compilation and linking flags.
CPPFLAGS= -I. -I$(ipath) $(ORBCPPFLAGS)
LDFLAGS	= -shared -rdynamic -L$(lpath)
LIBS	= 

SRC 	= TraderComponentsImpl.cc SupportAttributesImpl.cc LookupImpl.cc ServiceTypeRepositoryImpl.cc
TARGET	= traderd

vpath %.d $(dpath)
vpath %.hh  $(ipath)/Warsaw

DEP	= $(patsubst %.cc, $(dpath)/%.d, $(SRC))
OBJ	= $(patsubst %.cc, $(opath)/%.o, $(SRC))
GDB	= $(patsubst %.cc, $(gpath)/%.o, $(SRC))
PRF	= $(patsubst %.cc, $(ppath)/%.o, $(SRC))

$(TARGET):	$(OBJ)
		$(CXX) -o $@ $(OBJ) $(LIBS)

$(dpath)/%.d:	%.cc %.hh
		@echo making dependencies for $<
		-@if [ ! -d $(dpath) ]; then mkdir $(dpath); fi
		$(SHELL) -ec '$(CXX) $(DEPFLAGS) $(CPPFLAGS) $< \
		| sed "s/$*\\.o[ :]*/$(dpath)\/$*\\.d $(opath)\/$*\\.o $(gpath)\/$*\\.o $(ppath)\/$*\\.o : /g" > $@'
parser.cc:	parser.yy
		$(YACC) parser.yy
scan.cc:	scan.ll
		$(FLEX) scan.ll
$(opath)/%.o:	%.cc
		-@if [ ! -d $(opath) ]; then mkdir $(opath); fi
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOFLAGS) -c $< -o $@
$(gpath)/%.o:	%.cc
		-@if [ ! -d $(gpath) ]; then mkdir $(gpath); fi
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(GDBFLAGS) -c $< -o $@
$(ppath)/%.o:	%.cc
		-@if [ ! -d $(ppath) ]; then mkdir $(ppath); fi
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OPTFLAGS) $(SOFLAGS) $(PRFFLAGS) -c $< -o $@

clean:	
		rm -f $(opath)/*.o $(gpath)/*.o $(ppath)/*.o $(dpath)/*.d
		rm -f *~ $(hpath)/*~

distclean:	clean
		rm -f $(TARGET)
		rm -rf $(opath) $(gpath) $(ppath) $(dpath)

install:
		(if ! test -d $(libdir); \
		  then install -d $(libdir); \
		fi)
		install -m755 $(TARGET) $(libdir)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean) 
-include $(DEP)
endif 
endif

