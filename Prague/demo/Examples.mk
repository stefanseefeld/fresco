world:	Timer DataType Unicode

Lock:		Lock.o
		$(CXX) $(LDFLAGS) -o $@ $< $(LIBS)

Timer:		Timer.o
		$(CXX) $(LDFLAGS) -o $@ $< $(LIBS)

DataType:	DataType.o
		$(CXX) $(LDFLAGS) -o $@ $< $(LIBS)

Regex:		Regex.o
		$(CXX) $(LDFLAGS) -o $@ $< $(LIBS)

Logger:		Logger.o
		$(CXX) $(LDFLAGS) -o $@ $< $(LIBS)

Unicode:	Unicode.o
		$(CXX) $(LDFLAGS) -o $@ $< $(LIBS)

Plugin.so:	Plugin.o
		$(CXX) -shared $(LDFLAGS) -o $@ $< $(LIBS)

Loader:		Plugin.so Loader.o
		$(CXX) $(LDFLAGS) -o $@ Loader.o $(LIBS)


DataType.o:	DataType.cc
		$(CXX) $(CXXFLAGS) $(OPTFLAGS) $(SOFLAGS) -ftemplate-depth-23 -c $< -o $@

clean:	
		rm -f *.o *.d *~ core Timer DataType

