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

top	= .
cpath	= ./config

ifeq (,$(findstring $(MAKECMDGOALS), reconf))
SUBDIRS =
PACKAGES =
-include $(cpath)/packages.mk
endif

# Overridden by the clean-targets, allowing the same subdirs-rule to be used
# for everything.
ACTION	=

.PHONY: world subdirs $(SUBDIRS) config reconf
.PHONY: depclean clean clean-no-prague distclean cvsclean

world:
	$(MAKE) -j1 -C config
	$(MAKE) subdirs

# Neat trick from make's info page -- under "Phony Targets".
subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(ACTION)

#
# Dependencies between subdirs. Might be useful when doing a massive
# parallell-make or when the packages are listed in the wrong order...
#
ifeq (Server, $(findstring Server, $(PACKAGES)))

ifeq (Warsaw, $(findstring Warsaw, $(PACKAGES)))
src/Berlin: src/Warsaw
endif

ifeq (Prague, $(findstring Prague, $(PACKAGES)))
src/Berlin: src/Prague
endif

$(KIT_SUBDIRS): src/Berlin

# Does the server binary actually depend on the kits? If so, add $(KIT_SUBDIRS)
server: src/Berlin

endif

depclean:
	find -name '*.d' -exec rm -f \{\} \;

#
# removes everything
#
clean distclean cvsclean:
	$(MAKE) subdirs ACTION="$@"
	for dir in modules lib; do \
		find $$dir -name '*.so' -exec rm -f \{\} \; ; \
	done
	$(MAKE) -j1 -C config $@
#
# removes everything but config and Prague
#
clean-no-prague:
	$(MAKE) subdirs ACTION="clean" \
		SUBDIRS="$(filter-out src/Prague, $(SUBDIRS))"
	for dir in modules lib ; do \
		find $$dir -name '*.so' -exec rm -f \{\} \; ; \
	done
	$(MAKE) -j1 -C config clean

# 
# Forces a reconfiguration
#
reconf:
	$(MAKE) -j1 -C config reconf
