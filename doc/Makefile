# Generated automatically from Makefile.in by configure.
# $Id$
#
# This source file is a part of the Berlin Project.
# Copyright (C) 1999, 2000 Stefan Seefeld <stefan@berlin-consortium.org> 
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

SHELL		:= /bin/sh

top_srcdir	:= /home/hunger/c/berlin/Berlin
cdir		:= ../config

subdirs		:=  Tutorial

# Overridden by the clean-targets, allowing the same subdirs-rule to be used
# for everything.
action	:= all

.PHONY: all $(subdirs)
.PHONY: depclean clean distclean maintainer-clean dist clean

all:	$(subdirs)

$(subdirs):
	@echo making $(action) in $@
	$(MAKE) -C $@ $(action)

depclean:
	find -name '*.d' -exec rm -f \{\} \;

clean:
	$(MAKE) all action="clean"

distclean:
	@echo 'This command removes Makefiles and auxiliary files;'
	@echo 'run configure to regenerate them.'
	$(MAKE) all action="distclean"
	rm -f Makefile config.cache config.log config.status

maintainer-clean:
	@echo 'This command is intended for maintainers to use;'
	@echo 'it deletes configure and auxiliary files;'
	@echo 'run autogen.sh to regenerated them.'
	$(MAKE) all action="maintainer-clean"
	rm -f Makefile $(cdir)/Docs/local.mk config.cache config.log config.status
