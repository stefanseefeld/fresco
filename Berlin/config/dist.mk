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

major	= 0
minor	= 2
patch	= 1
kits	= Command Desktop Drawing Figure Gadget Image Layout Text Tool Widget
archive	= LICENSE.Berlin LICENSE.Fresco lib modules etc/PNG etc/glyph.dat \
          config/Server include/Berlin src/Berlin \
	  $(patsubst %, include/%, $(kits)) $(patsubst %, src/%, $(kits)) server
