#include <Prague/Sys/Plugin.hh>
#include <string>
#include <iostream>
#include <unistd.h>
#include "Action.hh"

using namespace Prague;

int main(int, char **)
{
  char cwd[128];
  getcwd(cwd, 128);
  for (int i = 0; i != 5; i++)
    {
      try
        {
          Plugin<Action> action(std::string(cwd) + "/Plugin1.so");
          action->execute();
        }
      catch(const std::runtime_error &e)
        {
          std::cerr << e.what() << std::endl;
        }
      try
        {
          Plugin<Action> action(std::string(cwd) + "/Plugin2.so");
          action->execute();
        }
      catch(const std::runtime_error &e)
        {
          std::cerr << e.what() << std::endl;
        }
    }
}
