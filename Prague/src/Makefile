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

top	= ../..
cpath	= $(top)/config

include $(cpath)/local.mk
-include $(cpath)/Prague/prague.mk

TARGET		= $(lpath)/libPrague.so
EXPAT		= $(lpath)/libexpat.so

vpath %.d $(dpath)

world:	$(TARGET)
	cd Unicode/Blocks; $(MAKE) plugins

include Sys/Sys.mk
include IPC/IPC.mk
include Filter/Filter.mk
include Network/Network.mk
include Unicode/Unicode.mk
include SAX/SAX.mk

vpath %.hh  $(ipath)/Prague/Sys $(ipath)/Prague/IPC $(ipath)/Prague/Filter $(ipath)/Prague/Network $(ipath)/Prague/Unicode $(ipath)/Prague/SAX

SRC = $(SYS_SRC) $(IPC_SRC) $(FLT_SRC) $(NTW_SRC) $(UNI_SRC) $(SAX_SRC)
OBJ = $(SYS_OBJ) $(IPC_OBJ) $(FLT_OBJ) $(NTW_OBJ) $(UNI_OBJ) $(SAX_OBJ)
GDB = $(SYS_GDB) $(IPC_GDB) $(FLT_GDB) $(NTW_GDB) $(UNI_GDB) $(SAX_GDB)
DEP = $(SYS_DEP) $(IPC_DEP) $(FLT_DEP) $(NTW_DEP) $(UNI_DEP) $(SAX_DEP)

$(TARGET):	$(EXPAT) $(OBJ)
		$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LIBS) -lexpat

$(EXPAT):
		cd SAX/expat; $(MAKE);

install:
		$(INSTALL) -m755 $(EXPAT) $(libdir)
		$(INSTALL) -m755 $(TARGET) $(libdir)

.PHONY: clean distclean

clean:	
		rm -f $(opath)/*.o $(gpath)/*.o $(ppath)/*.o $(dpath)/*.d
		cd SAX/expat; $(MAKE) clean;
		cd Examples; $(MAKE) clean;
		cd Unicode/Blocks; $(MAKE) clean;

distclean:	clean
		rm -f $(TARGET)
		rm -rf $(opath) $(gpath) $(ppath) $(dpath)
		rm -f config.cache config.log
		cd Examples; $(MAKE) distclean

$(cpath)/Prague/prague.mk: configure $(cpath)/Prague/prague.mk.in
	@echo Running ./configure $$CONFIGURE_OPTS...
	@./configure $$CONFIGURE_OPTS

configure: $(cpath)/Prague/configure.in $(cpath)/Prague/aclocal.m4
	@echo Running autoconf...
	@autoconf -l $(cpath)/Prague $(cpath)/Prague/configure.in > configure
	@chmod a+x configure

$(cpath)/Prague/aclocal.m4: $(cpath)/macros/*.m4
	@echo Running aclocal...
	@(cd $(cpath)/Prague && aclocal -I ../macros)
