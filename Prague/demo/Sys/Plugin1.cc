#include <iostream>
#include "Action.hh"

class Greeting1 : public Action
{
public:
  virtual void execute() { std::cout << "Hello World !" << std::endl;}
};

extern "C" Action *load() { return new Greeting1();}
