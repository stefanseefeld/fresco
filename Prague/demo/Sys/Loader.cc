#include "Prague/Sys/Plugin.hh"
#include "Action.hh"
#include <string>
#include <iostream>
#include <unistd.h>

using namespace Prague;

int main(int, char **)
{
  char cwd[128];
  getcwd(cwd, 128);
  string plugin1 = string(cwd) + "/Plugin1.so";
  string plugin2 = string(cwd) + "/Plugin2.so";
  for (int i = 0; i != 5; i++)
    {
      Plugin<Action> action1 (plugin1);
      Plugin<Action> action2 (plugin2);
      if (action1) action1->execute();
      else cerr << action1.error() << endl;
      if (action2) action2->execute();
      else cerr << action2.error() << endl;
    }
}
