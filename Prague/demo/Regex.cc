#include <Prague/Sys/regex.hh>
#include <iostream>

using namespace Prague;

main()
{
  regex rxfile("[_a-zA-Z0-9\\-\\.]*\\.cc$|"
	       "[_a-zA-Z0-9\\-\\.]*\\.C$|"
	       "[_a-zA-Z0-9\\-\\.]*\\.cxx$|"
	       "[_a-zA-Z0-9\\-\\.]*\\.c$|"
	       "[_a-zA-Z0-9\\-\\.]*\\.h$");
  string file1 = "a-a.cc";
  string file2 = "a-a.C~";
  cout << rxfile.match(file1) << endl;
  cout << rxfile.search(file1) << ' ' << rxfile.search(file2) << endl;
}
