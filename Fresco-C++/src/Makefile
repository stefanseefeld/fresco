# $Id$
#
# This source file is a part of the Berlin Project.
# Copyright (C) 1999 Stefan Seefeld <stefan@berlin-consortium.org> 
# http://www.berlin-consortium.org/
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

top		= ../..
cpath		= $(top)/config
hpath		= $(top)/include/Warsaw
wpath   	= $(top)/idl

include $(cpath)/local.mk
include $(cpath)/Warsaw/local.mk

# Extra compilation and linking flags.
IDLCXXFLAGS	+= -nf -Wbkeep_inc_path -C../src/Warsaw -I.
CPPFLAGS	+= $(ORB_CPPFLAGS) -I$(ipath)/Warsaw -include $(ipath)/Warsaw/config.hh
LIBS		+= $(ORB_LIBS)

CLEAN_EXTRA	= $(DYNSRC) $(DYNSTATSRC) $(STATSRC) $(DYNHDR) $(STATHDR)

DYNINT		= \
	Types.idl TextBuffer.idl BoundedValue.idl BoundedRange.idl \
	Selection.idl
STATINT		= \
	RefCountBase.idl Identifiable.idl ClientContext.idl Server.idl \
	Kit.idl Transform.idl Region.idl Allocation.idl Traversal.idl \
	PickTraversal.idl DrawTraversal.idl Graphic.idl Screen.idl \
	Input.idl Focus.idl Subject.idl Observer.idl Controller.idl View.idl \
	Drawable.idl DrawingKit.idl Grid.idl Viewport.idl Stage.idl LayoutKit.idl \
	Telltale.idl StreamBuffer.idl Trigger.idl Canvas.idl ToolKit.idl Choice.idl \
	WidgetKit.idl GadgetKit.idl Raster.idl ImageKit.idl Figure.idl \
	Image.idl FigureKit.idl Command.idl CommandKit.idl Metrics.idl \
	TextKit.idl Desktop.idl Window.idl DesktopKit.idl Types3D.idl \
	DrawingKit3D.idl Primitive.idl

INT		= $(DYNINT) $(STATINT)

DYNSRC		= $(patsubst %.idl, %DynSK.cc, $(DYNINT))
DYNSTATSRC	= $(patsubst %.idl, %SK.cc, $(DYNINT)) 
STATSRC		= $(patsubst %.idl, %SK.cc, $(STATINT))

UTILSRC		= IO.cc Unicode.cc ClientContextImpl.cc# Warsaw.cc

SRC		= $(DYNSRC) $(DYNSTATSRC) $(STATSRC) $(UTILSRC)

DYNHDR		= $(patsubst %.idl, $(ipath)/Warsaw/%.hh, $(DYNINT))
STATHDR		= $(patsubst %.idl, $(ipath)/Warsaw/%.hh, $(STATINT))
HDR		= $(DYNHDR) $(STATHDR) $(LCHDR)

MODULE		= Warsaw

all: world

vpath %.d $(dpath)
vpath %.idl $(wpath)/Warsaw
vpath %.hh $(ipath)/Warsaw
vpath %.mk $(cpath)/Warsaw

# --------------------------------------------------------------------
# Dependency generation part
# --------------------------------------------------------------------

# We need to generate our own dependencies
# (library.mk usually does this)
NO_DEPS		= 1

DEP		= $(patsubst %.idl, $(dpath)/%.d, $(INT))

$(dpath)/%.d: %.idl $(dpath)/stamp
	@echo making dependencies for $<
	@$(CXX) -x c++ $(DEPFLAGS) $(CPPFLAGS) -I$(wpath) $< \
	| ./idldep.pl $(ipath) $(dpath) $(wpath) $(opath) > $@

$(STATHDR):	$(ipath)/Warsaw/%.hh: %.idl
	(cd $(wpath) && $(IDLCXX) $(IDLCXXFLAGS) Warsaw/$(<F))
	mv $(@F) $(ipath)/Warsaw

$(DYNHDR): 	$(ipath)/Warsaw/%.hh:	$(wpath)/Warsaw/%.idl
	(cd $(wpath) && $(IDLCXX) $(IDLCXXFLAGS) $(IDLDYNFLAGS) Warsaw/$(<F))
	mv $(@F) $(ipath)/Warsaw

# added dependencies at the end aren't there because of any actual
# dependency; they prevent race conditions during a multithreaded
# make. Before, make would try to build Foo.hh at the same time as
# FooSK.cc, so it would run omniidl2 twice, each would create a Foo.hh
# (overwriting each other), one of them would move it to
# $(ipath)/Warsaw, then the other would try to mv it too but would
# error out because it no longer existed. By adding these dependencies
# we prohibit make building Foo.hh and FooSK.cc at the same time.
# An alternate solution would be to put - in front of all the mv
# invocations, so errors would be ignored, but that could conceal true
# errors.
# This solution, while it could cause make to build a bit more than it
# actually has to, will never be wrong.  Besides,
# Foo{.hh,SK.cc, DynSK.cc} all have the same dependencies anyway, so
# if one is rebuilt then they're all going to be rebuilt anyway.
$(STATSRC): %SK.cc:	$(wpath)/Warsaw/%.idl $(ipath)/Warsaw/%.hh
$(DYNSTATSRC): %SK.cc: 	$(wpath)/Warsaw/%.idl $(ipath)/Warsaw/%.hh
$(DYNSRC): %DynSK.cc:	$(wpath)/Warsaw/%.idl %SK.cc


# ------------------------------------------------------------------ #


include $(cpath)/library.mk
