TOPDIR=../..
OS_ARCH='Linux'
DIR_CXXFLAGS = -c -O3 -Wall -Wno-unused -fno-rtti 
DIR_INCLUDES =  
DIR_LDFLAGS  =  -L. -L$(TOPDIR)/lib -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC
DIR_CPPFLAGS = 
CXXSRCS = LayoutManager.cc Placement.cc Box.cc GridImpl.cc Glue.cc Deck.cc ShapeOf.cc LayoutKitImpl.cc #Backdrop.cc
SO_TARGET = libLayout.so
SO_MAJOR_libLayout.so = 0
SO_MINOR_libLayout.so = 0
SO_PATCH_libLayout.so = 1
SO_OBJS_libLayout.so = $(CXXSRCS:.cc=.o)
include $(TOPDIR)/config/rules.mk
