TOPDIR=../..
OS_ARCH='Linux'
DIR_INCLUDES = 
DIR_CXXFLAGS = -fno-rtti
DIR_LDFLAGS  = -L$(TOPDIR)/lib  -L. \
		 -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC \
		 -lstdc++ -lggi -ldl -lMesaGL -lMesaGLU -lwarsaw -lgfont \
		 -ldatatype 

CXXSRCS =   CommandKitImpl.cc ReactorImpl.cc
SO_TARGET = CommandKitImpl.so
SO_MAJOR_CommandKitImpl.so = 0
SO_MINOR_CommandKitImpl.so = 0
SO_PATCH_CommandKitImpl.so = 1
SO_OBJS_CommandKitImpl.so = $(CXXSRCS:.cc=.o)

include $(TOPDIR)/config/rules.mk

