TOPDIR=../..
OS_ARCH='Linux'
# despite almost everything working relative to /include, the IDL compiler output still needs
# a little assistance, so we need to include /include/warsaw.. sigh.
DIR_INCLUDES = -I$(TOPDIR)/include -I$(TOPDIR)/include/Warsaw
DIR_CXXFLAGS = -fno-rtti
#DIR_CPPFLAGS = -D__OSVERSION__=2 -D__OMNIORB2__ \
#		-D_MIT_POSIX_THREADS -D_REENTRANT 
DIR_LDFLAGS  = -L$(TOPDIR)/lib  -L. \
		 -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC \
		 -lstdc++ -lggi -ldl -lMesaGL -lMesaGLU -lwarsaw -lgfont \
		 -ldatatype 

CXXSRCS =   CommandKitImpl.cc ReactorImpl.cc
SO_TARGET = CommandKitImpl.so
SO_MAJOR_libberlin.so = 0
SO_MINOR_libberlin.so = 0
SO_PATCH_libberlin.so = 1
SO_OBJS_libberlin.so = $(CXXSRCS:.cc=.o)

include $(TOPDIR)/config/rules.mk

