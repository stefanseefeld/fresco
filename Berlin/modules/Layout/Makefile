DIR_CPPFLAGS = -D__x86__ -D__linux__ -D__OSVERSION__=2 -D__OMNIORB2__ -D_MIT_POSIX_THREADS -D_REENTRANT
DIR_CXXFLAGS = -c -ggdb -Wall -Wno-unused
DIR_INCLUDES =  -I../../include -I../../include/Warsaw -I/data1/seefelds/omniORB_2.7.0/include
DIR_LDFLAGS  =  -L. -L$(TOPDIR)/lib
LIBS	     =  -lomniORB2 -lomnithread -lpthread -ltcpwrapGK -lomniLC
SRC	=	LayoutManager.cc Placement.cc Box.cc Grid.cc Glue.cc Deck.cc ShapeOf.cc #Backdrop.cc
OBJ	=	$(patsubst %.cc, %.o, $(SRC))

libLayout.so:	$(OBJ)
	$(CXX) -shared $(DIR_LDFLAGS) $(OBJ) -o $@ $(LIBS)
	cp $@ $(LPATH)


%.o:	%.cc
	$(CXX) $(DIR_CPPFLAGS) $(DIR_CXXFLAGS) $(DIR_INCLUDES) -c $? -o $@

clean:	
	rm -f $(OBJ) *~ ../../include/Layout/*~

distclean:	clean
	rm -f libLayout.so
