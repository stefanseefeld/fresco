#include <Prague/Sys/GetOpt.hh>
#include <iostream>
#include <string>

using namespace Prague;

int main(int argc, char **argv)
{
  /*
   * initialize some options
   */
  GetOpt getopt1(argv[0], "nothing here");
  GetOpt getopt2(argv[0], "nothing as well");
  getopt1.add('v', "version", GetOpt::novalue, "version number");
  getopt1.add('h', "help", GetOpt::novalue, "help message");
  getopt1.add('d', "drawing", GetOpt::mandatory, "the DrawingKit to choose");
  getopt1.parse(argc - 1, argv + 1);
  /*
   * now test for some options
   */
  {
    string version;
    getopt1.get("version", &version);
    if (version == "true") cout << "version is " << "..." << endl;
  }
  {
    string help;
    getopt1.get("help", &help);
    if (help == "true") getopt1.usage();
  }
  {
    string drawing;
    getopt1.get("drawing", &drawing);
    if (!drawing.empty()) cout << "drawing: " << drawing << endl;
  }
}
