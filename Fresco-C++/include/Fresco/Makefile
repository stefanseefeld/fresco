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

cpath	= ../../config
ipath	= ../../include
lpath	= ../../lib
dpath	= dep
opath	= obj
rpath	= $(lpath)

include $(cpath)/local.mk

CPPFLAGS= $(SYSCPPFLAGS) $(ORBCPPFLAGS) -I. -I..
CXXFLAGS+= $(SOFLAGS)# $(ORBOPTFLAGS)
LDFLAGS	= -shared -rdynamic
LIBS	+= $(ORBLIBS)

DYNINT	= Types.idl TextBuffer.idl BoundedValue.idl BoundedRange.idl 
STATINT	= ClientContext.idl Server.idl Kit.idl Naming.idl \
	  Transform.idl Region.idl Allocation.idl Traversal.idl PickTraversal.idl DrawTraversal.idl Graphic.idl Screen.idl \
	  Input.idl Focus.idl Subject.idl Controller.idl View.idl \
	  DrawingKit.idl \
	  Grid.idl Viewport.idl Stage.idl LayoutKit.idl \
	  Telltale.idl StreamBuffer.idl Trigger.idl ToolKit.idl WidgetKit.idl \
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

UTIL	= Warsaw.cc Unicode.cc ClientContextImpl.cc

SRC	= $(DYNSRC) $(DYNSTATSRC) $(STATSRC) $(UTIL)

DYNHDR	= $(patsubst %.idl, %.hh, $(DYNINT))
STATHDR	= $(patsubst %.idl, %.hh, $(STATINT))
HDR	= $(DYNHDR) $(STATHDR) $(LCHDR)

OBJ	= $(patsubst %.cc, $(opath)/%.o, $(SRC))
TARGET	= $(lpath)/libWarsaw.so

vpath %.d $(dpath)

world:	$(TARGET)

$(TARGET):	$(OBJ)
		$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)
		strip --strip-unneeded $@

$(dpath)/%.d:	%.idl
		@echo making dependencies for $<
		@if [ ! -d $(dpath) ]; then mkdir $(dpath); fi
# Here there be dragons
#  (can we remove the $(SHELL) part?  it would help cut down the quoting noise)
#  note: this passes through both make and the shell; $$ means $ to make, and the \'s are for the shell
		@$(SHELL) -ec "$(CXX) -x c++ -M $(CPPFLAGS) $(CXXFLAGS) $< \
		| perl -e 'undef \$$/; while(<>)\
		    {\
	    	      (/^(.*)\\.idl\\.o:((.|\\n)*)/);\
		      \$$file = \$$1;\
		      \$$dep = \$$2;\
		      print \"\$$1\", \"SK.cc \", \$$file, \"DynSK.cc \",\
			    \$$file, \".hh $(dpath)\/\", \$$file, \".d:\", \$$dep;\
		      \$$dep =~ s/\\.idl/\\.hh/g;\
		      print \"$(opath)\/\", \$$file, \"SK.o $(opath)\/\", \$$file, \"DynSK.o\", \": \", \$$dep ;\
		    }' > $@"
$(STATHDR): %.hh:		%.idl
		$(IDL) $(IDLFLAGS) $<
$(DYNHDR): %.hh:	%.idl
		$(IDL) $(IDLFLAGS) $(DYNIDLFLAGS) $<
$(STATSRC): %SK.cc:		%.idl
		$(IDL) $(IDLFLAGS) $<
$(DYNSTATSRC): %SK.cc: 	%.idl
		$(IDL) $(IDLFLAGS) $(DYNIDLFLAGS) $<
$(DYNSRC): %DynSK.cc:	%.idl
		$(IDL) $(IDLFLAGS) $(DYNIDLFLAGS) $<
$(opath)/%.o:	%.cc
		@if [ ! -d $(opath) ]; then mkdir $(opath); fi
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:	
		rm -f $(opath)/*.o $(dpath)/*.d
		rm -f $(DYNSRC) $(STATSRC) $(LCSRC) $(DYNHDR) $(STATHDR) *~

distclean:	clean
		rm -f $(TARGET)
		rm -rf $(opath) $(dpath)

install:
		install -m755 $(TARGET) $(libdir)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean) 
-include $(DEP)
endif 
endif 

