#include "Prague/Sys/Plugin.hh"
#include "Action.hh"

class Greeting : public Action
{
  virtual void execute() { std::cout << "Hello World !" << std::endl;}
};

dload(Greeting);
