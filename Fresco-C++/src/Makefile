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
include $(cpath)/Warsaw/local.mk

wpath   = $(top)/idl
rpath	= $(lpath)

IDLFLAGS	+= -nf -bcxx -Wbkeep_inc_path -C../src/Warsaw -I.
DYNIDLFLAGS	+= -Wba
CPPFLAGS	+= $(ORBCPPFLAGS) $(ORBDEFS) -I$(ipath)/Warsaw
CXXFLAGS	+= $(SOFLAGS)
LDFLAGS		+= -shared -rdynamic
LIBS		+= $(ORBLIBS)

DYNINT	= Types.idl TextBuffer.idl BoundedValue.idl BoundedRange.idl Selection.idl
STATINT	= RefCountBase.idl ClientContext.idl Server.idl Kit.idl \
	  Transform.idl Region.idl Allocation.idl Traversal.idl PickTraversal.idl DrawTraversal.idl Graphic.idl Screen.idl \
	  Input.idl Focus.idl Subject.idl Controller.idl View.idl \
	  DrawingKit.idl \
	  Grid.idl Viewport.idl Stage.idl LayoutKit.idl \
	  Telltale.idl StreamBuffer.idl Trigger.idl ToolKit.idl \
	  Choice.idl WidgetKit.idl GadgetKit.idl \
	  Raster.idl ImageKit.idl \
	  Figure.idl Image.idl FigureKit.idl \
	  Command.idl CommandKit.idl \
	  Metrics.idl TextKit.idl \
	  Desktop.idl Window.idl DesktopKit.idl

INT	= $(DYNINT) $(STATINT)

DEP	= $(patsubst %.idl, $(dpath)/%.d, $(INT))

DYNSRC	= $(patsubst %.idl, %DynSK.cc, $(DYNINT))
DYNSTATSRC = $(patsubst %.idl, %SK.cc, $(DYNINT)) 
STATSRC	= $(patsubst %.idl, %SK.cc, $(STATINT))

UTIL	= IO.cc Unicode.cc ClientContextImpl.cc# Warsaw.cc

SRC	= $(DYNSRC) $(DYNSTATSRC) $(STATSRC) $(UTIL)

DYNHDR	= $(patsubst %.idl, $(ipath)/Warsaw/%.hh, $(DYNINT))
STATHDR	= $(patsubst %.idl, $(ipath)/Warsaw/%.hh, $(STATINT))
HDR	= $(DYNHDR) $(STATHDR) $(LCHDR)

OBJ	= $(patsubst %.cc, $(opath)/%.o, $(SRC))
TARGET	= $(lpath)/libWarsaw.so

vpath %.d $(dpath)
vpath %.idl $(wpath)/Warsaw
vpath %.h $(ipath)/Warsaw
vpath %.mk $(cpath)/Warsaw

world:	$(cpath)/Warsaw/local.mk
	$(MAKE) $(TARGET)

$(TARGET):	$(OBJ)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)
		strip --strip-unneeded $@

$(dpath)/%.d:	%.idl
		@echo making dependencies for $<
		-@if [ ! -d $(dpath) ]; then mkdir $(dpath); fi
# Here there be dragons
#  (can we remove the $(SHELL) part?  it would help cut down the quoting noise)
#  note: this passes through both make and the shell; $$ means $ to make, and the \'s are for the shell
		@$(SHELL) -ec "$(CXX) -x c++ $(DEPFLAGS) $(CPPFLAGS) -I$(wpath) $(CXXFLAGS) $< \
		| perl -e 'undef \$$/; while(<>)\
		    {\
	    	      (/^(.*)\\.idl\\.o:((.|\\n)*)/) || next;\
		      \$$file = \$$1;\
		      \$$dep = \$$2;\
		      print \"\$$file\", \"SK.cc \", \$$file, \"DynSK.cc \",\
			    \"$(ipath)\/Warsaw\/\", \$$file, \".hh $(dpath)\/\", \$$file, \".d:\", \$$dep;\
		      \$$dep =~ s#$(wpath)#$(ipath)#g;\
		      \$$dep =~ s/\.idl/\.hh/g;\
		      print \"$(opath)\/\", \$$file, \"SK.o $(opath)\/\", \$$file, \"DynSK.o\", \": \", \$$dep ;\
		    }' > $@"
$(STATHDR): $(ipath)/Warsaw/%.hh:	$(wpath)/Warsaw/%.idl
		(cd $(wpath) && $(IDL) $(IDLFLAGS) Warsaw/$(<F))
		mv $(@F) $(ipath)/Warsaw
$(DYNHDR): $(ipath)/Warsaw/%.hh:	$(wpath)/Warsaw/%.idl
		(cd $(wpath) && $(IDL) $(IDLFLAGS) $(DYNIDLFLAGS) Warsaw/$(<F))
		mv $(@F) $(ipath)/Warsaw
# added dependencies at the end aren't there because of any actual dependency;
# they prevent race conditions during a multithreaded make. Before, make would
# try to build Foo.hh at the same time as FooSK.cc, so it would run omniidl2
# twice, each would create a Foo.hh (overwriting each other), one of them
# would move it to $(ipath)/Warsaw, then the other would try to mv it too but
# would error out because it no longer existed.
# By adding these dependencies we prohibit make building Foo.hh and FooSK.cc
# at the same time.
# An alternate solution would be to put - in front of all the mv invocations,
# so errors would be ignored, but that could conceal true errors.
# This solution, while it could cause make to build a bit more than it
# actually has to, will never be wrong.  Besides, Foo{.hh,SK.cc, DynSK.cc}
# all have the same dependencies anyway, so if one is rebuilt then they're
# all going to be rebuilt anyway.
$(STATSRC): %SK.cc:		$(wpath)/Warsaw/%.idl $(ipath)/Warsaw/%.hh
		(cd $(wpath) && $(IDL) $(IDLFLAGS) Warsaw/$(<F))
		mv $(basename $(<F)).hh $(ipath)/Warsaw
$(DYNSTATSRC): %SK.cc: 	$(wpath)/Warsaw/%.idl $(ipath)/Warsaw/%.hh
		(cd $(wpath) && $(IDL) $(IDLFLAGS) $(DYNIDLFLAGS) Warsaw/$(<F))
		mv $(basename $(<F)).hh $(ipath)/Warsaw
$(DYNSRC): %DynSK.cc:	$(wpath)/Warsaw/%.idl %SK.cc
		(cd $(wpath) && $(IDL) $(IDLFLAGS) $(DYNIDLFLAGS) Warsaw/$(<F))
		mv $(basename $(<F)).hh $(ipath)/Warsaw
$(opath)/%.o:	%.cc
		-@if [ ! -d $(opath) ]; then mkdir $(opath); fi
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:	
		rm -f $(TARGET)
		rm -rf $(opath) $(dpath)
		rm -f $(DYNSRC) $(DYNSTATSRC) $(STATSRC) $(DYNHDR) $(STATHDR) *~

distclean:	clean
		rm -f $(ipath)/Warsaw/config.hh

install:
		install -m755 $(TARGET) $(libdir)

ifeq (,$(findstring $(MAKECMDGOALS), clean distclean))
-include $(DEP)
endif
