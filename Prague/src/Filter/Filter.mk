#+P
# This file is part of OffiX,
# a C++ API for the X Window System and Unix
# Copyright (C) 1995-98  Stefan Seefeld
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.

# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
# MA 02139, USA.
#-P
# $Id$
#
#
#
#
#
FLT_SRC	= gzbuf.cc xdrbuf.cc #bzbuf.cc 

FLT_OBJ	= $(patsubst %.cc, $(OPATH)/%.o, $(FLT_SRC))
FLT_PIC	= $(patsubst %.cc, $(SPATH)/%.o, $(FLT_SRC))
FLT_GDB	= $(patsubst %.cc, $(GPATH)/%.o, $(FLT_SRC))
FLT_PRF	= $(patsubst %.cc, $(PPATH)/%.o, $(FLT_SRC))
FLT_DEP = $(patsubst %.cc, $(DPATH)/%.d, $(FLT_SRC))

vpath %.h  $(IPATH)/OffiX/Filter

$(OPATH)/%.o:	Filter/%.cc
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c $< -o $@
$(GPATH)/%.o:	Filter/%.cc
		$(CXX) $(CXXFLAGS) $(GDBFLAGS) -c $< -o $@
$(PPATH)/%.o:	Filter/%.cc
		$(CXX) $(CXXFLAGS) $(PRFFLAGS) -c $< -o $@
$(SPATH)/%.o:	Filter/%.cc
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(SOFLAGS) -c $< -o $@
$(DPATH)/%.d:	Filter/%.cc %.h
		@echo making dependencies for $<
		@$(SHELL) -ec '$(CXX) -M $(CXXFLAGS) $< \
		| sed "s/$*\\.o[ :]*/$(OPATH)\/$*\\.o $(GPATH)\/$*\\.o $(PPATH)\/$*\\.o $(SPATH)\/$*\\.o $(DPATH)\/$*\\.d : /g" > $@'

clean::
		$(RM) Filter/*~
		$(RM) $(IPATH)/OffiX/Filter/*~

ifneq ($(MAKECMDGOALS),clean) 
ifneq ($(MAKECMDGOALS),distclean) 
-include $(FLT_DEP)
endif 
endif 
