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

SHELL	:= /bin/sh

top	:= .
cpath	:= ./config

#
# define which package subdirs to traverse
#
subdirs	=
-include $(cpath)/packages.mk

define makeconf
(cd config && $(MAKE) -j1 $(MAKECMDGOALS)) || case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; test -z "$$fail"
endef


.PHONY:	config depclean clean distclean install dist

world: all

all: $(cpath)/packages.mk
	@$(makeconf)
	@for dir in $(subdirs); do \
		(cd $$dir && $(MAKE)) \
		|| case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"; \

$(cpath)/packages.mk:
	@$(makeconf)

depclean:
	find -name '*.d' -exec rm -f \{\} \;

#
# removes everything but config stuff
#
clean:
	@for dir in $(subdirs); do \
	  (cd $$dir && $(MAKE) clean) \
	  || case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"
	for dir in modules lib; do \
	  find $$dir -name '*.so' -exec rm -f \{\} \; ; \
	done

#
# removes config related data
#
distclean:	clean
	@$(makeconf)

dist:	distclean
	@$(makeconf)

#install: all
#	@for dir in ${subdirs}; do \
#	  (cd $$dir && $(MAKE) install); \
#	done

#debs:
#	dpkg-buildpackage -rfakeroot -uc -us

config:
	@$(makeconf)
