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
SYS_SRC	= regex.cc Signal.cc User.cc Stopwatch.cc Time.cc Timer.cc \
	  File.cc Directory.cc Path.cc GetOpt.cc \
	  SHM.cc

ifndef DISABLE_DLL
SYS_SRC+= DLL.cc
endif

ifndef DISABLE_Thread
SYS_SRC+= Thread.cc
endif

SYS_OBJ	= $(patsubst %.cc, $(OPATH)/%.o, $(SYS_SRC))
SYS_PIC	= $(patsubst %.cc, $(SPATH)/%.o, $(SYS_SRC))
SYS_GDB	= $(patsubst %.cc, $(GPATH)/%.o, $(SYS_SRC))
SYS_PRF	= $(patsubst %.cc, $(PPATH)/%.o, $(SYS_SRC))
SYS_DEP	= $(patsubst %.cc, $(DPATH)/%.d, $(SYS_SRC))

vpath %.h  $(IPATH)/OffiX/Sys 

$(OPATH)/%.o:	Sys/%.cc
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c $< -o $@
$(GPATH)/%.o:	Sys/%.cc
		$(CXX) $(CXXFLAGS) $(GDBFLAGS) -c $< -o $@
$(PPATH)/%.o:	Sys/%.cc
		$(CXX) $(CXXFLAGS) $(PRFFLAGS) -c $< -o $@
$(SPATH)/%.o:	Sys/%.cc
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(SOFLAGS) -c $< -o $@
$(DPATH)/%.d:	Sys/%.cc %.h
		@echo making dependencies for $<
		@$(SHELL) -ec '$(CXX) -M $(CXXFLAGS) $< \
		| sed "s/$*\\.o[ :]*/$(OPATH)\/$*\\.o $(GPATH)\/$*\\.o $(PPATH)\/$*\\.o $(SPATH)\/$*\\.o $(DPATH)\/$*\\.d : /g" > $@'

clean::
		$(RM) Sys/*~
		$(RM) $(IPATH)/OffiX/Sys/*~

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean) 
-include $(SYS_DEP)
endif 
endif 
