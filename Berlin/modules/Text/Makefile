TOPDIR=../..
OS_ARCH='Linux'
DIR_CPPFLAGS = 
DIR_CXXFLAGS = -c -ggdb -Wall -Wno-unused -fno-rtti
DIR_INCLUDES = 
DIR_LDFLAGS  =  -L. -L$(TOPDIR)/lib -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC
CXXSRCS := TextKitImpl.cc TextChunk.cc FontChange.cc
SO_TARGET := libText.so
SO_MAJOR_libText.so := 0
SO_MINOR_libText.so := 0
SO_PATCH_libText.so := 1
SO_OBJS_libText.so := $(CXXSRCS:.cc=.o)

include $(TOPDIR)/config/rules.mk

