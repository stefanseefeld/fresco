TOPDIR=../..
OS_ARCH='Linux'
DIR_CXXFLAGS = -c -O3 -Wall -Wno-unused -fno-rtti 
DIR_INCLUDES =  
DIR_LDFLAGS  =  -L. -L$(TOPDIR)/lib -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC
DIR_CPPFLAGS = 
CXXSRCS = BoundedValueImpl.cc BoundedRangeImpl.cc TelltaleImpl.cc WidgetKitImpl.cc
SO_TARGET = libWidget.so
SO_MAJOR_libWidget.so = 0
SO_MINOR_libWidget.so = 0
SO_PATCH_libWidget.so = 1
SO_OBJS_libWidget.so = $(CXXSRCS:.cc=.o)
include $(TOPDIR)/config/rules.mk
