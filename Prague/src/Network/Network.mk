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
NET_SRC	= ip.cc ftp.cc smtp.cc #url.cc

NET_OBJ	= $(patsubst %.cc, $(OPATH)/%.o, $(NET_SRC))
NET_PIC	= $(patsubst %.cc, $(SPATH)/%.o, $(NET_SRC))
NET_GDB	= $(patsubst %.cc, $(GPATH)/%.o, $(NET_SRC))
NET_PRF = $(patsubst %.cc, $(PPATH)/%.o, $(NET_SRC))
NET_DEP	= $(patsubst %.cc, $(DPATH)/%.d, $(NET_SRC))

vpath %.h  $(IPATH)/OffiX/Network

$(OPATH)/%.o:	Network/%.cc
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c $< -o $@
$(GPATH)/%.o:	Network/%.cc
		$(CXX) $(CXXFLAGS) $(GDBFLAGS) -c $< -o $@
$(PPATH)/%.o:	Network/%.cc
		$(CXX) $(CXXFLAGS) $(PRFFLAGS) -c $< -o $@
$(SPATH)/%.o:	Network/%.cc
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(SOFLAGS) -c $< -o $@
$(DPATH)/%.d:	Network/%.cc %.h
		@echo making dependencies for $<
		@$(SHELL) -ec '$(CXX) -M $(CXXFLAGS) $< \
		| sed "s/$*\\.o[ :]*/$(OPATH)\/$*\\.o $(GPATH)\/$*\\.o $(PPATH)\/$*\\.o $(SPATH)\/$*\\.o $(DPATH)\/$*\\.d : /g" > $@'

clean::
		$(RM) Network/*~
		$(RM) $(IPATH)/OffiX/Network/*~

ifneq ($(MAKECMDGOALS),clean) 
ifneq ($(MAKECMDGOALS),distclean) 
-include $(NET_DEP)
endif 
endif 
