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

SHELL	= /bin/sh

cpath	= ./config
top	= .


# we treat config specially, forcing it single-threaded
#subdirs	= config
subdirs	=
#
# now add package subdirs
#
-include $(cpath)/packages.mk

.PHONY:	config depclean clean distclean install dist

world: all
	@echo $(subdirs)

all: $(cpath)/packages.mk
	@(cd config && $(MAKE) -j1) \
		|| case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	test -z "$$fail"
	@for dir in $(subdirs); do \
		(cd $$dir && $(MAKE)) \
		|| case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"; \

$(cpath)/packages.mk:
	cd $(cpath) && $(MAKE)

depclean:
	find -name '*.d' -exec rm -f \{\} \;

clean:
	/bin/rm -f *~
	@for dir in $(subdirs); do \
	  (cd $$dir && $(MAKE) clean) \
	  || case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

distclean:
	@for dir in $(subdirs); do \
	  (cd $$dir && $(MAKE) distclean) \
	  || case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"
	for dir in modules lib; do \
	  find $$dir -name '*.so' -exec rm -f \{\} \; ; \
	done

dist:	distclean
	@(cd config && $(MAKE) dist)

#install: all
#	@for dir in ${subdirs}; do \
#	  (cd $$dir && $(MAKE) install); \
#	done

# Someone said there was a way to include these rules only if the person
# invokes the export target. I don't know how to do that...
# include config/packages.mk

#debs:
#	dpkg-buildpackage -rfakeroot -uc -us

config:
	@(cd config && $(MAKE) config)
