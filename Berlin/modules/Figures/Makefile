TOPDIR=../..
OS_ARCH='Linux'
DIR_CPPFLAGS = 
DIR_CXXFLAGS = -c -ggdb -Wall -Wno-unused -fno-rtti
DIR_INCLUDES = 
DIR_LDFLAGS  =  -L. -L$(TOPDIR)/lib -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC
CXXSRCS := Rect.cc FigureKitImpl.cc
SO_TARGET := libFigure.so
SO_MAJOR_libFigure.so := 0
SO_MINOR_libFigure.so := 0
SO_PATCH_libFigure.so := 1
SO_OBJS_libFigure.so := $(CXXSRCS:.cc=.o)

include $(TOPDIR)/config/rules.mk

