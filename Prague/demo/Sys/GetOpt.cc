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
  getopt1.add('h', "help", GetOpt::novalue, "help message");
  getopt1.add('v', "version", GetOpt::novalue, "version number");
  getopt1.add('d', "drawing", GetOpt::mandatory, "the DrawingKit to choose");
  getopt1.add('o', "optional", GetOpt::optional, "some optional argument");
  getopt1.parse(argc - 1, argv + 1);
  /*
   * now test for some options
   */
  if (getopt1.is_set("help"))
    getopt1.usage();
  {
    std::string version;
    if (getopt1.get("version", &version))
      std::cout << "version is " << "..." << std::endl;
  }
  {
    std::string drawing;
    getopt1.get("drawing", &drawing);
    if (!drawing.empty()) std::cout << "drawing: " << drawing << std::endl;
  }
  {
    std::string option;
    if (getopt1.get("optional", &option))
      if (!option.empty()) std::cout << "option: " << option << std::endl;
      else std::cout << "option was set" << std::endl;
  }
}
