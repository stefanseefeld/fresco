# $Id$
#
# This source file is a part of the Berlin Project.
# Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
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

top	= ..
cpath	= $(top)/config
ipath	= $(top)/include
lpath	= $(top)/lib
mpath	= $(top)/modules
dpath	= dep
opath	= obj
gpath	= gdb
ppath	= prf
rpath	= $(lpath)

ifeq (,$(findstring $(MAKECMDGOALS), clean distclean))
include $(cpath)/local.mk
include $(cpath)/Server/local.mk
endif

# Compilation and linking flags.
CPPFLAGS= -I$(ipath) -I$(ipath)/Warsaw $(ORBCPPFLAGS)
CXXFLAGS= -pthread -Wall -Dprofile $(OPTFLAGS)
LDFLAGS	= -L$(lpath)
LIBS	= -lWarsaw -lBerlin -lPrague -lpthread
ldlibpath = LD_LIBRARY_PATH=$(lpath)

world:	server kits

server:		server.o
		$(ldlibpath) $(CXX) $(LDFLAGS) -o $@ $? $(LIBS)

kits:		kits.o
		$(ldlibpath) $(CXX) $(LDFLAGS) -o $@ $? $(LIBS)

install:	world
		install -m755 server $(bindir)

clean:	
		rm -f server.o server.d *~ bb.out gmon.out

distclean:	clean
		/bin/rm -f server

server.d:	server.cc
		@echo making dependencies for $<
		@$(SHELL) -ec '$(CXX) $(DEPFLAGS) $(CPPFLAGS) $< \
		| sed '\''s/\($*\)\.o[ :]*/\1.o $@ : /g'\'' > $@'
server.o:	server.cc
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

ifeq (,$(findstring $(MAKECMDGOALS), clean distclean))
-include server.d
endif
