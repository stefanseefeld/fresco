# $Id$
#
# This source file is a part of the Berlin Project.
# Copyright (C) 1999 Stefan Seefeld <seefelds@magellan.umontreal.ca> 
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

CPPFLAGS= $(SYSCPPFLAGS) $(ORBCPPFLAGS) -I.
CXXFLAGS+= $(SOFLAGS)# $(ORBOPTFLAGS)
LDFLAGS	= -shared -rdynamic
LIBS	+= $(ORBLIBS)

DYNINT	= Message.idl Event.idl Types.idl Style.idl
STATINT	= ClientContext.idl ServerContext.idl LifeCycle.idl Naming.idl Cloneable.idl \
	  Drawable.idl Pencil.idl DrawingKit.idl \
	  Damage.idl Transform.idl Region.idl Traversal.idl Graphic.idl Screen.idl \
	  FigureKit.idl \
	  Grid.idl Viewport.idl Stage.idl LayoutKit.idl \
	  CommandKit.idl \
	  Subject.idl Telltale.idl BoundedValue.idl BoundedRange.idl TextBuffer.idl WidgetKit.idl \
	  Metrics.idl Text.idl TextKit.idl View.idl

INT	= $(DYNINT) $(STATINT)
DEP	= $(patsubst %.idl, $(dpath)/%.d, $(INT))
SRC	= $(patsubst %.idl, %SK.cc, $(INT)) $(patsubst %.idl, %DynSK.cc, $(DYNINT))
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
		@$(SHELL) -ec "$(CXX) -x c++ -M $(CPPFLAGS) $(CXXFLAGS) $< \
		| perl -e 'undef \$$/; while(<>)\
		    {\
	    	      (/^(.*)\\.idl\\.o:((.|\\n)*)/);\
		      \$$file = \$$1;\
		      \$$dep = \$$2;\
		      print \"\$$1\", \"SK.cc \", \$$file, \"DynSK.cc \",\
			    \$$file, \".hh $(dpath)\/\", \$$file, \".d:\", \$$dep;\
		      \$$file .= \"SK\";\
		      \$$dep =~ s/\\.idl/\\.hh/g;\
		      print \"$(opath)\/\", \$$file, \".o\", \": \", \$$file, \".cc\", \$$dep ;\
		    }' > $@"
%.hh:		%.idl
		$(IDL) $(IDLFLAGS) $< 
%SK.cc:		%.idl
		$(IDL) $(IDLFLAGS) $<
%DynSK.cc:	%.idl
		$(IDL) $(DYNIDLFLAGS) $<
$(opath)/%.o:	%.cc
		@if [ ! -d $(opath) ]; then mkdir $(opath); fi
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:	
		rm -f $(opath)/*.o $(dpath)/*.d
		rm -f *.cc *.hh

distclean:	clean
		rm -f $(TARGET)
		rm -rf $(opath) $(dpath)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),distclean) 
-include $(DEP)
endif 
endif 
