#include <iostream>
#include "Action.hh"

class Greeting2 : public Action
{
public:
  virtual void execute() { std::cout << "Hi There !" << std::endl;}
};

extern "C" Action *load() { return new Greeting2();}
