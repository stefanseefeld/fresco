TOPDIR=../..
OS_ARCH='Linux'
DIR_CPPFLAGS = 
DIR_CXXFLAGS = -c -ggdb -Wall -Wno-unused -fno-rtti
DIR_INCLUDES = 
DIR_LDFLAGS  =  -L. -L$(TOPDIR)/lib -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC
CXXSRCS := ImageKitImpl.cc RasterImpl.cc   
SO_TARGET := libImage.so
SO_MAJOR_libImage.so := 0
SO_MINOR_libImage.so := 0
SO_PATCH_libImage.so := 1
SO_OBJS_libImage.so := $(CXXSRCS:.cc=.o)

include $(TOPDIR)/config/rules.mk

