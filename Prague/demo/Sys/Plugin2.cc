#include "Prague/Sys/Plugin.hh"
#include "Action.hh"

class Greeting2 : public Action
{
  virtual void execute() { cout << "Hi There !" << endl;}
};

dload(Greeting2)
