#include <Prague/Sys/Plugin.hh>
#include <Prague/Sys/File.hh>
#include <string>
#include <iostream>
#include "Action.hh"

using namespace Prague;

int main(int, char **argv)
{
  try
    {
      Plugin<Action> action(File::directory(argv[0]) + "/Plugin1.so");
      action->execute();
    }
  catch (const std::runtime_error &e) { std::cerr << "Runtime error: " << e.what() << std::endl;}
  try
    {
      Plugin<Action> action(File::directory(argv[0]) + "/Plugin2.so");
      action->execute();
    }
  catch (const std::runtime_error &e) { std::cerr << "Runtime error: " << e.what() << std::endl;}
}
