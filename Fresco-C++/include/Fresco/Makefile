TOPDIR=../../berlin-tree
OS_ARCH='Linux'

DIR_CPPFLAGS = -D__x86__ -D__linux__ -D__OSVERSION__=2 -D__OMNIORB2__ -D_MIT_POSIX_THREADS -D_REENTRANT
DIR_CXXFLAGS = -fgcse -Os -fomit-frame-pointer -fnonnull-objects -pthread 
DIR_INCLUDES =  -I.  -I/data1/seefelds/omniORB_2.7.0/include
DIR_LDFLAGS  =  -L. -L$(TOPDIR)/lib
LIBS	     =  -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC


ALL_IDL	=	Types.idl Transform.idl Region.idl Damage.idl Graphic.idl Traversal.idl Grid.idl Screen.idl \
		LayoutKit.idl Subject.idl \
		Drawable.idl Pencil.idl DrawingKit.idl DrawTraversal.idl

IDL	=	Types.idl Transform.idl Region.idl Damage.idl GTC.idl \
		Grid.idl Screen.idl LayoutKit.idl Subject.idl

SRC	=	$(patsubst %.idl, %SK.cc, $(IDL))
DSRC	=	$(patsubst %.idl, %DynSK.cc, $(IDL))
SKL	=	$(patsubst %SK.cc, %SK.o, $(SRC))
DSKL	=	$(patsubst %DynSK.cc, %DynSK.o, $(DSRC))

ALL_HDR	=	$(patsubst %.idl, %.hh, $(ALL_IDL))

ALL_SUBTARGETS = $(CORE_IDLS)

%SK.cc:	%.idl
	omniidl2 -l -a $<

%.hh:	%.idl
	omniidl2 -l -a $<

%SK.o:	%SK.cc
	$(CXX) $(DIR_CPPFLAGS) $(DIR_CXXFLAGS) $(DIR_INCLUDES) -c $? -o $@

libWarsaw.so:	headers $(SKL)
	$(CXX) -shared $(DIR_LDFLAGS) $(SKL) -o $@ $(LIBS)
#	cp $@ $(LPATH)

libWarsawDyn.so:	headers $(DSKL)
	$(CXX) -shared $(DIR_LDFLAGS) $(DSKL) -o $@ $(LIBS)
#	cp $@ $(LPATH)

GTC.idl:	Graphic.idl Traversal.idl DrawingKit.idl Drawable.idl Pencil.idl
		cat Graphic.idl > GTC.idl
		cat Traversal.idl >> GTC.idl
		cat DrawingKit.idl >> GTC.idl
		cat Drawable.idl >> GTC.idl
		cat Pencil.idl >> GTC.idl

#DK.idl:		DrawTraversal.idl
#		cat DrawingKit.idl > DK.idl
#		cat Drawable.idl >> DK.idl
#		cat Pencil.idl >> DK.idl
#		cat DrawTraversal.idl >> DK.idl


headers:	$(ALL_HDR)

clean:
	rm -f $(ALL_HDR) $(SKL) $(DSKL) $(SRC) $(DSRC) DK* GTC* *~

distclean:	clean
	rm -f libWarsaw.so