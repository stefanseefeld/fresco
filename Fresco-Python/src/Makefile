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

cpath	= ../../../config
ipath	= ../../../include
lpath	= ../../../lib
dpath	= dep
opath	= obj
rpath	= $(lpath)
wpath   = $(ipath)/Warsaw

#include $(cpath)/local.mk
IDL	= omniidl
IDLFLAGS= -I$(wpath) -bpython -Wbglobal=Warsaw

DYNINT	= Types.idl
STATINT	= ClientContext.idl Server.idl Kit.idl Naming.idl \
	  Transform.idl Region.idl Allocation.idl Traversal.idl PickTraversal.idl DrawTraversal.idl Graphic.idl Screen.idl \
	  Input.idl Focus.idl \
	  DrawingKit.idl \
	  Figure.idl Image.idl FigureKit.idl \
	  Grid.idl Viewport.idl Stage.idl LayoutKit.idl \
	  Command.idl CommandKit.idl \
	  Subject.idl Controller.idl View.idl \
	  Telltale.idl BoundedValue.idl BoundedRange.idl TextBuffer.idl StreamBuffer.idl \
	  Trigger.idl ToolKit.idl WidgetKit.idl \
	  Metrics.idl TextKit.idl \
	  Raster.idl ImageKit.idl \
	  Desktop.idl Window.idl DesktopKit.idl

INT	= $(DYNINT) $(STATINT) $(LCINT)

#DYNSRC	= $(patsubst %.idl, %DynSK.py, $(DYNINT))
DYNSTATSRC = $(patsubst %.idl, %_idl.py, $(DYNINT)) 
STATSRC	= $(patsubst %.idl, %_idl.py, $(STATINT))

SRC	= $(DYNSRC) $(DYNSTATSRC) $(STATSRC)
CMP	= $(patsubst %.py, %.pyc, $(SRC))

vpath %.d $(dpath)

world:	$(SRC)

$(STATSRC): %_idl.py:		$(wpath)/%.idl
		$(IDL) $(IDLFLAGS) $<
$(DYNSTATSRC): %_idl.py: 	$(wpath)/%.idl
		$(IDL) $(IDLFLAGS) $(DYNIDLFLAGS) $<
$(DYNSRC): %DynSK.py:	$(wpath)/%.idl
		$(IDL) $(IDLFLAGS) $(DYNIDLFLAGS) $<

clean:	
		rm -rf $(SRC) $(CMP) CosNaming Input Figures POA_* Warsaw *~

distclean:	clean
		rm -f $(TARGET)
		rm -rf $(opath) $(dpath)

install:
		install -m755 $(TARGET) $(libdir)
