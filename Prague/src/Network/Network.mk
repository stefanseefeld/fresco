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

# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 675 Mass Ave, Cambridge,
# MA 02139, USA.

NET_SRC	= ip.cc ftp.cc smtp.cc #url.cc

NET_DEP	= $(patsubst %.cc, $(dpath)/%.d, $(NET_SRC))
NET_OBJ	= $(patsubst %.cc, $(opath)/%.o, $(NET_SRC))
NET_GDB	= $(patsubst %.cc, $(gpath)/%.o, $(NET_SRC))
NET_PRF = $(patsubst %.cc, $(ppath)/%.o, $(NET_SRC))

$(dpath)/%.d:	Network/%.cc $(ipath)/Prague/Network/%.hh
		@echo making dependencies for $<
		@if [ ! -d $(dpath) ]; then mkdir $(dpath); fi
		@$(SHELL) -ec '$(CXX) -MM $(CXXFLAGS) $< \
		| sed "s/$*\\.o[ :]*/$(dpath)\/$*\\.d $(opath)\/$*\\.o $(gpath)\/$*\\.o $(ppath)\/$*\\.o : /g" > $@'
$(opath)/%.o:	Network/%.cc
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(SOFLAGS) -c $< -o $@
$(gpath)/%.o:	Network/%.cc
		$(CXX) $(CXXFLAGS) $(GDBFLAGS) -c $< -o $@
$(ppath)/%.o:	Network/%.cc
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(SOFLAGS) $(PRFFLAGS) -c $< -o $@

clean:		networkclean
networkclean:
		rm -f Network/*~
		rm -f $(ipath)/Prague/Network/*~

ifneq ($(MAKECMDGOALS),clean) 
ifneq ($(MAKECMDGOALS),distclean) 
-include $(NET_DEP)
endif 
endif 
