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
IPC_SRC	= ipcbuf.cc pipebuf.cc socketbuf.cc ptybuf.cc \
	  Agent.cc Coprocess.cc PipeAgent.cc TTYAgent.cc

IPC_DEP	= $(patsubst %.cc, $(DPATH)/%.d, $(IPC_SRC))
IPC_OBJ	= $(patsubst %.cc, $(OPATH)/%.o, $(IPC_SRC))
IPC_PIC	= $(patsubst %.cc, $(SPATH)/%.o, $(IPC_SRC))
IPC_GDB	= $(patsubst %.cc, $(GPATH)/%.o, $(IPC_SRC))

vpath %.h  $(IPATH)/OffiX/IPC

$(DPATH)/%.d:	IPC/%.cc %.h
	@echo making dependencies for $<
	@$(SHELL) -ec '$(CXX) -M $(CXXFLAGS) $< \
	| sed "s/$*\\.o[ :]*/$(OPATH)\/$*\\.o $(GPATH)\/$*\\.o $(PPATH)\/$*\\.o $(SPATH)\/$*\\.o $(DPATH)\/$*\\.d : /g" > $@'
$(SPATH)/%.o:	IPC/%.cc
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(SOFLAGS) -c $< -o $@ 
$(OPATH)/%.o:	IPC/%.cc
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c $< -o $@
$(GPATH)/%.o:	IPC/%.cc
	$(CXX) $(CXXFLAGS) $(GDBFLAGS) -c $< -o $@

clean::
		$(RM) IPC/*~
		$(RM) $(IPATH)/OffiX/IPC/*~

ifneq ($(MAKECMDGOALS),clean) 
ifneq ($(MAKECMDGOALS),distclean) 
-include $(IPC_DEP)
endif 
endif 
