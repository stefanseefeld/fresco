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

-include $(cpath)/local.mk

subdirs		= $(BASE_SUBDIRS)

.PHONY:	config test depclean clean distclean install debs

world: all

all: $(cpath)/local.mk
	@for dir in ${subdirs}; do \
		(cd $$dir && $(MAKE)) \
		|| case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"; \

depclean:
	find -name '*.d' -exec rm -f \{\} \;

clean:
	/bin/rm -f *~
	@for dir in ${subdirs}; do \
	  (cd $$dir && $(MAKE) clean) \
	  || case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"

distclean:
	/bin/rm -f config.cache config.log config.status
	@for dir in ${subdirs}; do \
	  (cd $$dir && $(MAKE) distclean) \
	  || case "$(MFLAGS)" in *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"
	for dir in modules lib; do \
	  find $$dir -name '*.so' -exec rm -f \{\} \; ; \
	done
	/bin/rm -f $(cpath)/local.mk

install: all
	@for dir in ${subdirs}; do \
	  (cd $$dir && $(MAKE) install); \
	done

# Someone said there was a way to include these rules only if the person
# invokes the export target. I don't know how to do that...
include config/packages.mk

debs:
	dpkg-buildpackage -rfakeroot -uc -us

$(cpath)/local.mk: configure $(cpath)/local.mk.in
	@echo Running ./configure $$CONFIGURE_OPTS...
	@./configure $$CONFIGURE_OPTS

configure: $(cpath)/configure.in $(cpath)/aclocal.m4
	@echo Running autoconf...
	@autoconf -l $(cpath) $(cpath)/configure.in > configure
	@chmod a+x configure

$(cpath)/aclocal.m4: $(cpath)/macros/*.m4
	@echo Running aclocal...
	@(cd $(cpath) && aclocal -I macros)
