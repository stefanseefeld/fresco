TOPDIR=../../..
OS_ARCH='Linux'
DIR_CXXFLAGS = -c -Wall -Wno-unused -fno-rtti
DIR_INCLUDES =  -I../../../include -I../../../include/Warsaw -I/data1/seefelds/omniORB_2.7.0/include
DIR_LDFLAGS  =  -L. -L$(TOPDIR)/lib -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC
CXXSRCS	=	GLDrawable.cc GLPencil.cc GLDrawingKit.cc
SO_TARGET = libDrawing.so
SO_MAJOR_libDrawing.so = 0
SO_MINOR_libDrawing.so = 0
SO_PATCH_libDrawing.so = 1
SO_OBJS_libDrawing.so = $(CXXSRCS:.cc=.o)
include $(TOPDIR)/config/rules.mk
