TOPDIR=../..
OS_ARCH='Linux'
DIR_CPPFLAGS = 
DIR_CXXFLAGS = -c -ggdb -Wall -Wno-unused -fno-rtti
DIR_INCLUDES = 
DIR_LDFLAGS  =  -L. -L$(TOPDIR)/lib -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC
CXXSRCS =	Debug.cc GenericFactoryImpl.cc FactoryFinderImpl.cc CloneableImpl.cc \
		RegionImpl.cc TransformImpl.cc TraversalImpl.cc DamageImpl.cc AllocationImpl.cc GraphicImpl.cc \
		ScreenImpl.cc MonoGraphic.cc PolyGraphic.cc Allocator.cc Requestor.cc DebugGraphic.cc \
		DrawTraversalImpl.cc PickTraversalImpl.cc ScreenManager.cc NameUtil.cc \
		SubjectImpl.cc ServerContextImpl.cc ClientContextImpl.cc ServerContextManagerImpl.cc

SO_TARGET := libBerlin.so
SO_MAJOR_libBerlin.so := 0
SO_MINOR_libBerlin.so := 0
SO_PATCH_libBerlin.so := 1
SO_OBJS_libBerlin.so := $(CXXSRCS:.cc=.o)

include $(TOPDIR)/config/rules.mk

